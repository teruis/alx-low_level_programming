#include "lists.h"

/**
 * listint_len - prints linked lists
 * @h: pointer to first node
 *
 * Return: number of nodes
 */
size_t listint_len(const listint_t *h)
{
	size_t count = 0;

	while (h)
	{
		h = h->next;
		count++;
	}

	return (count);
}
