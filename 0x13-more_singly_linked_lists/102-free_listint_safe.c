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
    listint_t *current, *temp;

    if (h == NULL || *h == NULL)
    {
        return 0;
    }

    while (*h != NULL)
    {
        current = *h;
        temp = current->next;

        if (temp >= current)
        {
            free(current);
            break;
        }

        free(current);
        len++;
        *h = temp;
    }

    *h = NULL;

    return len;
}
