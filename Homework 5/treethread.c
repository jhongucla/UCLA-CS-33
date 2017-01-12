#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *vargp);

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Wrong number of arguments\n");
		return 1;
	}
	int depth1, depth2;
	depth1 = depth2 = atoi(argv[1]) - 1;
	if (depth1 > 0)
	{
		pthread_t tid1, tid2;
		pthread_create(&tid1, NULL, thread, &depth1);
		pthread_create(&tid2, NULL, thread, &depth2);
		pthread_join(tid1, 0);
		pthread_join(tid2, 0);
	}
	printf("Hello, world\n");
	exit(0);
}

void *thread(void *vargp)
{
	int depth1, depth2;
	depth1 = depth2 = *((int *)vargp) - 1;
	if (depth1 > 0)
	{
		pthread_t tid1, tid2;
		pthread_create(&tid1, NULL, thread, &depth1);
		pthread_create(&tid2, NULL, thread, &depth2);
		pthread_join(tid1, 0);
		pthread_join(tid2, 0);
	}
	printf("Hello, world\n");
	return NULL;
}