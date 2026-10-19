# Problem Tracker

A command-line C++ program for logging coding problems, with notes and mistake counts, so you can review them later.

## Features

- Add, show, delete, edit, and search problems by tag
- Save problems to `problems.txt` on exit and load them on startup

## Build and Run

```
c++ -std=c++17 core.cpp -o core
./core
```

For multi-line code or notes, type `END` on a new line to finish.

## Simplicity

- A single source file, `core.cpp`, using only the C++ standard library.
- Data is kept in memory during a session and written to a plain text file.

## Limitations

- **Saves only on exit:** choose 6 to save. Quitting with Ctrl+C loses changes made in that session.
- **Tags aren't unique:** delete, edit, and search act on the first match.
- **Limited input validation:** typing text where a number is expected can break input.
- **Search is by tag only.**
- **Multi-line input ends at a line reading `END`.**