#include <stdio.h>


// 1.7
// Rotate Matrix: Given an image represented by an NxN matrix, where each pixel in the image is 4
// bytes, write a method to rotate the image by 90 degrees. (an you do this in place?

static void rotate(int n, int (*a)[n]) { // O (n^2)
    if (!a  || !n) return;

    for (int i = 0; i < n/2; i++) { // for each layer
        for (int j = i; j < n - 1 - i; j++) {
            // save left, top
            int temp = a[i][j];
            // bottom, left -> left, top
            a[i][j]         = a[n - 1 - j][i];
            // right, bottom -> left, bottom
            a[n - 1 - j][i] = a[n - 1 - i][n - 1 - j];
            // right, top -> right, bottom
            a[n - 1 - i][n - 1 - j] = a[j][n - 1 - i];
            // save -> right, top
            a[j][n - 1 - i] = temp;
        }
    }
}


static void print_matrix(int n, int (*a)[n]) {
    printf("{\n\t");
    for (int i = 0; i < n; i ++) {
        for(int j = 0; j < n; j++)
            printf("%3d ", a[i][j]);
        printf("\n\t");
    }
    printf("\b}\n\n");
}

int main() {
    int n = 5;
    int array[5][5] = {
            {  1,  2,  3,  4,  5  },
            {  5,  6,  7,  8,  9  },
            { 10, 11, 12, 13, 14, },
            { 15, 16, 17, 18, 19, },
            { 20, 21, 22, 23, 24  },
    };

    print_matrix(n, array);

    rotate(n, array);

    print_matrix(n, array);

    return 0;
}