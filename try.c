#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 256

// Function to escape shell metacharacters
char* shellescape(const char* input) {
    if (input == NULL) return NULL;

    size_t len = strlen(input);

    // Allocate memory for the worst-case scenario (all characters need to be escaped)
    char* escaped = malloc(2 * len + 1);
    if (escaped == NULL) return NULL;

    const char* special_chars = " '\";|&<>$\\`!*?{}";
    char* p = escaped;

    for (size_t i = 0; i < len; ++i)
    {
        if (strchr(special_chars, input[i]) != NULL)
        {
            *p++ = '\\';
        }
        *p++ = input[i];
    }
    *p = '\0';

    return escaped;
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    // Escape the user input
    char* escaped_input = shellescape(argv[1]);
    if (escaped_input == NULL) {
        fprintf(stderr, "Failed to allocate memory for escaped input.\n");
        return -1;
    }

    // Prepare the command buffer, ensuring not to exceed BUFSIZE
    char cmd[BUFSIZE];
    int written = snprintf(cmd, BUFSIZE, "wc -c < '%s'", escaped_input);

    // Free the allocated memory for the escaped input
    free(escaped_input);

    // Check if the command was truncated or an error occurred
    if (written >= BUFSIZE || written < 0) {
        fprintf(stderr, "Command buffer too small or error occurred.\n");
        return -1;
    }

    system(cmd);
    return 0;
}
