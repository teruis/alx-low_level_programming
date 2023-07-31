#include "lists.h"

/**
* print_listint - prints a linked lists
* @h: pointer to first node 
*
* return: size of list
*/
size_t listint_len(const listint_t *h)
{
    size_t count = 0;

    while (h)
    {
        count++;
        h = h->next;
    }

    return (count);
}


