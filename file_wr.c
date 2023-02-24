#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_NAME "./new_file"

int main(int c, char **v)
{
    int fd, i = 0;
    size_t ret, count = strlen(v[1]);
    char buf[50];
    
    fd = open(FILE_NAME, O_CREAT | O_RDWR, S_IRWXO | S_IRWXU | S_IRWXG);
    if(fd < 0){
        printf("Can't create file\n");
        return 1;
    }

    ret = write(fd, v[1], count);
    if(ret < 0){
        printf("Can't write to file\n");
        close(fd);
        return 1;
    }

    ret = lseek(fd, 0, SEEK_END);
    if(ret < 0){
        printf("Can't get file offset\n");
        close(fd);
        return 1;
    }

    count = ret;
    
    while(count--)
    {
        ret = lseek(fd, count, SEEK_SET);
        if(ret < 0){
            printf("Can't get file offset\n");
            close(fd);
            return 1;
        }
        ret = read(fd, &buf[i++], 1);
        if(ret < 0){
            printf("Can't read from file\n");
            close(fd);
            return 1;
        }
    }

    close(fd);

    printf("%s\n", buf);

    return 0;
}


