
#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/socket.h>
 
#define SERVER "127.0.0.1"
#define BUFLEN 512
#define PORT 5001 
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(int argc, char *argv[ ])
{
    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);
    char buf[BUFLEN];
    char message[BUFLEN];
 
    if(argc < 2){
        die("Falta parametros");
    }

    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(argv[1] , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
 
    while(1)
    {
        printf("[Cliente]- Nome: ");
        gets(message);
         
        // enviando mensagem para o servidor
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }

        printf("[Cliente]- Mensagem: ");
        gets(message);
        // enviando mensagem para o servidor
        if (sendto(s, message, strlen(message) , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }        
        memset(buf,'\0', BUFLEN);
        // Tentando receber alguma informação
        if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == -1)
        {
            die("recvfrom()");
        }
 		     
 		printf("[Cliente-]:" );        
        puts(buf);
    }
    close(s);
    return 0;
}