#include "monty.h"
#include <unistd.h>
#include <stdio.h>

/**
 * err_prt - exits the interpreter and deletes the stack
 * @stack: Top of Stack to be deleted
 * @msg: Message to print to stderr upon exit
 */
void err_prt(stack_t **stack, char *msg)
{
	delete_stack(stack);
	if (byteCode != NULL)
		fclose(byteCode);
	fprintf(stderr, "%s\n", msg);
	exit(EXIT_FAILURE);
}

/**
 * err_ln - exits the interpreter and deletes the stack
 * @stack: Top of Stack to be deleted
 * @line_number: Monty bytecode line number that caused error
 * @msg: Message to print to stderr upon exit
 */
void err_ln(stack_t **stack, unsigned int line_number, char *msg)
{
	delete_stack(stack);
	if (byteCode != NULL)
		fclose(byteCode);
	fprintf(stderr, "L%u: %s\n", line_number, msg);
	exit(EXIT_FAILURE);
}
