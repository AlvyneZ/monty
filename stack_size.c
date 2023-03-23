#include "monty.h"

/**
 * stack_size - Gets the number of elements in the stack
 * @top: Top of the stack
 * Return: Size of the Stack (Element count)
 */
size_t stack_size(const stack_t *top)
{
	size_t cnt;

	for (cnt = 0; top != NULL; top = top->prev, cnt++)
	;
	return (cnt);
}
