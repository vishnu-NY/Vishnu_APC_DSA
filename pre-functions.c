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
            printf("ERROR : Invalid character in 1st number\n");
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
        if(!isdigit((unsigned char)argv[3][i]))
        {
            printf("ERROR : Invalid character in 2nd number\n");
            return FAILURE;
        }
        i++;
    }

   // Validate operator.
    if(strlen(argv[2]) != 1 || !(argv[2][0] == '+' || argv[2][0] == '-' || argv[2][0] == '*' || argv[2][0] == '/'))
    {
        printf("ERROR : Unsupported operator\n");
        return FAILURE;
    }

    printf("INFO : Validation Successful\n");
    return SUCCESS;
}

status load_values_to_DLL(node ** head1, node** tail1,node** head2,node** tail2, char* num,char* num2)
{
    int i=0;
    while(num[i]!=0)
    {
        add_to_last(head1,tail1,(num[i]-'0'));
        i++;
    }
    if(num[i]=='\0')
    {
        printf("INFO : Loading num1 to List successful\n");
    }
    else
    {
        printf("ERROR : Loading num1 to list failed\n");
    }
    /*-----------------------------N U M -2 ---------------------*/
    i = 0; 
    while(num2[i]!=0)
    {
        add_to_last(head2,tail2,(num2[i]-'0'));
        i++;
    }
    if(num2[i]=='\0')
    {
        printf("INFO : Loading num2 to List successful\n");
    }
    else
    {
        printf("ERROR : Loading num2 to list failed\n");
    }

}
