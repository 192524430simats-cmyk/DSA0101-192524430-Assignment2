// Q2 prediction: the maximum starts at index 1 with value 91. Returning int&
// lets the caller update that array element directly. The bad local-reference
// example is kept in a separate file and must never be used at runtime.
#include <iostream>
#include <cstddef>

int& highestMark(int marks[], std::size_t count)
{
    std::size_t highest = 0;
    for (std::size_t i = 1; i < count; ++i)
        if (marks[i] > marks[highest])
            highest = i;
    return marks[highest];
}

std::size_t highestMarkIndex(const int marks[], std::size_t count)
{
    std::size_t highest = 0;
    for (std::size_t i = 1; i < count; ++i)
        if (marks[i] > marks[highest])
            highest = i;
    return highest;
}

int* highestMarkPointer(int marks[], std::size_t count)
{
    if (count == 0)
        return nullptr;
    return &marks[highestMarkIndex(marks, count)];
}

int main()
{
    int marks[] = {78, 91, 84, 91, 88};
    const std::size_t count = sizeof(marks) / sizeof(marks[0]);

    std::cout << "highest before: " << highestMark(marks, count) << '\n';
    highestMark(marks, count) += 2;
    std::cout << "array after reference moderation: ";
    for (std::size_t i = 0; i < count; ++i)
        std::cout << marks[i] << (i + 1 == count ? '\n' : ' ');

    std::cout << "index alternative points to: " << marks[highestMarkIndex(marks, count)] << '\n';
    if (int* highest = highestMarkPointer(marks, count))
        std::cout << "pointer alternative points to: " << *highest << '\n';

    const int copiedHighest = highestMark(marks, count);
    std::cout << "copy remains independent: " << copiedHighest << '\n';
}
