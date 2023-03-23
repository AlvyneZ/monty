#ifndef MONTY_INTPRTR_HEADER
#define MONTY_INTPRTR_HEADER

#define  _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>

extern FILE *byteCode;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

typedef void (*op_func_t)(stack_t **, unsigned int);

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;


size_t stack_size(const stack_t *top);

void delete_stack(stack_t **stack);
size_t free_stack_space(stack_t **stack, size_t max);

void err_prt(stack_t **stack, char *msg);
void err_ln(stack_t **stack, unsigned int line_number, char *msg);

void print_all(stack_t **stack, unsigned int line_number);
void print_int(stack_t **stack, unsigned int line_number);
void print_char(stack_t **stack, unsigned int line_number);
void print_str(stack_t **stack, unsigned int line_number);

void push_mty(stack_t **stack, void *var, unsigned int line_number);
void pop_mty(stack_t **stack, unsigned int line_number);

void swap_mty(stack_t **stack, unsigned int line_number);
void nop_mty(stack_t **stack, unsigned int line_number);

void add_mty(stack_t **stack, unsigned int line_number);
void sub_mty(stack_t **stack, unsigned int line_number);
void div_mty(stack_t **stack, unsigned int line_number);
void mul_mty(stack_t **stack, unsigned int line_number);
void mod_mty(stack_t **stack, unsigned int line_number);

void rotl_mty(stack_t **stack, unsigned int line_number);
void rotr_mty(stack_t **stack, unsigned int line_number);

#endif /* MONTY_INTPRTR_HEADER */
