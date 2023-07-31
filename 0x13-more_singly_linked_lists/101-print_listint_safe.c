#include "lists.h"

/**
 * print_listint_safe - function that prints a linked list with a loop safely.
 * @head: pointer to the 1st node of the linked list
 * Return: number of nodes in the list
 */
size_t print_listint_safe(const listint_t *head)
{
	const listint_t *current = NULL;
	const listint_t *loop_node = NULL;
	size_t counter = 0;

	current = head;
	while (current)
	{
		printf("[%p] %d\n", (void *)current, current->n);
		counter++;
		current = current->next;
		loop_node = head;
		size_t loop_counter = 0;
		while (loop_counter < counter)
		{
			if (current == loop_node)
			{
				printf("-> [%p] %d\n", (void *)current, current->n);
				return counter;
			}
			loop_node = loop_node->next;
			loop_counter++;
		}
	}
	return counter;
}

