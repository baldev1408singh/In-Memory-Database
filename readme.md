# In-Memory Database

A command-line key-value database written in C. Data is stored in memory
using a linked list built from scratch with `malloc` and `free`, with no
database or caching libraries.

## Features

- `SET`, `GET`, `DEL` and `EXISTS` commands
- `SAVE <filename>` and `LOAD <filename>` to write and read data from a file
- Automatic load on startup and save on exit (`auto.txt`)
- Input validation and clear error messages


## Commands

Commands are written in uppercase. Keys are single words. Values can
contain spaces.

| Command | What it does |
|---|---|
| `SET <key> <value>` | Stores a value, or replaces it if the key exists |
| `GET <key>` | Prints the value, or an error if the key is missing |
| `DEL <key>` | Deletes a key |
| `EXISTS <key>` | Prints `True` or `False` |
| `SAVE <filename>` | Writes all data to a file |
| `LOAD <filename>` | Reads a file and adds its data |
| `PRINT` | Shows everything stored |
| `EXIT` | Saves to `auto.txt` and quits |
| `DEL_ALL` | Deletes everything stired|

## Example

```
>>>>> SET city New Delhi
OK
>>>>> GET city
New Delhi
>>>>> EXISTS city
True
>>>>> DEL city
ok
>>>>> GET city
ERROR: key 'city' not found
```