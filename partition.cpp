// Hi Harry! How are you doing :)

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <fstream>
#include <array>
#include <queue>

using namespace std;
using namespace std::chrono;

default_random_engine generator;
uniform_int_distribution<int> random_positive_integer(0, RAND_MAX);
uniform_real_distribution<float> uniform(0, 1);
uniform_int_distribution<long long int> big_positive_integer(0, std::llround(std::pow(2,62)));
// ^ I think we're gonna need randomness eventually, just putting this in for now

const int max_iter = 30000;

// Helper Code
int *generate_random_prepartition(int n) {
    int *prep = new int[n];
    for (int i = 0; i < n; i++) {
        prep[i] = random_positive_integer(generator)%n + 1;
    }
    return prep;
}

pair<int, int> generate_random_prepartition_move(int *source, int n) {
    int i = random_positive_integer(generator)%n;
    int old = source[i];
    int j = random_positive_integer(generator)%(n-1);
    if (j == i) j = n-1;
    source[i] = j;
    // Take random i, j with source[i] != j, then set source[i] = j
    return pair(i, old);
}

void undo_prep_move(int *source, pair<int, int> move) {
    source[move.first] = move.second;
}

int *generate_random_solution(int n) {
    int *prep = new int[n];
        int r = 0;
        for (int i = 0; i < n; i++) {
            if (!(i%16)) {
                r = random_positive_integer(generator);
            }
            prep[i] = 2*(r & 1) - 1;
            r = r >> 1;
        }
    return prep; 
}

pair<int, int> generate_random_move(int *source, int n) {
    int i = random_positive_integer(generator)%n;
    
    source[i] *= -1;

    int j = -1;
    // 1 50% of the time
    int flip_j = random_positive_integer(generator) & 1;

    if (flip_j) {
        j = random_positive_integer(generator)%(n-1);
        if (j == i) j = n - 1;
        source[j] *= -1;
    }

    return pair(i, j); // TODO
}

void undo_random_move(int *source, pair<int, int> move) {
    source[move.first] *= -1;
    if (move.second != -1) source[move.second] *= -1;
}

long long value_normal(int *solution, long long *instance, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += solution[i] * instance[i];
    }
    return sum;
}

long long* transform_instance(int *solution, long long *instance, int n) {
    long long *normal_instance = new long long[n];
    for (int i = 0; i < n; i++) { normal_instance[i] = 0; }
    for (int i = 0; i < n; i++) {
        normal_instance[solution[i]] += instance[i];
    }
    return normal_instance;
}

// Algs themselves
long long karmarkar_karp(long long *instance, int n) {
    priority_queue<long long> maxHeap;
    for (int i = 0;i<n;i++){ 
        maxHeap.push(instance[i]); 
    }
    while (maxHeap.size() > 1){
        long long largest1 = maxHeap.top();
        maxHeap.pop();
        long long largest2 = maxHeap.top();
        maxHeap.pop();
        maxHeap.push(largest1-largest2);
    }
    return maxHeap.top(); // TODO
}

long long value_prepartitioned(int *solution, long long *instance, int n) {
    return karmarkar_karp(transform_instance(solution, instance, n), n);
}

pair<long long, int*> repeated_random(long long* instance, bool prepartitioned, int n) {
    int *solution = prepartitioned ? generate_random_prepartition(n) : generate_random_solution(n);
    long long value = prepartitioned ? value_prepartitioned(solution, instance, n) : value_normal(solution, instance, n);
    for (int i = 0; i < max_iter; i++) {
        int *solution2 = prepartitioned ? generate_random_prepartition(n) : generate_random_solution(n);
        long long value2 =  prepartitioned ? value_prepartitioned(solution2, instance, n) : value_normal(solution2, instance, n);
        if (abs(value2) < abs(value)) {
            solution = solution2;
            value = value2;
        }
    }
    return pair(abs(value), solution); // TODO
}

pair<long long, int*> hill_climbing(long long* instance, bool prepartitioned, int n) {
    int *solution = prepartitioned ? generate_random_prepartition(n) : generate_random_solution(n);
    long long value = prepartitioned ? value_prepartitioned(solution, instance, n) :  value_normal(solution, instance, n);

    for (int i = 0; i < max_iter; i++) {
        pair<int, int> move = prepartitioned ? generate_random_prepartition_move(solution, n) : generate_random_move(solution, n);
        // long long value2 = value_normal(solution, instance, n);
        long long value2;
        if (!prepartitioned) {
            value2 = value + 2 * solution[move.first] * instance[move.first];
            if (move.second != -1) value2 += 2 * solution[move.second] * instance[move.second];
        }
        else {
            value2 = value_prepartitioned(solution, instance, n);
        }

        if (abs(value2) < abs(value)) {
            value = value2;
        }
        else {
            if (prepartitioned) undo_prep_move(solution, move); else undo_random_move(solution, move);
        }
    }
    return pair(abs(value), solution);
}

double T(int i) {
    return pow(10, 10) * pow(0.8, i/300.0);
}

bool test_prob(int value, int value2, int i) {
    double p = exp(-(abs(value2) - abs(value))/T(i));
    return uniform(generator) < p;
}

pair<long long, int*> simulated_annealing(long long* instance, bool prepartitioned, int n) {
    int *solution = prepartitioned ? generate_random_prepartition(n) : generate_random_solution(n);
    int *best = new int[n];
    copy(solution, solution + n, best);

    long long value = prepartitioned ? value_prepartitioned(solution, instance, n) :  value_normal(solution, instance, n);
    long long best_value = value;

    cout << "\n";
    for (int i = 0; i < max_iter; i++) {
        // cout << i << ", " << best_value << "\n";
        pair<int, int> move = prepartitioned ? generate_random_prepartition_move(solution, n) : generate_random_move(solution, n);
        long long value2;
        if (!prepartitioned) {
            value2 = value + 2 * solution[move.first] * instance[move.first];
            if (move.second != -1) value2 += 2 * solution[move.second] * instance[move.second];
        }
        else {
            value2 = value_prepartitioned(solution, instance, n);
        }

        if (abs(value2) < abs(value)) {
            value = value2;

            if (abs(value) < abs(best_value)) {
                best_value = value;
                copy(solution, solution + n, best);
            }
        }
        else {
            if (test_prob(value, value2, i)) {
                value = value2;
            }
            else {
                if (prepartitioned) undo_prep_move(solution, move); else undo_random_move(solution, move);
            }
        }
    }
    // cout << "\n";
    return pair(abs(best_value), best);
}

// Main Helper Code
long long *generate_random_instance(int n) {
    long long *instance = new long long[n];
    for (int i = 0; i < n; i++) {
        instance[i] = big_positive_integer(generator);
    }
    return instance; // TODO
}

long long *get_instance(string filename, int n) {
    fstream infile;

    infile.open(filename, ios::in); 
    string value;

    long long *instance = new long long[n];
    for (int i = 0; i < n; i++) {
        getline(infile, value);
        instance[i] = stol(value);
    }

    return instance;
}

pair<long long, int*> run_algorithm(long long* instance, int n, int alg) {
    if (alg == 0) {
        return pair(karmarkar_karp(instance, n), nullptr);
    }
    int prep = alg/10;
    alg = alg%10;
    if (alg == 1) {
        return repeated_random(instance, prep, n);
    }
    if (alg == 2) {
        return hill_climbing(instance, prep, n);
    }
    if (alg == 3) {
        return simulated_annealing(instance, prep, n);
    }
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
        long long *instance = get_instance(filename, 100);
        pair<int, int*> p = run_algorithm(instance, 100, algorithm);
        cout << p.first << "\n";
    }
    else if (flag == 1) {
        int N = 100;

        long long *instance;

        if (argc > 3) instance = get_instance(filename, N);
        else instance = generate_random_instance(N);

        for (int i = 0; i < N; i++) {
            cout << instance[i] << " ";
        }
        cout << "\n";

        pair<long long, int*> p = run_algorithm(instance, N, algorithm);
        for (int i = 0; i < N; i++) {
            cout << p.second[i] << " ";
        }
        cout << "\n";
        cout << p.first << " : " << log(p.first) << "\n";

        cout << "\nVerifying: \n";
        if (algorithm < 10) {
            
            long long sum = 0;
            for (int i = 0; i < N; i++) {
                sum += p.second[i] * instance[i];
            }
            cout << log(abs(sum)) << "\n";
            cout << "\nComparing to Our Function:\n";
            cout << log(abs(value_normal(p.second, instance, N)));
            cout << "\nComparing to Random Solution: \n"; 

            int *sol = generate_random_solution(N);
            sum = 0;
            for (int i = 0; i < N; i++) {
                sum += sol[i] * instance[i];
            }
            cout << log(abs(sum)) << "\n";
        }
        else {
            long long value = value_prepartitioned(p.second, instance, N);
            cout << log(abs(value)) << "\n";

            cout << "\nComparing to Random Solution: \n"; 

            int *sol = generate_random_prepartition(N);
            cout << log(abs(value_prepartitioned(sol, instance, N))) << "\n";
        }
    }
    else if (flag == 2) {

    }
}
