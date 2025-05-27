#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

void Node_to_End(Node **head, int newdata)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = newdata;
    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *current = *head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = newNode;
}

int main()
{
    Node *head = NULL;
    int n;
    while (1)
    {
        scanf("%d", &n);
        if (n == 0)
        {
            break;
        }
        Node_to_End(&head, n);
    }

    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d->", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
    // Освобождение памяти
    temp = head;
    while (temp != 0)
    {
        Node *nextNode = temp->next;
        free(temp);
        temp = nextNode;
    }
}