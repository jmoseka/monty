#include "monty.h"
/**
 * select_op - Look for a function that match with the opcode
 * @opcode: String with the operation code
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 * Return: o if success, -1 if fails
 */
int select_op(char *opcode, stack_t **stack, unsigned int line_number)
{
	instruction_t funct_op[] = {
		{"pall", pall_op}

	int i = 0;

	if (strcmp(opcode, "nop") == 0)
		return (0);
	while (funct_op[i].opcode != NULL)
	{
		if (strcmp(opcode, funct_op[i].opcode) == 0)
		{
			(funct_op[i].f)(stack, line_number);
			return (0);
		}
	i++;
	}
	return (-1);
}
