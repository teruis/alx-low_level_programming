#include "lists.h"

/**
 * free_listint_safe - checks if a linked list of integers can be freed safely
 * @h: double pointer to the head of the list
 * Return: the number of nodes freed
 */
size_t free_listint_safe(listint_t **h)
{
    size_t len = 0;
    intptr_t diff;
    listint_t *temp;

    if (!h || !*h)
        return (0);

    while (*h)
    {
        diff = (intptr_t)*h - (intptr_t)(*h)->next;
        if (diff > 0)
        {
            temp = (*h)->next;
            free(*h);
            *h = temp;
            len++;
        }
        else
        {
            free(*h);
            *h = NULL;
            len++;
            break;
        }
    }
    *h = NULL;
    return (len);
}

