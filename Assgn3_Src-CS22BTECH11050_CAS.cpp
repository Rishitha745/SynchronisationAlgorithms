#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <atomic>
#include <pthread.h>
using namespace std;

struct Data
{
    int **matrix;
    int num_rows;
    int rowInc;
    int **finalmatrix;
};

int value(0);

int C = 0;
void *Calculate(void *arg)
{
    struct Data *thread_data = (struct Data *)arg;
    int N = thread_data->num_rows;
    int **input = thread_data->matrix;
    int **output = thread_data->finalmatrix;
    int rowInc = thread_data->rowInc;
    int temp = 0;
    while (true)
    {
        while (__sync_val_compare_and_swap(&value, 0, 1)!=0)
        {
        }
        // critical section
        temp = C;
        if (C >= N)
        {
            value = 0;
            break;
        }
        C = C + rowInc;
        value = 0;
        // remainder section
        for (int i = temp; i < temp + rowInc; i++)
        {
            if (i >= N)
            {
                break;
            }
            for (int column = 0; column < N; column++)
            {
                int sum = 0;
                for (int row = 0; row < N; row++)
                {
                    sum = sum + input[i][row] * input[row][column];
                }
                output[i][column] = sum;
            }
        }
    }
    return 0;
}

int main()
{
    chrono::high_resolution_clock::time_point start = chrono::high_resolution_clock::now();
    int N, K, rowInc;
    ifstream input("inp.txt");
    input >> N;
    input >> K;
    input >> rowInc;
    int **InputMatrix = new int *[N];
    int **OutputMatrix = new int *[N];
    for (int i = 0; i < N; i++)
    {
        InputMatrix[i] = new int[N];
        OutputMatrix[i] = new int[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            input >> InputMatrix[i][j];
        }
    }
    pthread_t Threads[K];
    struct Data thread_data[K];
    for (int i = 0; i < K; i++)
    {
        thread_data[i].matrix = InputMatrix;
        thread_data[i].num_rows = N;
        thread_data[i].rowInc = rowInc;
        thread_data[i].finalmatrix = OutputMatrix;
        pthread_create(&Threads[i], NULL, Calculate, (void *)&thread_data[i]);
    }
    for (int i = 0; i < K; i++)
    {
        pthread_join(Threads[i], NULL);
    }
    chrono::high_resolution_clock::time_point stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    ofstream output("out_CAS.txt");
    output << "Time taken using CAS method : " << duration.count() << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            output << OutputMatrix[i][j] << " ";
        }
        output << endl;
    }
    for (int i = 0; i < N; i++)
    {
        delete[] InputMatrix[i];
        delete[] OutputMatrix[i];
    }
    delete[] InputMatrix;
    delete[] OutputMatrix;
}