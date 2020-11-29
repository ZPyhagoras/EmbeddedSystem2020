/*
 * thread_create.c
 *
 * Created on: 2016-10-30
 * Author: Arthur
 * Modified on: 2020-11-29
 * Author: Zhang Qiyang
 * StudentID: PT2000186
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem[6];
void *print_hello (void *arg)
{
	int i = (int)arg;
	/*
	Method 3
	sem_wait(&sem[i]);
	*/
	printf("it's me, thread %d!\n", i);
	/*
	Method 3
	sem_post(&sem[i + 1]);
	*/
	pthread_exit(NULL);
	return (NULL);
}

int main (int argc, char *argv[])
{

	int			ret;
	int			i;
	pthread_t	tid[5];
	/*
	Method 3
	sem_init(&sem[0], 0, 1);
	for (i = 1; i < 6; i++) {
		sem_init(&sem[i], 0, 0);
	}
	*/
	for (i = 0; i < 5; i++) {
	printf("in main: creating thread %d\n", i);
	ret = pthread_create(&tid[i], NULL, print_hello, (void *)i);
	if (ret != 0) {
	    printf("create thread failed\n");
	    exit(-1);
	    }
	}
	/*
	Method 1
	void *status;
	for (i = 0; i < 5; i++) {
		pthread_join(tid[i], &status);
	}
	*/
	/*
	Method 2
	sleep(1);
	*/
	/*
	Method 3
	sem_wait(&sem[5]);
	*/

	printf("in main: exit!\n");
	pthread_exit(NULL);
	
	/*
	Method 3
	for (i = 0; i < 6; i++) {
		sem_destroy(&sem[i]);
	}
	*/
	return (0);
}
