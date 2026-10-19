# Problem Tracker

A command-line C++ program for logging coding problems, along with your notes and mistake counts, so you can review them later.

## Features

- Add a problem with its code, optional notes, tag number, and mistake count
- Show all problems
- Delete a problem by tag
- Edit a problem by tag
- Search for a problem by tag

## Build


## Simplicity

- A single source file, `core.cpp`, using only the C++ standard library.
- Stores everything in memory, with no database or file format.

## Limitations

- **No saving:** all problems are lost when the program exits.
- **Tags aren't unique:** delete, edit, and search act on the first match.
- **Limited input validation:** typing text where a number is expected can break input.
- **Search is by tag only.**
- **Multi-line input ends at a line reading `END`.**
