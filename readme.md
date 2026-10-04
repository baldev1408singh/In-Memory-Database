# In-Memory Database

A command-line key-value database written in C. Data is stored in memory
using a linked list built from scratch with `malloc` and `free`, with no
database or caching libraries.

## Features

- `SET`, `GET`, `DEL` and `EXISTS` commands
- `SAVE <filename>` and `LOAD <filename>` to write and read data from a file
- Automatic load on startup and save on exit (`auto.txt`)
- Input validation and clear error messages