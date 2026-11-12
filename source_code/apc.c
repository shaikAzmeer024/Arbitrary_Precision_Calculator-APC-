#include "apc.h"

#include "apc.h"

int cla_validation(int argc, char *argv[])
{
    int i;

    /* Display help information */
    if (argc == 2 && strcmp(argv[1], "--help") == 0)
    {
        printf("Usage: ./a.out operand1 operator operand2\n");
        printf("\nOperators:\n");
        printf("  +  Addition\n");
        printf("  -  Subtraction\n");
        printf("  x  Multiplication\n");
        printf("  X  Multiplication\n");
        printf("  /  Division\n");

        return FAILURE;
    }

    /* Check the number of command-line arguments */
    if (argc != 4)
    {
        printf("Usage: ./a.out operand1 operator operand2\n");
        printf("Use ./a.out --help for help\n");
        return FAILURE;
    }

    /* Check whether the first operand contains only digits */
    if (argv[1][0] == '\0')
    {
        printf("Invalid first operand\n");
        return FAILURE;
    }

    for (i = 0; argv[1][i] != '\0'; i++)
    {
        if (argv[1][i] < '0' || argv[1][i] > '9')
        {
            printf("Invalid first operand\n");
            return FAILURE;
        }
    }

    /* Check whether the second operand contains only digits */
    if (argv[3][0] == '\0')
    {
        printf("Invalid second operand\n");
        return FAILURE;
    }

    for (i = 0; argv[3][i] != '\0'; i++)
    {
        if (argv[3][i] < '0' || argv[3][i] > '9')
        {
            printf("Invalid second operand\n");
            return FAILURE;
        }
    }

    /* Check whether the operator is valid */
    if (argv[2][1] != '\0' || (argv[2][0] != '+' && argv[2][0] != '-' && argv[2][0] != 'x' && argv[2][0] != 'X' && argv[2][0] != '/'))
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    return SUCCESS;
}


/* Insert a digit at the beginning of the list */
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->prev = NULL;
    new->next = *head;

    /* If the list already has nodes, update the first node */
    if (*head != NULL)
        (*head)->prev = new;
    else
        *tail = new;

    *head = new;

    return SUCCESS;
}


/* Insert a digit at the end of the list */
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));

    if (new == NULL)
        return FAILURE;

    new->data = data;
    new->next = NULL;
    new->prev = *tail;

    /* If the list is not empty, connect the last node */
    if (*tail != NULL)
        (*tail)->next = new;
    else
        *head = new;

    *tail = new;

    return SUCCESS;
}


/* Create a linked list from an operand string */
void create_list(char *opr, node **head, node **tail)
{
    int i;

    *head = NULL;
    *tail = NULL;

    /* Store each character as a separate digit */
    for (i = 0; opr[i] != '\0'; i++)
    {
        if (insert_last(head, tail, opr[i] - '0') == FAILURE)
        {
            printf("Memory allocation failed\n");
            delete_list(head, tail);
            return;
        }
    }

    /* Remove unnecessary zeros from the beginning */
    remove_pre_zeros(head);
}


/* Delete all nodes in the list */
int delete_list(node **head, node **tail)
{
    node *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;

        free(temp);
    }

    /* Both pointers must be NULL after deletion */
    *tail = NULL;

    return SUCCESS;
}


/* Print all digits in the list */
void print_list(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }

    printf("\n");
}


/* Return the number of digits in the list */
int list_len(node *head)
{
    int count = 0;

    while (head != NULL)
    {
        count++;
        head = head->next;
    }

    return count;
}


/* Remove leading zeros, but keep one zero for the number zero */
void remove_pre_zeros(node **head)
{
    node *temp;

    while (*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;

        free(temp);
    }
}


/* Compare two non-negative numbers */
int compare_list(node *head1, node *head2)
{
    int len1 = list_len(head1);
    int len2 = list_len(head2);

    /* A number with more digits is larger */
    if (len1 > len2)
        return 1;

    if (len1 < len2)
        return -1;

    /* Same number of digits: compare from left to right */
    while (head1 != NULL && head2 != NULL)
    {
        if (head1->data > head2->data)
            return 1;

        if (head1->data < head2->data)
            return -1;

        head1 = head1->next;
        head2 = head2->next;
    }

    /* Both numbers are equal */
    return 0;
}