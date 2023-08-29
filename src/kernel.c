#include "uart.h"
#include "mbox.h"
#include "framebf.h"

void main()
{
    // set up serial console
	uart_init();

	// say hello
	uart_puts("\n\nHello World!\n");

	// Initialize frame buffer
	framebf_init();

	// Draw something on the screen
	drawRectARGB32(50,50,400,400,0x00AA0000,1); //RED
	// drawRectARGB32(100,100,400,400,0x00f4a896,1); //PINK
	drawRectARGB32(100,100,400,400,0x00f4a896,0); //No Fill
	drawRectARGB32(150,150,400,400,0x0000BB00,1); //GREEN
	drawRectARGB32(200,200,400,400,0x000000CC,1); //BLUE
	drawRectARGB32(250,250,400,400,0x00FFFF00,1); //YELLOW
	drawPixelARGB32(300, 300, 0x00FF0000); //RED


	// echo everything back
	while(1) {
		//read each char
		char c = uart_getc();

		//send back twice
		uart_sendc(c);
		uart_sendc(c);
	}
}
