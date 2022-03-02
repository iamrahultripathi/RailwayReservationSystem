// Railway reservation using linked lists and Queues.
// If the reservation is full, prompt reservation full!! Put them in waiting list (queue).
// If a passenger wishes to cancel his ticket, he may cancel. Then the passenger in waiting list is booked automatically.
// Display all the contents of reserved passengers.

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define size 5
#define MAX_SIZE 20

struct node
{
    int ticket_no;
    int age;
    char name[MAX_SIZE];
    struct node *next;
};

void enqueue(struct node *);
void create();
int cancel(int);
void display();
int reservation();
struct node *dequeue();

struct node *head;
struct node *front;
struct node *rear;
int ticketno = 1;
int waitingno = 1;
void create()
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->ticket_no = ticketno;
    ticketno++;
    printf("Name: ");
    scanf("%s", temp->name);
    printf("Age : ");
    scanf("%d", &temp->age);
    temp->next = NULL;
    head = temp;
}
int reservation()
{

    if (head == NULL)
    {
        create();
        return 1;
    }
    else
    {
        struct node *temp;
        temp = head;
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        printf("Name: ");
        scanf("%s", new_node->name);
        printf("Age : ");
        scanf("%d", &new_node->age);
        int c = 1;
        while ((temp != NULL))
        {
            if (temp->ticket_no == 0)
            {
                strcpy(temp->name, new_node->name);
                temp->age = new_node->age;
                temp->ticket_no = c;
                return c;
            }
            temp = temp->next;
            c++;
        }
        temp = head;
        new_node->next = NULL;
        new_node->ticket_no = ticketno;
        ticketno++;

        if (ticketno <= size + 1)
        {
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = new_node;
            return new_node->ticket_no;
        }
        else
        {
            enqueue(new_node);
            return 0;
        }
    }
}

void enqueue(struct node *new_node)
{
    new_node->ticket_no = waitingno;
    waitingno++;
    if (front == NULL)
    {
        rear = new_node;
        rear->next = NULL;
        front = rear;
    }
    else
    {
        rear->next = new_node;
        rear = new_node;
    }
}
int cancel(int t_no)
{
    struct node *temp;
    struct node *prev;
    struct node *f;
    temp = head;
    if (front == NULL)
    {
        while (temp->ticket_no != t_no)
        {
            temp = temp->next;
            if (temp == NULL)
                break;
        }
        if (temp == NULL)
            return -1;
        else
        {
            temp->ticket_no = 0;
            return 1;
        }
    }
    else
    {

        if (t_no == 1)
        {
            f = dequeue();
            f->ticket_no = t_no;
            f->next = temp->next;
            head = f;
            free(temp);
            return 1;
        }
        else
        {
            while (temp->ticket_no != t_no)
            {
                prev = temp;
                temp = temp->next;
                if (temp == NULL)
                    break;
            }

            if (temp == NULL)
                return -1;
            else
            {
                f = dequeue();
                f->ticket_no = t_no;
                prev->next = f;
                f->next = temp->next;
                free(temp);
                return 1;
            }
        }
    }
}
struct node *dequeue()
{
    if (front == NULL)
    {
        return NULL;
    }
    else
    {
        struct node *temp;
        temp = front;
        front = front->next;
        return temp;
    }
}
void display()
{
    struct node *temp;
    temp = head;
    printf("\n******CONFIRMED SEATS******\n");
    printf("Ticket number\t\tName\t\t\tAge\n");
    while (temp != NULL)
    {
        if (temp->ticket_no == 0)
        {
            temp = temp->next;
            continue;
        }
        printf("%d\t\t\t", temp->ticket_no);
        printf("%s\t\t\t", temp->name);
        printf("%d\n", temp->age);
        temp = temp->next;
    }
    printf("\n******WAITING LIST******\n");
    printf("Waiting number\t\tName\t\t\tAge\n");
    struct node *temp2;
    temp2 = front;
    int c = 1;
    while (temp2 != NULL)
    {
        printf("%d\t\t\t", c);
        printf("%s\t\t\t", temp2->name);
        printf("%d\n", temp2->age);
        c++;
        temp2 = temp2->next;
    }
}
int main()
{
    int choice, status = 0, canc = 0, reg = 0;
    head = NULL;
    rear = NULL;
    front = NULL;
    printf("\t\t\t***RAILWAY RESERVATION***\t\t\t\t\n");
    int ch = 0;
    while (ch != 4)
    {
        printf("\n\nDo you want to - \n 1. Reserve a ticket? \n 2. Cancel Booking \n 3. Display passenger details \n 4. exit\n\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            status = reservation();
            if (status == 0)
            {
                printf("\nBooking Full!! \nYou are added to waiting list.");
            }
            else
                printf("\nBooking Successful!!! Enjoy your journey! Your Ticket No. is %d\n", status);

            break;

        case 2:
            printf("\nGive the Ticket number to be cancelled : ");
            scanf("%d", &reg);
            if (reg > size)
                printf("Ticket number invalid !!");
            else
            {
                canc = cancel(reg);
                if (canc == -1)
                    printf("Ticket number invalid !!");
                else
                    printf("Ticket cancelled successfully");
            }
            break;

        case 3:
            display();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf("\nWrong choice!\n");
        }
    }
}