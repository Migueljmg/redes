#include <stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){


  //Open the file
  int f = open("goku.png",O_RDONLY);

  if(f<0)
    return 1;


  struct stat st;
  stat("goku.png", &st);
  const int size = st.st_size;


  unsigned char byte[size];

  int t=read(f,&byte,size);

  if(t<0)
    return 1;

  /*
  int i=0;
  while(i<size){
    printf("%c",byte[i]);
    i++;
  }
  */


  //Open the file
  int f2 = open("output.png",O_WRONLY);
  int t2=write(f2,&byte,size);

  FILE *fp;
  fp=fopen("test.txt", "w");
  fprintf(fp, "Testing...\n");

  if(t2<0)
    return 1;



  return 0;

}
