#include <stdio.h>
#include <stdlib.h>

#define DIVIDER 1000000007

int **createMatrix(int length, int height) {
    int **result = (int **) calloc(height, sizeof(int *));
    for (int i = 0; i < height; i++) {
        result[i] = (int *) calloc(length, sizeof(int));
    }
    return result;
}

void clearMem(int **target, int height) {
    for (int i = 0; i < height; i++) {
        free(target[i]);
    }
    free(target);
}

int main() {
    int target_number;
    scanf("%d", &target_number);

    int **matrix = createMatrix(target_number + 1, target_number + 1);

    for (int i = 1; i <= target_number; i++) {
        matrix[i][0] = 0;
    }

    for (int i = 0; i <= target_number; i++) {
        matrix[0][i] = 1;
    }


    for (int i = 1; i <= target_number; i++) {
        for (int j = 1; j <= target_number; j++) {
            if (j <= i) matrix[i][j] = (matrix[i][j - 1] + matrix[i - j][j]) % DIVIDER;
            if (i < j) matrix[i][j] = matrix[i][i];
        }
    }
    printf("%d", matrix[target_number][target_number]);

    //я так и не смог написать нормальную очистку памяти через функцию блинб
    for (int i = 0; i < target_number; i++) {
        free(matrix[i]);
    }
    free(matrix);
}