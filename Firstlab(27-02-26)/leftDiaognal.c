#include <stdio.h>

int main() {
    int n;

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    int matrix[n][n];
    int sum = 0;

    printf("Enter %d x %d matrix elements:\n", n, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Sum of left (main) diagonal
    for (int i = 0; i < n; i++) {
        sum += matrix[i][i];
    }

    printf("Sum of left diagonal = %d\n", sum);

    return 0;
}
