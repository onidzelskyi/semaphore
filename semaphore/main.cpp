//
//  main.cpp
//  semaphore
//
//  Created by Alexey on 10/19/13.
//  Copyright (c) 2013 Alexey. All rights reserved.
//

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


sem_t* mutex_A;
sem_t* mutex_B;
pthread_t thread_A;
pthread_t thread_B;
const char* line_A = "Test line A\n";
const char* line_B = "Test line B\n";
char* buf = 0;


void* handler_A(void*) {
    buf = (char*)line_A;
    sem_post(mutex_A);
    pthread_exit(0);
}


void* handler_B(void*) {
    sem_wait(mutex_A);
    printf("%s", buf);
    pthread_exit(0);
}


int main(int argc, const char * argv[])
{
/*
#ifdef __APPLE__
    if((mutex_A=sem_open("/sem_A",O_CREAT,0777,0))==SEM_FAILED) {
        perror("sem_open");
    }
#elif __linux___
    if (sem_init(mutex_A, 0, 0)==-1) {
        perror("Error:");
    }
#elif _WIN32
#endif
*/
    if((mutex_A=sem_open("/sem_A",O_CREAT,0777,0))==SEM_FAILED) {
        perror("sem_open");
    }
    pthread_create(&thread_A, 0, handler_A, 0);
    pthread_create(&thread_B, 0, handler_B, 0);

    pthread_join(thread_A, 0);
    pthread_join(thread_B, 0);

    sem_destroy(mutex_A);
    return 0;
}

