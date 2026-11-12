#include "apc.h"

/* Copy one linked list into another */
static int copy_list(node *head, node **copy, node **tail)
{
    *copy = NULL;
    *tail = NULL;

    /* Copy each node from the original list */
    while (head != NULL)
    {
        /* Insert the current digit into the new list */
        if (insert_last(copy, tail, head->data) == FAILURE)
        {
            /* Delete the copied nodes if insertion fails */
            delete_list(copy, tail);
            return FAILURE;
        }

        head = head->next;
    }

    return SUCCESS;
}

/* Check whether the given number is zero */
static int is_zero(node *head)
{
    /* Check every digit in the list */
    while (head != NULL)
    {
        /* If any digit is non-zero, the number is not zero */
        if (head->data != 0)
            return 0;

        head = head->next;
    }

    /* All digits are zero */
    return 1;
}

/* Subtract the divisor from the remainder.
   This function is called only when remainder >= divisor. */
static int subtract_value(node **head1, node **tail1, node *head2)
{
    /* Start subtraction from the last digit of the remainder */
    node *p = *tail1;
    node *q = head2;

    int digit1, digit2;
    int diff, borrow = 0;

    /* Move the divisor pointer to its last digit */
    while (q != NULL && q->next != NULL)
    {
        q = q->next;
    }

    /* Subtract digits from right to left */
    while (p != NULL)
    {
        /* Get the current digit of the remainder */
        digit1 = p->data;
        digit2 = 0;

        /* Get the corresponding digit of the divisor */
        if (q != NULL)
        {
            digit2 = q->data;
            q = q->prev;
        }

        /* Subtract both digits and any previous borrow */
        diff = digit1 - digit2 - borrow;

        /* Borrow from the next digit if the result is negative */
        if (diff < 0)
        {
            diff += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        /* Store the subtraction result in the current node */
        p->data = diff;

        /* Move to the previous digit */
        p = p->prev;
    }

    /* Remove unnecessary zeros from the beginning */
    remove_pre_zeros(head1);

    /* Update the tail pointer after removing leading zeros */
    *tail1 = *head1;

    /* Move to the last node to get the correct tail */
    while (*tail1 != NULL && (*tail1)->next != NULL)
    {
        *tail1 = (*tail1)->next;
    }

    return SUCCESS;
}

/* Divide the first number by the second number */
void division(node *head1, node *head2, node **headR, node **tailR)
{
    /* Temporary list to store the remainder */
    node *remHead = NULL;
    node *remTail = NULL;

    /* Stores the current quotient digit */
    node *temp;

    int quotient_digit;

    /* Initialize the quotient result list */
    *headR = NULL;
    *tailR = NULL;

    /* Check whether either input list is empty */
    if (head1 == NULL || head2 == NULL)
    {
        printf("Invalid input\n");
        return;
    }

    /* Division by zero is not allowed */
    if (is_zero(head2))
    {
        printf("Error: Division by zero\n");
        return;
    }

    /* Initialize the remainder with zero */
    if (insert_last(&remHead, &remTail, 0) == FAILURE)
        return;

    /* Process each digit of the dividend */
    while (head1 != NULL)
    {
        /* Bring down the next digit into the remainder */
        if (remHead->data == 0 && remHead->next == NULL)
        {
            /* Reuse the zero node for the first digit */
            remHead->data = head1->data;
        }
        else
        {
            /* Append the next dividend digit to the remainder */
            if (insert_last(&remHead, &remTail, head1->data) == FAILURE)
            {
                /* Free allocated nodes if insertion fails */
                delete_list(&remHead, &remTail);
                delete_list(headR, tailR);
                return;
            }
        }

        /* Remove unnecessary leading zeros from the remainder */
        remove_pre_zeros(&remHead);

        /* Update the remainder tail pointer */
        remTail = remHead;

        while (remTail->next != NULL)
            remTail = remTail->next;

        /* Count how many times the divisor fits into the remainder */
        quotient_digit = 0;

        while (compare_list(remHead, head2) >= 0)
        {
            /* Subtract the divisor from the remainder */
            subtract_value(&remHead, &remTail, head2);

            /* Each subtraction increases the quotient digit */
            quotient_digit++;
        }

        /* Append the calculated quotient digit to the result */
        if (insert_last(headR, tailR, quotient_digit) == FAILURE)
        {
            /* Free both lists if result insertion fails */
            delete_list(&remHead, &remTail);
            delete_list(headR, tailR);
            return;
        }

        /* Move to the next digit of the dividend */
        head1 = head1->next;
    }

    /* Remove unnecessary leading zeros from the quotient */
    remove_pre_zeros(headR);

    /* Update the tail pointer of the quotient list */
    *tailR = *headR;

    while (*tailR != NULL && (*tailR)->next != NULL)
        *tailR = (*tailR)->next;

    /* Free the temporary remainder list */
    delete_list(&remHead, &remTail);
}