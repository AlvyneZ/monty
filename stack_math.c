#include "monty.h"

/**
 * add_mty - Adds the element at the top of the stack to the
 *  second top element
 * @stack: Top of Stack to be operated on
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty add opcode
 */
void add_mty(stack_t **stack, unsigned int line_number)
{
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't add, stack too short");
	}
	(*stack)->prev->n += (*stack)->n;
	free_stack_space(stack, 1);
}

/**
 * sub_mty - subtracts the element at the top of the stack from the
 *  second top element
 * @stack: Top of Stack to be operated on
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty sub opcode
 */
void sub_mty(stack_t **stack, unsigned int line_number)
{
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't sub, stack too short");
	}
	(*stack)->prev->n -= (*stack)->n;
	free_stack_space(stack, 1);
}

/**
 * div_mty - Divides the stack's second top element by the element
 *  at the top of the stack
 * @stack: Top of Stack to be operated on
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty div opcode
 */
void div_mty(stack_t **stack, unsigned int line_number)
{
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't div, stack too short");
	}
	(*stack)->prev->n /= (*stack)->n;
	free_stack_space(stack, 1);
}

/**
 * mul_mty - Multiplies the element at the top of the stack to the
 *  second top element
 * @stack: Top of Stack to be operated on
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty mul opcode
 */
void mul_mty(stack_t **stack, unsigned int line_number)
{
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't mul, stack too short");
	}
	(*stack)->prev->n *= (*stack)->n;
	free_stack_space(stack, 1);
}

/**
 * mod_mty - Computes the remainder of the division of the stack's second
 *  top element by the element at the top of the stack
 * @stack: Top of Stack to be operated on
 * @line_number: Monty bytecode line number being executed
 * Return: None
 *
 * Description: Handles the monty mod opcode
 */
void mod_mty(stack_t **stack, unsigned int line_number)
{
	if ((stack == NULL) || ((*stack) == NULL) || ((*stack)->prev == NULL))
	{
		err_ln(stack, line_number, "can't mod, stack too short");
	}
	(*stack)->prev->n %= (*stack)->n;
	free_stack_space(stack, 1);
}
