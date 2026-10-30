#include<stdio.h>
#include<string.h>
#include"header.h"


int main (int argc, char* argv[])
{
    struct node* head1=NULL;
    struct node* tail1=NULL;

    struct node* head2=NULL;
    struct node* tail2=NULL;

    struct node* reshead=NULL;
    struct node* restail=NULL;

    input input;

    if(validate_arguments(argv,&input)==FAILURE)
    {
        printf("ERROR : Validate arguments failed\n");
    }
    if(load_values_to_DLL(&head1,&tail1,&head2,&tail2,argv[1],argv[3])==FAILURE)
    {
        printf("ERROR : Loading values to Linked lists Failed\n");
    }
    addition(head1,head2,tail1,tail2,&reshead,&restail);
    
    display_list(head1);//TESTING
    display_list(head2);
    printf("The result is \n");
    display_list(reshead); // TESTING
    
}