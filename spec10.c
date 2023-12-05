//COVERED PIPES + I/O  IN spec11


/*


int main() {
    int pipefd[2]; // File descriptors for the pipe
    pid_t child_pid;

    // Create the pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Create a child process
    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        close(pipefd[1]); // Close the write end of the pipe (not needed)

        char buffer[256];
        // Read data from the pipe
        ssize_t num_bytes = read(pipefd[0], buffer, sizeof(buffer));
        ///////////////* /////
        int index = 0;  its explanation
        char ch;

        while (read(pipefd[0], &ch, 1) > 0) {
            if (ch == '\0') {
                break; // Null character marks the end of the string
            }
            buffer[index++] = ch;
        }
        buffer[index] = '\0';
	////* ////////////////
	
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        // Null-terminate the received data
        buffer[num_bytes] = '\0';

        printf("Child Process Received: %s\n", buffer);

        close(pipefd[0]); // Close the read end of the pipe

        exit(EXIT_SUCCESS);
    } else {
        // Parent process
        close(pipefd[0]); // Close the read end of the pipe (not needed)

        char message[] = "Hello, Child Process!";
        
        // Write data to the pipe
        ssize_t num_bytes = write(pipefd[1], message, strlen(message));
        if (num_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]); // Close the write end of the pipe

        // Wait for the child process to finish
        wait(NULL);

        exit(EXIT_SUCCESS);
    }

    return 0;
}
The pipe is created using pipe, creating a unidirectional communication channel between the parent and child.

The child process is forked using fork. At this point, both the parent and child have a copy of the file descriptors for the pipe.

In the child process, the code immediately closes the write end of the pipe using close(pipefd[1]), indicating that it won't write to the pipe.

The child process enters a loop to read from the read end of the pipe (pipefd[0]) character by character until it encounters a null character ('\0') or until the pipe is closed. It stores the characters in a buffer and null-terminates the string.

In the parent process, the code closes the read end of the pipe using close(pipefd[0]), indicating that it won't read from the pipe.

The parent process writes the message to the pipe using write, including the null terminator.

The child process reads the message from the pipe
*/
