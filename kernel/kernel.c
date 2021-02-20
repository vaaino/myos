#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "kernel.h"
#include "../libc/string.h"

void main()
{
	isr_install();
	irq_install();

	clear_screen();

	kprint("Kernel command line utility");
	kreturn(3);

	kprint("Type something, it will go through the kernel\n"
	       "Type END to halt the CPU\n$ ");
}

void user_input(char *input)
{
	if (strcmp(input, "END") == 0) {
		kprint("Stopping the CPU. Bye!\n");
		asm volatile("hlt");
	} else if (strcmp(input, "CLEAR") == 0) {
		clear_screen();
	} else if (strcmp(input, "ECHO") == 0) {
		char test[strlen(input)];
		strsep("qsd qsd qs d", ' ', &test);
		kprint(test);
	} else {
		kprint("Command not found: ");
		kprint(input);
	}
	kprint("\n$ ");
}
