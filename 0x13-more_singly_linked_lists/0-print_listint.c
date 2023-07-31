#include "lists.h"

/**
* print_listint - prints a linked lists
* @h: pointer to first node 
*
* return: size of list
*/
size_t print_listint(const listint_t *h)
{
    size_t count = 0;
    const listint_t *current = h;

    while (current != NULL)
    {
        printf("%d\n", current->n);
        current = current->next;
        count++;
    }

    return (count);
}
