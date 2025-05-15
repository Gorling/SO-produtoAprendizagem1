#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int **matriz;
    int *vetor;
    int *resultado;
    int start, end, N;
} ThreadData;

void* multiplicar(void* arg) {
    ThreadData *data = (ThreadData*) arg;

    for (int i = data->start; i < data->end; i++) {
        data->resultado[i] = 0;
        for (int j = 0; j < data->N; j++) {
            data->resultado[i] += data->matriz[i][j] * data->vetor[j];
        }
    }
    pthread_exit(NULL);
}

int main() {
    int N, num_threads;

    printf("Digite a ordem N da matriz quadrada: ");
    scanf("%d", &N);

    printf("Digite o número de threads: ");
    scanf("%d", &num_threads);

    int **matriz = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++)
        matriz[i] = malloc(N * sizeof(int));

    int *vetor = malloc(N * sizeof(int));
    int *resultado = malloc(N * sizeof(int));

    printf("Digite os elementos da matriz:\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            scanf("%d", &matriz[i][j]);

    printf("Digite os elementos do vetor:\n");
    for (int i = 0; i < N; i++)
        scanf("%d", &vetor[i]);

    pthread_t threads[num_threads];
    ThreadData thread_data[num_threads];

    int linhas_por_thread = N / num_threads;
    int extra = N % num_threads;
    int start = 0;

    for (int i = 0; i < num_threads; i++) {
        thread_data[i].matriz = matriz;
        thread_data[i].vetor = vetor;
        thread_data[i].resultado = resultado;
        thread_data[i].start = start;
        thread_data[i].end = start + linhas_por_thread + (i < extra ? 1 : 0);
        thread_data[i].N = N;
        pthread_create(&threads[i], NULL, multiplicar, &thread_data[i]);
        start = thread_data[i].end;
    }

    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    printf("Resultado da multiplicação:\n");
    for (int i = 0; i < N; i++)
        printf("%d\n", resultado[i]);

    for (int i = 0; i < N; i++)
        free(matriz[i]);
    free(matriz);
    free(vetor);
    free(resultado);

    return 0;
}
