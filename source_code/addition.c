
#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    int sum, carry = 0;
    int digit1, digit2;

    node *temp;

    while (tail1 != NULL || tail2 != NULL || carry != 0)
    {
        if (tail1 != NULL)
        {
            digit1 = tail1->data;
            tail1 = tail1->prev;
        }
        else
        {
            digit1 = 0;
        }

        if (tail2 != NULL)
        {
            digit2 = tail2->data;
            tail2 = tail2->prev;
        }
        else
        {
            digit2 = 0;
        }

        sum = digit1 + digit2 + carry;

        carry = sum / 10;
        sum = sum % 10;

        temp = malloc(sizeof(node));

        if (temp == NULL)
        {
            return;
        }

        temp->data = sum;
        temp->prev = NULL;
        temp->next = *headR;

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
}
