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
status multiplication(node *head1, node *head2,
                      node *tail1, node *tail2,
                      node **reshead, node **restail,
                      input *info)
{
    /* The caller must provide an empty result list. */
    if(*reshead != NULL || *restail != NULL ||
       head1 == NULL || head2 == NULL ||
       tail1 == NULL || tail2 == NULL)
    {
        return FAILURE;
    }

    node *result1head = NULL;
    node *result1tail = NULL;

    node *result2head = NULL;
    node *result2tail = NULL;

    node *sumhead = NULL;
    node *sumtail = NULL;

    node *temp2 = tail2;

    long long int  count = 0;

    while(temp2 != NULL)
    {
        node *temp1 = tail1;

        int carry = 0;
        int product;

        node **partialhead;
        node **partialtail;

        /* First partial product goes into result1.
           Remaining partial products go into result2. */
        if(count == 0)
        {
            partialhead = &result1head;
            partialtail = &result1tail;
        }
        else
        {
            partialhead = &result2head;
            partialtail = &result2tail;
        }

        /* Shift this partial product according to place value:
           count = 0: no zeroes
           count = 1: one trailing zero
           count = 2: two trailing zeroes */
        for(long long int i = 0; i < count; i++)
        {
            if(add_to_last(partialhead, partialtail, 0)
               != LIST_SUCCESS)
            {
                return FAILURE;
            }
        }

        /* Multiply every digit of the first number
           by the current digit of the second number. */
        while(temp1 != NULL)
        {
            product = temp1->data * temp2->data + carry;

            if(add_to_first(partialhead, partialtail,
                            product % 10) != LIST_SUCCESS)
            {
                return FAILURE;
            }

            carry = product / 10;

            temp1 = temp1->prev;
        }

        if(carry != 0)
        {
            if(add_to_first(partialhead, partialtail, carry) != LIST_SUCCESS)
            {
               return FAILURE;
            }
        }

        /* From the second partial product onward,
           add result1 and result2. */
        if(count != 0)
        {
            input addition_info = {0};

            if(addition(result1head, result2head,result1tail, result2tail,&sumhead, &sumtail,&addition_info) != SUCCESS)
            {
               return FAILURE;
            }

            delete_list(&result1head, &result1tail);
            delete_list(&result2head, &result2tail);

            /* Move the sum into result1 for the next round. */
            copy_list(&result1head, &result1tail,&sumhead, &sumtail);
        }

        count++;
        temp2 = temp2->prev;
    }

    
    while(result1head != NULL &&result1head->data == 0 && result1head->next != NULL)
    {
        node *temp = result1head;

        result1head = result1head->next;
        result1head->prev = NULL;

        free(temp);
    }

    
    info->flagres = (info->flag1 != info->flag2); // == 1 if signs are different, 0 if same

   
    if(result1head != NULL &&result1head->data == 0 &&result1head->next == NULL)
    {
        info->flagres = 0; // If result is Zero, no sign displayed
    }

    /* Transfer the completed answer to the caller. */
    copy_list(reshead, restail,
              &result1head, &result1tail);

    return SUCCESS;

    
}