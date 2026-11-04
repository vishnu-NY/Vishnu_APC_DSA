#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"header.h"

status validate_arguments(char** argv, input* input)
{
    int i = 0;

    // Default signs: 0 = positive, 1 = negative.
    input->flag1 = 0;
    input->flag2 = 0;
    input->flagres = 0;

    // Validate first char
    if(argv[1][0] == '-')
    {
        input->flag1 = 1;
        i = 1;
    }

    if(argv[1][i] == '\0')
    {
        printf("ERROR : 1st number must contain digits\n");
        return FAILURE;
    }

    while(argv[1][i] != '\0')
    {
        if(!isdigit((unsigned char)argv[1][i]))
        {
            printf("ERROR : Invalid character in 1st number : %c\n", argv[1][i]);
            return FAILURE;
        }
        i++;
    }

    // Validate second number. 
    i = 0;

    if(argv[3][0] == '-')
    {
        input->flag2 = 1;
        i = 1;
    }

    if(argv[3][i] == '\0')
    {
        printf("ERROR : 2nd number must contain digits\n");
        return FAILURE;
    }

    while(argv[3][i] != '\0')
    {
        if(!isdigit(( char)argv[3][i]))
        {
            printf("ERROR : Invalid character in 2nd number : %c\n", argv[3][i]);
            return FAILURE;
        }
        i++;
    }

   // Validate operator.
    if(strlen(argv[2]) != 1 || !(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == 'x' || argv[2][0] == '/'))
    {
        printf("ERROR : Unsupported operator\n");
        return FAILURE;
    }

    printf("INFO : Validation Successful\n");
    return SUCCESS;
}

status load_values_to_DLL(node **head1, node **tail1,node **head2, node **tail2,char *num, char *num2)
{
    int i = 0;

    // Skip the first number's negative sign. 
    if(num[i] == '-')
    {
        i++;
    }

    // Skip leading zeroes. 
    while(num[i] == '0')
    {
        i++;
    }

    // An all-zero number must still have one zero node.
    if(num[i] == '\0')
    {
        if(add_to_last(head1, tail1, 0) != LIST_SUCCESS)
        {
            return FAILURE;
        }
    }
    else
    {
        while(num[i] != '\0')
        {
            if(add_to_last(head1, tail1, num[i] - '0') != LIST_SUCCESS)
            {
                return FAILURE;
            }
            i++;
        }
    }

    // Load the second number. 
    i = 0;

    if(num2[i] == '-')
    {
        i++;
    }

    while(num2[i] == '0')
    {
        i++;
    }

    if(num2[i] == '\0')
    {
        if(add_to_last(head2, tail2, 0) != LIST_SUCCESS)
        {
            return FAILURE;
        }
    }
    else
    {
        while(num2[i] != '\0')
        {
            if(add_to_last(head2, tail2, num2[i] - '0') != LIST_SUCCESS)
            {
                return FAILURE;
            }
            i++;
        }
    }

    return SUCCESS;
}
int check_operation(char *operator)
{
    //Reject empty spaces or strings with more than one character.
    if(operator == NULL ||operator[0] == '\0' || operator[1] != '\0')
    {
        return 0;
    }

    switch(operator[0])
    {
        case '+':
            return 1;

        case '-':
            return 2;

        case 'x':
            return 3;

        case '/':
            return 4;

        default:
            return 0;
    }
}