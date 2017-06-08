#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


pthread_mutex_t mutex;
pthread_cond_t cond;
int sillas[5]= {0, 0, 0, 0, 0}; // 0 si la silla esta disponible, 1 si no

// para que una silla este disponible, debe estar disponible la siguiente y la anterior (debido a que se necesitan
// ambos palitos)


int buscarSilla() {
    pthread_mutex_lock(&mutex); //pide el mutex para buscar

    for (;;) {
        if (sillas[0] == 0 && sillas[1] == 0 && sillas[4] == 0){
            sillas[0] = 1;
            pthread_mutex_unlock(&mutex);
            return 0;
        }
        else if (sillas[1] == 0 && sillas[2] == 0 && sillas[0] == 0){
            sillas[1] = 1;
            pthread_mutex_unlock(&mutex);
            return 1;
        }
        else if (sillas[2] == 0 && sillas[3] == 0 && sillas[1] == 0){
            sillas[2] = 1;
            pthread_mutex_unlock(&mutex);
            return 2;
        }
        else if (sillas[3] == 0 && sillas[4] == 0 && sillas[2] == 0){
            sillas[3] = 1;
            pthread_mutex_unlock(&mutex);
            return 3;
        }
        else if (sillas[4] == 0 && sillas[0] == 0 && sillas[3] == 0){
            sillas[4] = 1;
            pthread_mutex_unlock(&mutex);
            return 4;
        }
        else{ //ninguna silla esta disponible
            pthread_cond_wait(&cond, &mutex); // espera a que usa silla este disponible
        }
    }
}




void desocuparSilla(int k){
    pthread_mutex_lock(&mutex);
    sillas[k] = 0;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}
