#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **A, **B, **C;
    int start_row, end_row, cols;
} ThreadData;

void* somar_matrizes(void *arg) {
    ThreadData *data = (ThreadData*) arg;

    for (int i = data->start_row; i < data->end_row; i++) {
        for (int j = 0; j < data->cols; j++) {
            data->C[i][j] = data->A[i][j] + data->B[i][j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    int rows, cols, num_threads;
    printf("Digite número de linhas e colunas da matriz: ");
    scanf("%d %d", &rows, &cols);

    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);

    int **A = malloc(rows * sizeof(int*));
    int **B = malloc(rows * sizeof(int*));
    int **C = malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        A[i] = malloc(cols * sizeof(int));
        B[i] = malloc(cols * sizeof(int));
        C[i] = malloc(cols * sizeof(int));
    }

    printf("Digite os elementos da matriz A:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &A[i][j]);

    printf("Digite os elementos da matriz B:\n");
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &B[i][j]);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int rows_per_thread = rows / num_threads;
    int extra = rows % num_threads;

    int current_row = 0;
    for (int i = 0; i < num_threads; i++) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].start_row = current_row;
        thread_data[i].end_row = current_row + rows_per_thread + (i < extra ? 1 : 0);
        thread_data[i].cols = cols;
        pthread_create(&threads[i], NULL, somar_matrizes, &thread_data[i]);
        current_row = thread_data[i].end_row;
    }

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    printf("Resultado da soma:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++)
            printf("%d ", C[i][j]);
        printf("\n");
    }

    for (int i = 0; i < rows; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A); free(B); free(C);

    return 0;
}
