#include "monty.h"

/**
 * push_mty - Adds an element to the top of the stack
 * @stack: Top of Stack to be pushed to
 * @var: Pointer to arguments of opcode (Integer to be added)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty push opcode
 */
void push_mty(stack_t **stack, void *var, unsigned int line_number)
{
	stack_t *new_node;

	(void)line_number;
	new_node = malloc(sizeof(stack_t));
	if (new_node == NULL)
	{
		err_prt(stack, "Error: malloc failed");
	}
	if ((*stack) != NULL)
		(*stack)->next = new_node;
	new_node->n = *((int *)var);
	new_node->prev = (*stack);
	new_node->next = NULL;
	(*stack) = new_node;
}

/**
 * pop_mty - Removes an element to the top of the stack
 * @stack: Top of Stack to be popped from
 * @var: Pointer to arguments of opcode (Unused)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty pop opcode
 */
void pop_mty(stack_t **stack, void *var, unsigned int line_number)
{
	stack_t *cur = NULL;

	(void)var;
	if ((stack == NULL) || ((*stack) == NULL))
	{
		err_ln(stack, line_number, "can't pop an empty stack");
	}

	cur = (*stack);
	(*stack) = (*stack)->prev;
	free(cur);
}
