#include "monty.h"

/**
 * swap_mty - swaps the element at the top of the stack with the
 *  second top element
 * @stack: Top of Stack
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty swap opcode
 */
void swap_mty(stack_t **stack, unsigned int line_number)
{
	stack_t *cur, *prev;

	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't swap, stack too short");
	}
	cur = (*stack);
	prev = (*stack)->prev;
	cur->next = prev;
	cur->prev = prev->prev;
	prev->next = NULL;
	prev->prev = cur;
	(*stack) = prev;
}

/**
 * nop_mty - Does nothing
 * @stack: Top of Stack
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty nop opcode
 */
void nop_mty(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}
