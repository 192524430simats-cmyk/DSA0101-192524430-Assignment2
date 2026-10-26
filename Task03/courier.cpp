// Six overload predictions, before execution:
// charge(2): int overload (exact match); charge(2.0): double (exact).
// charge(2.0f): double (float-to-double promotion beats float-to-int conversion).
// charge(250): int (exact); charge(1250,true): int (exact).
// charge(Parcel{...}): Parcel overload (exact class match).
#include <iomanip>
#include <iostream>
#include <string>

struct Parcel
{
    double kilograms;
    bool express = false;
    bool insured = false;
};

double charge(double kilograms, bool express = false, bool insured = false)
{
    const double total = kilograms * 50.0 + (express ? 20.0 : 0.0) +
                         (insured ? 10.0 : 0.0);
    std::cout << "double kg overload: $";
    return total;
}

double charge(int grams, bool express = false, bool insured = false)
{
    const double total = charge(static_cast<double>(grams) / 1000.0, express, insured);
    std::cout << "int grams overload: $";
    return total;
}

double charge(const Parcel& parcel)
{
    const double total = charge(parcel.kilograms, parcel.express, parcel.insured);
    std::cout << "Parcel overload: $";
    return total;
}

void showCharge(double value)
{
    std::cout << std::fixed << std::setprecision(2) << value << '\n';
}

int main()
{
    std::cout << "charge(2) -> "; showCharge(charge(2));
    std::cout << "charge(2.0) -> "; showCharge(charge(2.0));
    std::cout << "charge(2.0f) -> "; showCharge(charge(2.0f));
    std::cout << "charge(250) -> "; showCharge(charge(250));
    std::cout << "charge(1250, true) -> "; showCharge(charge(1250, true));
    std::cout << "charge(Parcel{1.5, true, false}) -> ";
    showCharge(charge(Parcel{1.5, true, false}));
}
