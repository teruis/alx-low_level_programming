#include "lists.h"

/**
 * free_listint_safe - frees a linked list
 * @h: pointer to the first node in the linked list
 *
 * Return: number of elements in the freed list
 */
size_t free_listint_safe(listint_t **h)
{
	size_t len = 0;
	listint_t *current_node, *next_node;

	while (*h)
	{
		current_node = *h;
		next_node = (*h)->next;

		free(current_node);
		*h = next_node;
		len++;

		if (next_node >= current_node)
			break;
	}

	*h = NULL;

	return (len);
}
