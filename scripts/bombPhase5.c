#include <stdio.h>

// target indexes in array_123: 15, 0, 5, 11, 13, 1

int main() {
    char s[6] = "aaaaaa";
    int target[6] = {15, 0, 5, 11, 13, 1};
    int j;

    for (int i = 0; i < 6; i++) {
        j = -1;
        while (j != target[i]) {
            s[i]++;
            j = s[i] & 0xF;
        }
    }
    for (int i = 0; i < 6; i++) {
        printf("%c", s[i]);
    }
    printf("\n");
    return 0;
}