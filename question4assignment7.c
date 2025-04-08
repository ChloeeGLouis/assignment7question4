#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 2

sem_t forks[NUM_PHILOSOPHERS];
sem_t mutex;

void think(int phil_id) {
    printf("Philosopher %d is thinking...\n", phil_id);
    sleep(1);
}

void eat(int phil_id) {
    printf("Philosopher %d is eating...\n", phil_id);
    sleep(2);
}

void* philosopher(void* arg) {
    int phil_id = *(int*)arg;
    while (1) {
        think(1);
        sem_wait(&forks[phil_id]);
        printf("Philosopher %d has picked up the left fork.\n", phil_id);
        sem_wait(&forks[phil_id+1]);
        printf("Philosopher %d has picked up the right fork.\n", phil_id+1);
        eat(phil_id);
        sem_post(&forks[phil_id]);
        printf("Philosopher %d has put down the left fork.\n", phil_id);
        sem_post(&forks[phil_id + 1]);
        printf("Philosopher %d has put down the right fork.\n", phil_id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for(int i=0; i<NUM_PHILOSOPHERS; i++) 
        sem_init(&forks[i], 0, 1);

    for (int i=0; i<NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i=0; i<NUM_PHILOSOPHERS; i++) 
        pthread_join(philosophers[i], NULL);

    for (int i=0; i<NUM_PHILOSOPHERS; i++) 
        sem_destroy(&forks[i]);

    return 0;
}
