#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(){
    int sockfd,retval,n;
    socklen_t client;    
    struct sockaddr_in cliaddr,servaddr;
    char buf[10000];
    
    sockfd  =socket(AF_INET, SOCK_DGRAM,0);
    if(sockfd < 0){
        perror("sock:");
        exit(1);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      //htonl(inaddrany)
    servaddr.sin_port = htons(8000);    //tcp protocol http port.
    retval = bind (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(retval < 0){
        perror("bind:");
        exit(2);
    }
    printf("socket bound to port 8000");
    client=sizeof(struct sockaddr_in);
    while(1){
        printf("Before recvfrom\n");
        int n;
        n = recvfrom(sockfd,buf,10000,0,(struct sockaddr *)&cliaddr,&client);
        printf("Received %d bytes\n",n);
        buf[n] = '\0';
        printf("Msg from client = %s\n",buf);


    }
}