#include<stdio.h>
#include<unistd.h>
#include<limits.h>

int main(int argc, int argv[]){
    char hostname[_SC_HOST_NAME_MAX + 1];
    hostname[ _SC_HOST_NAME_MAX] =0 ;
    if(gethostname(hostname, _SC_HOST_NAME_MAX) == 0)
        puts(hostname);
    else    
        perror("gethostname:");
    return 0;
}