// Şevval Çakmak 22118080010 CENG205_assignment1
#include <stdio.h>
#define MAX_SIZE 101

void readUpperTriangularMatrix(FILE *file, int *arr, int n);                       // reads integers from the file and assign them to 1D array
int *multiplication(int *arrayA, int *arrayB, int n);                              // multiplicates two arrays and returns the results of the multiplication
void convertUpperTriangularMatrix1Dto2D(int *arr1D, int arr2D[][MAX_SIZE], int n); // converts 1D array multiplication results to 2D array by including all zeros
void print1DArr(int *arr, int size);                                               // prints 1D arrays
void print2DArr(int arr[][MAX_SIZE], int n);                                       // prints 2D arrays

int main(int argc, char const *argv[]){
    // define instance variables
    int n;
    int size;
    int arrayA[MAX_SIZE];
    int arrayB[MAX_SIZE];
    int *arrayC;
    int multiplication2D[MAX_SIZE][MAX_SIZE]; // define 2D array to print multiplication result as a matrix(2D array)
    FILE *file;

    file = fopen("input.txt", "r");             //open the file
    fscanf(file, "%d", &n);                     // reads first integer which contains "n"
    size = n * (n + 1) / 2;                     // calculate the size with the formula with "n"
    readUpperTriangularMatrix(file, arrayA, n); // function reads as many integers as there are elements of the upper triangular matrix.
    readUpperTriangularMatrix(file, arrayB, n); // function reads as many integers as there are elements of the upper triangular matrix.
    fclose(file);                               // close the file

    arrayC = multiplication(arrayA, arrayB, n);                      // multiplicates arrayA and arrayB and assign the multiplication function result to arrayC
    convertUpperTriangularMatrix1Dto2D(arrayC, multiplication2D, n); // arrayC's values stored to 2D array by including all zeros
    print1DArr(arrayC, size);                                        // print multiplication result as 1D array format
    print2DArr(multiplication2D, n);                                 // print multiplication result as 2D array format
    return 0;
}

void readUpperTriangularMatrix(FILE *file, int *arr, int n){ // reads integers from the file and assign them to 1D array
    int size = n * (n + 1) / 2; // formula of size
    for (int i = 0; i < size; i++)
    {
        for (int j = i; j < n; j++) // i to n because it is upper triangular matrix
        {
            fscanf(file, "%d", &arr[n * i + j - i * (i + 1) / 2]); // reads integers from the file and assigns them to the position of arr[i][j] in the 1D array
        }
    }
}

int *multiplication(int *arrayA, int *arrayB, int n){ // multiplicates two arrays and returns the results of the multiplication
    int i, j, k;
    static int arrayC[MAX_SIZE]; // using static to return pointer(arrayC)
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++) // i to n because it is upper triangular matrix
        {
            arrayC[n * i + j - i * (i + 1) / 2] = 0;                                                                              // assign initial value to zero
            for (k = i; k <= j; k++)                                                                                              // arrayC[i][j] += arrayA[i][k] * ArrayB[k][j]
            {                                                                                                                     // implement our formula to 1D arrays (the position of arr[i][j] = n * i + j - i * (i + 1) / 2)
                arrayC[n * i + j - i * (i + 1) / 2] += arrayA[n * i + k - i * (i + 1) / 2] * arrayB[n * k + j - k * (k + 1) / 2]; // summing the products of elements
            }
        }
    }
    return arrayC; // return pointer of multiplication array
}

void convertUpperTriangularMatrix1Dto2D(int *arr1D, int arr2D[][MAX_SIZE], int n){ // convert 1D array multiplication results to 2D array by including all zeros
    for (int i = 0; i < n; i++) // each row of the matrix
    {
        for (int j = 0; j < n; j++) // each column of the each row
        {
            if (i <= j) // if it is non-zero element (upper triangular)
            {
                arr2D[i][j] = arr1D[n * i + j - i * (i + 1) / 2]; // the position of arr[i][j] in the 1D array formula
            }
            else // otherwise the other elements are zero
            {
                arr2D[i][j] = 0;
            }
        }
    }
}

void print1DArr(int *arr, int size){ // prints 1D arrays
    for (int a = 0; a < size; a++)
    {
        printf("%d ", arr[a]);
    }
    printf("\n");
}

void print2DArr(int arr[][MAX_SIZE], int n){ // prints 2D arrays
    printf("\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d\t", arr[i][j]);
        }
        printf("\n"); // next line after printing each row
    }
}