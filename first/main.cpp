#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
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
    Ticket(const string& passengerName, const string& date, const string& seatNumber, const string& flightNumber, const float& price)
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

    void resetBooking() {
        this->passengerName = "-";
        this->bookingStatus = true;
    }
};

class Passenger {
    string name;
    vector<Ticket> tickets;

public:
    Passenger(const string& name): name(name){}

    void addTicket(const Ticket& ticket) {
        this->tickets.push_back(ticket);
    }

    string getName() const {
        return this->name;
    }

    vector<Ticket>& getTickets() {
        return this->tickets;
    }

};

class Airplane{
private:
    string date;
    int totalSize;
    string flightNumber;
    vector<Ticket> tickets;

public:
    Airplane(const string& flightNumber, string& date): flightNumber(flightNumber), date(date) {}

    void setTotalSize(const int& total) {
        this->totalSize = total;
    }

    void addTicket(const Ticket& newTicket) {
        this->tickets.push_back(newTicket);
    }

    string getDate() const {
        return this->date;
    }

    string getFlightNumber() const {
        return this->flightNumber;
    }

    vector<Ticket> getTickets() const {
        return this->tickets;
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

    void bookSeat(const string& passengerName, const string& seatNumber, int& id, vector<Ticket>* bookedTickets, vector<Passenger>* passengers) {
        for (auto & ticket : this->tickets) {
            if (ticket.getSeatNumber() == seatNumber && ticket.getBookingStatus()) {
                ticket.setPassengerName(passengerName);
                ticket.setId(id);
                bookedTickets->push_back(ticket);
                bool passengerFound = false;
                for (auto & passenger : *passengers) {
                    if (passenger.getName() == passengerName) {
                        passenger.addTicket(ticket);
                        passengerFound = true;
                        break;
                    }
                }
                if (!passengerFound) {
                    Passenger newPassenger(passengerName);
                    newPassenger.addTicket(ticket);
                    passengers->push_back(move(newPassenger));
                }
                cout << "Confirmed with ID " << id << endl;
                return;
            }
        }
        cout << "Seat not available or already booked." << endl;
    }

    void returnTicket(const int ticketId) {
        for (auto& ticket : tickets) {
            if (ticket.getId() == ticketId) {
                ticket.resetBooking();
                return;
            }
        }
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
            airplanes.push_back(move(airplane));
        }

        return airplanes;
    }
};

class FlightBookingSystem {
private:
    vector<Airplane> airplanes;
    vector<Passenger> passengers;
    vector<Ticket> bookedTickets;
    int nextId = 123;

    void loadAirplanes(const string& filePath) {
        ConfigReader reader;
        airplanes = move(reader.readConfiguration(filePath)); //////////////////////////////////////////////////////////////////////////////////////////////////////
    }

public:
    FlightBookingSystem(const string& configFilePath) {
        loadAirplanes(configFilePath);
    }

    void check() {
        string date, flightNumber;
        cout << "Enter date and flight number (example: 11.12.2022 FQ12): ";
        cin >> date >> flightNumber;

        for (auto& airplane : airplanes) {
            if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                auto availableTickets = airplane.checkSeatAvailability();
                if (availableTickets.empty()) {
                    cout << "No available seats." << endl;
                } else {
                    cout << "Available seats:" << endl;
                    for (auto& ticket : availableTickets) {
                        cout << "Seat: " << ticket.getSeatNumber() << ", Price: $" << ticket.getPrice() << endl;
                    }
                }
                return;
            }
        }
        cout << "Flight not found." << endl;
    }

    void book() {
        string passengerName, date, flightNumber, seatNumber;
        cout << "Enter passenger name, date, flight number, and seat number (example: John 11.12.2022 FQ12 1A): " << endl;
        cin >> passengerName >> date >> flightNumber >> seatNumber;

        for (auto &airplane : airplanes) {
            if (airplane.getDate() == date && airplane.getFlightNumber() == flightNumber) {
                airplane.bookSeat(passengerName, seatNumber, nextId, &bookedTickets, &passengers);
                nextId++;
                return;
            }
        }

        {

        }
        cout << "Flight not found or seat number is incorrect." << endl;
    }

    void commandReturn() {
        int idCheck;
        cout << "Enter confirmation ID: " << endl;
        cin >> idCheck;

        for (auto& airplane : airplanes) {
            for (auto& ticket : airplane.getTickets()) {
                if (ticket.getId() == idCheck && !ticket.getBookingStatus()) {
                    airplane.returnTicket(idCheck);
                    removeTicketFromPassenger(ticket);
                    removeTicketFromBookedTickets(idCheck);
                    cout << "Confirmed " << ticket.getPrice() << "$" << " refund for " << ticket.getPassengerName() << endl;
                    return;
                }
            }
        }
        cout << "Ticket with the given ID not found." << endl;
    }

    void removeTicketFromPassenger(const Ticket& ticket) {
        for (auto& passenger : passengers) {
            if (passenger.getName() == ticket.getPassengerName()) {
                vector<Ticket>& passengerTickets = passenger.getTickets();
                for (auto it = passengerTickets.begin(); it != passengerTickets.end(); ++it) {
                    if (it->getId() == ticket.getId()) {
                        passengerTickets.erase(it);
                        break;
                    }
                }
                break;
            }
        }
    }

    void removeTicketFromBookedTickets(int& ticketId) {
        for (auto it = bookedTickets.begin(); it != bookedTickets.end(); ++it) {
            if (it->getId() == ticketId) {
                bookedTickets.erase(it);
                return;
            }
        }
    }

    void view() {
        int idCheck;
        cout << "Enter confirmation ID: ";
        cin >> idCheck;

        for (const auto& ticket : bookedTickets) {
            if (ticket.getId() == idCheck) {
                cout << "Ticket details: Flight " << ticket.getFlightNumber() << ", Date: " << ticket.getDate()
                << ", Seat: " << ticket.getSeatNumber() << ", Price: $" << ticket.getPrice() << endl;
                return;
            }
        }
        cout << "Ticket with given ID not found." << endl;
    }

    void all() {
        string passengerName;
        cout << "Enter passenger name: ";
        cin >> passengerName;

        for (auto& passenger : passengers) {
            if (passenger.getName() == passengerName) {
                vector<Ticket>& tickets = passenger.getTickets();
                cout << "Tickets for " << passengerName << ":" << endl;
                for (auto& ticket : tickets) {
                    cout << "Flight " << ticket.getFlightNumber() << ", Date: " << ticket.getDate()
                         << ", Seat: " << ticket.getSeatNumber() << ", Price: $" << ticket.getPrice() << endl;
                }
                return;
            }
        }
        cout << "No tickets found for passenger: " << passengerName << endl;
    }

};

int main() {
    // FlightBookingSystem system("C:\\Users\\svobo\\OneDrive\\Desktop\\Yarrochka\\OOPD\\one\\first\\data.txt");
    FlightBookingSystem system("/Users/Yarrochka/Mine/Study/OOPD/first/data.txt");

    string command;
    while (true) {
        cout << "Enter command (check, book, return, view, all, exit): ";
        cin >> command;

        if (command == "check") {
            system.check();
        } else if (command == "book") {
            system.book();
        } else if (command == "return") {
            system.commandReturn();
        } else if (command == "view") {
            system.view();
        } else if (command == "all") {
            system.all();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Invalid command." << endl;
        }
    }

    return 0;
}