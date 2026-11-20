# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Build and run

This is a dependency-free C11 project using MinGW/GCC on Windows. Each source file is a separate executable with its own `main`; **do not link `demo.c` and `time_test.c` together**, because they also define duplicate sorting symbols.

The report mentions a Makefile, but none exists. Use direct compiler invocations from the repository root:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic demo.c -o demo.exe
gcc -std=c11 -O2 -Wall -Wextra -Wpedantic time_test.c -o time_test.exe

./demo.exe
./time_test.exe
```

Use `-O2` for meaningful benchmark results and `-g -O0` when preparing an executable for GDB.

Run the warning-only checks configured by the VS Code C/C++ Runner settings with:

```bash
gcc -std=c11 -fsyntax-only -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference demo.c
gcc -std=c11 -fsyntax-only -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wcast-align -Wconversion -Wsign-conversion -Wnull-dereference time_test.c
```

Warnings are not treated as errors. The full warning set currently reports three `-Wsign-conversion` warnings in the allocations at `time_test.c:74-76`.

## Validation

There is no automated test framework or test runner. Validation consists of running the two programs individually:

- `./demo.exe` is the deterministic correctness/trace check. Its final sorted array for both algorithms should be `13 27 38 49 49 65 76 97`.
- `./time_test.exe` is a benchmark, not a correctness test. It seeds from the current time and uses `clock()`, so timings and which algorithm appears faster can vary between runs.

## Architecture

The repository implements one sorting assignment as two deliberately independent programs:

- `demo.c` demonstrates recursive merge sort and Lomuto-partition quicksort on the fixed eight-element input `{49, 38, 65, 97, 76, 13, 27, 49}`. Merge sort prints the whole array after every recursive merge; quicksort prints after every partition using the rightmost element as the pivot. Tracing is embedded in `mergeSort` and `partition`, and the trace loops use the compile-time `N`, so changing the demonstration size requires updating both `N` and the input data.
- `time_test.c` contains matching sorting implementations without trace output. For each size in `test_size`, it creates one random input, sorts a copy with each algorithm, and times only the sorting calls. Merge sort requires the caller-provided `tmp` buffer; quicksort operates in place but uses recursive stack space. The benchmark sizes and random-data generation are in `main` and `randomArray`.

The Chinese `.docx` report is the assignment/design reference and includes the intended algorithm analysis and program output. It is documentation, not a build input, and is excluded by `.gitignore` along with generated executables and `.vscode/`.

## Editor configuration

`.vscode/settings.json` selects `gcc`/`gdb` and defines the warning flags above. Other VS Code settings are machine-specific: `c_cpp_properties.json` contains an absolute compiler path, and `launch.json` points to an older workspace location and `build/Debug/outDebug`. The direct GCC commands above are the reliable build path unless those local paths are corrected.
