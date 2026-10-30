#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"header.h"

status addition(node *head1, node *head2, node* tail1, node* tail2, node** reshead, node** restail,input *info)
{

     /* Different signs: subtract the smaller magnitude
       from the larger magnitude. */
    if(info->flag1 != info->flag2)
    {
        int larger = compare_lists(head1, head2);

        if(larger == 0)
        {
            /* Equal magnitudes with opposite signs give zero. */
            info->flagres = 0;

            if(add_to_first(reshead, restail, 0) != LIST_SUCCESS)
            {
                return FAILURE;
            }

            return SUCCESS;
        }
        else if(larger == 1)
        {
            /* First number has the larger magnitude.
               Result takes the first number's sign. */
            info->flagres = info->flag1;

            return subtraction(head1, head2, tail1, tail2,
                               reshead, restail);
        }
        else
        {
            /* Second number has the larger magnitude.
               Result takes the second number's sign. */
            info->flagres = info->flag2;

            return subtraction(head2, head1, tail2, tail1,
                               reshead, restail);
        }
    }

    /* Same signs: add normally and keep their common sign. */
    
    info->flagres = info->flag1;

    node* temp1 = tail1;
    node* temp2 = tail2;
    int d1=temp1->data,d2=temp2->data,res,carry=0;
    while(temp1!=NULL || temp2!=NULL)
    {
        res = carry + d1 + d2;

        add_to_first( reshead,restail,(res%10));

        if(res/10)
        {
            carry = res/10;
        }
        else
        {
            carry=0;
        }

        if(temp1 == NULL)
        {
            d1=0;
            temp2 = temp2->prev;
            if(temp2!=NULL)
            d2=temp2->data; 
        }
        
        else if(temp2 == NULL)
        {
            d2=0;
            
            temp1 = temp1->prev;
            if(temp1!=NULL)
            d1=temp1->data;
            
        }
        else
        {
            temp2 = temp2->prev;
            temp1 = temp1->prev;
            if(temp1!=NULL) d1=temp1->data;
            else d1=0;

            if(temp2!=NULL) d2=temp2->data;
            else d2=0;
           
        }
    }
            if (carry != 0)
        {
            add_to_first(reshead, restail, carry);
        }
}