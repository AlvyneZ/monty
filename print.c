#include "monty.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * print_int - Prints the data (integer form) at the top of the stack
 * @stack: Top of the stack
 * @var: Pointer to arguments of opcode (Unused)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty pint opcode
 */
void print_int(stack_t **stack, void *var, unsigned int line_number)
{
	(void)var;
	if ((stack == NULL) || ((*stack) == NULL))
	{
		err_ln(stack, line_number, "can't pint, stack empty");
	}
	printf("%d\n", (*stack)->n);
}

/**
 * print_all - Prints all the data (integer form) in the stack
 * @stack: Top of the stack
 * @var: Pointer to arguments of opcode (Unused)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty pall opcode
 */
void print_all(stack_t **stack, void *var, unsigned int line_number)
{
	stack_t *h = *stack;

	(void)line_number;
	(void)var;
	for (; h != NULL; h = h->prev)
	{
		printf("%d\n", h->n);
	}
}

/**
 * print_char - Prints the data (ascii character) at the top of the stack
 * @stack: Top of the stack
 * @var: Pointer to arguments of opcode (Unused)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty pchar opcode
 */
void print_char(stack_t **stack, void *var, unsigned int line_number)
{
	(void)var;
	if ((stack == NULL) || ((*stack) == NULL))
	{
		err_ln(stack, line_number, "can't pchar, stack empty");
	}
	printf("%c\n", (*stack)->n);
}

/**
 * print_str - Prints the string stored in the stack
 * @stack: Top of the stack
 * @var: Pointer to arguments of opcode (Unused)
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty pstr opcode
 */
void print_str(stack_t **stack, void *var, unsigned int line_number)
{
	stack_t *h = *stack;

	(void)line_number;
	(void)var;
	for (; ((h != NULL) && (h->n > 0) && (h->n <= 127)); h = h->prev)
	{
		printf("%c", h->n);
	}
	printf("\n");
}
