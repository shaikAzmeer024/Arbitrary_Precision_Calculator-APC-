/******************************************************************************
*
* Author          : Shaik Azmeer
* Reg_no          : 26015_079
* Project Name    : APC (Arbitary Precesion Control)
* 
******************************************************************************/

/******************************************************************************
*
* File Name    : main.c
*
* Description  : Starting program for Arbitrary Precision Calculator.
*                Accepts operands and operator through command line arguments
*                and performs arithmetic operations using Doubly Linked Lists.
*
******************************************************************************/

#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    char oper;

    /* Step 1: Validate command-line arguments */
    if (cla_validation(argc, argv) == FAILURE)
    {
        return FAILURE;
    }

    /* Step 2: Store both operands in linked lists */
    create_list(argv[1], &head1, &tail1);
    create_list(argv[3], &head2, &tail2);

    /* Check whether list creation was successful */
    if (head1 == NULL || head2 == NULL)
    {
        printf("Failed to create operand lists\n");

        delete_list(&head1, &tail1);
        delete_list(&head2, &tail2);

        return FAILURE;
    }

    /* Step 3: Remove leading zeros */
    remove_pre_zeros(&head1);
    remove_pre_zeros(&head2);

    /* Step 4: Get the operator */
    oper = argv[2][0];
    int negative = 0;

    /* Step 5: Perform the selected operation */
    switch (oper)
    {
        case '+':
            addition(tail1, tail2, &headR, &tailR);
            break;

        case '-':
            subtraction(tail1, tail2, &headR, &tailR, &negative);
            break;

        case 'x':
        case 'X':
            multiplication(tail1, tail2, &headR, &tailR);
            break;

        case '/':
            division(head1, head2, &headR, &tailR);
            break;

        default:
            printf("Invalid operator\n");

            delete_list(&head1, &tail1);
            delete_list(&head2, &tail2);

            return FAILURE;
    }

    /* Step 6: Display the result */
    printf("\n-----------------------------\n");
    printf("     ARBITRARY CALCULATOR\n");
    printf("-----------------------------\n");

    printf("Operand 1 : %s\n", argv[1]);
    printf("Operator  : %c\n", oper);
    printf("Operand 2 : %s\n", argv[3]);
    printf("-----------------------------\n");
    printf("Result    : ");

    if (oper == '-' && negative == 1)
    {
        printf("-");
    }

    if (headR != NULL)
    {
        print_list(headR);
    }
    else
    {
        printf("Error");
    }

    printf("-----------------------------\n");

    /* Step 7: Free all allocated memory */
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return SUCCESS;
}

/******************************************************************************
 Project  Description :
    This project implements an Arbitrary Precision Calculator (APC) using
 Doubly Linked Lists to perform arithmetic operations on integers of
 arbitrary length. Each digit of a number is stored in a separate node,
 allowing the calculator to overcome the limitations of built-in data
 types. The program accepts operands through command-line arguments,
 performs addition, subtraction, multiplication, and division by processing
 the numbers digit by digit, and produces accurate results for very large
 integers while demonstrating the use of dynamic memory allocation, linked
 list manipulation, and arithmetic algorithms.
******************************************************************************/