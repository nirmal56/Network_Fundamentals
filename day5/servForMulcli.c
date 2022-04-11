#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

//this is iterative server.it accepts only one client. After one client terminates, process data but data is taken parallely.

#define PORT 8000
#define MAXSZ 100

int main(){
    int sockfd,newsockfd,n;
    char msg[MAXSZ];
    int clientAddrLen;
    socklen_t client;    
    struct sockaddr_in cliaddr,servaddr;
    char buf[10000];
    
    sockfd  =socket(AF_INET, SOCK_STREAM,0);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      //htonl(inaddrany)
    servaddr.sin_port = htons(PORT);    //tcp protocol http port.
    bind (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    printf("socket bound to port 8000");
    listen(sockfd,5);

    while(1){
        printf("************server waiting for new client connection*************\n");
        clientAddrLen = sizeof(cliaddr);
        newsockfd = accept(sockfd, (struct sockaddr*)&cliaddr,&clientAddrLen);
        while(1){
            int n;
            n = recv(newsockfd, msg, MAXSZ, 0);
            if( n == 0){
                close(newsockfd);
                break;
            }
            msg[n] = 0;
            send(newsockfd, msg, n, 0);
            printf("received and set %s\n", msg);
        }

    }
    return 0;
}