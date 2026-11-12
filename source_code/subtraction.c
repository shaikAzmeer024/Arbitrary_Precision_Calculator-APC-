#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR, int *negative)
{
    int digit1, digit2, diff;
    int borrow = 0;
    int len1 = 0, len2 = 0;

    node *t1 = tail1;
    node *t2 = tail2;
    node *temp;

    /* Initialize the result and sign */
    *headR = NULL;
    *tailR = NULL;
    *negative = 0;

    /* Count the digits in the first number */
    while (t1 != NULL)
    {
        len1++;
        t1 = t1->prev;
    }

    /* Count the digits in the second number */
    while (t2 != NULL)
    {
        len2++;
        t2 = t2->prev;
    }

    /* Compare the two numbers */
    if (len1 < len2)
    {
        *negative = 1;
    }
    else if (len1 == len2)
    {
        /* Move to the first digit of both numbers */
        t1 = tail1;
        t2 = tail2;

        while (t1 != NULL && t1->prev != NULL)
            t1 = t1->prev;

        while (t2 != NULL && t2->prev != NULL)
            t2 = t2->prev;

        /* Compare from the most significant digit */
        while (t1 != NULL && t2 != NULL)
        {
            if (t1->data < t2->data)
            {
                *negative = 1;
                break;
            }

            if (t1->data > t2->data)
                break;

            t1 = t1->next;
            t2 = t2->next;
        }
    }

    /* If the first number is smaller, swap the tails */
    if (*negative)
    {
        temp = tail1;
        tail1 = tail2;
        tail2 = temp;
    }

    /* Subtract digits from right to left */
    while (tail1 != NULL || tail2 != NULL)
    {
        digit1 = 0;
        digit2 = 0;

        /* Get a digit from the first number */
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }

        /* Get a digit from the second number */
        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }

        /* Subtract the digits and previous borrow */
        diff = digit1 - digit2 - borrow;

        if (diff < 0)
        {
            diff = diff + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        /* Create a node for the result digit */
        temp = malloc(sizeof(node));

        if (temp == NULL)
        {
            delete_list(headR, tailR);
            *negative = 0;
            return;
        }

        temp->data = diff;
        temp->prev = NULL;
        temp->next = *headR;

        /* Insert the digit at the beginning */
        if (*headR == NULL)
        {
            *headR = temp;
            *tailR = temp;
        }
        else
        {
            (*headR)->prev = temp;
            *headR = temp;
        }
    }

    /* Remove leading zeros */
    remove_pre_zeros(headR);

    /* Update the result tail */
    *tailR = *headR;

    while (*tailR != NULL && (*tailR)->next != NULL)
        *tailR = (*tailR)->next;

    /* Do not display a negative sign for zero */
    if (*headR != NULL &&
        (*headR)->data == 0 &&
        (*headR)->next == NULL)
    {
        *negative = 0;
    }
}