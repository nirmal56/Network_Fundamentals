#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

void handleclient(int connfd){
    int n;
    char buf[200];
    n =read(connfd, buf , 200);
    buf[n] = '\0';
    printf("data recieved from client = %s\n",buf);
    printf("requested  haldled by server %d\n",getpid());
    write(connfd, "good bye!", 8);
}

int main(){
    int listfd,connfd,retval;
    socklen_t client;
    
    struct sockaddr_in cliaddr,servaddr;

    listfd = socket (AF_INET, SOCK_STREAM, 0);   //tcp ....///connection.../. fifo

    if(listfd < 0){
        perror("sock:");
        exit(1);
    }

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);      //htonl(inaddrany)
    servaddr.sin_port = htons(8000);    //tcp protocol http port.
    retval = bind (listfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(retval < 0){
        perror("bind:");
        exit(2);
    }
    listen (listfd , 5);
    while(1){
        int n;
        char buf[200];
        client = sizeof(cliaddr);
        connfd = accept(listfd, (struct sockaddr *) &cliaddr, &cliaddr);
        printf("client connected!!\n");
        pid_t p;
        p = fork();
        if(p == 0){
            close(listfd);
            handleclient(connfd);
        }
        close(connfd);
    }
}