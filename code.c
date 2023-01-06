#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev; 
}node;

void push(node **top, int number)
{
    node *new = malloc(sizeof(node));
    new->data = number;
    new->prev = *top;
    *top = new;
}
void print(node *top)
{
     node *temp = top;
        while(temp!=NULL){
        printf("data = %d", temp->data);
        temp = temp->prev;
        }
        printf("\n");
}

int pop(node **top)
{
    int buffer = (*top)->data;
    int *ptr = (*top)->prev;
    free(*top);
    *top = ptr;
    return buffer;

}

int main()
{
    node *list = NULL;
    node *top = NULL;
    push(&top,5);print(top);
    push(&top,3);print(top);
    push(&top,6);print(top);
    pop(&top);
    print(top);

}