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

// return TRUE if match
bool LinkedList_data_matches(void *data, void *other_data)
{
    return memcmp(data, other_data, sizeof(*data)) == 0;
}
int LinkedList_length(LinkedList_node_t **head)
{
    LinkedList_node_t *tmp = *head;

    int i = 0;
    for (; tmp != NULL; i++)
        tmp = tmp->next;

    return i;
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
        if (LinkedList_data_matches(tmp->data, after_data))
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
    if (*head == NULL)
        return NULL;

    if (LinkedList_data_matches((*head)->data, before_data))
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
    {
        if (LinkedList_data_matches(tmp->next->data, before_data))
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
    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return NULL;

    if (index == 0)
        return LinkedList_prepend(head, data);

    LinkedList_node_t *tmp = *head;
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


LinkedList_node_t *LinkedList_get(LinkedList_node_t **head, int index)
{
    int length = LinkedList_length(head);
    if (index < 0)
        index += length - 1;

    if (index < 0 || index >= length)
        return NULL;

    LinkedList_node_t *tmp = *head;
    for (int i = 0; i < index && tmp != NULL; i++)
        tmp = tmp->next;

    return tmp;
}
// return -1 if not found
int LinkedList_get_index(LinkedList_node_t **head, void *data)
{
    LinkedList_node_t *tmp = *head;
    for (int i = 0; tmp != NULL; i++)
    {
        if (LinkedList_data_matches(tmp->data, data))
            return i;
        tmp = tmp->next;
    }

    return -1;
}

LinkedList_node_t *LinkedList_get_after(LinkedList_node_t **head, void *data)
{
    LinkedList_node_t *tmp = *head;
    while (tmp != NULL)
    {
        if (LinkedList_data_matches(tmp->data, data))
            return tmp->next;
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_get_before(LinkedList_node_t **head, void *data)
{
    if (*head == NULL)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
    {
        if (LinkedList_data_matches(tmp->next->data, data))
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}
LinkedList_node_t *LinkedList_get_tail(LinkedList_node_t **head)
{
    if (*head == NULL)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;

    return tmp;
}

LinkedList_node_t *LinkedList_delete_list(LinkedList_node_t **head)
{
    LinkedList_node_t *tmp = *head;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        free(*head);
        *head = tmp;
    }

    return NULL;
}

void *LinkedList_pop_head(LinkedList_node_t **head)
{
    if (*head == NULL)
        return NULL;

    LinkedList_node_t *tmp = *head;
    *head = (*head)->next;
    void *retrieve = tmp->data;
    free(tmp);
    return retrieve;
}
void *LinkedList_pop_tail(LinkedList_node_t **head)
{
    if (*head == NULL)
        return NULL;

    LinkedList_node_t *tmp = *head;
    while (tmp->next != NULL)
        tmp = tmp->next;
        
    void *retrieve = tmp->data;
    free(tmp);
    return retrieve;
}


int main()
{
}
