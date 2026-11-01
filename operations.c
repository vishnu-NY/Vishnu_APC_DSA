#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"header.h"
#include<stdlib.h>


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

            return subtraction(head1, head2, tail1, tail2,reshead, restail, info);
        }
        else
        {
            /* Second number has the larger magnitude.
               Result takes the second number's sign. */
            info->flagres = info->flag2;

            return subtraction(head2, head1, tail2, tail1,reshead, restail, info);
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

status subtraction(node *head1, node *head2,node *tail1, node *tail2,node **reshead, node **restail,input *info)
{
    /* Different signs mean addition of magnitudes:
       99 - (-100) = 199
       -99 - 100   = -199 */
    if(info->flag1 != info->flag2)
    {
        input magnitude_info = {0};

        status result = addition(head1, head2, tail1, tail2,
                                 reshead, restail,
                                 &magnitude_info);

        info->flagres = info->flag1;

        /* Avoid displaying negative zero. */
        if(result == SUCCESS &&*reshead != NULL &&(*reshead)->data == 0 && (*reshead)->next == NULL)
        {
            info->flagres = 0;
        }

        return result;
    }

    int larger = compare_lists(head1, head2);

    if(larger == 0)
    {
        info->flagres = 0;

        if(add_to_first(reshead, restail, 0) != LIST_SUCCESS)
        {
            return FAILURE;
        }

        return SUCCESS;
    }

    node *temp1;
    node *temp2;

    /* Always subtract smaller magnitude from larger. */
    if(larger == 1)
    {
        temp1 = tail1;
        temp2 = tail2;

        info->flagres = info->flag1;
    }
    else
    {
        temp1 = tail2;
        temp2 = tail1;

        info->flagres = !info->flag1;
    }

    int borrow = 0;
    int d1, d2, res;

    while(temp1 != NULL || temp2 != NULL)
    {
        d1 = (temp1 != NULL) ? temp1->data : 0;
        d2 = (temp2 != NULL) ? temp2->data : 0;

        res = d1 - d2 - borrow;

        if(res < 0)
        {
            res += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        if(add_to_first(reshead, restail, res) != LIST_SUCCESS)
        {
            return FAILURE;
        }

        if(temp1 != NULL)
        {
            temp1 = temp1->prev;
        }

        if(temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    /* Remove leading zeroes, keeping one node for zero. */
    while(*reshead != NULL && (*reshead)->data == 0 && (*reshead)->next != NULL)
    {
        node *temp = *reshead;

        *reshead = temp->next;
        (*reshead)->prev = NULL;

        free(temp);
    }

    return SUCCESS;
}