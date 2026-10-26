# DSA Assignment 2 Report

**Student:** Mohamed Haarun M.H  
**Register number:** 192524430  
**Course focus:** C++ functions and object-oriented concepts  
**Submission date stated in assignment:** 31 October 2026  
**Repository:** https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment2

> **AI assistance:** The student stated that faculty permitted full AI assistance. The code and explanations in this repository were prepared with ChatGPT. The student should review the implementation and be able to explain it during the course verification.

## Environment and execution method

The programs were built and run by GitHub Actions on Ubuntu 24.04 with **g++ 13.3.0**. Standard compile command:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic <source.cpp> -o <program>
```

Q6 was additionally compiled using `-O0` and `-O2`; Q7 used `-O2`. The successful validation run is [GitHub Actions run 40336138680](https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment2/actions/runs/40336138680). Per-task console transcripts are stored beside their source files and the run has an `assignment-run-evidence` artifact containing the complete raw logs.

## Q1 — Call by value, reference, and pointer (6 marks)

### Prediction

Before the first validation run, the predicted first three output lines were:

```text
1 12 13
1 100
16 13 6 
```

The predicted concession results were 45000 for the value parameter and 40500 for both the reference and pointer. Applying 10%, 15%, then 25% sequentially was predicted to produce 25819 because each integer percentage calculation truncates the fractional discount.

### Observed result

The output matched:

```text
1 12 13
1 100
16 13 6 
after call by value    : 45000
after call by reference: 40500
after call by pointer  : 40500
after 10%, 15%, 25% in sequence: 25819
```

`a` is passed as a copy, so incrementing the local parameter does not change the caller's `a`. `b` aliases the caller's object and `c` points to the caller's object, so those values change. `bigger` returns a reference to the larger argument; after `change`, `c` is 13 and is larger, so assignment through the returned reference sets `c` to 100. The calls `show(1)`, `show(1,2)`, and `show(1,2,3)` use (y,z) defaults (5,10), (z) default 10, and no defaults respectively.

A const reference is suitable for a large read-only object: it avoids a copy and prevents writes through that parameter. The concession function uses a reference because its name and purpose imply changing the caller's stored fee. Returning a new fee would also be a sound design where immutable transformations or explicit assignment are preferred. The pointer version checks for null.

**Complexity:** Each update performs a constant number of arithmetic operations: O(1) time. Passing a long long by value copies a fixed-size scalar; copying a large Student by value copies its members. References and pointers avoid that object copy.

Source and transcript: [Q1 source](Task01/value_reference_pointer.cpp), [Q1 output](Task01/actions_output.txt).

## Q2 — Return by reference and its dangers (4 marks)

### Prediction and observed result

The highest value is initially 91. The function returns a reference to the first maximum, at index 1. Adding 2 through that reference changes the array element to 93. The run showed:

```text
highest before: 91
array after reference moderation: 78 93 84 91 88
index alternative points to: 93
pointer alternative points to: 93
copy remains independent: 93
```

The array is non-empty for this example; the search helpers require that precondition. Returning an `int&` gives the caller a writable alias to the array element. A `const int&` would allow reading but not writing through that name. Returning `int` gives a safe copy that cannot change the array. An index gives the caller a location to re-access, but should be bounds-checked; a pointer needs valid lifetime and null handling.

The warning-only source was compiled but not executed. GCC emitted `-Wreturn-local-addr` for returning a reference to `local`. The local object's lifetime ends when the function returns, so using the returned reference would be undefined behavior. A vector may reallocate as it grows, invalidating element references and pointers obtained before reallocation; indices remain meaningful only if the logical element ordering is preserved.

**Complexity:** Finding the maximum is O(n) time and O(1) extra space; returning the reference, index, pointer, or copy is O(1) after the search.

Source and transcript: [Q2 source](Task02/marks_register.cpp), [warning example](Task02/dangling_reference_warning.cpp), [Q2 output and diagnostic](Task02/actions_output.txt).

## Q3 — Default arguments and function overloading (6 marks)

The original set is ambiguous for a one-argument call because both `charge(double)` and `charge(double,bool=false,bool=false)` can accept it. The revised set uses one overload for grams, one for kilograms, and one for a Parcel, with optional express and insurance flags on the numeric overloads.

The six predictions were: `charge(2)` selects the int overload by exact match; `charge(2.0)` selects double exactly; `charge(2.0f)` promotes float to double, which is better than converting float to int; `charge(250)` and `charge(1250,true)` select int exactly; and a Parcel argument selects the Parcel overload.

The run reported the predicted overload for all six calls. Charges use $50 per kilogram, plus $20 for express and $10 for insurance. The Parcel overload accepts a const reference to avoid copying. Default arguments must be trailing because callers cannot omit an earlier required argument while supplying a later one.

A single Parcel struct can group optional fields and makes a new option easy to add without extending every signature. It makes simple calls more verbose and requires callers to construct or initialize a Parcel. A template can support multiple numeric types, but explicit unit distinctions still matter: a template alone does not explain whether a number means grams or kilograms.

**Complexity:** Overload selection occurs at compile time and adds no runtime dispatch. Computing the charge is O(1). Passing Parcel by const reference avoids copying its fields.

Source and transcript: [Q3 source](Task03/courier.cpp), [Q3 output](Task03/actions_output.txt).

## Q4 — Savings account with an array (6 marks)

`SavingsAccount` keeps its account number, balance, ten transaction records, and count private. Deposit is defined inside the class; withdrawal and mini-statement are defined outside using the scope operator. The methods reject non-positive deposits/withdrawals and reject withdrawals above the current balance.

The implementation uses a fixed array and shifts retained records left when the eleventh transaction arrives, then appends the new one. This is simple to print in chronological order. With 10 entries it moves at most 9 records per accepted insertion after the array is full; if capacity is k, insertion costs O(k). A circular index overwrites the oldest entry in O(1) time but makes chronological printing more involved. For 50 transactions, the circular buffer avoids repeatedly moving records and is the chosen redesign direction.

The run made eleven accepted operations (an initial deposit, one withdrawal, and nine later deposits). The mini-statement showed the latest ten, beginning with the withdrawal. A $5000 withdrawal was rejected, did not change the balance or history, and the final balance was $1300.00.

A deque can also append and remove from opposite ends in amortized/constant time, but the fixed circular array provides a clear bounded-memory design. Shifting may remain preferable when the limit is tiny and simplicity matters more than the small amount of movement.

**Space:** The fixed transaction array uses O(k) storage, where k is 10 in this implementation.

Source and transcript: [Q4 source](Task04/savings_account.cpp), [Q4 output](Task04/actions_output.txt).

## Q5 — Static members and arrays of objects (7 marks)

`BusTicket::issued` is static because the issued-seat count belongs to the class, not an individual ticket. It is defined once outside the class. The constructor assigns seats 1 through 3 and leaves later tickets on the waiting list without increasing the seat count. `count()` is static and accesses only static state; it has no `this` object and cannot access an individual ticket's non-static name or seat.

For the Token program, the predicted output was `101 103 104 4`: the three array elements receive IDs 101–103, the extra object receives 104, and four constructions have occurred. The observed output matched. The four-ticket array assigned three seats and put Dev on the waiting list. A function called twice created two more waiting-list tickets; the count remained 3.

A global count also has one shared value but weakens encapsulation. A TicketOffice object passed to each ticket makes the owner explicit and supports two buses with separate capacity and count. A single static counter is appropriate only when all tickets share one global capacity.

**Complexity:** Creating or querying a ticket is O(1); the array of n ticket objects uses O(n) space.

Source and transcript: [Q5 source](Task05/static_members.cpp), [Q5 output](Task05/actions_output.txt).

## Q6 — Friend and inline functions (8 marks)

The friend functions convert each time to minutes after midnight. The predicted output for 09:45 and 13:10 was `205 false`; the observed result matched. Additional tests returned 0 minutes and false for equal times, and 20 minutes and true for 11:50 compared with 12:10.

A friend is a non-member function that has access to private fields and treats the two times symmetrically. A member call such as `departure.minutesTo(arrival)` is also reasonable but makes one object the apparent receiver. Getters avoid friendship but expose accessors that may not otherwise be part of the class interface. The fields remain private.

### Timing method and results

The experiment used a fixed deterministic input array and five runs of 10,000,000 calls for each implementation. The table reports the median on a GitHub-hosted Ubuntu 24.04 runner with g++ 13.3.0.

| Build | Inline median | Out-of-line median | Checksum |
|---|---:|---:|---:|
| `-O0` | 55.8009 ms | 56.1739 ms | 4,805,418,226 |
| `-O2` | 7.19487 ms | 15.5535 ms | 4,805,418,226 |

At `-O0`, the times were nearly equal. At `-O2`, the inline version was about 2.16 times faster than the deliberately non-inlined comparison. This benchmark uses GCC/Clang's `noinline` attribute on the out-of-line function to preserve the contrast; `inline` is a language linkage/definition rule and an optimization hint, not a guarantee that the compiler substitutes a call. Results are hardware- and load-dependent and should not be treated as a universal speedup.

**Complexity:** Each time comparison is O(1), with O(1) additional space.

Source and transcript: [Q6 source](Task06/time_friend_inline.cpp), [Q6 output and timings](Task06/actions_output.txt).

## Q7 — Diagnose, redesign, validate (13 marks)

### A. Diagnosis

Q4's shifting history must move each retained record on every insertion after reaching capacity. The number of moves grows with k, making the insertion O(k).

### B. Objective

Keep exactly the latest k records in chronological order while reducing the insertion operation to O(1), without changing the retained results.

### C. Redesign

The benchmark uses two custom array-backed classes rather than replacing the solution with a library container. The shift design appends until full, then moves entries left before adding the new record. The ring design tracks the oldest slot and overwrites it, advancing the start index. Both allocate k values, so both use O(k) space. The ring adds index arithmetic when reading in chronological order.

### D. Prediction

Both designs should retain the same latest entries. As capacity grows, shift insertion time should rise with k; ring insertion time should stay approximately flat.

### E. Validation

The benchmark ran 50,000 pushes per run, five times at each capacity, and reports median time. All capacities reported `same_contents=true`, confirming output equivalence. At capacity 1000, shifting took 6.37392 ms and the ring took 0.169989 ms, about 37.5 times faster in this measured workload. At capacity 10 the times were 0.363243 ms and 0.169579 ms. The ring time stayed near 0.17 ms while shifting rose with capacity.

### F. Evaluation

The measured results support the objective for this synthetic fixed-size workload. The ring design avoids record movement but requires correct wraparound indexing and more careful statement traversal. Shifting is easier to understand for a very small limit. The measurement is from a shared hosted runner and a simple numeric-record benchmark; performance will vary by hardware and transaction type.

Source and transcript: [Q7 benchmark](Task07/history_redesign_benchmark.cpp), [Q7 output](Task07/actions_output.txt).

## Evidence note

The repository contains source code, predictions in source comments, per-task console transcripts, the compiler warning, the Q6 timing table, and Q7 comparison. The transcripts came from the successful GitHub Actions run and are also available in its [run page and artifact](https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment2/actions/runs/40336138680). The Actions runner produced raw terminal transcripts rather than desktop screenshot images; if the course requires literal screenshots, those need to be captured from the visible run output and added to each task folder.
