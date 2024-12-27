#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

void* get_tasks_info(void* arg) {
    while (1) {
        int fd;
        char buf[256];
        ssize_t bytesRead;

        fd = open("/dev/kernel_tasks", O_RDONLY);
        if (fd == -1) {
            perror("Failed to open device file");
            continue;
        }

        while ((bytesRead = read(fd, buf, sizeof(buf) - 1)) > 0) {
            buf[bytesRead] = '\0';
            printf("%s", buf);
        }

        close(fd);

        // Sleep for 2 seconds
        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t t1;

    // Create a new thread to run get_tasks_info
    if (pthread_create(&t1, NULL, get_tasks_info, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish (in this case, it never does)
    pthread_join(t1, NULL);

    return 0;
}

