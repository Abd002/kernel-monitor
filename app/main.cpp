#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <chrono>

void get_tasks_info(int id){
    while(1){
        int fd;
        char buf[256];

        ssize_t bytesRead;

        fd = open("/dev/kernel_tasks", O_RDONLY);
        if (fd == -1) {
            perror("Failed to open device file");
            continue;
        }
        while((bytesRead =read(fd, buf, sizeof(buf) - 1)>0)){
            buf[bytesRead] = '\0';
            std::cout<<buf;
        }

        close(fd);

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
} 

int main(){


    std::thread t1(get_tasks_info, 1);


    t1.join();

    return 0;
}
