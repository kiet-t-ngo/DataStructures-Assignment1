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
void InsertSortedByDestination(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare);
struct FlightInfo* FindFlight(struct FlightInfo* head, char* destination, char* date);
void ReadInputString(char* buffer, int size);

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

// inserts a flight node into a sorted destination list in ascending order
void InsertSortedByDestination(struct FlightInfo** head, struct FlightInfo** tail, char* destination, char* date, float fare)
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

    // compares flight destinations and keep going until we find a node with a flight destination 
    // that comes before or equal to the new flights destination
    while (current != NULL && strcmp(current->Destination, newFlight->Destination) <= 0)
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

// goes thru the list starting from the head node and print the formatted list of flight details  
void PrintList(struct FlightInfo* head) 
{
    struct FlightInfo* current = head;
    //printf("\nForward");
    while (current != NULL) 
    {
        printf("\nDestination: %s, Date: %s, Fare: %.2f\n", current->Destination, current->Date, current->Fare);
        printf("--------------------------------------------------------------\n");
        current = current->Next;
    }
}
/*void PrintReverseList(struct FlightInfo* tail)
{
    printf("\nBackwards");
    struct FlightInfo* current = tail;
    while (current != NULL)
    {
        printf("\nDestination: %s, Date: %s, Fare: %.2f\n", current->Destination, current->Date, current->Fare);
        printf("--------------------------------------------------------------\n");
        current = current->Prev;
    }
}*/

// Free all dynamically allocated memory in the list
void FreeList(struct FlightInfo* head) {

    struct FlightInfo* current = head;
    struct FlightInfo* tempNode;

    while (current != NULL) {
        tempNode = current->Next;
        free(current->Destination);
        free(current->Date);
        free(current);
        current = tempNode;
    }

}

// read user string input
// buffer will point to char array where text will be stored
// size is the maximum number of characters the buffer can hold
void ReadInputString(char* buffer, int size) 
{
    // read user input and ensures its valid or not empty
    if (fgets(buffer, size, stdin) != NULL) 
    {
        // Note: Currently Buffer size is too small so it skips fare. The input filled buffer and left \n in stdin
        // Can't increase buffer size cuz requirements state destination[15] and date[9] otherwise it would be easily fixed
        size_t length = strlen(buffer); // calculates the length of the string currently stored inside buffer and saves into length variable
        // checks if string is not empty and if the last character read is \n, if its true than replace the trailing \n with a \0
        if (length > 0 && buffer[length - 1] == '\n') {
            buffer[length - 1] = '\0';
        }
        else
        {
            // Clears out remaining characters inside stdin until it reachs a \n or end of file
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        }
        // From GetString() example demo, gets rid of trailing \n from fgets
        // Note: would work if i could increase buffer size
        //buffer[strcspn(buffer, "\n")] = '\0';
    }
    
}

int main(void)
{
    // list pointers
    //struct FlightInfo* head = NULL;
    //struct FlightInfo* tail = NULL;

    struct FlightInfo* fareHead = NULL;
    struct FlightInfo* fareTail = NULL;

    struct FlightInfo* destinationHead = NULL;
    struct FlightInfo* destinationTail = NULL;

    char destination[15]; // max 15 chars
    char date[9]; // max 9 chars in length
    char fareBuffer[64]; // reading fare as a string instead of a float
    float fare;

    // Keep asking for flight information until user enters '.' to exit, then display flight details
    while (1)
    {
        printf("Enter Destination: ");
        // Calls ReadInputString() to get destination input from user
        ReadInputString(destination, sizeof(destination));
        // Exit while loop if input from user is '.'
        if (strcmp(destination, ".") == 0) 
        {
            break;
        }

        printf("Enter Date: ");
        // Calls ReadInputString() to get date input from user
        ReadInputString(date, sizeof(date));
        // Exit while loop if input from user is '.'
        if (strcmp(date, ".") == 0) {
            break;
        }

        printf("Enter fare: ");
        // Calls ReadInputString() to get fare input from user
        // store fare input inside fareBuffer as characters instead of a float
        ReadInputString(fareBuffer, sizeof(fareBuffer));
        // Gets ASCII value of the string and converts it to float value 
        fare = (float)atof(fareBuffer);
        
        
        // insert flight details into sorted fare and destination node
        InsertSortedByFare(&fareHead, &fareTail, destination, date, fare);
        InsertSortedByDestination(&destinationHead, &destinationTail, destination, date, fare);
    }

    // print both sorted lists
    printf("\nFlights Sorted By Fare:");
    PrintList(fareHead);
    printf("\nFlights Sorted By Destination:");
    PrintList(destinationHead);

    /*
    // Testing
    printf("=== TEST 1: Insert into an Empty List ===\n");
    printf("Expected: Only Chicago ($300.00). Head and Tail should point to Chicago\n");
    InsertSortedByFare(&head, &tail, "Chicago", "15052026", 300.00f);
    PrintList(head);
    //PrintReverseList(tail);

    printf("=== TEST 2: Insert with a Lower Fare (New Head) ===\n");
    printf("Expected Order: New York ($150.00) -> Chicago ($300.00)\n");
    InsertSortedByFare(&head, &tail, "New York", "11052026", 150.00f);
    PrintList(head);
    //PrintReverseList(tail);

    printf("=== TEST 3: Insert with a Higher Fare (New Tail) ===\n");
    printf("Expected Order: New York ($150.00) -> Chicago ($300.00) -> Texas ($600.00)\n");
    InsertSortedByFare(&head, &tail, "Texas", "12052026", 600.00f);
    PrintList(head);
    //PrintReverseList(tail);

    printf("=== TEST 4: Insert in the Middle ===\n");
    printf("Expected Order: New York ($150.00) -> Chicago ($300.00) -> Florida ($450.00) -> Texas ($600.00)\n");
    InsertSortedByFare(&head, &tail, "Florida", "13052026", 450.00f);
    PrintList(head);
    //PrintReverseList(tail);

    printf("=== TEST 5: Insert with Duplicate Fare ===\n");
    printf("Expected Order should handle the duplicate $300.00 next to Chicago since they are the same fare amount\n");
    InsertSortedByFare(&head, &tail, "California", "10052026", 300.00f);
    PrintList(head);
    //PrintReverseList(tail);

    // Free the list memory
    FreeList(head);
    */

    return 0;
}