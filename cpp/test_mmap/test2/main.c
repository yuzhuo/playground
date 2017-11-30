
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main()
{
    int fd = open("test", O_RDWR);
    char* str = (char*)mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    /*printf("%d\n", sysconf(_SC_PAGE_SIZE));*/
    char buf[16];
    str[1] = 'x';
    strncpy(buf, str, 10);
    buf[10] = 0;
    printf("%s\n", buf);

    munmap(str, 10);

    return 0;
}
