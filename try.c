#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#define BUFSIZE 256

int is_valid_file_path(const char* path)
{
    struct stat statbuf;
    if (stat(path, &statbuf) != 0)
    {
        return 0;
    }

    if (S_ISREG(statbuf.st_mode))
    {
        // The path is a regular file
        return 1;
    }
    // The path is not a regular file
    return 0;
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return -1;
    }

    // Check if the input is a valid file path
    if (!is_valid_file_path(argv[1])) {
        fprintf(stderr, "Invalid file path.\n");
        return -1;
    }

    // Prepare the command buffer, ensuring not to exceed BUFSIZE
    char cmd[BUFSIZE];
    int written = snprintf(cmd, BUFSIZE, "wc -c < '%s'", argv[1]);

    // Check if the command was truncated or an error occurred
    if (written >= BUFSIZE || written < 0) {
        fprintf(stderr, "Command buffer too small or error occurred.\n");
        return -1;
    }

    system(cmd);
    return 0;
}
