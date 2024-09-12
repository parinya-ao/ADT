#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// Function to check if two characters are equal or if one of them is a wildcard '?'
bool charMatch(char a, char b) {
    return (a == b) || (a == '?') || (b == '?');
}

// Function to check if a substring matches the pattern
bool isMatch(char *str, char *pattern, int start, int p_len) {
    for (int i = 0; i < p_len; i++) {
        if (!charMatch(str[start + i], pattern[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    int n, p, m;

    // Read n, p, m
    scanf("%d %d %d", &n, &p, &m);

    // Allocate memory for strings
    char str[m + 1];
    char pattern[p + 1];

    // Read the input string and the pattern
    scanf("%s", str);
    scanf("%s", pattern);

    // Loop through the string and check for matches
    for (int i = 0; i <= m - p; i++) {
        if (isMatch(str, pattern, i, p)) {
            printf("%i\n", i);
        }
    }

    return 0;
}
