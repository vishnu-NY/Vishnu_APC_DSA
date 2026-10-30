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