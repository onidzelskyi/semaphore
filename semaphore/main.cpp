//
//  main.cpp
//  semaphore
//
//  Created by Alexey on 10/19/13.
//  Copyright (c) 2013 Alexey. All rights reserved.
//

#include <iostream>
#include <semaphore.h>
#include <errno.h>
#include <unistd.h>


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
    exit(0);
}


void* handler_B(void*) {
    sem_wait(mutex_A);
    printf("%s", buf);
    exit(0);
}


int main(int argc, const char * argv[])
{
#ifdef __APPLE__
    if((mutex_A=sem_open("/sem_A",O_CREAT,0777,0))==SEM_FAILED) {
        perror("sem_open");
    }
#elif __linux___
    if (sem_init(mutex_A, 0, 0)) {
        perror("Error:");
    }
#elif _WIN32
#endif
    pthread_create(&thread_A, 0, handler_A, 0);
    pthread_create(&thread_B, 0, handler_B, 0);

    pthread_join(thread_A, 0);
    pthread_join(thread_B, 0);

    /*
    sem_t* sem = sem_open("/sem1",O_CREAT,0777,10);
    if(sem==SEM_FAILED) {
        perror("sem_open");
    } else  {
//        sem_post(sem);
        int ret = sem_wait(sem);
        if(ret) {
            perror("sem_open");
        } else {
            std::cout << "Hello, World!\n";
        }
    }
     */
    while (1) {
        sleep(1);
    }
    return 0;
}

