#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "socket.h"

int send_broadcast()
{
    // create socket
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("create socket error");
        exit(0);
    }

    // setsockopt
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    // init server info
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(9999);
    inet_pton(AF_INET, "192.168.1.255", &seraddr.sin_addr.s_addr);

    char buf[1024];
    //char ipbuf[64];
    //struct sockaddr_in cliaddr;
    socklen_t seraddr_len = sizeof(seraddr);
    int num = 0;
    // communication
    while (1)
    {
        sprintf(buf, "hello,server...%d\n", num++);
        sendto(fd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&seraddr, seraddr_len);

        //memset(buf, 0, sizeof(buf));
        //recvfrom(fd, buf, sizeof(buf), 0, NULL, NULL);
        //printf("server say:%s\n", buf);
        sleep(1);
    }

    close(fd);

    return 0;
}