#ifndef STATION_H
#define STATION_H
#define MAX_LINES 5
#define MAX_TAXIS 5

typedef struct {
    int id;
    int passengers;
    int maxPassengers;
    int isActive;
    float moneyCollected;
    int totalPassengers;
    float totalMoney;
    int trips;
    int hasDeparted;
    int nextAvailableTime;
} Taxi;

typedef struct {
    int lineNumber;
    float price;
    int departureTime;
    Taxi taxis[MAX_TAXIS];
    int taxiCount;
    int arrivalTime;
} Line;

typedef struct {
    Line lines[MAX_LINES];
    int lineCount;
} Station;

void initStation(Station* station);
void displayLines(Station* station);
int registerPassenger(Station* station);
void displayStatus(Station* station);
void printTicket(Line* line, Taxi* taxi);
void generateReport(Station* station);
#endif
