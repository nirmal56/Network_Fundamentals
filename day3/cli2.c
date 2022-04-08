#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>

int main(){
    char buf[200];
    char *serv_ip = "127.0.0.1";
    int sockfd,ret_val;
    int n;
    struct sockaddr_in servaddr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family =AF_INET;
    servaddr.sin_port = htons(8000);
    inet_pton(AF_INET, serv_ip, &servaddr.sin_addr);

    ret_val = connect (sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if(ret_val < 0){
        perror("bind:");
        exit(2);
    }
    printf("enter data to be sent ot server\n");
    gets(buf);
    write(sockfd,buf, 200);
    n = read(sockfd,buf,200);
    buf[n] = '\0';
    printf("reciever data from server:%s \n",buf);
    close(sockfd);
    return 0;
}