#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int arg, char * args[])
{
    char buf[2048]={0};
	char result[] = "success";
    struct sockaddr_in addr;
    struct sockaddr_in client_addr;
    socklen_t addrlen = sizeof(client_addr);

    if (arg < 2) {
        printf("please input: port!\n");
        return -1;
    }

    int port = atoi(args[1]);
    int fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1) {
        printf("open socket failed ! error: %s\n", strerror(errno));
        return -1;
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    //bind port
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        printf("bind IP failed ! error: %s\n", strerror(errno));
        goto out;
    }

	while(1) {
		memset(&client_addr, 0, sizeof(client_addr));
		if (recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &addrlen)==-1) {
			printf("recvfrom failed ! error: %s\n",strerror(errno));
			goto out;
		} else {
			printf("from %s:%s\n",inet_ntoa(client_addr.sin_addr), buf);

			if (sendto(fd, result, sizeof(result), 0, (struct sockaddr *)&client_addr, addrlen) == -1) {
				printf("sendto failed ! error: %s\n", strerror(errno));
				goto out;
			}
		}
		bzero(buf, sizeof(buf));		
	}

out:
	close(fd);

    return 0;
}


