
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
    int fd = open("log", O_CREAT | O_WRONLY);// | O_APPEND);
    pid_t pid = fork();
    if (0 == pid) {
        write(fd, "msg 1", 5);
        close(fd);
    } else {
        write(fd, "msg 23", 6);
        close(fd);
    }

    return 0;
}
