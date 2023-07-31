#include <stdio.h>
#include <stdlib.h>
#include "lists.h" // Assuming you have a header file with the definition of listint_t

size_t print_listint_safe(const listint_t *head)
{
    size_t count = 0;
    const listint_t *current = head;

    while (current != NULL)
    {
        printf("[%p] %d\n", (void *)current, current->n);
        count++;

        if (current >= current->next)
        {
            printf("-> [%p] %d\n", (void *)current->next, current->next->n);
            printf("Error: linked list is not properly terminated\n");
            exit(98);
        }

        current = current->next;
    }

    return count;
}
