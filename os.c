#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
void* reader();
void* writer();
pthread_mutex_t mRead,mWrite;
int sharedValue=0;
int readCount=0;
int main()
{ pthread_mutex_init(&mRead,NULL);
  pthread_mutex_init(&mWrite,NULL);
  int r=0,w=0,i=0;
  puts("enter the number of readers");
  scanf("%d",&r);
  puts("enter the number of writer");
  scanf("%d",&w);
  pthread_t t1[r],t2[w];
  for(i=0;i<r;i++)
  {
  pthread_create(&t1[i],NULL,reader,NULL);
  }
  for(i=0;i<w;i++)
  {
  pthread_create(&t2[i],NULL,writer,NULL);
  }
  for(i=0;i<r;i++)
    pthread_join(t1[i],NULL);
  for(i=0;i<w;i++)
    pthread_join(t2[i],NULL);



}
void* reader()
{ pthread_mutex_lock(&mRead);
  printf(" A reader is trying to read\n");
  readCount++;
  if(readCount==1)
    pthread_mutex_lock(&mWrite);
    pthread_mutex_unlock(&mRead);
    printf("The read value: %d\n",sharedValue);
    printf("Number of Readers:%d\n",readCount);
    sleep(5);
    readCount--;
  if(readCount==0)
    pthread_mutex_unlock(&mWrite);
    printf("A reader left\n");
}
void* writer()
{ pthread_mutex_lock(&mWrite);
  int x;
  x=sharedValue;
  x++;
  sharedValue=x;
  printf("Written Value is %d\n",sharedValue);
  printf("Number of Readers:%d\n",readCount);
  sleep(5);
  pthread_mutex_unlock(&mWrite);

}
