#include "monty.h"
/**
 * pall_op - Print all the elements of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void pall_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL)
		return;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	while (tmp->prev != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->prev;
	}
	printf("%d\n", tmp->n);
	(void)line_number;
}
