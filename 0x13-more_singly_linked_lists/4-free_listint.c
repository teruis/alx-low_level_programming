#include "lists.h"

/**
 * free_listint - frees a linked list
 * @head: listint_t list to be freed
 */
void free_listint(listint_t *head)
{
	listint_t *current_node;

	if (head == NULL) {
		return;
	}

	current_node = head;
	while (current_node != NULL) {
		listint_t *next_node = current_node->next;
		free(current_node);
		current_node = next_node;
	}
}
