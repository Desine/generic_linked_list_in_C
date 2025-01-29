#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedList_node
{
    void *data;
    struct LinkedList_node *next;
} LinkedList_node_t;

void *malloc_int(int value)
{
    int *tmp = malloc(sizeof(int));
    if (!tmp)
        return NULL;
    *tmp = value;
    return tmp;
}

LinkedList_node_t *LinkedList_malloc_node(void *data)
{
    LinkedList_node_t *tmp = malloc(sizeof(LinkedList_node_t));
    if (!tmp)
        return NULL;
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}
LinkedList_node_t *LinkedList_prepend(LinkedList_node_t **head, void *data)
{
    LinkedList_node_t *tmp = LinkedList_malloc_node(data);
    if (!tmp)
        return NULL;
    tmp->next = *head;
    *head = tmp;
    return *head;
}
LinkedList_node_t *LinkedList_append(LinkedList_node_t **head, void *data)
{
    if (*head == NULL)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    LinkedList_node_t *new_node = LinkedList_malloc_node(data);
    tmp->next = new_node;
    return new_node;
}
LinkedList_node_t *LinkedList_insert_after(LinkedList_node_t **head, void *data, void *after_data)
{
    LinkedList_node_t *tmp = *head;
    while (tmp != NULL)
    {
        if (tmp->data == after_data)
        {
            LinkedList_node_t *new_node = LinkedList_malloc_node(data);
            if (!new_node)
                return NULL;
            new_node->next = tmp->next;
            tmp->next = new_node;
            return new_node;
        }
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_insert_before(LinkedList_node_t **head, void *data, void *before_data)
{
    if (*head == NULL || (*head)->data == before_data)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
    {
        if (tmp->next->data == before_data)
        {
            LinkedList_node_t *new_node = LinkedList_malloc_node(data);
            if (!new_node)
                return NULL;
            new_node->next = tmp->next;
            tmp->next = new_node;
            return new_node;
        }
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_insert(LinkedList_node_t **head, void *data, int index)
{
    if (index == 0)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    if (index < 0)
    {
        int length = 0;
        while (tmp != NULL)
        {
            length++;
            tmp = tmp->next;
        }
        index += length;
    }

    tmp = *head;
    for (int i = 0; i < index - 1 && tmp != NULL; i++)
        tmp = tmp->next;

    if (!tmp)
        return NULL;

    LinkedList_node_t *new_node = LinkedList_malloc_node(data);
    if (!new_node)
        return NULL;

    new_node->next = tmp->next;
    tmp->next = new_node;
    return tmp->next;
}

int main()
{
    int *data = malloc(sizeof(int));
    *data = 1;

    LinkedList_node_t *head = NULL;
    LinkedList_node_t *tmp = NULL;

    LinkedList_append(&head, malloc_int(-111));
    LinkedList_append(&head, malloc_int(-222));
    LinkedList_node_t *before = LinkedList_prepend(&head, malloc_int(-12));
    LinkedList_prepend(&head, malloc_int(-36));
    LinkedList_append(&head, malloc_int(-73));

    for (int i = 0; i < 5; i++)
    {
        tmp = LinkedList_insert_before(&head, malloc_int(i + 1), before->data);
        // printf("\ntmp: %d", *(int *)tmp->data);
    }
    LinkedList_insert(&head, malloc_int(-2), -2);
    LinkedList_insert(&head, malloc_int(-3), -3);
    LinkedList_insert(&head, malloc_int(22), 2);
    LinkedList_insert(&head, malloc_int(33), 3);
    tmp = head;
    while (tmp != NULL)
    {
        printf("\ntmp: %d", *(int *)tmp->data);
        tmp = tmp->next;
    }

    printf("\n\n");
}