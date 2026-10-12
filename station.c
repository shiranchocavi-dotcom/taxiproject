#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "station.h"
extern int currentTime;
void initStation(Station* station) {
    station->lineCount = 5;

    int times[5] = { 8, 10, 12, 14, 16 };

    for (int i = 0; i < station->lineCount; i++) {
        Line* line = &station->lines[i];

        line->lineNumber = i + 1;
        line->price = 20 + i * 5;
        line->departureTime = times[i];
        line->arrivalTime = line->departureTime + 1;
        line->taxiCount = 1;

        for (int j = 0; j < line->taxiCount; j++) {
            Taxi* taxi = &line->taxis[j];

            taxi->id = j + 1;
            taxi->passengers = 0;
            taxi->maxPassengers = 3 + (i % 3);
            taxi->isActive = 1;
            taxi->moneyCollected = 0;
            taxi->totalPassengers = 0;
            taxi->totalMoney = 0;

            taxi->hasDeparted = 0;
        }
    }
}
int registerPassenger(Station* station) {
    int lineChoice;

    printf("\nCurrent time: %02d:00\n", currentTime);
    printf("Note: Each booking advances time by one hour.\n");
    // Show only available lines
    printf("\n===== AVAILABLE LINES =====\n");

    int available = 0;

    for (int i = 0; i < station->lineCount; i++) {
        Line* line = &station->lines[i];

        if (line->departureTime >= currentTime) {
            printf("Line %d | Departure: %02d:00 | Price: %.2f\n",
                line->lineNumber,
                line->departureTime,
                line->price);
            available = 1;
        }
    }

    if (!available) {
        printf("No available lines at this time!\n");
        return 0;
    }

    // Line selection
    printf("\nChoose line: ");
    if (scanf("%d", &lineChoice) != 1) {
        printf("Invalid input!\n");
        return 0;
    }

    // Finding a line
    Line* selectedLine = NULL;
    for (int i = 0; i < station->lineCount; i++) {
        if (station->lines[i].lineNumber == lineChoice) {
            selectedLine = &station->lines[i];
            break;
        }
    }

    if (!selectedLine) {
        printf("Line not found!\n");
        return 0;
    }

    // Checking if the line has already been released
    if (currentTime > selectedLine->departureTime) {
        printf("This line has already departed!\n");
        return 0;
    }

    // There is one taxi per line.
    Taxi* selectedTaxi = &selectedLine->taxis[0];

    int availableSeats = selectedTaxi->maxPassengers - selectedTaxi->passengers;

    printf("Available seats: %d/%d\n",
        availableSeats,
        selectedTaxi->maxPassengers);

    // Check if full
    if (availableSeats <= 0) {
        printf("Taxi is full!\n");
        return 0;
    }

    // Number of tickets
    int tickets;
    printf("How many tickets? ");
    if (scanf("%d", &tickets) != 1 || tickets <= 0) {
        printf("Invalid number!\n");
        return 0;
    }

    if (tickets > availableSeats) {
        printf("Not enough seats available!\n");
        return 0;
    }

    // Quick calculation
    double totalPrice = tickets * selectedLine->price;

    printf("Total price: %.2f\n", totalPrice);

    // payment
    double payment;
    printf("Enter payment: ");
    if (scanf("%lf", &payment) != 1) {
        printf("Invalid payment input!\n");
        return 0;
    }

    if (payment < totalPrice) {
        printf("Not enough payment!\n");
        return 0;
    }

    double change = payment - totalPrice;
    printf("Payment accepted. Change: %.2f\n", change);

    // Data update
    selectedTaxi->passengers += tickets;
    selectedTaxi->moneyCollected += totalPrice;

    selectedTaxi->totalPassengers += tickets;
    selectedTaxi->totalMoney += totalPrice;

    // Card printing
    printTicket(selectedLine, selectedTaxi);

    return 1; // success
}
void printTicket(Line* line, Taxi* taxi) {
    printf("\n");
    printf("=====================================\n");
    printf("           TAXI TICKET               \n");
    printf("=====================================\n");
    printf(" Line Number   : %d\n", line->lineNumber);
    printf(" Departure Time: %02d:00\n", line->departureTime);
    printf(" Taxi ID       : %d\n", taxi->id);
    printf("-------------------------------------\n");
    printf(" Price Paid    : %.2f\n", line->price);
    printf(" Passenger No. : %d/%d\n",
        taxi->passengers,
        taxi->maxPassengers);
    printf("-------------------------------------\n");

    if (taxi->passengers == taxi->maxPassengers) {
        printf(" Status        : FULL - Leaving now!\n");
    }
    else {
        printf(" Status        : Waiting for passengers\n");
    }

    printf("=====================================\n\n");
}

void displayLines(Station* station) {
    printf("=================================\n");
    printf("   TAXI STATION (working hours :08:00 - 17:00)\n");
    printf("=================================\n");

    printf("\nAvailable Lines:\n");

    for (int i = 0; i < station->lineCount; i++) {
        Line* line = &station->lines[i];
        printf("Line %d | Departure: %02d:00 | Arrival: %02d:00 | Price: %.2f\n",
            line->lineNumber,
            line->departureTime,
            line->arrivalTime,
            line->price);
    }
}


void displayStatus(Station* station) {
    int inputTime;

    printf("Enter hour (8-17): ");
    scanf("%d", &inputTime);

    // Checking whether the station is open
    if (inputTime < 8 || inputTime >= 17) {
        printf("The station is closed at this hour!\n");
        return;
    }


    printf("\n===== STATUS =====\n");

    for (int i = 0; i < station->lineCount; i++) {
        Line* line = &station->lines[i];

        printf("\nLine %d | Departure: %02d:00 | Arrival: %02d:00 | Price: %.2f",
            line->lineNumber,
            line->departureTime,
            line->arrivalTime,
            line->price);

        for (int j = 0; j < line->taxiCount; j++) {
            Taxi* taxi = &line->taxis[j];

            printf("\nTaxi %d | passengers: %d/%d | money: %.2f | active: %d",
                taxi->id,
                taxi->totalPassengers,
                taxi->maxPassengers,
                taxi->totalMoney,
                taxi->isActive);

            if (inputTime >= line->arrivalTime) {
                printf(" | STATUS: Arrived\n");
            }
            else if (inputTime >= line->departureTime) {
                printf(" | STATUS: On the way\n");
            }
            else {
                printf(" | STATUS: Waiting\n");
            }
        }
    }

    printf("\n========================\n");
}
void generateReport(Station* station) {
    int totalPassengers = 0;
    float totalMoney = 0;

    printf("\n===== DAILY REPORT =====\n");

    for (int i = 0; i < station->lineCount; i++) {
        Line* line = &station->lines[i];

        int linePassengers = 0;
        float lineMoney = 0;
        int lineTrips = 0;

        for (int j = 0; j < line->taxiCount; j++) {
            Taxi* taxi = &line->taxis[j];

            linePassengers += taxi->totalPassengers;
            lineMoney += taxi->totalMoney;
            lineTrips += taxi->trips;
        }

        printf("\nLine %d:\n", line->lineNumber);
        printf("Passengers: %d\n", linePassengers);
        printf("Money: %.2f\n", lineMoney);

        totalPassengers += linePassengers;
        totalMoney += lineMoney;
    }

    printf("\n===== TOTAL =====\n");
    printf("Total Passengers: %d\n", totalPassengers);
    printf("Total Money: %.2f\n", totalMoney);
}