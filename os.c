#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void* rdr();
void* wrtr();
pthread_mutex_t mr,mw;
int shared_value=0;
int readcount=0;
int main()
{ pthread_mutex_init(&mr,NULL);
  pthread_mutex_init(&mw,NULL);
  int r=0,w=0,i=0;
  puts("enter the number of readers");
  scanf("%d",&r);
  puts("enter the number of writer");
  scanf("%d",&w);
  pthread_t t1[r],t2[w];
  for(i=0;i<r;i++)
  {
  pthread_create(&t1[i],NULL,rdr,NULL);
  }
  for(i=0;i<w;i++)
  {
  pthread_create(&t2[i],NULL,wrtr,NULL);
  }
  for(i=0;i<r;i++)
    pthread_join(t1[i],NULL);
  for(i=0;i<w;i++)
    pthread_join(t2[i],NULL);



}
void* rdr()
{ pthread_mutex_lock(&mr);
  printf(" A reader is trying to read");
  readcount++;
  if(readcount==1)
    pthread_mutex_lock(&mw);
    pthread_mutex_unlock(&mr);
    printf("The read value: %d",shared_value);
    printf("Number of Readers:%d",readcount);
    readcount--;
  if(readcount==0)
    pthread_mutex_unlock(&mw);
    printf("A reader left");
}


void* wrtr()
{ pthread_mutex_lock(&mw);
  int x;
  x=shared_value;
  x++;
  shared_value=x;
  printf("Written Value is %d",shared_value);
  printf("Number of Readers:%d",readcount);
  pthread_mutex_unlock(&mw);

}