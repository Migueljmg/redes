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

char * file = "Logbook.pdf";


  //Open the file
  int f = open(file,O_RDONLY);

  if(f<0)
    return 1;


  struct stat st;
  stat(file, &st);
  const int size = st.st_size;


unsigned char *byte_all;
byte_all=malloc(size*sizeof(unsigned char));



int t=read(f,byte_all,size);



if(t<0)
return 1;

const int max=60000;
const int npackets = (int)size/max+1;
printf("packets %d \n",npackets);
printf("size %d \n",size);
int remain = size - (npackets-1)*max;
printf("remain %d \n",remain);
unsigned char **byte;
byte=malloc(npackets*sizeof(unsigned char*));

int j=0;
for(j=0;j<npackets;j++){
  byte[j]=malloc(max*sizeof(unsigned char));
}



int h=0;
while(h<npackets){

if(h==npackets-1){
int i=0;
   while(i<max){
     byte[h][i] = byte_all[h*max+i];
     i++;
   }
/*
   i=remain;
while(i<max){
     byte[h][i] = '\0';
     i++;
}
*/

}
 else{
int i=0;
   while(i<max){
     byte[h][i] = byte_all[h*max+i];
//printf("%d \n",byte[h][i]);
     i++;
   }
}


h++;
}







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



        int info[4];
        info[0]=size;
        info[1]=max; 
        info[2]=npackets; 
        info[3]=remain;

printf("%d  %d  %d  %d \n", size,max,npackets,remain);

        if (sendto(s, &info, 16 , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }

usleep(1);


     //send the message
     j=0;
     while(j<npackets){
        if (sendto(s, byte[j], max , 0 , (struct sockaddr *) &si_other, slen)==-1)
        {
            die("sendto()");
        }
        j++;
usleep(1);
     }

        printf("Image sent");

         
        //receive a reply and print it
        //clear the buffer by filling null, it might have previously received data

        //memset(byte,'\0', size);



for(j=0;j<npackets;j++){
  free(byte[j]);
}

free(byte);
free(byte_all);

    close(s);

    return 0;
}
