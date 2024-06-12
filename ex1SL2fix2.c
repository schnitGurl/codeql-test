#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 256

// This program prints the size of a specified file in bytes
int main(int argc, char** argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Please provide a file address (using only one command as input): %s <file_path>\n", argv[0]);
        return -1;
    }

    // Prepare the command buffer, ensuring not to exceed BUFSIZE
    char cmd[BUFSIZE];
    // Use snprintf to safely format the input into the command
    int written = snprintf(cmd, BUFSIZE, "wc -c < '%s'", argv[1]);

    // Check if the command was truncated or an error occurred
    if (written >= BUFSIZE || written < 0) {
        fprintf(stderr, "Command buffer too small or error occurred.\n");
        return -1;
    }
    
    system(cmd);
    return 0;
}
