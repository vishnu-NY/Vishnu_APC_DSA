#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"header.h"

status validate_arguments(char **argv, input *info)
{
    info->flag1 = 0;
    info->flag2 = 0;
    info->flagres = 0;

    /* Validate both numbers:
       argv[1] = first number
       argv[3] = second number */
    for(int operand = 1; operand <= 3; operand += 2)
    {
        int i = 0;
        int negative = 0;

        /* Allow one optional sign, only at the beginning. */
        if(argv[operand][i] == '+' || argv[operand][i] == '-')
        {
            negative = (argv[operand][i] == '-');
            i++;
        }

        /* Reject empty numbers and signs without digits. */
        if(argv[operand][i] == '\0')
        {
            printf("ERROR : Number %d must contain digits\n",
                   (operand == 1) ? 1 : 2);
            return FAILURE;
        }

        while(argv[operand][i] != '\0')
        {
            if(!isdigit((unsigned char)argv[operand][i]))
            {
                printf("ERROR : Invalid character in number %d: %c\n",
                       (operand == 1) ? 1 : 2,
                       argv[operand][i]);
                return FAILURE;
            }

            i++;
        }

        if(operand == 1)
        {
            info->flag1 = negative;
        }
        else
        {
            info->flag2 = negative;
        }
    }

    /* Accept exactly one supported operator. */
    if(strlen(argv[2]) != 1 ||
       !(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == 'x' || argv[2][0] == '*' || argv[2][0] == '/'))
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

    // Skip the first number's negative sign or possitive sign. 
    
if(num[i] == '-' || num[i] == '+')
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

    if(num2[i] == '-' || num2[i] == '+')
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