#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "socket.h"

int send_multicast()
{
    // create socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("create socket error");
        exit(0);
    }

    // setsockopt
    struct in_addr opt;
    inet_pton(AF_INET, "239.0.1.10", &opt.s_addr);
    setsockopt(fd, IPPROTO_IP, IP_MULTICAST_IF, &opt, sizeof(opt));

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);
    inet_pton(AF_INET, "239.0.1.10", &seraddr.sin_addr.s_addr);

    char buf[1024];
    socklen_t seraddr_len = sizeof(seraddr);
    int num = 0;
    while (1)
    {
        sprintf(buf, "Hello,server...%d\n", num++);
        sendto(fd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&seraddr, seraddr_len);
        printf("sendto:%s\n", buf);
        sleep(1);
    }

    close(fd);

    return 0;
}