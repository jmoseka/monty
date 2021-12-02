#include "monty.h"

/**
 * free_stack - Function to free a double linked list
 * @stack: Double linked used to stack the integers
 */

void free_stack(stack_t *stack)
{
	stack_t *tmp, *aux;

	if (stack == NULL)
	return;
	tmp = stack;
	while (tmp != NULL)
	{
		aux = tmp->next;
		free(tmp);														tmp = aux;
	}
}


/**
 *free-errors - Frees all errors
 * @stack: Double linked used to stack the integers
 * @buffer: Buffer that stores the line for getline
 * @fd: File descriptor of the Monty's file
 */
void free_errors(stack_t *stack, char *buffer, FILE *fd)
{
	if (stack != NULL)
		free_stack(stack);
	fclose(fd);
	free(buffer);
	exit(EXIT_FAILURE);
}


/**
 * free_everything - Frees every malloc in main
 * @stack: Double linked used to stack the integers
 * @buffer: Buffer that stores the line for getline
 * @fd: File descriptor of the Monty's file
 */
void free_everything(stack_t *stack, char *buffer, FILE *fd)
{
	if (stack != NULL)
		free_stack(stack);
	fclose(fd);
	free(buffer);
}
