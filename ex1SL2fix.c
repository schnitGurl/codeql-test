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
        fprintf(stderr, "Please provide a file address: %s <file_path>\n", argv[0]);
        return -1;
    }

    // Prepare the arguments for the 'wc' command
    char *args[] = {"wc", "-c", NULL, NULL};
    args[2] = argv[1];

    // Execute the 'wc' command using execvp
    execvp("wc", args);

    // If execvp returns, it means it has failed
    perror("execvp failed");
    return -1;
}
