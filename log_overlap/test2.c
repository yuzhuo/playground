
#include <unistd.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUF_SIZE 200 * 1024 * 1024
int main()
{
    char *buf1 = malloc(BUF_SIZE);
    char *buf2 = malloc(BUF_SIZE);
    for (int i = 0; i < BUF_SIZE; ++i) {
        buf1[i] = 'a';
        buf2[i] = 'b';
    }

    int fd = open("log", O_CREAT | O_WRONLY);// | O_APPEND);
    printf("initialization done!\n");
    pid_t pid = fork();
    if (0 == pid) {
        printf("child\n");
        write(fd, buf1, BUF_SIZE);
        /*printf("i'm child process.\n");*/
        /*int v = lseek(fd, 0, SEEK_CUR);*/
        /*printf("child: %d\n", v);*/
        close(fd);
    } else {
        printf("parent\n");
        /*int v = lseek(fd, 0, SEEK_CUR);*/
        /*printf(": %d\n", v);*/
        write(fd, buf2, BUF_SIZE);
        /*printf("spawn a child: %d\n", pid);*/
        /*v = lseek(fd, 0, SEEK_CUR);*/
        /*printf(": %d\n", v);*/
        close(fd);
    }

    return 0;
}
