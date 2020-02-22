#include <stdio.h>

int matrix[101][10001] = {0};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int num_numbers, divider;
    scanf("%d%d", &num_numbers, &divider);

    for (int i = 1; i <= num_numbers; i++) {
        scanf("%d", &matrix[0][i]);
    }
    for (int i = 0; i < divider; i++) {
        matrix[i + 1][0] = i;
    }
    int index1 = matrix[0][1] % divider + 1;
    int index2 = 0;
    if (index1 < 0) index1 += divider;
    matrix[index1][1] = 1;
    index1 = 0;

    for (int y = 2; y <= num_numbers; y++) {
        char tmp = matrix[0][y] % divider;
        if (tmp < 0) tmp += divider;
        for (int x = 1; x <= divider; x++) {
            if (matrix[x][y - 1] == 1) {
                index1 = (tmp + matrix[x][0]) % divider;
                index2 = (tmp - matrix[x][0]) % divider;
                if (index2 < 0) index2 += divider;
                matrix[index1 + 1][y] = 1;
                matrix[index2 + 1][y] = 1;
            }
        }
    }
    if (matrix[1][num_numbers] == 1) {
        printf("Divisible");
    } else {
        printf("Not divisible");
    }
}
