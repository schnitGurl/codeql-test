#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 256

// Function to escape shell metacharacters
void sanitize_input(const char* input, char* sanitized, size_t buf_size)
{
    const char* metacharacters = " '\";|&<>$\\`";
    size_t i, j = 0;

    for (i = 0; i < strlen(input) && j < buf_size - 1; ++i)
    {
        if (strchr(metacharacters, input[i]))
        {
            if (j < buf_size - 2)
            {
                sanitized[j++] = '\\';
            }
            else
            {

                break;
            }
        }
        sanitized[j++] = input[i];
    }
    sanitized[j] = '\0';
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Please provide a file address (using only one command as input): %s <file_path>\n", argv[0]);
        return -1;
    }

    char sanitized_input[BUFSIZE];
    sanitize_input(argv[1], sanitized_input, BUFSIZE);

    // Prepare the command buffer, ensuring not to exceed BUFSIZE
    char cmd[BUFSIZE];
    int written = snprintf(cmd, BUFSIZE, "wc -c < '%s'", sanitized_input);

    if (written >= BUFSIZE || written < 0) {
        fprintf(stderr, "Command buffer too small or error occurred.\n");
        return -1;
    }

    system(cmd);
    return 0;
}
