// Q7 prediction before execution: both implementations keep identical data,
// while circular insertion time should grow less as capacity grows. Shifting is
// O(k) once full; ring insertion is O(1). The workflow reports medians of 5 runs.
#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <memory>

class ShiftHistory
{
    std::unique_ptr<unsigned long long[]> data_;
    std::size_t capacity_;
    std::size_t count_ = 0;

public:
    explicit ShiftHistory(std::size_t capacity)
        : data_(new unsigned long long[capacity]), capacity_(capacity) {}

    void push(unsigned long long value)
    {
        if (count_ < capacity_)
            data_[count_++] = value;
        else
        {
            for (std::size_t i = 1; i < capacity_; ++i)
                data_[i - 1] = data_[i];
            data_[capacity_ - 1] = value;
        }
    }

    std::size_t size() const { return count_; }
    unsigned long long at(std::size_t i) const { return data_[i]; }
};

class RingHistory
{
    std::unique_ptr<unsigned long long[]> data_;
    std::size_t capacity_;
    std::size_t count_ = 0;
    std::size_t oldest_ = 0;

public:
    explicit RingHistory(std::size_t capacity)
        : data_(new unsigned long long[capacity]), capacity_(capacity) {}

    void push(unsigned long long value)
    {
        if (count_ < capacity_)
        {
            data_[(oldest_ + count_) % capacity_] = value;
            ++count_;
        }
        else
        {
            data_[oldest_] = value;
            oldest_ = (oldest_ + 1) % capacity_;
        }
    }

    std::size_t size() const { return count_; }
    unsigned long long at(std::size_t i) const
    {
        return data_[(oldest_ + i) % capacity_];
    }
};

template <typename History>
double run(History& history, std::size_t operations)
{
    const auto start = std::chrono::steady_clock::now();
    for (std::size_t i = 0; i < operations; ++i)
    {
        const unsigned long long value =
            (static_cast<unsigned long long>(i) * 1103515245ULL + 12345ULL) % 1000003ULL;
        history.push(value);
    }
    const auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}

bool sameContents(const ShiftHistory& shifted, const RingHistory& ring)
{
    if (shifted.size() != ring.size())
        return false;
    for (std::size_t i = 0; i < shifted.size(); ++i)
        if (shifted.at(i) != ring.at(i))
            return false;
    return true;
}

int main()
{
    constexpr std::size_t OPERATIONS = 50000;
    constexpr std::size_t REPEATS = 5;
    const std::size_t capacities[] = {10, 50, 100, 500, 1000};
    std::cout << "operations_per_run=" << OPERATIONS
              << " repeats=" << REPEATS << '\n';
    for (std::size_t capacity : capacities)
    {
        ShiftHistory shifted(capacity);
        RingHistory ring(capacity);
        std::array<double, REPEATS> shiftMs{}, ringMs{};
        for (std::size_t repeat = 0; repeat < REPEATS; ++repeat)
        {
            shiftMs[repeat] = run(shifted, OPERATIONS);
            ringMs[repeat] = run(ring, OPERATIONS);
        }
        std::sort(shiftMs.begin(), shiftMs.end());
        std::sort(ringMs.begin(), ringMs.end());

        const bool equal = sameContents(shifted, ring);
        unsigned long long checksum = 0;
        for (std::size_t i = 0; i < ring.size(); ++i)
            checksum += ring.at(i);

        std::cout << "capacity=" << capacity
                  << " shift_median_ms=" << shiftMs[REPEATS / 2]
                  << " ring_median_ms=" << ringMs[REPEATS / 2]
                  << " same_contents=" << std::boolalpha << equal
                  << " checksum=" << checksum << '\n';
    }
}
