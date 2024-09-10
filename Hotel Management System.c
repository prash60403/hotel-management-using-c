#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define SINGLE "Single"
#define DOUBLE "Double"
#define DELUXE "Deluxe"

typedef struct {
    int roomNumber;
    char roomType[10];
    int isOccupied;
} Room;

typedef struct {
    int bookingID;
    char guestName[50];
    int roomNumber;
    int nightsStayed;
    double roomRate;
    double extraCharges;
    double billAmount;
} Booking;


Room rooms[MAX_ROOMS];
int totalRooms = 0; 

Booking bookings[MAX_ROOMS];
int totalBookings = 0; 


void bookRoom();
void checkIn();
void checkOut();
void amountBill(Booking *booking); 
void loadData();
void saveData(); 

int main() {
    int choice;
    loadData(); 

    while(1) {
        printf("\n--- Hotel Management System ---\n");
        printf("1. Book Room\n");
        printf("2. Check-In\n");
        printf("3. Check-Out\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: bookRoom(); break;
            case 2: checkIn(); break;
            case 3: checkOut(); break;
            case 4: saveData(); exit(0); break;
            default: printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}

void bookRoom() {
    char roomType[10];
    int roomFound = 0;

    printf("\n--- Book a Room ---\n");
    printf("Enter Room Type (Single, Double, Deluxe): ");
    scanf("%s", roomType);

    for (int i = 0; i < totalRooms; i++) {
        if (strcmp(rooms[i].roomType, roomType) == 0 && rooms[i].isOccupied == 0) {
            printf("Room %d is available. Booking now...\n", rooms[i].roomNumber);

          
            rooms[i].isOccupied = 1;
            roomFound = 1;

           
            Booking newBooking;
            newBooking.bookingID = rand() % 10000;
            printf("Enter Guest Name: ");
            scanf("%s", newBooking.guestName);
            newBooking.roomNumber = rooms[i].roomNumber;
            printf("Enter number of nights stayed: ");
            scanf("%d", &newBooking.nightsStayed);

            if (strcmp(roomType, SINGLE) == 0) {
                newBooking.roomRate = 100.0;
            } else if (strcmp(roomType, DOUBLE) == 0) {
                newBooking.roomRate = 150.0;
            } else if (strcmp(roomType, DELUXE) == 0) {
                newBooking.roomRate = 200.0;
            }

            newBooking.extraCharges = 0.0; 

            newBooking.billAmount = newBooking.nightsStayed * newBooking.roomRate;

            bookings[totalBookings++] = newBooking; // Save booking in the array

            printf("Booking Successful! Your Booking ID is %d\n", newBooking.bookingID);
            break;
        }
    }

    if (!roomFound) {
        printf("Sorry, no available rooms of type %s.\n", roomType);
    }
}


void checkIn() {
    int bookingID;
    int bookingFound = 0;

    printf("\n--- Check-In ---\n");
    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);

    for (int i = 0; i < totalBookings; i++) {
        if (bookings[i].bookingID == bookingID && rooms[bookings[i].roomNumber - 101].isOccupied == 1) {
            printf("Guest %s is checked in to room %d.\n", bookings[i].guestName, bookings[i].roomNumber);
            bookingFound = 1;
            break;
        }
    }

    if (!bookingFound) {
        printf("Booking ID not found or room is already checked in.\n");
    }
}


void checkOut() {
    int bookingID;
    int bookingFound = 0;

    printf("\n--- Check-Out ---\n");
    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);

    for (int i = 0; i < totalBookings; i++) {
        if (bookings[i].bookingID == bookingID && rooms[bookings[i].roomNumber - 101].isOccupied == 1) {
            
            amountBill(&bookings[i]);

            printf("Guest %s is checking out from room %d.\n", bookings[i].guestName, bookings[i].roomNumber);
            printf("Total Bill: $%.2f\n", bookings[i].billAmount);

            // Mark the room as unoccupied
            rooms[bookings[i].roomNumber - 101].isOccupied = 0;

            
            bookings[i] = bookings[totalBookings - 1]; 
            totalBookings--;

            bookingFound = 1;
            break;
        }
    }

    if (!bookingFound) {
        printf("Booking ID not found or room is not checked in.\n");
    }
}

void amountBill(Booking *booking) {
    double additionalCharges = 0.0;
    printf("Enter any additional charges (e.g., room service, food): ");
    scanf("%lf", &additionalCharges);

    booking->extraCharges += additionalCharges;
    booking->billAmount += additionalCharges;
}

void loadData() {
   
    rooms[0] = (Room){101, SINGLE, 0};
    rooms[1] = (Room){102, DOUBLE, 0};
    rooms[2] = (Room){103, DELUXE, 0};
    totalRooms = 3;
}

void saveData() {
}
