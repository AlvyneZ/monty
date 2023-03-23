#include "monty.h"

/**
 * free_stack_space - frees a specified amount of memory allocated
 *  for the stack
 * @stack: Top of Stack whose space is to be freed
 * @max: Count of Elements to free
 *
 * Return: Elements freed
 */
size_t free_stack_space(stack_t **stack, size_t max)
{
	stack_t *cur = NULL;
	size_t cnt = 0;

	if (stack != NULL)
	{
		while (((*stack) != NULL) && (cnt < max))
		{
			cur = (*stack);
			(*stack) = (*stack)->prev;
			free(cur);
			cnt++;
		}
	}
	return (cnt);
}

/**
 * delete_stack - frees all the memory allocated
 *  for the stack and deletes the stack
 * @stack: Top of Stack whose space is to be freed
 */
void delete_stack(stack_t **stack)
{
	stack_t *cur = NULL;

	if (stack != NULL)
	{
		while (((*stack) != NULL))
		{
			cur = (*stack);
			(*stack) = (*stack)->prev;
			free(cur);
		}
		free(stack);
	}
}
