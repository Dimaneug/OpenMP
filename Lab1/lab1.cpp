#include <iostream>
#include <omp.h>

using namespace std;

const int N = 3, M = 3, LIMIT = 200000;

int main() {
    int **matrix = new int*[N]; 
    int i,j,k,sum;
    int count = 0, total = 0;

    for (i = 0; i < N; i++) {
        matrix[i] = new int[M];
        for (j = 0; j < M; j++) {
            matrix[i][j] = rand() % 99 + 1;
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << count << endl;
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel shared(matrix)
    {
        #pragma omp for private(i,j,k,count) reduction(+:total)
        for (i = 0; i< N; i++) {
            count = 0;
            for (j = 0; j < M; j++) {
                for(k = j+1; k < M; k++) {
                    sum = matrix[i][j] + matrix[i][k];
                    while(sum > 0) {
                        int temp = sum % 10;
                       
                        if (temp == 7) count += 1; 
                        printf("count = %d\n", count);
                        sum = sum / 10;
                    }
                }
               
            }
            printf("%d row have %d sevens\n", i, total);
            total += count;
        }

    }
    end = omp_get_wtime();
    printf("Total time with omp: %f second\n", end-start);

    printf("total of sevens: %d", total);

    return 0;
}