
#include <vector> 

extern "C" bool isPrime1(int n) {
    if (n <= 1) return false;
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}
extern "C" int PrimeCountNaive(int A, int B) {
    int count = 0;
    for (int i = A; i <= B; ++i) {
        if (isPrime1(i)) {
            count += 1;
        }
    }
    return count;
}


extern "C" int PrimeCountSieve(int A, int B) {
    if (A > B) {
        return 0;
    }

    std::vector<bool> is_prime(B + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int p = 2; p * p <= B; ++p) {
        if (is_prime[p]) {
            for (int i = p * p; i <= B; i += p)
                is_prime[i] = false;
        }
    }

    int count = 0;
    for (int p = A; p <= B; ++p) {
        if (is_prime[p]) {
            count++;
        }
    }
    return count;
}
