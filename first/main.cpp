#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

class Ticket {
private:
    int id;
    string passengerName;
    string date;
    string flightNumber;
    string seatNumber;
    bool bookingStatus;
    float price;

public:
    Ticket(const string& passengerName, string date, string seatNumber, const string& flightNumber, float price)
            : passengerName(passengerName), date(date), seatNumber(seatNumber), flightNumber(flightNumber),
            price(price), bookingStatus(true) {}

    int getId() const {
        return this->id;
    }

    string getSeatNumber() const {
        return this->seatNumber;
    }

    float getPrice() const {
        return this->price;
    }

    bool getBookingStatus() const {
        return this->bookingStatus;
    }

    string getPassengerName() const{
        return this->passengerName;
    }

    string getFlightNumber() const {
        return this->flightNumber;
    }

    string getDate() const {
        return this->date;
    }

    void setPassengerName(const string& name) {
        this->passengerName = name;
        this->bookingStatus = false;
    }

    void setId(int id){
        this->id = id;
    }

};

class Airplane{
private:
    string date;
    int totalSize;
    string flightNumber;
    vector<Ticket> tickets;

public:
    Airplane(const string& flightNumber, string date): flightNumber(flightNumber), date(date) {}

    void setTotalSize(int total) {
        this->totalSize = total;
    }

    void addTicket(const Ticket& newTicket) {
        tickets.push_back(newTicket);
    }

    string getDate() const {
        return this->date;
    }

    string getFlightNumber() const {
        return this->flightNumber;
    }

    vector<Ticket> checkSeatAvailability() const {
        vector<Ticket> availableTickets;
        for (const auto& ticket : this->tickets) {
            if (ticket.getBookingStatus() == true && ticket.getPassengerName() == "-") {
                availableTickets.push_back(ticket);
            }
        }
        return availableTickets;
    }

    void bookSeat(const string& passengerName, const string& seatNumber, int id, vector<Ticket>* bookedTickets) {
        for (auto & ticket : tickets) {
            if (ticket.getSeatNumber() == seatNumber && ticket.getBookingStatus()) {
                ticket.setPassengerName(passengerName);
                ticket.setId(id);
                bookedTickets->push_back(ticket);
                cout << "Confirmed with ID " << id << endl;
                return;
            }
        }
        cout << "Seat not available or already booked." << endl;
    }

};

class ConfigReader {
public:
    ConfigReader()= default;

    vector<Airplane> readConfiguration(const string& filePath) {
        ifstream file(filePath);
        vector<Airplane> airplanes;
        string line;

        if (!file.is_open()) {
            cout << "Unable to open file. Try again." << endl;
            return airplanes;
        }

        getline(file, line);
        while (getline(file, line)){
            stringstream ss(line);
            string date, flightNumber;
            int seatsPerRow, startRow, endRow;
            float price;
            char sign, seatLetter;
            vector<pair<int, int>> priceSections;

            ss >> date >> flightNumber >> seatsPerRow;
            Airplane airplane(flightNumber, date);

            while (ss >> startRow >> sign >> endRow >> price >> sign) {
                 for (int i = startRow; i <= endRow; ++i) {
                    for (int j = 0; j < seatsPerRow; ++j) {
                        seatLetter = 'A' + j;
                        string seat = to_string(i) + seatLetter;
                        Ticket ticket("-", date, seat, flightNumber, price);
                        airplane.addTicket(ticket);
                    }
                }
            }
            airplane.setTotalSize(seatsPerRow * endRow);
            airplanes.push_back(airplane);
        }

        return airplanes;
    }
};

int main() {
    ConfigReader reader;
    vector<Airplane> airplanes = reader.readConfiguration("C:\\Users\\svobo\\OneDrive\\Desktop\\Yarrochka\\OOPD\\one\\first\\data.txt");
    vector<Ticket> bookedTickets;
    int id = 123;
    int idCheck;

    string command, passengerName, seatNumber, flightNumber, date;
    while (true) {
        cout << "Enter command (check, book, return, view, all, exit): " << endl;
        cin >> command;

        if (command == "check") {
            cout << "Enter date and flight number (example: 11.12.2022 FQ12): " << endl;
            cin >> date >> flightNumber;

            bool flightFound = false;
            for (const auto& airplane : airplanes) {
                if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                    flightFound = true;
                    vector<Ticket> availableTickets = airplane.checkSeatAvailability();
                    if (availableTickets.empty()) {
                        cout << "No seats available." << endl;
                    } else {
                        cout << "Available seats for flight " << flightNumber << " on " << date << ":" << endl;
                        for (const auto& ticket : availableTickets) {
                            cout << "Seat: " << ticket.getSeatNumber() << ", Price: $" << ticket.getPrice() << endl;
                        }
                    }
                    break;
                }
            }
            if (!flightFound) {
                cout << "Flight not found." << endl;
            }

        } else if (command == "book") {
            cout << "Enter passenger name, date, flight number, and seat number (example: John 11.12.2022 FQ12 1A): " << endl;
            cin >> passengerName >> date >> flightNumber >> seatNumber;

            bool isBooked = false;
            for (auto &airplane : airplanes) {
                if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                    airplane.bookSeat(passengerName, seatNumber, id, &bookedTickets);
                    id++;
                    isBooked = true;
                    break;
                }
            }
            if (!isBooked) {
                cout << "Flight not found or seat number is incorrect." << endl;
            }

        } else if (command == "return") {
            cout << "Enter confirmation ID: " << endl;
            cin >> idCheck;

            bool ticketFound = false;
            for (const auto& ticket : bookedTickets) {
                if (ticket.getId() == idCheck) {
                    cout << "Confirmed " << ticket.getPrice() << "$" << " refund for " << ticket.getPassengerName() << endl;
                    ticketFound = true;
                    break;
                }
            }
            if (!ticketFound) {
                cout << "Ticket with the given ID not found." << endl;
            }
        } else if (command == "view") {
            cout << "Enter confirmation ID: " << endl;
            cin >> idCheck;

            bool ticketFound = false;
            for (const auto& ticket : bookedTickets) {
                if (ticket.getId() == idCheck) {
                    cout << "Flight " << ticket.getFlightNumber() << ", " << ticket.getDate() << ", seat " << ticket.getSeatNumber() << ", price " << ticket.getPrice() << "$, " << ticket.getPassengerName() << endl;
                    ticketFound = true;
                    break;
                }
            }
            if (!ticketFound) {
                cout << "Ticket with the given ID not found." << endl;
            }
        } else if (command == "all") {
            cout << "Enter passenger name: " << endl;
            cin >> passengerName;

        } else if (command == "exit") {
            break;
        }
    }

    return 0;
}