#include<stdio.h>
//capturing packet at datalnk layer.



///working at datalink layer that's why we need sudo tu run the program. its in /etc/services. try cat /etc/services.
#include<sys/socket.h>
#include<netinet/in.h>
#include<netpacket/packet.h>
#include<net/ethernet.h>

int main(){
    int pack_soket, n ;
    struct sockaddr_ll sa;
    socklen_t sl;
    char buf[2000];
    sl= sizeof(struct sockaddr_ll);

    pack_soket = socket(PF_PACKET, SOCK_DGRAM, htons(ETH_P_ALL));
    if(pack_soket < 0){
        printf("failed to open packet sockket\n");
        exit(0);

    }

    printf("packet opened successfully\n");
    while (1){
        n = recvfrom(pack_soket, buf, 2000, 0, (struct sockaddr *)&sa, &sl);
        printf("received packet length %d\n",n);
    }
    close(pack_soket);
    
}