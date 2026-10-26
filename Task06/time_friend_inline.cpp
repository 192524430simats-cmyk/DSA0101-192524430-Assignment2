// Q6 correctness cases are reasoned before execution:
// 09:45 to 13:10 is 205 minutes; 13:10 is not earlier than 09:45.
// Equal times differ by zero and neither is earlier. 11:50 precedes 12:10 by 20 min.
// The benchmark compares an inline function and an out-of-line noinline function.
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>

class Time
{
    int h_;
    int m_;

public:
    Time(int hour, int minute) : h_(hour), m_(minute) {}
    friend int minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

inline int minutesBetween(const Time& a, const Time& b)
{
    const int left = a.h_ * 60 + a.m_;
    const int right = b.h_ * 60 + b.m_;
    return std::abs(left - right);
}

inline bool earlier(const Time& a, const Time& b)
{
    return a.h_ * 60 + a.m_ < b.h_ * 60 + b.m_;
}

inline int absoluteDifferenceInline(int a, int b)
{
    return std::abs(a - b);
}

#if defined(__GNUC__) || defined(__clang__)
__attribute__((noinline))
#endif
int absoluteDifferenceOutOfLine(int a, int b)
{
    return std::abs(a - b);
}

int main()
{
    const Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';

    const Time sameA(11, 59), sameB(11, 59);
    std::cout << "same time: " << minutesBetween(sameA, sameB) << ' '
              << earlier(sameA, sameB) << '\n';

    const Time beforeNoon(11, 50), afterNoon(12, 10);
    std::cout << "across noon: " << minutesBetween(beforeNoon, afterNoon) << ' '
              << earlier(beforeNoon, afterNoon) << '\n';

    constexpr std::size_t DATA_SIZE = 4096;
    constexpr int CALLS = 10000000;
    constexpr int REPEATS = 5;
    std::array<int, DATA_SIZE> left{}, right{};
    unsigned int state = static_cast<unsigned int>(
        std::chrono::steady_clock::now().time_since_epoch().count());
    for (std::size_t i = 0; i < DATA_SIZE; ++i)
    {
        state = state * 1664525u + 1013904223u;
        left[i] = static_cast<int>(state % 1440u);
        state = state * 1664525u + 1013904223u;
        right[i] = static_cast<int>(state % 1440u);
    }

    auto inlineWork = [&left, &right]() {
        long long checksum = 0;
        for (int i = 0; i < CALLS; ++i)
        {
            const std::size_t index = static_cast<std::size_t>(i) & (DATA_SIZE - 1);
            checksum += absoluteDifferenceInline(left[index], right[index]);
        }
        return checksum;
    };
    auto outOfLineWork = [&left, &right]() {
        long long checksum = 0;
        for (int i = 0; i < CALLS; ++i)
        {
            const std::size_t index = static_cast<std::size_t>(i) & (DATA_SIZE - 1);
            checksum += absoluteDifferenceOutOfLine(left[index], right[index]);
        }
        return checksum;
    };

    std::array<double, REPEATS> inlineMs{}, outOfLineMs{};
    long long inlineChecksum = 0, outOfLineChecksum = 0;
    for (int r = 0; r < REPEATS; ++r)
    {
        auto start = std::chrono::steady_clock::now();
        inlineChecksum = inlineWork();
        auto end = std::chrono::steady_clock::now();
        inlineMs[r] = std::chrono::duration<double, std::milli>(end - start).count();

        start = std::chrono::steady_clock::now();
        outOfLineChecksum = outOfLineWork();
        end = std::chrono::steady_clock::now();
        outOfLineMs[r] = std::chrono::duration<double, std::milli>(end - start).count();
    }

    std::sort(inlineMs.begin(), inlineMs.end());
    std::sort(outOfLineMs.begin(), outOfLineMs.end());
    std::cout << "timing: calls=" << CALLS << " repeats=" << REPEATS
              << " inline_median_ms=" << inlineMs[REPEATS / 2]
              << " out_of_line_median_ms=" << outOfLineMs[REPEATS / 2]
              << " checksum_match=" << std::boolalpha
              << (inlineChecksum == outOfLineChecksum)
              << " checksum=" << inlineChecksum << '\n';
}
