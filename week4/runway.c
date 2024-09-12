#pragma optimize("Ofast")
#include <stdio.h>
#include <stdbool.h>

// Function to find the largest power of 2 less than or equal to n
void set_i(int *n) {
    int value = *n;
    value |= value >> 1;
    value |= value >> 2;
    value |= value >> 4;
    value |= value >> 8;
    value |= value >> 16;
    value++;
    *n = value >> 1;
}

// Recursive function to find the number of 2x2 tiles required
int find(int m, int n) {
    // Base cases
    if (n == 0 || m == 0) {
        return 0;
    }
    if (n < m) {
        int temp = n;
        n = m;
        m = temp;
    }

    int i = n;
    set_i(&i); // Find the largest power of 2 less than or equal to n

    return (m / i) * (n / i) + find(m % i, n) + find(i, n % i);
}

int main() {
    int n, m;
    scanf("%i %i", &m, &n);

    printf("%i\n", find(m, n));
    return 0;
}
