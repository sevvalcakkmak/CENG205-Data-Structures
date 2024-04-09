// Şevval Çakmak 22118080010 CENG205_assignment2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_SIZE 20

typedef struct // define struct for circular queues
{
    int front, rear;
    int order; // first or second, 1 or 2.
} CircularQueue;

void initializeCircularQueues(CircularQueue *first, CircularQueue *second);                 // initialize the queues
int isCircularQueueEmpty(CircularQueue *cq);                                                // checks if the queue is empty
int isCircularQueueFull(CircularQueue *checkedCQ, CircularQueue *otherCQ);                  // checks if the queue is full
void enqueue(CircularQueue *enqueuedCQ, CircularQueue *otherCQ, int *arr, int value);       // enqueues the value to specified queue
int dequeue(CircularQueue *cq, int *arr);                                                   // dequeues the value from specified queue
char *getOrderName(CircularQueue *cq);                                                      // returns "FIRST" or "SECOND"
void printCQ(CircularQueue *cq, int *arr);                                                  // prints the queue elements
int getSize(CircularQueue *cq);                                                             // returns the size of queue
void displayFileResults(FILE *file, CircularQueue *first, CircularQueue *second, int *arr); // reads input file and then process

int main()
{
    FILE *fptr;
    fptr = fopen("input.txt", "r"); // open the file

    int arr[ARRAY_SIZE];
    CircularQueue first = {.order = 1};  // define first circular queue and set the order
    CircularQueue second = {.order = 2}; // define second circular queue and set the order

    displayFileResults(fptr, &first, &second, arr); // display all the results we get from the file
    fclose(fptr);                                   // close the file

    return 0;
}

void initializeCircularQueues(CircularQueue *first, CircularQueue *second) // initialize the queues
{                                                                          // set initial values
    first->front = 0;
    first->rear = 0;
    second->front = 10;
    second->rear = 10;
}

int isCircularQueueEmpty(CircularQueue *cq) // checks if the queue is empty
{
    return (cq->front == cq->rear);
}

int isCircularQueueFull(CircularQueue *checkedCQ, CircularQueue *otherCQ) // checks if the queue is full
{
    return (checkedCQ->rear + 1) % ARRAY_SIZE == otherCQ->front;
}

void enqueue(CircularQueue *enqueuedCQ, CircularQueue *otherCQ, int *arr, int value) // enqueues the value to specified queue
{
    if (isCircularQueueFull(enqueuedCQ, otherCQ)) // if the queue is full
    {
        printf("Queue\t%s\tis full\n", getOrderName(enqueuedCQ));
    }
    else // if the queue is not full
    {
        arr[enqueuedCQ->rear] = value;                          // set the value
        enqueuedCQ->rear = (enqueuedCQ->rear + 1) % ARRAY_SIZE; // go one step further from end of the queue
        printf("%d\tis inserted to queue\t%s\n", value, getOrderName(enqueuedCQ));
    }
}

int dequeue(CircularQueue *cq, int *arr) // dequeues the value from specified queue
{
    int value;
    if (isCircularQueueEmpty(cq)) // if the queue is empty
    {
        printf("Queue\t%s\tis empty\n", getOrderName(cq));
        return -1; // return invalid value
    }
    else // if the queue is not empty
    {
        value = arr[cq->front];                   // get the value from the beginning
        cq->front = (cq->front + 1) % ARRAY_SIZE; // go one step further from beginning of the queue
        printf("%d\tis deleted from queue\t%s\n", value, getOrderName(cq));
        return value; // return dequeued element
    }
}

char *getOrderName(CircularQueue *cq) // returns "FIRST" or "SECOND"
{
    char *str = (char *)malloc(sizeof(char) * 10); // set the size of string
    if (cq->order == 1)
    {
        strcpy(str, "FIRST"); // copy "FIRST" to str
        return str;
    }
    else if (cq->order == 2)
    {
        strcpy(str, "SECOND"); // copy "SECOND" to str
        return str;
    }
    else // invalid order
    {
        return "ERROR";
    }
}

void printCQ(CircularQueue *cq, int *arr) // prints the queue elements
{
    printf("QUEUE:%s\tFRONT:%d\tREAR:%d\tSIZE:%d\n", getOrderName(cq), cq->front, cq->rear, getSize(cq));
    if (isCircularQueueEmpty(cq)) // if the queue is empty
    {
        printf("NO_CONTENT\n");
    }
    else // if the queue is not empty
    {
        int i = cq->front;
        do // print values of the queue
        {
            printf("%d\t", arr[i]);
            i = (i + 1) % ARRAY_SIZE;
        } while (i != cq->rear); // until end of the queue
        printf("\n");
    }
}

int getSize(CircularQueue *cq) // returns the size of queue
{
    if (cq->front <= cq->rear)
    {
        return (cq->rear - cq->front);
    }
    else
    {
        return ((ARRAY_SIZE - cq->front) + cq->rear);
    }
}

void displayFileResults(FILE *file, CircularQueue *first, CircularQueue *second, int *arr) // reads input file and then process
{
    initializeCircularQueues(first, second); // initialize the queues
    char input[20];
    int value;
    while (fscanf(file, "%s", input) != EOF) // read each string until we reach the end of file
    {
        if (strcmp(input, "PRINT") == 0) // if the commands is "PRINT"
        {
            fscanf(file, "%s", input); // read next command to get <queue>
            if (strcmp(input, "FIRST") == 0)
            {
                printCQ(first, arr); // PRINT FIRST
            }
            else if (strcmp(input, "SECOND") == 0)
            {
                printCQ(second, arr); // PRINT SECOND
            }
            else
            {
                printf("ERROR");
            }
        }
        else if (strcmp(input, "ENQUEUE") == 0) // if the commands is "ENQUEUE"
        {
            fscanf(file, "%s", input);  // read next command to get <queue>
            fscanf(file, "%d", &value); // read next command to get <value>
            if (strcmp(input, "FIRST") == 0)
            {
                enqueue(first, second, arr, value); // ENQUEUE FIRST <value>
            }
            else if (strcmp(input, "SECOND") == 0)
            {
                enqueue(second, first, arr, value); // ENQUEUE SECOND <value>
            }
            else // invalid <queue>
            {
                printf("ERROR");
            }
        }
        else if (strcmp(input, "DEQUEUE") == 0) // if the commands is "DEQUEUE"
        {
            fscanf(file, "%s", input); // read next command to get <queue>
            if (strcmp(input, "FIRST") == 0)
            {
                dequeue(first, arr); // DEQUEUE FIRST
            }
            else if (strcmp(input, "SECOND") == 0)
            {
                dequeue(second, arr); // DEQUEUE SECOND
            }
            else // invalid <queue>
            {
                printf("ERROR");
            }
        }
        else // unvalid command
        {
            printf("ERROR");
        }
    }
}
