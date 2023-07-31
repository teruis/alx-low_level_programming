#include "lists.h"
#include <stdio.h>

size_t looped_listint_len(const listint_t *head);
size_t print_listint_safe(const listint_t *head);
size_t looped_listint_len(const listint_t *head)
{
    const listint_t *tortoise = head;
    const listint_t *hare = head;

    if (head == NULL || head->next == NULL)
        return 0;

    while (hare != NULL && hare->next != NULL)
    {
        tortoise = tortoise->next;
        hare = hare->next->next;

        if (tortoise == hare)
        {
            size_t count = 1;
            tortoise = tortoise->next;

            while (tortoise != hare)
            {
                count++;
                tortoise = tortoise->next;
            }

            return count;
        }
    }

    return 0;
}

size_t print_listint_safe(const listint_t *head)
{
    size_t count = 0;
    size_t loop_length = looped_listint_len(head);

    if (loop_length == 0)
    {
        while (head != NULL)
        {
            printf("[%p] %d\n", (void *)head, head->n);
            head = head->next;
            count++;
        }
    }
    else
    {
        while (count < loop_length)
        {
            printf("[%p] %d\n", (void *)head, head->n);
            head = head->next;
            count++;
        }

        printf("-> [%p] %d\n", (void *)head, head->n);
        count++;
    }

    return count;
}
