#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main()
{
    int fd = open("test_file", O_RDWR);

    struct stat stat_buf;
    fstat(fd, &stat_buf);
    printf("stat size: %d\n", stat_buf.st_size);

    int offset = lseek(fd, 0, SEEK_CUR);
    printf("current location: %d\n", offset);

    offset = lseek(fd, 0, SEEK_END);
    printf("file size: %d\n", offset);

    offset = lseek(fd, 0, SEEK_SET);
    printf("set localtion to 0\n");

    offset = lseek(fd, 0, SEEK_CUR);
    printf("current location: %d\n", offset);

    int buf[16];
    int ncount = read(fd, &buf, 12);
    printf("%d characters read\n", ncount);

    offset = lseek(fd, 0, SEEK_SET);
    printf("set localtion to 0\n");

    char *pc = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    /*char *pc = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);*/
    strcpy(pc, "abcde");

    sleep(10);

    munmap(pc, 10);

    close(fd);

    return 0;
}
