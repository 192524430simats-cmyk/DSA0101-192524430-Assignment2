// Token prediction before running: constructors assign IDs 101, 102, 103, 104.
// Output is "101 103 104 4"; the shared next counter starts at 100 and four
// constructors run. BusTicket's class-wide count remains three after capacity.
#include <iostream>
#include <string>

class Token
{
    static int next;
    int id_;

public:
    Token() : id_(++next) {}
    int get() const { return id_; }
    static int issued() { return next - 100; }
};

int Token::next = 100;

class BusTicket
{
    static int issued;
    static const int CAPACITY = 3;
    int seat_;
    std::string name_;

public:
    explicit BusTicket(const std::string& name) : seat_(0), name_(name)
    {
        if (issued < CAPACITY)
            seat_ = ++issued;
    }

    static int count() { return issued; }

    void print() const
    {
        std::cout << name_ << ": "
                  << (seat_ ? "Seat " + std::to_string(seat_) : "Waiting")
                  << '\n';
    }
};

int BusTicket::issued = 0;

void createTicketInFunction(int callNumber)
{
    BusTicket ticket("Function ticket " + std::to_string(callNumber));
    ticket.print();
}

int main()
{
    Token counter[3];
    Token extra;
    std::cout << "Token prediction program: "
              << counter[0].get() << ' ' << counter[2].get() << ' '
              << extra.get() << ' ' << Token::issued() << '\n';

    BusTicket trip[4] = {
        BusTicket("Asha"), BusTicket("Bala"),
        BusTicket("Chitra"), BusTicket("Dev")
    };
    for (const BusTicket& ticket : trip)
        ticket.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';

    createTicketInFunction(1);
    createTicketInFunction(2);
    std::cout << "Issued after function calls: " << BusTicket::count() << '\n';
}
