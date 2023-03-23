#include "monty.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

FILE *byteCode = NULL;

/**
 * get_opFunc - Looks up op code function for a op code
 * @opCodeStr: String of the op code to look up
 *
 * Return: The instruction structure if the opcode is valid
 */
instruction_t *get_opFunc(char *opCodeStr)
{
	static instruction_t inst_map[] = {
		{"pint", print_int},
		{"pall", print_all},
		{"pchar", print_char},
		{"pstr", print_str},
		{"pop", pop_mty},
		{"swap", swap_mty},
		{"nop", nop_mty},
		{"add", add_mty},
		{"sub", sub_mty},
		{"div", div_mty},
		{"mul", mul_mty},
		{"mod", mod_mty},
		{"rotl", rotl_mty},
		{"rotr", rotr_mty},
		{NULL, nop_mty}
	};
	int idx;

	for (idx = 0; inst_map[idx].opcode != NULL; idx++)
	{
		if (strcmp(opCodeStr, inst_map[idx].opcode) == 0)
			return (&inst_map[idx]);
	}
	return (NULL);
}

/**
 * handle_specOpCode - Handles special opCodes eg that take arguments
 * @buf: Line of byteCode
 * @cur: op Code part of byteCode line
 * @stack: top of the stack
 * @var: pointer to store op code arguments
 * @line_number: Current line being read
 *
 * Return: 1 if opcode instruction executed, 0 otherwise
 */
int handle_specOpCode(char *buf, char *cur,
		stack_t **stack, int *var, unsigned int *line_number)
{
	size_t len;

	if (strcmp(cur, "push") == 0)
	{
		cur = strtok(NULL, " \t\n");
		len = strlen(cur);
		if ((cur == NULL) || (strspn(cur, "+-0123456789") != len) ||
				((strspn(cur, "+-")) && (len == 1)) ||
				((len > 1) && (strpbrk(&cur[1], "-+"))))
		{
			free(buf);
			err_ln(stack, (*line_number), "usage: push integer");
		}
		var[0] = atoi(cur);
		push_mty(stack, var, (*line_number));
		return (1);
	}
	return (0);
}

/**
 * get_opCode - Gets op code instruction from file stream
 * @byteCode: file stream to read from
 * @opCode: pointer to store op code instruction found
 * @stack: top of the stack
 * @var: pointer to store op code arguments
 * @line_number: Current line being read
 *
 * Return: characters read on success, -1 otherwise
 */
ssize_t get_opCode(FILE *byteCode, instruction_t **opCode,
		stack_t **stack, int *var, unsigned int *line_number)
{
	char *buf = NULL, *cur = NULL, temp[20];
	size_t buf_size = 0;
	ssize_t lin_sz = 0;

	lin_sz = getline(&buf, &(buf_size), byteCode);
	(*line_number)++;
	/* End of file */
	if (lin_sz <= 0)
	{
		free(buf);
		return (0);
	}
	cur = strtok(buf, " \t\n");
	/* Empty or Comment line */
	if ((cur == NULL) || (cur[0] == '\n') || (cur[0] == '#'))
	{
		free(buf);
		return (1);
	}
	(*opCode) = get_opFunc(cur);
	if ((*opCode) == NULL)
	{
		if (handle_specOpCode(buf, cur, stack, var, line_number) == 0)
		{
			strncpy(temp, cur, 20);
			free(buf);
			fprintf(stderr, "L%u: unknown instruction ", (*line_number));
			err_prt(stack, temp);
		}
	}

	free(buf);
	return (lin_sz);
}

/**
 * main - simple Monty Scripting language Interpreter
 * @argc: Number of command line arguments
 * @argv: Array of strings of command line arguments
 * Return: 0 on success
*/
int main(int argc, char **argv)
{
	stack_t **stack = NULL;
	instruction_t *curOpCode = NULL;
	int var[1] = {0};
	unsigned int line_number = 0;

	if (argc != 2)
		err_prt(stack, "USAGE: monty file");
	stack = malloc(sizeof(stack_t *));
	if (stack == NULL)
		err_prt(stack, "Error: malloc failed");
	(*stack) = NULL;

	byteCode = fopen(argv[1], "r");
	if (byteCode == NULL)
	{
		fprintf(stderr, "Error: Can't open file ");
		err_prt(stack, argv[1]);
	}

	while (get_opCode(byteCode, &curOpCode, stack, var, &line_number))
	{
		if (curOpCode == NULL)
			continue; /* Empty line */
		curOpCode->f(stack, line_number);
		curOpCode = NULL;
	}

	delete_stack(stack);
	fclose(byteCode);
	return (0);
}
