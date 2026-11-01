#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include"header.h"

list_status add_to_last(node ** head, node** tail,int data)
{
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    if(*head == NULL)
    {
        *head = newnode;
        *tail = newnode; 
        return LIST_SUCCESS;  
    }
    (*tail)->next = newnode;
    newnode->prev = *tail;
    *tail = newnode;

    return LIST_SUCCESS;
}

list_status add_to_first(node ** head, node** tail,int data)
{
    node* newnode = malloc(sizeof(node));
    newnode->data = data;
    newnode->prev = NULL;
    newnode->next = NULL;
    if(*head == NULL)
    {
        *head = newnode;
        *tail = newnode;
        return LIST_SUCCESS;      
    }
    (*head)->prev = newnode;
    newnode->next = *head;
    *head = newnode;
    return LIST_SUCCESS;
    
}

list_status display_list(node* head)
{
    if(head == NULL)
    {
        printf("INFO : List is empty\n");
        return LIST_EMPTY;
    }
    node* temp = head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp = temp->next;
    }
    printf("\n");
    return LIST_SUCCESS;
}
int compare_lists(node *head1, node *head2)
{
    node *temp1 = head1;
    node *temp2 = head2;

    long long int count1 = 0;
    long long int count2 = 0;

    /* Skip leading zeroes on both list. */
    while(temp1 != NULL && temp1->data == 0)
    {
        temp1 = temp1->next;
    }

    while(temp2 != NULL && temp2->data == 0)
    {
        temp2 = temp2->next;
    }

    node *start1 = temp1;
    node *start2 = temp2;

    /* Count digits after ignoring leading zeroes. */
    while(temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if(count1 > count2)
    {
        return 1;
    }

    if(count2 > count1)
    {
        return 2;
    }

    //if counts are equal.
    temp1 = start1;
    temp2 = start2;

    while(temp1 != NULL && temp2 != NULL)
    {
        if(temp1->data > temp2->data)
        {
            return 1;
        }

        if(temp2->data > temp1->data)
        {
            return 2;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

void delete_list(node **head, node **tail)
{
    node *temp = *head;

    while(temp != NULL)
    {
        node *next = temp->next;

        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}