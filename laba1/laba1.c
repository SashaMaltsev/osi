
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"


int main() {

    char file_name[100];
    printf("Введите имя файла: ");
    scanf("%s", file_name);

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (0 == pid) {

        FILE *file = fopen(file_name, "r");
        close(fd[0]);

        float a, b, c; 
        float res;
        
        while((fscanf(file, "%f %f %f", &a, &b, &c) == 3)) {
            if ((b == 0) || (c == 0)) {
                break;
            } else {
                res = a / b / c;
                write(fd[1], &res, sizeof(float));
            }
        }
        fclose(file);
        close(fd[1]);
        exit(0);

    } else {

        close(fd[1]);

        float x;

        while (read(fd[0], &x, sizeof(float)) > 0) {
            printf("%f\n", x);
        }

        close(fd[0]);
    }

    return 0;
}
