#include <stdio.h>

// Function to add two integers
int add(int a, int b) {
    return a + b;
}

// Function to subtract two integers
int sub(int a, int b) {
    return a - b;
}

// Function to multiply two integers
int mul(int a, int b) {
    return a * b;
}

// Function to divide two integers (integer division)
int div(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Division by zero\n");
        return 0;
    }
    return a / b;
}

// Function to calculate the modulus of two integers
int mod(int a, int b) {
    if (b == 0) {
        fprintf(stderr, "Modulus by zero\n");
        return 0;
    }
    return a % b;
}
