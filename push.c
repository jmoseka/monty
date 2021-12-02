#include "monty.h"
/**
 * push_op - Adds a new element to the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 * @num: Element to add
 */
void push_op(stack_t **stack, unsigned int line_number, char *num)
{
	stack_t *new, *tmp;
	int value;

	value = atoi(num);
	if (value == 0 && *num != '0')
	{
		printf("L%u: usage: push integer\n", line_number);
		exit(EXIT_FAILURE);
	}
	new = malloc(sizeof(stack_t));
	if (new == NULL)
	{
		printf("Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	if (*stack == NULL)
	{
		new->n = value;
		new->prev = (*stack);
		new->next = NULL;
		*stack = new;
		return;
	}
	new->n = value;
	new->next = NULL;
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	new->prev = tmp;
	tmp->next = new;
}
