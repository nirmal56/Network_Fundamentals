#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

#define PORT 8000
#define MAXSZ 100

int main(){
    char msg1[MAXSZ];
    char msg2[MAXSZ];
    int sockfd,ret_val;
    int n;
    socklen_t addr_len;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    sockfd  =socket(AF_INET, SOCK_STREAM,0);
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      //htonl(inaddrany)
    servaddr.sin_port = htons(PORT);    //tcp protocol http port.
    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    while(1){
        printf("Enter msg to be sent to srever\n");
        fgets(msg1,MAXSZ, stdin);
        if(msg1[0]=='#')
            break;
        n = strlen(msg1)+1;
        send(sockfd, msg1, n, 0);
        
        n = recv(sockfd, msg2, MAXSZ, 0);
        printf("recived msg form served:%s\n",msg2);
        // close(sockfd);

    }
    return 0;
}