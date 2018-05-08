
#include<stdio.h> 
#include<string.h> 
#include<stdlib.h> 
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define TAM_BUFFER 512  
#define PORT 5001   
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{
    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    char buf[TAM_BUFFER],resp[TAM_BUFFER];

     
    //criando o socket upd
    if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
     
    //ZERANDO A ESTRUTURA
    memset((char *) &si_me, 0, sizeof(si_me));
    

    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    // CONECTANDO SOCKET NA PORTA
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     int flag =0;
    // ESCUTANDO PARA RECEBER INFORMAÇÕES DO CLIENTE
    while(1)
    {

        printf("[SERVIDOR:ESCUTANDO]...");
        fflush(stdout);
         
        // Tentando receber informações
        if ((recv_len = recvfrom(s, buf, TAM_BUFFER, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
        flag++;
        if(flag==2) {
        
        printf("[SERVIDOR: RECEBIDO INFORMAÇÕES] %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("[SERVIDOR]: %s\n",buf);
        flag=0;        
        // respondendo o cliente
        strcpy(resp,"Obrigado por falar cmg");
        if (sendto(s, resp, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        {
            die("sendto()");
        }
        }
    }
 
    close(s);
    return 0;
}