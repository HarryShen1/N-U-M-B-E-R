// Hi Harry! How are you doing :)

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

default_random_engine generator;
uniform_int_distribution<int> random_positive_integer(0, RAND_MAX);

// ^ I think we're gonna need randomness eventually, just putting this in for now

// Helper Code
int *generate_random_prepartition(int n) {
    // Random list of numbers 1 through n of length n
    return nullptr; // TODO
}

int *generate_random_prepartition_move(int *source, int n) {
    // Take random i, j with source[i] != j, then set source[i] = j
    return nullptr; // TODO
}

int *generate_random_solution(int n) {
    // Returns a random list of length n 
    // List consists of +1 and -1, signs of the solution
    return nullptr; // TODO
}

int *generate_random_move(int *source, int n) {
    // Take two random indices i, j with i \neq j
    // flip i 
    // flip j with probability .5
    return nullptr; // TODO
}

// Algs themselves
int karmarkar_karp(long long *instance) {
    return -1; // TODO
}

int repeated_random(long long* instance, bool prepartitioned) {
    return -1; // TODO
}

int hill_climbing(long long* instance, bool prepartitioned) {
    return -1; // TODO
}

int simulated_annealing(long long* instance, bool prepartitioned) {
    return -1; // TODO
}

// Main Helper Code
long long *generate_random_instance(int n) {
    return nullptr; // TODO
}

long long *get_instance(string filename, int n) {
    return nullptr; // TODO
}

// Main Function :D
int main(int argc, const char * argv[]) {
    int flag = atoi(argv[1]);
    int algorithm = atoi(argv[2]);

    string filename;
    if (argc > 3) filename = argv[3]; 

    // 0 is for autograder
    // 1 is for debug/test
    // 2 is for the "run 50 times"
    if (flag == 0) {

    }
    else if (flag == 1) {

    }
    else if (flag == 2) {

    }
}


