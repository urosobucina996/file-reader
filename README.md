# File Watcher in C

This is a simple C program that monitors a text file (`data.txt`) for changes.

The program reads the entire file into memory and displays its contents in the terminal. It continuously checks whether the file size has changed, and if it detects an update, it reallocates the buffer if necessary and reloads the file. The terminal is refreshed every second to always show the latest contents.

## Build

```bash
gcc main.c -o main
```

## Run

```bash
./main
```

Then edit `data.txt` while the program is running to see the changes appear in the terminal.