#include <iostream> 
#include <pthread.h>
#include <cstdlib>
#include <ctime>


pthread_mutex_t mutex;
size_t first_player_won = 0;
size_t second_player_won = 0; 
size_t draws = 0;


int rollDice() {
    return rand() % 6 + 1;
}


void* game(void *args) {

    size_t* K = static_cast<size_t*>(args);
    
    int sum1 = 0;
    int sum2 = 0;

    for (size_t i = 0; i < *K; ++i) {
        sum1 += rollDice();
        sum1 += rollDice();
    }

    for (size_t i = 0; i < *K; ++i) {
        sum2 += rollDice();
        sum2 += rollDice();
    }

    pthread_mutex_lock(&mutex);

    if (sum1 > sum2) {
        ++first_player_won;
    } else if (sum2 > sum1) {
        ++second_player_won;
    } else {
        ++draws;
    }

    pthread_mutex_unlock(&mutex);

    pthread_exit(0);
}


int main() {

    srand(static_cast<unsigned int>(time(0)));

    // input 
    size_t K, N;
    std::cin >> K >> N;

    pthread_t tid[N];
    pthread_mutex_init(&mutex, NULL);
    size_t* thread_arg = new size_t(K); 

    for (size_t i = 0; i < N; ++i) {
        pthread_create(&tid[i], NULL, game, thread_arg);
    }

    for (size_t i = 0; i < N; i++) {
        pthread_join(tid[i], NULL);
    }

    std::cout << "first player won : " << first_player_won << std::endl;
    std::cout << "second player won : " << second_player_won << std::endl;
    std::cout << "draws : " << draws << std::endl;

    return 0;
}
