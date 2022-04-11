#include<netdb.h>
#include<stdio.h>

int main(){
    char **names;
    int i;
    struct servent *se = NULL;
    printf("outside\n");
    while((se = getservent()) != NULL){
        printf("-----------------------------\n");
        printf("official service naem:%s\n",se->s_name);
        printf("port no =%d \n", ntohs(se->s_port));
        printf("protocol = %s \n", se->s_proto);
        for(int i =0; names[i]!= NULL; i++ ){
            printf("....%c....\n",names[i]);
            printf("........\n");
        }
    }
}