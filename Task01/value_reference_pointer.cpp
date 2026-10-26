// AI-assisted implementation prepared after faculty permission was reported by the student.
// Read and understand each function before using this work for coursework.
// Prediction written before the validation workflow was added:
// change(1,2,&3) prints 1 12 13; bigger(a,c)=100 changes c, so prints 1 100.
// show(1), show(1,2), show(1,2,3) print 16 13 6.
#include <iostream>

void change(int a, int& b, int* c)
{
    a += 10;
    b += 10;
    *c += 10;
}

int& bigger(int& p, int& q)
{
    return p > q ? p : q;
}

void show(int x, int y = 5, int z = 10)
{
    std::cout << x + y + z << ' ';
}

void applyByValue(long long fee, int percent)
{
    fee -= fee * percent / 100;
}

void applyConcession(long long& fee, int percent)
{
    fee -= fee * percent / 100;
}

void applyByPointer(long long* fee, int percent)
{
    if (fee != nullptr)
        *fee -= *fee * percent / 100;
}

int main()
{
    int a = 1, b = 2, c = 3;
    change(a, b, &c);
    std::cout << a << ' ' << b << ' ' << c << '\n';

    bigger(a, c) = 100;
    std::cout << a << ' ' << c << '\n';

    show(1);
    show(1, 2);
    show(1, 2, 3);
    std::cout << '\n';

    long long valueFee = 45000;
    long long referenceFee = 45000;
    long long pointerFee = 45000;
    applyByValue(valueFee, 10);
    applyConcession(referenceFee, 10);
    applyByPointer(&pointerFee, 10);

    std::cout << "after call by value    : " << valueFee << '\n';
    std::cout << "after call by reference: " << referenceFee << '\n';
    std::cout << "after call by pointer  : " << pointerFee << '\n';

    long long combinedFee = 45000;
    applyConcession(combinedFee, 10);
    applyConcession(combinedFee, 15);
    applyConcession(combinedFee, 25);
    std::cout << "after 10%, 15%, 25% in sequence: " << combinedFee << '\n';
}
