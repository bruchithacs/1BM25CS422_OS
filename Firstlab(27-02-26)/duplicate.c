#include <stdio.h>

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    int visited[n];   // To mark counted elements
    int count = 0;

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        visited[i] = 0;  // Initialize visited array
    }

    for (int i = 0; i < n; i++) {
        if (visited[i] == 1)
            continue;

        int duplicateFound = 0;

        for (int j = i + 1; j < n; j++) {
            if (arr[i] == arr[j]) {
                visited[j] = 1;
                duplicateFound = 1;
            }
        }

        if (duplicateFound)
            count++;
    }

    printf("Total number of duplicate elements = %d\n", count);

    return 0;
}
