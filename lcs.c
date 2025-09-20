#include <stdio.h>
#include <string.h>

struct Cell {
    int value;
    char dir; // 'd' = diagonal, 'u' = up, 's' = side, 'h' = init
};

struct Cell c[100][100]; 

void lcs(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                c[i][j].value = 0;
                c[i][j].dir = 'h'; // boundary
            }
            else {
                if (X[i-1] != Y[j-1]) {  // FIXED indexing
                    if (c[i-1][j].value > c[i][j-1].value) {  // FIXED tie case
                        c[i][j].value = c[i-1][j].value;
                        c[i][j].dir = 'u';
                    } else {
                        c[i][j].value = c[i][j-1].value;
                        c[i][j].dir = 's';
                    }
                }
                else {  // match
                    c[i][j].value = c[i-1][j-1].value + 1;
                    c[i][j].dir = 'd';
                }
            }
        }
    }
}

// Recursive function to print LCS
void printLCS(char X[], int i, int j) {
    if (i == 0 || j == 0) return;

    if (c[i][j].dir == 'd') {
        printLCS(X, i-1, j-1);
        printf("%c", X[i-1]);
    }
    else if (c[i][j].dir == 'u') {
        printLCS(X, i-1, j);
    }
    else {
        printLCS(X, i, j-1);
    }
}

// Function to print matrix with values and directions
void printMatrix(char X[], char Y[]) {
    int m = strlen(X);
    int n = strlen(Y);

    printf("\nCost matrix (value,dir):\n     ");
    for (int j = 0; j < n; j++) {
        printf("   %c", Y[j]);
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i > 0) printf(" %c ", X[i-1]);
        else printf("   ");

        for (int j = 0; j <= n; j++) {
            printf(" %2d%c", c[i][j].value, c[i][j].dir);
        }
        printf("\n");
    }
}

int main() {
    char X[] = "AGCCCTAAGGGCTACCTAGCTT";
    char Y[] = "GACAGCCTACAAGCGTTAGCTTG";

    printf("String X: %s\n", X);
    printf("String Y: %s\n", Y);

    lcs(X, Y);
    printMatrix(X, Y);

    printf("\nLength of LCS = %d\n", c[strlen(X)][strlen(Y)].value);
    printf("LCS sequence = ");
    printLCS(X, strlen(X), strlen(Y));
    printf("\n");

    return 0;
}
