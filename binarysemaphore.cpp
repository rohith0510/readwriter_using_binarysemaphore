#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/types.h>
sem_t mutex,write;
int data = 0,rowcounting = 0;
void *reader(void *ast)
{
int s;
s = ((int)ast); 
sem_wait(&mutex);
rowcounting = rowcounting + 1;
if(rowcounting==1)
sem_wait(&write);
sem_post(&mutex);
printf("Data read by the reader%d is %d\n",s,data);
sleep(1);
sem_wait(&mutex);
rowcounting = rowcounting - 1;
if(rowcounting==0)
sem_post(&write);
sem_post(&mutex);
}
void *writer(void *ast){
int s;
s = ((int) ast);
sem_wait(&write);
data++;
printf("Data writen by the writer%d is %d\n",s,data);
sleep(1);
sem_post(&write);
}
int main()
{
int i,b;
pthread_t rd[5],wr[5];
sem_init(&mutex,0,1);
sem_init(&write,0,1);
for(i=0;i<=2;i++)
{
pthread_create(&wr[i],NULL,writer,(void *)i);
pthread_create(&rd[i],NULL,reader,(void *)i);
}
for(i=0;i<=2;i++)
{
pthread_join(wr[i],NULL);
pthread_join(rd[i],NULL);
} return 0;} 


