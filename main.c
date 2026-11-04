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
        return 1;
    }
    if(load_values_to_DLL(&head1,&tail1,&head2,&tail2,argv[1],argv[3])==FAILURE)
    {
        printf("ERROR : Loading values to Linked lists Failed\n");
        return 1;
    }
    switch(check_operation(argv[2]))
{
    case 1:
        addition(head1, head2, tail1, tail2,&reshead, &restail, &input);
        break;

    case 2:
        subtraction(head1, head2, tail1, tail2,&reshead, &restail, &input);
        break;

    case 3:
    if(multiplication(head1, head2, tail1, tail2,&reshead, &restail, &input) == FAILURE)
    {
        printf("ERROR : Multiplication failed\n");
        return 1;
    }
    break;

    case 4:
        if(division(head1, head2, tail1, tail2, &reshead, &restail, &input) == FAILURE)
        {
            printf("ERROR : Division failed\n");
            return 1;
        }

        break;

    default:
        printf("ERROR : Unsupported operator\n");
        return 1;
}
    
    
    printf("The result is \n");
    if(input.flagres == 1)
    {
        printf("-");
    }


display_list(reshead); 
}