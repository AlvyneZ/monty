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
		{"pint", 0, print_int},
		{"pall", 0, print_all},
		{"pchar", 0, print_char},
		{"pstr", 0, print_str},
		{"push", 1, push_mty},
		{"pop", 0, pop_mty},
		{"swap", 0, swap_mty},
		{"nop", 0, nop_mty},
		{"add", 0, add_mty},
		{"sub", 0, sub_mty},
		{"div", 0, div_mty},
		{"mul", 0, mul_mty},
		{"mod", 0, mod_mty},
		{"rotl", 0, rotl_mty},
		{"rotr", 0, rotr_mty},
		{NULL, 0, nop_mty}
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
	size_t buf_size = 0, i;
	ssize_t lin_sz = 0;

	lin_sz = getline(&buf, &(buf_size), byteCode);
	(*line_number)++;
	/* End of file */
	if (lin_sz <= 0)
		return (0);
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
		strncpy(temp, cur, 20);
		free(buf);
		fprintf(stderr, "L%u: unknown instruction ", (*line_number));
		err_prt(stack, temp);
	}
	for (i = 0; i < (*opCode)->var_cnt; i++)
	{
		cur = strtok(NULL, " \t\n");
		if ((cur == NULL) || (strspn(cur, "0123456789") != strlen(cur)))
		{
			free(buf);
			err_ln(stack, (*line_number), "usage: push integer");
		}
		var[i] = atoi(cur);
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
		curOpCode->f(stack, var, line_number);
		curOpCode = NULL;
	}

	delete_stack(stack);
	fclose(byteCode);
	return (0);
}