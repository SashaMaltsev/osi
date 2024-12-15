#include "stdio.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {

    char file_name[100];
    printf("Введите имя файла: ");
    scanf("%s", file_name);

    int fd = shm_open("/shared_file", O_RDWR | O_CREAT , 0666);
    
    if (fd == -1) {
        perror("shm_open");
        return 1;
    }

    int SIZE = 1024; 

    if (ftruncate(fd, SIZE) == -1) {
        perror("ftruncate");
        shm_unlink("/shared_file");
        return 1;
    }

    float* shared_mem = (float*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        shm_unlink("/shared_file");
        close(fd);
        return 1;
    }

    pid_t pid = fork();

    if (0 == pid) {
        FILE* file = fopen(file_name, "r");
        
        if (file == NULL) {
            perror("fopen");
            exit(1);
        }

        float a, b, c;
        int i = 0;

        while ((fscanf(file, "%f %f %f", &a, &b, &c) == 3)) {
            if ((b == 0) || (c == 0)) {
                break;
            } else {
                float res = a / b / c;
                shared_mem[i++] = res;
                if (i >= (SIZE / sizeof(float))) {
                    break;
                }
            }
        }
        fclose(file);
        shared_mem[i] = -1.0f; 
        munmap(shared_mem, SIZE);
        close(fd);
        shm_unlink("/shared_file");
        exit(0);

    } else {

        wait(NULL);
        int i = 0;
        while (shared_mem[i] != -1.0f) {
            printf("%f\n", shared_mem[i]);
            i++;
        }
        munmap(shared_mem, SIZE);
        close(fd);
        shm_unlink("/shared_file");
    }

    return 0;
}
