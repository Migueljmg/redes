#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
 
#define SERVER "10.0.2.15"
#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to send data
 
void die(char *s)
{
    perror(s);
    exit(1);
}
 
int main(void)
{


char * file = "mr.pdf";


  //Open the file
  int f = open(file,O_RDONLY);

  if(f<0)
    return 1;


  struct stat st;
  stat(file, &st);
  const int size = st.st_size;

  unsigned char byte[size];

  int t=read(f,&byte,size);

  if(t<0)
    return 1;






    struct sockaddr_in si_other;
    int s, i, slen=sizeof(si_other);

 
    if ( (s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        die("socket");
    }
 
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(PORT);
     
    if (inet_aton(SERVER , &si_other.sin_addr) == 0) 
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }
        
 
        //send the message
        if (sendto(s, byte, size , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }

        printf("Image sent");

         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data

        memset(buf,'\0', BUFLEN);

    close(s);
    return 0;
}
