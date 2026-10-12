// taxiproject_327537734.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "station.h"
int currentTime = 8;
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"
void printMenu() {
    printf("\n");
    printf(CYAN "=====================================\n" RESET);
    printf(BOLD BLUE "        TAXI STATION SYSTEM\n" RESET);
    printf(CYAN "=====================================\n" RESET);

    printf(YELLOW "|  1. View Lines                    |\n" RESET);
    printf(YELLOW "|  2. Register Passenger           |\n" RESET);
    printf(YELLOW "|  3. View Status                  |\n" RESET);
    printf(YELLOW "|  4. Daily Report                 |\n" RESET);
    printf(RED    "|  0. Exit                         |\n" RESET);

    printf(CYAN "=====================================\n" RESET);
    printf(GREEN "Choose option: " RESET);
}

void menu(Station* station) {
    int choice;

    do {
        printMenu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");

            while (getchar() != '\n');

            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            displayLines(station);
            break;
        case 2:
            if (registerPassenger(station)) {
                currentTime++;

                if (currentTime >= 17) {
                    currentTime = 8;
                }
                printf("\n[INFO] Time advanced by one hour after booking.\n");
            }
            break;
        case 3:
            displayStatus(station);
            break;
        case 4:
            generateReport(station);
            break;
        case 0:
            printf("Goodbye!\n");
            break;

        default:
            printf("Invalid option! Please choose 0-4.\n");
        } 
        }      while (choice != 0); 
}

int main() {
    Station station;

    initStation(&station);
    menu(&station);

    return 0;
}