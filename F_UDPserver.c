#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{


  struct stat st;
  stat("mr.pdf", &st);
  const int size = st.st_size;



    struct sockaddr_in si_me, si_other;
     
    int s, i, slen = sizeof(si_other) , recv_len;
    unsigned char buf[size];
     
    //create a UDP socket
    s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);//AF_INET corresponde a familia de enderecos com IPv4, SOCK_DGRAM - especifica que o socket vai ser criado para UDP
    if (s == -1)
    {
        die("socket");
    }
     
    // zero out the structure
    memset((char *) &si_me, 0, sizeof(si_me));
     
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(PORT);//host to network short, conversao da byte order do host(minha maquina) para a "network byte order", utilizada como predefinicao para comunicacoes 
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
     
    //bind socket to port
    if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
    {
        die("bind");
    }
     
    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);
         
        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, size, 0, (struct sockaddr *) &si_other, &slen)) == -1)
        {
            die("recvfrom()");
        }
         
        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
//printf("Data: %s\n" , buf);
         
        //now reply the client with the same data
        //if (sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == -1)
        //{
        //    die("sendto()");
        ///}

  //Open the file
  int f2 = open("output.pdf",O_WRONLY);
  int t2=write(f2,&buf,size);

    }
 
//unsigned char byte[size];



    close(s);
    return 0;
}
