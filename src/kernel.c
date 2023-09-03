#include "uart.h"
#include "mbox.h"
#include "framebf.h"

void printName() {
	// Background color
	drawRectARGB32(0, 0, 1024, 768, 0x00FF0000, 1);

	//Upper case test
	drawLetter('A', 40, 40, 0x00634B95);
	drawLetter('B', 80, 40, 0x00634B95);
	drawLetter('C', 120, 40, 0x00634B95);
	drawLetter('D', 160, 40, 0x00634B95);
	drawLetter('E', 200, 40, 0x00634B95);
	drawLetter('F', 240, 40, 0x00634B95);
	drawLetter('G', 280, 40, 0x00634B95);
	drawLetter('H', 320, 40, 0x00634B95);
	drawLetter('I', 360, 40, 0x00634B95);

	drawLetter('J', 40, 80, 0x00634B95);
	drawLetter('K', 80, 80, 0x00634B95);
	drawLetter('L', 120, 80, 0x00634B95);
	drawLetter('M', 160, 80, 0x00634B95);
	drawLetter('N', 200, 80, 0x00634B95);
	drawLetter('O', 240, 80, 0x00634B95);
	drawLetter('P', 280, 80, 0x00634B95);
	drawLetter('Q', 320, 80, 0x00634B95);
	drawLetter('R', 360, 80, 0x00634B95);

	drawLetter('S', 40, 120, 0x00634B95);
	drawLetter('T', 80, 120, 0x00634B95);
	drawLetter('U', 120, 120, 0x00634B95);
	drawLetter('V', 160, 120, 0x00634B95);
	drawLetter('W', 200, 120, 0x00634B95);
	drawLetter('X', 240, 120, 0x00634B95);
	drawLetter('Y', 280, 120, 0x00634B95);
	drawLetter('Z', 320, 120, 0x00634B95);

	//Lower case test
	drawLetter('a', 40, 160, 0x00634B95);
	drawLetter('b', 80, 160, 0x00634B95);
	drawLetter('c', 120, 160, 0x00634B95);
	drawLetter('d', 160, 160, 0x00634B95);
	drawLetter('e', 200, 160, 0x00634B95);
	drawLetter('f', 240, 160, 0x00634B95);
	drawLetter('g', 280, 160, 0x00634B95);
	drawLetter('h', 320, 160, 0x00634B95);
	drawLetter('i', 360, 160, 0x00634B95);

	// drawLetter('j', 40, 200, 0x00634B95);
	// drawLetter('k', 80, 200, 0x00634B95);
	// drawLetter('l', 120, 200, 0x00634B95);
	// drawLetter('m', 160, 200, 0x00634B95);
	// drawLetter('n', 200, 200, 0x00634B95);
	// drawLetter('o', 240, 200, 0x00634B95);
	// drawLetter('p', 280, 200, 0x00634B95);
	// drawLetter('q', 320, 200, 0x00634B95);
	// drawLetter('r', 360, 200, 0x00634B95);

	// drawLetter('s', 40, 240, 0x00634B95);
	// drawLetter('t', 80, 240, 0x00634B95);
	// drawLetter('u', 120, 240, 0x00634B95);
	// drawLetter('v', 160, 240, 0x00634B95);
	// drawLetter('w', 200, 240, 0x00634B95);
	// drawLetter('x', 240, 240, 0x00634B95);
	// drawLetter('y', 280, 240, 0x00634B95);
	// drawLetter('z', 320, 240, 0x00634B95);

	// // Number and Special letter
	// drawLetter('0', 40, 280, 0x00634B95);
	// drawLetter('1', 80, 280, 0x00634B95);
	// drawLetter('2', 120, 280, 0x00634B95);
	// drawLetter('3', 160, 280, 0x00634B95);
	// drawLetter('4', 200, 280, 0x00634B95);
	// drawLetter('5', 240, 280, 0x00634B95);
	// drawLetter('6', 280, 280, 0x00634B95);
	// drawLetter('7', 320, 280, 0x00634B95);
	// drawLetter('8', 360, 280, 0x00634B95);

	// drawLetter('9', 40, 320, 0x00634B95);
	// drawLetter('.', 80, 320, 0x00634B95);
	// drawLetter(',', 120, 320, 0x00634B95);
	// drawLetter(';', 160, 320, 0x00634B95);
	// drawLetter(':', 200, 320, 0x00634B95);
	// drawLetter('$', 240, 320, 0x00634B95);
	// drawLetter('#', 280, 320, 0x00634B95);
	// drawLetter('\'', 320, 320, 0x00634B95);
	// drawLetter('!', 360, 320, 0x00634B95);

	// drawLetter('"', 40, 360, 0x00634B95);
	// drawLetter('/', 80, 360, 0x00634B95);
	// drawLetter('?', 120, 360, 0x00634B95);
	// drawLetter('%', 160, 360, 0x00634B95);
	// drawLetter('&', 200, 360, 0x00634B95);
	// drawLetter('(', 240, 360, 0x00634B95);
	// drawLetter(')', 280, 360, 0x00634B95);
	// drawLetter('@', 320, 360, 0x00634B95);

	// //Group name
	// drawLetter('P', 20, 20, 0x00634B95);
	// drawLetter('h', 60, 20, 0x00634B95);
	// drawLetter('a', 100, 20, 0x00634B95);
	// drawLetter('n', 140, 20, 0x00634B95);
	// drawLetter('N', 200, 20, 0x00634B95);
	// drawLetter('h', 240, 20, 0x00634B95);
	// drawLetter('a', 280, 20, 0x00634B95);
	// drawLetter('t', 320, 20, 0x00634B95);
	// drawLetter('M', 380, 20, 0x00634B95);
	// drawLetter('i', 420, 20, 0x00634B95);
	// drawLetter('n', 460, 20, 0x00634B95);
	// drawLetter('h', 500, 20, 0x00634B95);

	// drawLetter('T', 20, 80, 0x00634B95);
	// drawLetter('r', 60, 80, 0x00634B95);
	// drawLetter('a', 100, 80, 0x00634B95);
	// drawLetter('n', 140, 80, 0x00634B95);
	// drawLetter('M', 200, 80, 0x00634B95);
	// drawLetter('a', 240, 80, 0x00634B95);
	// drawLetter('i', 280, 80, 0x00634B95);
	// drawLetter('N', 360, 80, 0x00634B95);
	// drawLetter('h', 400, 80, 0x00634B95);
	// drawLetter('u', 440, 80, 0x00634B95);
	// drawLetter('n', 480, 80, 0x00634B95);
	// drawLetter('g', 520, 80, 0x00634B95);

	// drawLetter('N', 20, 140, 0x00634B95);
	// drawLetter('g', 60, 140, 0x00634B95);
	// drawLetter('u', 100, 140, 0x00634B95);
	// drawLetter('y', 140, 140, 0x00634B95);
	// drawLetter('e', 180, 140, 0x00634B95);
	// drawLetter('n', 220, 140, 0x00634B95);
	// drawLetter('N', 280, 140, 0x00634B95);
	// drawLetter('g', 320, 140, 0x00634B95);
	// drawLetter('o', 360, 140, 0x00634B95);
	// drawLetter('c', 400, 140, 0x00634B95);
	// drawLetter('M', 460, 140, 0x00634B95);
	// drawLetter('i', 500, 140, 0x00634B95);
	// drawLetter('n', 540, 140, 0x00634B95);
	// drawLetter('h', 580, 140, 0x00634B95);

	// drawLetter('T', 20, 200, 0x00634B95);
	// drawLetter('r', 60, 200, 0x00634B95);
	// drawLetter('a', 100, 200, 0x00634B95);
	// drawLetter('n', 140, 200, 0x00634B95);
	// drawLetter('N', 200, 200, 0x00634B95);
	// drawLetter('g', 240, 200, 0x00634B95);
	// drawLetter('u', 280, 200, 0x00634B95);
	// drawLetter('y', 320, 200, 0x00634B95);
	// drawLetter('e', 360, 200, 0x00634B95);
	// drawLetter('n', 400, 200, 0x00634B95);
	// drawLetter('H', 460, 200, 0x00634B95);
	// drawLetter('a', 500, 200, 0x00634B95);
	// drawLetter('K', 560, 200, 0x00634B95);
	// drawLetter('h', 600, 200, 0x00634B95);
	// drawLetter('a', 640, 200, 0x00634B95);
	// drawLetter('n', 680, 200, 0x00634B95);
	// drawLetter('h', 720, 200, 0x00634B95);
}

void main()
{
    // set up serial console
	uart_init();

	// say hello
	uart_puts("\n\nHello World!\n");

	// Initialize frame buffer
	framebf_init();

	// Display group name
	printName();

	// Draw something on the screen
	// drawRectARGB32(50,50,400,400,0x00AA0000,1); //RED
	// // drawRectARGB32(100,100,400,400,0x00f4a896,1); //PINK
	// drawRectARGB32(100,100,400,400,0x00f4a896,0); //No Fill
	// drawRectARGB32(150,150,400,400,0x0000BB00,1); //GREEN
	// drawRectARGB32(200,200,400,400,0x000000CC,1); //BLUE
	// drawRectARGB32(250,250,400,400,0x00FFFF00,1); //YELLOW
	// drawPixelARGB32(300, 300, 0x00FF0000); //RED


	// echo everything back
	while(1) {
		//read each char
		char c = uart_getc();

		//send back twice
		uart_sendc(c);
		uart_sendc(c);
	}
}
