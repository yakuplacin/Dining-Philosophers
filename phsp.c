#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>
#include <sys/time.h>

#define THINKING 2
#define HUNGRY 1
#define EATING 0

int LEFT;
int RIGHT;
int N;
int *state;

int *phil;
sem_t mutex;
sem_t *S;

double totalDurationHunger = 0.0;
double* durationHungerArray;

struct thread_data_philosopher{
   int  philosopherNumber;
   int  num;
   char* dst;
   int 	minThinking;
   int 	maxThinking;
   int 	minDining;
   int 	maxDining;
};

void test(int phnum)
{
		int LEFT = (phnum + N-1) % N;
		int RIGHT = (phnum + 1) % N;

	if (state[phnum] == HUNGRY
		&& state[LEFT] != EATING
		&& state[RIGHT] != EATING) {

		state[phnum] = EATING;

		printf("Philosopher %d takes chopstick %d and %d as left and right\n",
					phnum + 1, LEFT + 1, phnum + 1);

		printf("Philosopher %d is Eating the rice\n", phnum + 1);

		sem_post(&S[phnum]);
	}
}


//Here, I searched a lot and took some help from the geeksforgeeks
void takeChopstick(int phnum, void* data)
{
	int num = ((struct thread_data_philosopher*)data)->philosopherNumber;
	int num2 = ((struct thread_data_philosopher*)data)->num;	
	char* dist = ((struct thread_data_philosopher*)data)->dst;
	int minThink = ((struct thread_data_philosopher*)data)->minThinking;	
	int maxThink = ((struct thread_data_philosopher*)data)->maxThinking;
	int minDine = ((struct thread_data_philosopher*)data)->minDining;		
	int maxDine = ((struct thread_data_philosopher*)data)->maxDining;

	double mean = (double) (maxDine+minDine)/2.0; 	

	double diningWait;

	if(strcmp(dist,"exponential") == 0){
	
		double lambda =  1.0/((double)mean);// 2.0/(double)((minDine+maxDine)/1000.0);                 //1.0 / (double)mean;

		//thinkingWait = (double)((rand() % (maxThink - minThink + 1)) + minThink)/(double)1000;  // (rand() % (60000 - 1 + 1 )) + 1;  min max

		//double expWait = -log(1-thinkingWait) / lambda;

		double expWait;
		do{
		
	//	printf("%d %d aaaaaaaaaaaaaaaa",minDine,maxDine);
		diningWait =  (double)rand()/(double)(RAND_MAX +  1.0);    // (double)((rand() % (maxDine - minDine + 1)) + minDine);  // (rand() % (60000 - 1 + 1 )) + 1;  min max

	//	printf("I AM HEREE ŞSGFHSAHGOA%f", -log(1-diningWait));


		expWait = -log(1-diningWait) / (lambda);


	//	printf("%d  DİİİNNNGGG  %f\n", num, expWait);
		} while((expWait>(maxDine)) || expWait<(minDine));

	//	printf("Dİning WAİTTTT  %d" ,num);

		diningWait = expWait;

 		
		} else if ((strcmp(dist,"uniform") == 0)) {
		
		 diningWait = (double)((rand() % (maxDine - minDine + 1)) + minDine);  // (rand() % (60000 - 1 + 1 )) + 1;  min max
		
	}
		
	printf("Waiting time For Dining Wait:  %f\n",diningWait);
		
	sem_wait(&mutex);

	state[phnum] = HUNGRY;
/*
	clock_t start, end;
    double cpu_time_used;
	start = clock();
*/
	printf("Philosopher %d is Hungry\n", phnum + 1);

	// eat if neighbours are not eating
	test(phnum);

	sem_post(&mutex);

	// if unable to eat wait to be signalled
	sem_wait(&S[phnum]);


//	double diningWait = ((rand() % (1000 )) + 1)/(double)1000;
//	printf("Dining time: %f",diningWait);

		
		usleep(diningWait*1000); ///////
/*
		end = clock();
     	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		durationHungerArray[phnum] += cpu_time_used;
		printf("phnum %d %f\n", phnum, durationHungerArray[phnum]);
*/
}
// put down chopsticks
void put_fork(int phnum)
{
	int LEFT = (phnum + N-1) % N;
	int RIGHT = (phnum + 1) % N;

	sem_wait(&mutex);

	// state that thinking
	state[phnum] = THINKING;

	printf("Philosopher %d putting fork %d and %d down\n",
		phnum + 1, LEFT + 1, phnum + 1);
	printf("Philosopher %d is thinking\n", phnum + 1);

	test(LEFT);
	test(RIGHT);

	sem_post(&mutex);
}

void* philosopher(void* data)
{
	int num = ((struct thread_data_philosopher*)data)->philosopherNumber;
	int num2 = ((struct thread_data_philosopher*)data)->num;	
	char* dist = ((struct thread_data_philosopher*)data)->dst;
	int minThink = ((struct thread_data_philosopher*)data)->minThinking;	
	int maxThink = ((struct thread_data_philosopher*)data)->maxThinking;
	int minDine = ((struct thread_data_philosopher*)data)->minDining;		
	int maxDine = ((struct thread_data_philosopher*)data)->maxDining;
	double mean = (double) (maxThink+minThink)/2.0; 	

	double thinkingWait;

	for(int i = 0; i < num2; i++){

		if(strcmp(dist,"exponential") == 0){
	
		double lambda =  1.0/((double)mean) ;                //1.0 / (double)mean;

		//thinkingWait = (double)((rand() % (maxThink - minThink + 1)) + minThink)/(double)1000;  // (rand() % (60000 - 1 + 1 )) + 1;  min max

		//double expWait = -log(1-thinkingWait) / lambda;

		double expWait;
		do{
		
		//thinkingWait = (double)rand() /(double)(RAND_MAX + 1); // ((rand() % (maxThink - minThink + 1)) + minThink)/(double)1000;  // (rand() % (60000 - 1 + 1 )) + 1;  min max

		thinkingWait =  (double)rand()/(double)(RAND_MAX +  1.0);  
		
		expWait = -log(1-thinkingWait) / (lambda);

	//	printf("%d  phiii  %f\n", num, expWait);
		} while((expWait>(maxThink)) || expWait<(minThink));

	//	printf("compledeeesdf  piiasdad  %d" ,num);

		thinkingWait = expWait;

 		
		} else if ((strcmp(dist,"uniform") == 0)) {
		
		 thinkingWait = (double)((rand() % (maxThink - minThink + 1)) + minThink);  // (rand() % (60000 - 1 + 1 )) + 1;  min max
		
		}

		struct timeval startTime, stopTime;

		/*clock_t start, end;
     	double cpu_time_used;
	    start = clock();
		*/
		gettimeofday(&startTime, NULL);
		printf("Thinking waiting time: %f\n",thinkingWait);
		usleep(thinkingWait*1000);
		//end = clock();
     	//cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		//printf("\n\nsfsdfsdfsd %f a sdadasd\n\n", cpu_time_used);
		printf("%d has eaten %d times\n", num+1,i);
		
    	takeChopstick(num, data);

		gettimeofday(&stopTime, NULL);
		double time = (double)(stopTime.tv_usec - startTime.tv_usec) / 1000000 + (double)(stopTime.tv_sec - startTime.tv_sec);
		printf("TIME for the hungry: %f\n", time);

		durationHungerArray[num] += time*1000.0;
		printf("Until now, philosopher %d total duration Hunger time %f\n", num, durationHungerArray[num]);

		put_fork(num);
	}
	printf("%d IS DONE\n",num);
	pthread_exit(NULL);
}

int main(int argc, char * argv[])
{

	N = atoi(argv[1]);

	state = malloc(N*sizeof(int));
	
	durationHungerArray = malloc(N*sizeof(double));
	phil = malloc(N*sizeof(int));
	
	for(int i = 0; i < N; i++){
		phil[i] = i;
		durationHungerArray[i] = 0.0;
	}

	S = malloc(N*sizeof(*S));
	

	int i;
	int dinNum = atoi(argv[7]);
	pthread_t thread_id[N];
	char distribution[20] = "exponential";

	// initialize the semaphores
	sem_init(&mutex, 0, 1);

	for (i = 0; i < N; i++)

		sem_init(&S[i], 0, 0);

	for (i = 0; i < N; i++) {

		 struct thread_data_philosopher *pthreadData = (struct thread_data_philosopher *)malloc(sizeof(struct thread_data_philosopher));
		 pthreadData->philosopherNumber = phil[i];
		 pthreadData->num = dinNum;
		 pthreadData->dst = argv[6];
		 pthreadData->minThinking = atoi(argv[2]);
		 pthreadData->maxThinking = atoi(argv[3]);
		 pthreadData->minDining = atoi(argv[4]);
		 pthreadData->maxDining = atoi(argv[5]);

		// create philosopher processes

		srand(time(NULL));
		pthread_create(&thread_id[i], NULL,
					philosopher, pthreadData);

		printf("Philosopher %d is thinking\n", i );
	}

	for (i = 0; i < N; i++)
	{	
		pthread_join(thread_id[i], NULL);
	}

	double x = 0.0;
	for(int i = 0; i < N; i++){
		totalDurationHunger += durationHungerArray[i];
		printf("The philosopher %d has total duration Hunger: %f\n", i, durationHungerArray[i]);
	}

	double meanDurationHunger = (double) totalDurationHunger / (double)(N);
	double variance = 0;
	for(i = 0; i < N; i++){
		variance += pow(meanDurationHunger-durationHungerArray[i],2);
	}
	variance = variance/(double)(N-1);
	double standardDeviation = sqrt(variance);
	printf("\nVariance: %f \nStandard Deviation: %f  \nMean Duration: %f  \ntotal: %f\nTHE PROGRAM IS DONE", variance, standardDeviation, meanDurationHunger, totalDurationHunger);
		
}
