#ifndef _MONTY_H_
#define _MONTY_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#define DELIM " \n\t\r"

extern int err_status;

/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
		int n;
		struct stack_s *prev;
		struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
		char *opcode;
		void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

void pall_op(stack_t **stack, unsigned int line_number);
void pint_op(stack_t **stack, unsigned int line_number);
void push_op(stack_t **stack, unsigned int line_number, char *num);
void pop_op(stack_t **stack, unsigned int line_number);
void swap_op(stack_t **stack, unsigned int line_number);
void add_op(stack_t **stack, unsigned int line_number);
void sub_op(stack_t **stack, unsigned int line_number);
void mul_op(stack_t **stack, unsigned int line_number);
int select_op(char *opcode, stack_t **stack, unsigned int line_number);
void free_stack(stack_t *stack);
void free_everything(stack_t *stack, char *buffer, FILE *fd);
void free_errors(stack_t *stack, char *buffer, FILE *fd);
void error_usage(void);
void error_open(char *file_name);
void error_unknown(char *opcode, unsigned int line_number);
void error_pint(unsigned int line_number);
void error_pop(unsigned int line_number);
void error_swap(unsigned int line_number);
void error_add(unsigned int line_number);
void error_sub(unsigned int line_number);
void error_mul(unsigned int line_number);
void id_status(stack_t *stack, char *buffer, FILE *fd, unsigned int l_number);

#endif /* _MONTY_H_ */
