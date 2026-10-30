#ifndef HEADER
#define HEADER

typedef enum {
    SUCCESS,
    FAILURE
}status;

typedef struct node
{
    struct node* prev;
    int data;
    struct node* next;
}node;

typedef struct input
{
    int flag1;
    int flag2;
    int flagres;
    long long int count1;
    long long int count2;

}input;

typedef enum{
    LIST_EMPTY,
    LIST_FAILURE,
    LIST_SUCCESS,

}list_status;

status validate_arguments(char** argv,input* input);
status load_values_to_DLL(node ** head1, node** tail1,node** head2,node** tail2,char* num,char*num2);
int compare_lists(node *head1, node *head2);

status addition(node *head1, node *head2, node* tail1, node* tail2, node** reshead, node** restail);


list_status add_to_last(node ** head, node** tail,int data);
list_status display_list(node* head);
list_status add_to_first(node ** head, node** tail,int data);

#endif
