// Hi Harry! How are you doing :)

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>

using namespace std;
using namespace std::chrono;

default_random_engine generator;
// ^ I think we're gonna need randomness eventually, just putting this in for now

// Helper Code
int *generate_random_prepartition(int n) {
    return nullptr; // TODO
}

int *generate_random_prepartition_move(int *source, int n) {
    return nullptr; // TODO
}

int *generate_random_solution(int n) {
    return nullptr; // TODO
}

int *generate_random_move(int *source, int n) {
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


