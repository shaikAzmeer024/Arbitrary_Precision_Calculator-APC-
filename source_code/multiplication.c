
#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *p, *q, *temp;
    int mul, carry;
    int i, j;
    int a[1000] = {0};
    int n1 = 0, n2 = 0;

    // Count the digits in the first number
    p = tail1;
    while (p != NULL)
    {
        n1++;
        p = p->prev;
    }

    // Count the digits in the second number
    p = tail2;
    while (p != NULL)
    {
        n2++;
        p = p->prev;
    }

    // Store the first number's digits in an array
    p = tail1;
    for (i = 0; i < n1; i++)
    {
        a[i] = p->data;
        p = p->prev;
    }

    // Create an array to store the multiplication result
    int result[2000] = {0};

    // Start from the last digit of the first number
    p = tail1;
    i = 0;

    while (p != NULL)
    {
        // Start from the last digit of the second number
        q = tail2;
        j = 0;
        carry = 0;

        while (q != NULL)
        {
            // Multiply digits and add the existing result and carry
            mul = p->data * q->data + result[i + j] + carry;

            // Store the last digit of the multiplication
            result[i + j] = mul % 10;

            // Calculate the carry for the next position
            carry = mul / 10;

            // Move to the previous digit of the second number
            q = q->prev;
            j++;
        }

        // Store any remaining carry
        if (carry != 0)
            result[i + j] += carry;

        // Move to the previous digit of the first number
        p = p->prev;
        i++;
    }

    // Maximum possible number of result digits
    int size = n1 + n2;

    // Remove unnecessary zeros from the most significant side
    while (size > 1 && result[size - 1] == 0)
        size--;

    // Insert the result digits into the linked list
    // Read the array backwards to get the correct digit order
    for (i = size - 1; i >= 0; i--)
    {
        // Allocate memory for a new result node
        temp = malloc(sizeof(node));

        // Stop if memory allocation fails
        if (temp == NULL)
            return;

        // Store the current result digit
        temp->data = result[i];

        // Connect the new node after the current tail
        temp->prev = *tailR;
        temp->next = NULL;

        // If the result list is empty, set head and tail
        if (*headR == NULL)
        {
            *headR = temp;
            *tailR = temp;
        }
        else
        {
            // Link the old tail to the new node
            (*tailR)->next = temp;

            // Update the tail to the new node
            *tailR = temp;
        }
    }
}
