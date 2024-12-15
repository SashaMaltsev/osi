

extern "C" float PiLeibniz(int K) {
    float pi = 0.0;
    float sign = 1.0;
    for (int i = 0; i < K; ++i) {
        pi += sign / (2.0 * i + 1.0);
        sign *= -1.0;
    }
    return 4.0 * pi;
}

extern "C" float PiWallis(int K) {
    float res = 1;
    for (int i = 1; i <= K; ++i) {
        res *= (((2.0 * i) / (2.0 * i - 1)) * ((2.0 * i) / (2.0 * i + 1)));
    }
    return res * 2.0;
}