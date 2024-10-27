#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "socket.h"

int send_tcp()
{
    // create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("create socket error");
        exit(0);
    }

    // connect
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(10000);
    inet_pton(AF_INET, "192.168.1.21", &addr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect error");
        exit(0);
    }

    // communication
    int number = 0;
    while (1)
    {
        // write recv
        char buf[1024];
        sprintf(buf, "hello,server...%d\n", number++);
        write(fd, buf, strlen(buf) + 1);

        // read send
        memset(buf, 0, sizeof(buf));
        int len = read(fd, buf, sizeof(buf));
        if (len > 0)
        {
            printf("server say:%s\n", buf);
        }
        else if (len == 0)
        {
            printf("server disconnect connection ...\n");
            break;
        }
        else
        {
            perror("read error");
            break;
        }
        sleep(1);
    }

    close(fd);

    return 0;
}