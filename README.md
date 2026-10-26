# DSA Assignment 2

**Student:** Mohamed Haarun M.H  
**Register number:** 192524430  
**Assignment date in the PDF:** 31 October 2026  
**Repository:** https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment2

This repository contains the seven task programs, an explanatory report, console transcripts from a successful GitHub Actions run, and a workflow that rebuilds and runs the programs.

**AI assistance:** Code and report were prepared with ChatGPT after the student stated that faculty authorized full AI assistance. Review the code and explanations and be prepared to discuss them.

## Environment

- Compiler: GitHub-hosted Ubuntu 24.04, g++ 13.3.0
- Standard: C++17
- Common warning build: `g++ -std=c++17 -Wall -Wextra -pedantic`
- Validation workflow: [run 40336138680](https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment2/actions/runs/40336138680)
- Full transcript artifact: available from the Actions run page; per-task transcripts are also committed in each Task folder.

## Compile and run

Run these commands from the repository root:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic Task01/value_reference_pointer.cpp -o q1 && ./q1
g++ -std=c++17 -Wall -Wextra -pedantic Task02/marks_register.cpp -o q2 && ./q2
g++ -std=c++17 -Wall -Wextra -Wreturn-local-addr -c Task02/dangling_reference_warning.cpp -o q2-warning.o
g++ -std=c++17 -Wall -Wextra -pedantic Task03/courier.cpp -o q3 && ./q3
g++ -std=c++17 -Wall -Wextra -pedantic Task04/savings_account.cpp -o q4 && ./q4
g++ -std=c++17 -Wall -Wextra -pedantic Task05/static_members.cpp -o q5 && ./q5
g++ -std=c++17 -Wall -Wextra -pedantic -O0 Task06/time_friend_inline.cpp -o q6-o0 && ./q6-o0
g++ -std=c++17 -Wall -Wextra -pedantic -O2 Task06/time_friend_inline.cpp -o q6-o2 && ./q6-o2
g++ -std=c++17 -Wall -Wextra -pedantic -O2 Task07/history_redesign_benchmark.cpp -o q7 && ./q7
```

## Tasks and observed result notes

- **Q1:** Confirmed value versus alias behavior, the returned reference from `bigger`, default arguments, and the fee outputs 45000/40500/40500.
- **Q2:** Moderated the first highest array value through a returned reference; captured GCC's `-Wreturn-local-addr` diagnostic for the unsafe local-reference example. That example is compiled only and never executed.
- **Q3:** Six calls selected the intended int, double, and Parcel overloads. The float argument selected double by promotion.
- **Q4:** The private fixed array retained the latest ten accepted transactions by shifting. An overdraw attempt was rejected; final balance was $1300.00.
- **Q5:** Three seats were assigned and later tickets waited; the shared count remained three. The Token prediction matched `101 103 104 4`.
- **Q6:** Correctness cases returned 205/false, 0/false, and 20/true. Five-run medians were 55.8009 vs 56.1739 ms at `-O0`, and 7.19487 vs 15.5535 ms at `-O2` (inline vs out-of-line).
- **Q7:** For 50,000 insertions at capacity 1000, the five-run median was 6.37392 ms for shifting and 0.169989 ms for the ring; both retained identical contents.

See [REPORT.md](REPORT.md) for predictions, explanations, alternatives, complexity analysis, measurement method, and limitations.

## Evidence

- Q1: [source](Task01/value_reference_pointer.cpp), [transcript](Task01/actions_output.txt)
- Q2: [source](Task02/marks_register.cpp), [warning example](Task02/dangling_reference_warning.cpp), [transcript](Task02/actions_output.txt)
- Q3: [source](Task03/courier.cpp), [transcript](Task03/actions_output.txt)
- Q4: [source](Task04/savings_account.cpp), [transcript](Task04/actions_output.txt)
- Q5: [source](Task05/static_members.cpp), [transcript](Task05/actions_output.txt)
- Q6: [source](Task06/time_friend_inline.cpp), [timing transcript](Task06/actions_output.txt)
- Q7: [benchmark](Task07/history_redesign_benchmark.cpp), [benchmark transcript](Task07/actions_output.txt)

The CI run provides actual console transcripts. It did not capture desktop screenshot images; add literal screenshots from the run page if your instructor requires image files in each task folder.
