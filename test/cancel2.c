//
// Created by Wayne on 24/1/13.
//

#include <stdio.h>
#include "uthread.h"

static long cnt = 0;
static long del = 0;

void* thread1(void *arg) {
    while (1);
}

void* thread2(void *arg) {
    cnt += 1;

    return NULL;
}

int main(int argc, char *argv[]) {
    uthread_t tids[1023];
    long i;

    for (i = 0; i < 16; ++ i) {
        uthread_create(&tids[i], thread1, NULL);
    }

    for (i = 0; i < 16; ++ i) {
        long tmp;

        uthread_cancel(tids[i]);
        uthread_join(tids[i], (void **) &tmp);
        del += tmp;
    }

    for (i = 0; i < 1023; ++ i) {
        uthread_create(&tids[i], thread2, NULL);
    }
    
    for (i = 0; i < 1023; ++ i) {
        uthread_join(tids[i], NULL);
    }

    printf("%ld %ld\n", del, cnt);

    return 0;
}
