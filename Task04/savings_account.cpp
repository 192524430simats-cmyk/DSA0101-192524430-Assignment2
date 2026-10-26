// Q4 design: a private circular array stores the latest ten transactions.
// Prediction: after 11 accepted operations, the statement contains the withdrawal
// and deposits 10 through 90; the rejected withdrawal does not enter the history.
#include <iomanip>
#include <iostream>
#include <string>

class SavingsAccount
{
    struct Transaction
    {
        std::string type;
        double amount;
        double balanceAfter;
    };

    long long accountNumber_;
    double balance_;
    Transaction transactions_[10]{};
    int count_ = 0;
    int oldest_ = 0;

    void record(const std::string& type, double amount)
    {
        const int slot = (oldest_ + count_) % 10;
        transactions_[slot] = Transaction{type, amount, balance_};
        if (count_ < 10)
            ++count_;
        else
            oldest_ = (oldest_ + 1) % 10;
    }

public:
    explicit SavingsAccount(long long accountNumber)
        : accountNumber_(accountNumber), balance_(0.0) {}

    bool deposit(double amount)
    {
        if (amount <= 0.0)
            return false;
        balance_ += amount;
        record("deposit", amount);
        return true;
    }

    bool withdraw(double amount);
    void miniStatement() const;
    double balance() const { return balance_; }
};

bool SavingsAccount::withdraw(double amount)
{
    if (amount <= 0.0 || amount > balance_)
        return false;
    balance_ -= amount;
    record("withdrawal", -amount);
    return true;
}

void SavingsAccount::miniStatement() const
{
    std::cout << "Account " << accountNumber_ << " balance=$"
              << std::fixed << std::setprecision(2) << balance_ << '\n';
    for (int i = 0; i < count_; ++i)
    {
        const Transaction& t = transactions_[(oldest_ + i) % 10];
        std::cout << t.type << " amount=$" << t.amount
                  << " balance-after=$" << t.balanceAfter << '\n';
    }
}

int main()
{
    SavingsAccount account(2024001);
    account.deposit(1000.0);
    account.withdraw(150.0);
    for (int i = 1; i <= 9; ++i)
        account.deposit(i * 10.0);

    const bool accepted = account.withdraw(5000.0);
    std::cout << "insufficient withdrawal rejected: "
              << std::boolalpha << !accepted << '\n';
    account.miniStatement();
}
