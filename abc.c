#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define BUFSIZE 256

// Function to validate the file path
int is_valid_file_path(const char *path) 
{
    // Check each character in the string
    for (const char *p = path; *p; p++) 
    {
        if (!isalnum((unsigned char)*p) && *p != '.' && *p != '-' && *p != '_') 
        {
            return 0;
        }
    }
    
    return 1;
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv)
{
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return -1;
    }
    
    // Validate the file path
    if (!is_valid_file_path(argv[1])) {
        fprintf(stderr, "Invalid file path.\n");
        return -1;
    }

    // Prepare the command buffer, ensuring not to exceed BUFSIZE
    char cmd[BUFSIZE];
    int written = snprintf(cmd, BUFSIZE, "wc -c < '%s'", argv[1]);

    if (written >= BUFSIZE || written < 0) {
        fprintf(stderr, "Command buffer too small or error occurred.\n");
        return -1;
    }
    
    system(cmd);
    return 0;
}
