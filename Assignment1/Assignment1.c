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

struct FlightInfo* CreateFlight (char destination, char date, float fare);
struct FlightInfo* FindFlight(struct FlightInfo* head, const char* destination, const char* date);



struct FlightInfo* CreateFlight(char* destination, char* date, float fare)
{
    struct FlightInfo* newFlight = (struct FlightInfo*)malloc(sizeof(struct FlightInfo));
    if (newFlight == NULL)
    {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }

    newFlight->Destination = (char*)malloc((strlen(destination) + 1) * sizeof(char));
    newFlight->Date = (char*)malloc((strlen(date) + 1) * sizeof(char));

    // if there is no destination or date input (empty), display no memory error and exit
    if (newFlight->Destination == NULL || newFlight->Date == NULL) {
        printf("No Memory!");
        exit(EXIT_FAILURE);
    }
    strcpy(newFlight->Destination, destination);
    strcpy(newFlight->Date, date);
    newFlight->Destination = destination;
    newFlight->Date = date;
    newFlight->Fare = fare;
    newFlight->Prev = NULL;
    newFlight->Next = NULL;

    return newFlight;
}

struct FlightInfo* FindFlight(struct FlightInfo* head, const char* destination, const char* date)
{

}

int main(void)
{
    // list pointers
    struct FlightInfo* head = NULL;
    struct FlightInfo* tail = NULL;


    return 0;
}