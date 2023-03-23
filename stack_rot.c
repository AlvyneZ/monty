#include "monty.h"

/**
 * rotl_mty - Rotates the stack to the top, moving the top element
 *  to the bottom and making the second top become the new top
 * @stack: Top of Stack to be left rotated
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty rotl opcode
 */
void rotl_mty(stack_t **stack,  unsigned int line_number)
{
	stack_t *cur, *other;

	(void)line_number;
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		return;
	}
	cur = (*stack);
	other = (*stack)->prev;
	cur->prev = NULL;
	other->next = NULL;
	(*stack) = other;
	for (; other->prev != NULL; other = other->prev)
	;
	cur->next = other;
	other->prev = cur;
}

/**
 * rotr_mty - Rotates the stack to the bottom, moving the bottom element
 *  to the top of the stack
 * @stack: Top of Stack to be right rotated
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty rotr opcode
 */
void rotr_mty(stack_t **stack,  unsigned int line_number)
{
	stack_t *cur, *other;

	(void)line_number;
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		return;
	}
	cur = (*stack);
	other = (*stack)->prev;
	for (; other->prev != NULL; other = other->prev)
	;
	other->next->prev = NULL;
	cur->next = other;
	other->next = NULL;
	other->prev = cur;
	(*stack) = other;
}
