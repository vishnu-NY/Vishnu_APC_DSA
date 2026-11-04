#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"header.h"
#include<stdlib.h>


status addition(node *head1, node *head2,node *tail1, node *tail2,node **reshead, node **restail,input *info)
{
    /* Different signs: subtract magnitudes. */
    if(info->flag1 != info->flag2)
    {
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

        /* Make subtraction treat both magnitudes as positive. */
        input subtraction_info = {0};
        status result;

        if(larger == 1)
        {
            result = subtraction(head1, head2, tail1, tail2,
                                 reshead, restail,
                                 &subtraction_info);

            info->flagres = info->flag1;
        }
        else
        {
            result = subtraction(head2, head1, tail2, tail1,
                                 reshead, restail,
                                 &subtraction_info);

            info->flagres = info->flag2;
        }

        return result;
    }

    /* Same signs: add magnitudes from right to left. */
    node *temp1 = tail1;
    node *temp2 = tail2;

    int carry = 0;

    while(temp1 != NULL || temp2 != NULL || carry != 0)
    {
        int d1 = (temp1 != NULL) ? temp1->data : 0;
        int d2 = (temp2 != NULL) ? temp2->data : 0;

        int sum = d1 + d2 + carry;

        if(add_to_first(reshead, restail, sum % 10)
           != LIST_SUCCESS)
        {
            return FAILURE;
        }

        carry = sum / 10;

        if(temp1 != NULL)
        {
            temp1 = temp1->prev;
        }

        if(temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    info->flagres = info->flag1;

    //No signs for 0 outputa.
    if(*reshead != NULL &&
       (*reshead)->data == 0 &&
       (*reshead)->next == NULL)
    {
        info->flagres = 0;
    }

    return SUCCESS;
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
status multiplication(node *head1, node *head2,node *tail1, node *tail2,node **reshead, node **restail,input *info)
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

            if(add_to_first(partialhead, partialtail,product % 10) != LIST_SUCCESS)
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

status division(node *head1, node *head2,node *tail1, node *tail2,node **reshead, node **restail,input *info)
{
    /* Result list must initially be empty. */
    if(head1 == NULL || head2 == NULL ||tail1 == NULL || tail2 == NULL ||*reshead != NULL || *restail != NULL)
    {
        return FAILURE;
    }

    /* Skip any leading zeroes in the divisor. */
    node *divisor = head2;

    while(divisor != NULL && divisor->data == 0)
    {
        divisor = divisor->next;
    }

    if(divisor == NULL)
    {
        printf("ERROR : Division by zero\n");
        return FAILURE;
    }

    node *remainderhead = NULL;
    node *remaindertail = NULL;

    node *temphead = NULL;
    node *temptail = NULL;

    node *quotienthead = NULL;
    node *quotienttail = NULL;

    node *current = head1;

    while(current != NULL)
    {
        /* Bring down the next dividend digit.
           Appending a digit means:
           remainder = remainder * 10 + current digit. */
        if(add_to_last(&remainderhead, &remaindertail,
                       current->data) != LIST_SUCCESS)
        {
            return FAILURE;
        }

        /* Remove leading zeroes from the remainder. */
        while(remainderhead->data == 0 &&
              remainderhead->next != NULL)
        {
            node *temp = remainderhead;

            remainderhead = remainderhead->next;
            remainderhead->prev = NULL;

            free(temp);
        }

        int count = 0;

        /* compare_lists returns:
           0: equal
           1: remainder is larger
           2: divisor is larger

           Keep subtracting while remainder >= divisor. */
       while(compare_lists(remainderhead, divisor) != 2)
{
    /* Both magnitudes are treated as positive.
       Keep the original input signs unchanged. */
    input subtraction_info = {0};

    if(subtraction(remainderhead, divisor,remaindertail, tail2,&temphead, &temptail,&subtraction_info) != SUCCESS)
    {
        return FAILURE;
    }

    /* Replace the old remainder with the subtraction result. */
    delete_list(&remainderhead, &remaindertail);

    copy_list(&remainderhead, &remaindertail,
              &temphead, &temptail);

    count++;
}

        /* Store this round's quotient digit. */
        if(add_to_last(&quotienthead, &quotienttail,
                       count) != LIST_SUCCESS)
        {
            return FAILURE;
        }

        current = current->next;
    }

    /* Remove leading zeroes from the quotient,
       retaining one node when the answer is zero. */
    while(quotienthead->data == 0 && quotienthead->next != NULL)
    {
        node *temp = quotienthead;

        quotienthead = quotienthead->next;
        quotienthead->prev = NULL;

        free(temp);
    }

    /* Different signs give a negative quotient. */
    info->flagres = (info->flag1 != info->flag2);

    /* Avoid negative zero. */
    if(quotienthead->data == 0 &&
       quotienthead->next == NULL)
    {
        info->flagres = 0;
    }

    copy_list(reshead, restail, &quotienthead, &quotienttail);

    delete_list(&remainderhead, &remaindertail);

    return SUCCESS;

}