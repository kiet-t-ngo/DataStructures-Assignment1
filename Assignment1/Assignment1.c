#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct FlightInfo {
    char* Destination;
    char* Date;
    float Fare;

    struct FlightInfo* Prev;
    struct FlightInfo* Next;

};

//Function prototype
void PrintList(struct FlightInfo* head);
void PrintReverseList(struct FlightInfo* tail);
void FreeList(struct FlightInfo* head);
struct FlightInfo* CreateFlight (char* destination, char* date, float fare);
void InsertSortedByFare(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare);
struct FlightInfo* FindFlight(struct FlightInfo* head, char* destination, char* date);

// allocates and initializes a new FlightInfo node
struct FlightInfo* CreateFlight(char* destination, char* date, float fare)
{
    // allocating memory for node
    struct FlightInfo* newFlight = (struct FlightInfo*)malloc(sizeof(struct FlightInfo));
    // safe check, if allocation fails or is out of memory, display error and exit
    if (newFlight == NULL)
    {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }

    // allocating memory for destination and date strings
    newFlight->Destination = (char*)malloc((strlen(destination) + 1) * sizeof(char));
    newFlight->Date = (char*)malloc((strlen(date) + 1) * sizeof(char));

    // if there is no destination or date input (empty), display no memory error and exit
    if (newFlight->Destination == NULL || newFlight->Date == NULL) {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    // copy data and initializing fields
    strcpy(newFlight->Destination, destination);
    strcpy(newFlight->Date, date);
    //newFlight->Destination = destination;
    //newFlight->Date = date;
    newFlight->Fare = fare;
    newFlight->Prev = NULL;
    newFlight->Next = NULL;

    return newFlight;
}

// inserts a flight node into a sorted fare list in ascending order
void InsertSortedByFare(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare)
{
    struct FlightInfo* newFlight = CreateFlight(destination, date, fare);
    // list is empty
    if (*head == NULL)
    {
        // set new nodes to head and tail
        *head = newFlight;
        *tail = newFlight;
        // set next and prev pointers to NULL
        newFlight->Next = NULL;
        newFlight->Prev = NULL;
        return;
    }

    struct FlightInfo* current = *head;
    
    // keep going until we find a node with a higher fare
    while (current != NULL && current->Fare <= newFlight->Fare) 
    {
        current = current->Next;
    }
    // insert at head
    if (current == *head)
    {
        newFlight->Next = *head;
        newFlight->Prev = NULL;
        (*head)->Prev = newFlight;
        *head = newFlight;
    }
    // if we reach the end of the list, insert at tail if current postion == NULL
    else if (current == NULL)
    {
        newFlight->Prev = *tail;
        newFlight->Next = NULL; // set next to null because its at the end of the list
        (*tail)->Next = newFlight;
        *tail = newFlight;
    }
    // insert in the middle (before current)
    else
    {
        newFlight->Prev = current->Prev;
        newFlight->Next = current;
        current->Prev->Next = newFlight;
        current->Prev = newFlight;
    }
}

struct FlightInfo* FindFlight(struct FlightInfo* head, char* destination, char* date)
{

}

void PrintList(struct FlightInfo* head) 
{
    
}
void PrintReverseList(struct FlightInfo* tail)
{
    
}


int main(void)
{
    // list pointers
    struct FlightInfo* head = NULL;
    struct FlightInfo* tail = NULL;


    return 0;
}