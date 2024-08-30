#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SZ (4 * 1024 * 1024)

static void change(char *buf, int *len);

int main(int argc, void* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s file_path\n", argv[0]);
        return -1;
    }
    char *buf = malloc(BUF_SZ);
    if (!buf)
    {
        printf("Malloc fail\n");
        return -1;
    }
    int fd = open(argv[1], O_RDWR);
    if (fd < 0)
    {
        printf("file open fail\n");
        return -1;
    }
    int len = read(fd, buf, BUF_SZ); 
    if (len > 0)
    {
        change(buf, &len);
        lseek(fd, 0, SEEK_SET);
        if (write(fd, buf, len) < len)
        {
            printf("Write Error\n");
            return -1;
        }
    }
    close(fd);
    return 0;
}

static void change(char *buf, int *len)
{
    int i = 0;
    while (i < *len - 1)
    {
        if ((buf[i] == '/') && (buf[i + 1] == '/'))
        {
            buf[i + 1] = '*';
            i++;
            while ((i < *len - 1) && (buf[i] != 0x0D) && (buf[i] != 0x0A))
            {
                i++;
            }
            if ((buf[i] == 0x0D) || (buf[i] == 0x0A))
            {
                *len += 2;
                memmove(&buf[i + 2], &buf[i], *len - i);
                buf[i] = '*';
                buf[i + 1] = '/';
            }
            int cnt = 0;
            while ((i >= 1) && ((buf[i - 1] == ' ') || (buf[i - 1] == '\t')))
            {
                cnt++;
            }
            printf("find %d space\n", cnt);
#if 0
            if (cnt > 0)
            {
                memmove(&buf[i - cnt], &buf[i], cnt);
                *len -= cnt;
                i -= cnt;
            }
#endif
        }
        i++;
    }
}
