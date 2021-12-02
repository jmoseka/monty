#include "monty.h"

void error_usage(void);
void error_open(char *file_name);
void error_unknown(char *opcode, unsigned int line_number);
void free_errors(stack_t *stack, char *buffer, FILE *fd);
void push_op(stack_t **stack, unsigned int line_number, char *num);
void free_stack(stack_t *stack);
int select_op(char *opcode, stack_t **stack, unsigned int line_number);
void pall_op(stack_t **stack, unsigned int line_number);
void pint_op(stack_t **stack, unsigned int line_number);
void pop_op(stack_t **stack, unsigned int line_number);
void swap_op(stack_t **stack, unsigned int line_number);
void add_op(stack_t **stack, unsigned int line_number);
void sub_op(stack_t **stack, unsigned int line_number);
void mul_op(stack_t **stack, unsigned int line_number);
void id_status(stack_t *stack, char *buffer, FILE *fd, unsigned int l_number);
void error_pint(unsigned int line_number);
void error_pop(unsigned int line_number);
void error_swap(unsigned int line_number);
void error_add(unsigned int line_number);
void error_sub(unsigned int line_number);
void error_mul(unsigned int line_number);



/**
 * main - Main functions of Monty's Interpreter
 * @argc: Argument's counter
 * @argv: Arguments to main
 * Return: 0 is success
 */
int err_status = 0;
int main(int argc, char *argv[])
{
	FILE *fd;
	stack_t *stack = NULL;
	char *buffer = NULL, *opcode = NULL, *tokens = NULL;
	size_t len_buff = 0;
	ssize_t bytes_read = 0;
	unsigned int line_number = 0;
	int select = 0;

	if (argc != 2)
		error_usage();
	fd = fopen(argv[1], "r");
	if (fd == NULL)
		error_open(argv[1]);

	while (bytes_read != -1)
	{
		bytes_read = getline(&buffer, &len_buff, fd);
		if (bytes_read == -1)
			break;
		line_number++, opcode = strtok(buffer, DELIM);

		if (opcode != NULL)
		{
			if (strcmp(opcode, "push") == 0)
			{
				tokens = strtok(NULL, DELIM);
				if (tokens == NULL)
					error_unknown(opcode, line_number), free_errors(stack, buffer, fd);
				else
					push_op(&stack, line_number, tokens);
			}
			else
			{
				select = select_op(opcode, &stack, line_number);
				id_status(stack, buffer, fd, line_number);
				if (select == -1)
					error_unknown(opcode, line_number), free_errors(stack, buffer, fd);
			}
		}
	}

	return (0);
}

/**
 * error_usage - Error when user doesn't give any file
 */
void error_usage(void)
{
	fprintf(stderr, "USAGE: monty file\n");
	exit(EXIT_FAILURE);
}

/**
 * error_open - Its not possible to open the file
 * @file_name: Files name
 */
void error_open(char *file_name)
{
	fprintf(stderr, "Error: Can't open file %s\n", file_name);
	exit(EXIT_FAILURE);
}

/**
 * error_unknown - Error for invalid instruction
 * @opcode:String with the operation code
 * @line_number: Line number of the current opcode
 */
void error_unknown(char *opcode, unsigned int line_number)
{
	fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
}

/**
 * free_errors - Frees all errors
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
		free(tmp);
		tmp = aux;
	}
}


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
		{"pall", pall_op},
		{"pint", pint_op},
		{"pop", pop_op},
		{"swap", swap_op},
		{"add", add_op},
		{"sub", sub_op},
		{"mul", mul_op},
		{NULL, NULL}
	};

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

/**
 * pint_op - Print the value at the top of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */

void pint_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp = *stack;

	if (*stack == NULL)
	{

		err_status = 2;
		return;
	}
	while (tmp->next != NULL)
	{
		tmp = tmp->next;

	}
	printf("%d\n", tmp->n);
	(void)line_number;

}

/**
 * pop_op - Remove the top element of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void pop_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;

	if (*stack == NULL)
	{
		err_status = 3;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	if (tmp->prev != NULL)
	{
		tmp->prev->next = NULL;
		free(tmp);
	}
	else
	{
		free(tmp);
		*stack = NULL;
	}
	(void)line_number;
}

/**
 * swap_op - Swaps the top 2 elements of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void swap_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp, *aux;
	int i = 0;

	if (*stack == NULL)
	{
		err_status = 4;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < 2)
	{
		err_status = 4;
		return;
	}
	aux = tmp->prev;
	aux->prev->next = tmp;
	tmp->prev = aux->prev;
	aux->prev = tmp;
	tmp->next = aux;
	aux->next = NULL;
	(void)line_number;
}

/**
 * add_op - Adds the top 2 element of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void add_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	int i = 0;

	if (*stack == NULL)
	{
		err_status = 5;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < 2)
	{
		err_status = 5;
		return;
	}
	tmp = tmp->prev;
	tmp->n = tmp->next->n + tmp->n;
	pop_op(stack, line_number);
}

/**
 * sub_op - Subtracts the top 2 element of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void sub_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	int i = 0;

	if (*stack == NULL)
	{
		err_status = 6;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < 2)
	{
		err_status = 6;
		return;
	}
	tmp = tmp->prev;
	tmp->n = tmp->n - tmp->next->n;
	pop_op(stack, line_number);
}

/**
 * mul_op - Multiplies the top 2 element of the stack
 * @stack: Double linked used to stack the integers
 * @line_number: Line number of the current opcode
 */
void mul_op(stack_t **stack, unsigned int line_number)
{
	stack_t *tmp;
	int i = 0;

	if (*stack == NULL)
	{
		err_status = 6;
		return;
	}
	tmp = *stack;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	if (i < 2)
	{
		err_status = 7;
		return;
	}
	tmp = tmp->prev;
	tmp->n = tmp->n * tmp->next->n;
	pop_op(stack, line_number);
}

/**
 * id_status - Check's for type of error
 * @stack: Double linked used to stack the integers
 * @l_number: Line number of the current opcode
 * @fd: File descriptor of the Monty's file
 * @buffer: Buffer that stores the line for getline
 */
void id_status(stack_t *stack, char *buffer, FILE *fd, unsigned int l_number)
{
	if (err_status == 2)
	{
		error_pint(l_number);
		free_errors(stack, buffer, fd);
	}
	if (err_status == 3)
	{
		error_pop(l_number);
		free_errors(stack, buffer, fd);
	}
	if (err_status == 4)
	{
		error_swap(l_number);
		free_errors(stack, buffer, fd);
	}
	if (err_status == 5)
	{
		error_add(l_number);
		free_errors(stack, buffer, fd);
	}
	if (err_status == 6)
	{
		error_sub(l_number);
		free_errors(stack, buffer, fd);
	}
	if (err_status == 7)
	{
		error_mul(l_number);
		free_errors(stack, buffer, fd);
	}
}


/**
 * error_pint - Error for empty stack
 * @line_number: Line number of the current opcode
 */
void error_pint(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pint, stack empty\n", line_number);
}
/**
 * error_pop - Error for empty stack
 * @line_number: Line number of the current opcode
 */
void error_pop(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't pop an empty stack\n", line_number);
}
/**
 * error_swap - Error for too short stack
 * @line_number: Line number of the current opcode
 */
void error_swap(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't swap, stack too short\n", line_number);
}
/**
 * error_add - Error for too short stack
 * @line_number: Line number of the current opcode
 */
void error_add(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't add, stack too short\n", line_number);
}
/**
 * error_sub - Error for too short stack
 * @line_number: Line number of the current opcode
 */
void error_sub(unsigned int line_number)
{
	fprintf(stderr, "L%u: can't sub, stack too short\n", line_number);
}
/**
 * error_mul - Error for too short stack
 * @line_number: Line number of the current opcode
 */
void error_mul(unsigned int line_number)
{
		fprintf(stderr, "L%u: can't mul, stack too short\n", line_number);
}
