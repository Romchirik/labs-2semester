#include <stdio.h>

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int n;
    scanf("%d", &n);

    long int fib_num[1000] = {1, 1};
    for (int i = 2; i < n + 2; i++)
        fib_num[i] = fib_num[i - 2] + fib_num[i - 1];

    printf("%ld", fib_num[n + 1]);
}
