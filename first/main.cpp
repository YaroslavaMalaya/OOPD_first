#include <iostream>
#include <vector>
using namespace std;

class Airplane {
private:
    int totalSize;
    vector<bool> seatAvailability; // dynamic array

public:
    Airplane(int totalSize);

    bool checkSeatAvailability(int seatNumber);
};

class Ticket {
private:
    string passengerName;
    string flightInfo;
    int seatNumber;
    bool bookingStatus;
    int price;
public:
    Ticket(const string& passengerName, int seatNumber, const string& flightInfo, int price);
};

class Flight {
private:
    Airplane airplane;
    string flightNumber;
    vector<Ticket> tickets;
public:
    Flight(const Airplane& airplane, const string& flightNumber);

    void checkAvailability();

    Ticket bookTicket(const string& passengerName, int seatNumber);

    bool returnTicket(int ticketID);

    Ticket viewBooking(int ticketID);

    void viewUserBookings(const string& username);

};

class ConfigReader {
public:
    void readConfiguration(const string& filePath);
};


int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
