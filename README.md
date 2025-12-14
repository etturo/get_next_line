*This project has been created as part of the 42 curriculum by eturini.*

# Get Next Line

## Description
**Get Next Line** is a project at that challenges students to create a function capable of reading a text file (or any file descriptor) one line at a time. The goal is to learn about static variables, file descriptors, memory management, and the lifecycle of a buffer.

This function allows reading from a file descriptor until a newline character is found or the end of the file is reached, returning the line read.

## Instructions

### Compilation
To compile the project, you can use `gcc` (or `cc`). You must define the `BUFFER_SIZE` macro at compilation time to determine the size of the read buffer.

**Mandatory:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

**Bonus:**
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

### Usage
To use `get_next_line` in your own project:
1. Include the header file: `#include "get_next_line.h"`
2. Call the function in a loop:
```c
int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL)
{
    printf("%s", line);
    free(line);
}
close(fd);
```

## Algorithm Explanation & Justification

The algorithm implemented relies on the use of a **static variable** (`stash`) to persist data between function calls. This is crucial because `get_next_line` may be called multiple times, and any data read from the file but not yet returned (because it was after the newline) must be saved for the next call.

### Steps:
1.  **Read & Accumulate:** The function reads `BUFFER_SIZE` bytes from the file descriptor into a temporary buffer. This buffer is immediately appended to the static `stash` string using `ft_strjoin`. This process repeats in a loop until a newline character (`\n`) is found in the stash or the End of File (EOF) is reached.
2.  **Extract Line:** Once a newline is detected (or EOF), the function identifies the substring from the start of the `stash` up to and including the newline. This substring is allocated and returned as the result.
3.  **Update Stash:** The remaining part of the `stash` (everything after the newline) is saved. A new string is allocated for this remainder, the old `stash` is freed, and the static pointer is updated to point to the new remainder.

### Justification:
This "String Stash" approach was selected for its **readability and simplicity**. By treating the accumulated data as a standard C string, we can utilize familiar string manipulation logic. While this approach involves repeated memory allocation and copying (which can be slower with extremely small buffer sizes), it provides a robust and easy-to-debug solution for standard use cases, ensuring no memory leaks occur through careful management of the static pointer.
It would have been better if I had used linked list, because in every node i would have stored the red buffer, and only when a `EOF` or a `\n` is found the copy starts, using only one copy per line and not every iteration.

## Bonus Part

The bonus version of **Get Next Line** includes support for managing **multiple file descriptors** simultaneously.

### How it works
To handle multiple files without losing the reading progress of each, the single static `stash` variable is replaced by an array of pointers:
`static char *stash[__FD_SETSIZE];`

`__FD_SETSIZE` is a macro that takes the linux shell command: `ulimit -a` in the section of **open files**, can be used also the command `ulimit -n` to see specifically the number of **open files**.

```bash
ulimit -a   #to see the max of all the internal values of computer
ulimit -n   #to only see the number of file descriptors can the computer handle
```

Each index of this array corresponds to a file descriptor, allowing the function to store the specific buffer for each open file independently. This enables interleaved calls to `get_next_line` with different file descriptors (e.g., reading line 1 from file A, then line 1 from file B, then line 2 from file A).

## Resources

### References
- [man read(2)](https://man7.org/linux/man-pages/man2/read.2.html)
- [man malloc(3)](https://man7.org/linux/man-pages/man3/malloc.3.html)
- [File Descriptors explained](https://en.wikipedia.org/wiki/File_descriptor)

### AI Usage
Artificial Intelligence was used in this project for the following task:
- **Performance Optimization:** Understanding the algorithmic complexity ($O(N^2)$) associated with `ft_strjoin` when using a `BUFFER_SIZE` of 1, and exploring alternative data structures.
