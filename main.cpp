#include <iostream>
#include <vector>
using namespace std;

class Airplane {
private:
    int totalSize;
    std::vector<bool> seatAvailability; // dynamic array

public:
    Airplane(int totalSize);

    bool checkSeatAvailability(int seatNumber);
};

class Ticket {
private:
    std::string passengerName;
    std::string flightInfo;
    int seatNumber;
    bool bookingStatus;
    int price;
public:
    Ticket(const std::string& passengerName, int seatNumber, const std::string& flightInfo, int price);
};

class Flight {
private:
    Airplane airplane;
    std::string flightNumber;
    std::vector<Ticket> tickets;
public:
    Flight(const Airplane& airplane, const std::string& flightNumber);

    void checkAvailability();

    Ticket bookTicket(const std::string& passengerName, int seatNumber);

    bool returnTicket(int ticketID);

    Ticket viewBooking(int ticketID);

    void viewUserBookings(const std::string& username);

};

class ConfigReader {
public:
    void readConfiguration(const std::string& filePath);
};


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
