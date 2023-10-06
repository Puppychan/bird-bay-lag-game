// -----------------------------------mbox.c -------------------------------------
#include "mbox.h"
#include "uart.h"
#include "../gpio.h"

/* Mailbox Data Buffer (each element is 32-bit)*/
/*
 * The keyword attribute allows you to specify special attributes
 *
 * The aligned(N) attribute aligns the current data item on an address
 * which is a multiple of N, by inserting padding bytes before the data item
 *
 * __attribute__((aligned(16)) : allocate the variable on a 16-byte boundary.
 *
 *
 * We must ensure that our our buffer is located at a 16 byte aligned address,
 * so only the high 28 bits contain the address
 * (last 4 bits is ZERO due to 16 byte alignment)
 *
*/

volatile unsigned int  __attribute__((aligned(16))) mBuf[36];


int max(int x, int y) {
	return (x > y ? x : y);
}

void mbox_buffer_setup(unsigned int buffer_addr, unsigned int tag_identifier, unsigned int **res_data, unsigned int res_length, unsigned int req_length,...) {
	// get optinal argument list
	va_list ap;
	va_start(ap, req_length); 

	// cast the buffer address to a pointer in order to access the value at that address
	unsigned int *mailbox = (unsigned int *) ((unsigned long) buffer_addr);

	switch (tag_identifier) {

		case MBOX_TAG_SETPHYWH: {
			// get  
			int width = va_arg(ap, unsigned int); 
			int height = va_arg(ap, unsigned int);
			mailbox[0] = 8*4; 		 // Length of message in bytes
			mailbox[1] = MBOX_REQUEST;
			mailbox[2] = MBOX_TAG_SETPHYWH; //Set physical width-height
			mailbox[3] = max(res_length, req_length); // Value buffer size in bytes (max of request and response lengths)
    	mailbox[4] = 0;			 // REQUEST CODE = 0
			mailbox[5] = width;   // Value(width)
			mailbox[6] = height;  // Value(height)
    	mailbox[7] = MBOX_TAG_LAST;
			*res_data = (unsigned int *) &mailbox[5];
			break;
		}

		case MBOX_TAG_SETVIRTWH: {
			int width = va_arg(ap, unsigned int);
			int height = va_arg(ap, unsigned int);
			mailbox[0] = 8*4; 		 // Length of message in bytes
			mailbox[1] = MBOX_REQUEST;
			mailbox[2] = MBOX_TAG_SETPHYWH; //Set physical width-height
			mailbox[3] = max(res_length, req_length); // Value buffer size in bytes (max of request and response lengths)
    	mailbox[4] = 0;			 // REQUEST CODE = 0
			mailbox[5] = width;   // Value(width)
			mailbox[6] = height;  // Value(height)
    	mailbox[7] = MBOX_TAG_LAST;
			*res_data = (unsigned int *) &mailbox[5];
			break;
		}

		case MBOX_TAG_SETVIRTOFF: {
			int x = va_arg(ap, int);
			int y = va_arg(ap, int);
			mailbox[0] = 8*4; // Length of message in bytes
			mailbox[1] = MBOX_REQUEST;
			mailbox[2] = MBOX_TAG_SETVIRTOFF; //Set physical width-height
			mailbox[3] = max(res_length, req_length); // Value buffer size in bytes (max of request and response lengths)
    	mailbox[4] = 0;	// REQUEST CODE = 0
			mailbox[5] = x;  // x offset
			mailbox[6] = y;  // y offset
    	mailbox[7] = MBOX_TAG_LAST;
			*res_data = (unsigned int *) &mailbox[5];
			break;
		}

		case MBOX_TAG_SETDEPTH: {
			int dept = va_arg(ap, unsigned int);
			mailbox[0] = 7*4; // Length of message in bytes
			mailbox[1] = MBOX_REQUEST;
			mailbox[2] = MBOX_TAG_SETDEPTH; //Set depth
			mailbox[3] = max(res_length, req_length); // Value buffer size in bytes (max of request and response lengths)
    	mailbox[4] = 0;		// REQUEST CODE = 0
			mailbox[5] = dept; // Value(width)
    	mailbox[6] = MBOX_TAG_LAST;
			*res_data = (unsigned int *) &mailbox[5];
			break;
		}
		
		default:
			break;
	}

	va_end(ap); // end the using the variable argument list
}


/**
 * Read from the mailbox
 */
uint32_t mailbox_read(unsigned char channel)
{
	//Receiving message is buffer_addr & channel number
	uint32_t res;

	// Make sure that the message is from the right channel
	do {
		// Make sure there is mail to receive
		do{
			asm volatile("nop");
		}while(*MBOX0_STATUS & MBOX_EMPTY);

		// Get the message
		res = *MBOX0_READ;
	} while ( (res & 0xF) != channel);

	return res;
}


/**
 * Write to the mailbox
 */
void mailbox_send(uint32_t msg, unsigned char channel)
{
	//Sending message is buffer_addr & channel number

	// Make sure you can send mail
	do{
		asm volatile("nop");
	}while(*MBOX1_STATUS & MBOX_FULL);

	// send the message
	*MBOX1_WRITE = msg;
}



/**
 * Make a mailbox call. Returns 0 on failure, non-zero on success
 */
int mbox_call(unsigned int buffer_addr, unsigned char channel)
{
	//Check Buffer Address
	// uart_puts("Buffer Address: ");
	// uart_hex(buffer_addr);
	// uart_sendc('\n');
	
	//Prepare Data (address of Message Buffer)
	unsigned int msg = (buffer_addr & ~0xF) | (channel & 0xF);
	mailbox_send(msg, channel);

	/* now wait for the response */
	/* is it a response to our message (same address)? */
	if (msg == mailbox_read(channel)) {
		/* is it a valid successful response (Response Code) ? */
		if (mBuf[1] == MBOX_RESPONSE)
			// uart_puts("Got successful response \n");
	
		return (mBuf[1] == MBOX_RESPONSE);
	}

    return 0;
}
