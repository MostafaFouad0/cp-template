const int mod = 1e9 + 7;
#define double long double
const double PI = acosl(-1);
using cd = complex<double>;
const cd I = cd(0, 1);

void fft(vector<cd> &A, int n, int op) {
    vector<int> r(n, 0);
    for (int i = 0; i < n; i++) r[i] = r[i / 2] / 2 + ((i % 2) ? n / 2 : 0);
    for (int i = 0; i < n; i++) if (i < r[i]) swap(A[i], A[r[i]]);
    vector<cd> wn(n);
    for (int i = 0; i < n; i++) wn[i] = exp(I * (2 * PI * i / n * op));
    for (int i = 2; i <= n; i <<= 1) {
        for (int j = 0; j < n; j += i) {
            for (int k = j; k < j + i / 2; k++) {
                cd w = wn[(k - j) * (n / i)];
                cd x = A[k], y = w * A[k + i / 2];
                A[k] = x + y;
                A[k + i / 2] = x - y;
            }
        }
    }
}

void doubleDFT(vector<cd> &a, vector<cd> &b, int n) {
    vector<cd> p(n);
    for (int i = 0; i < n; i++) p[i] = a[i] + b[i] * I;
    fft(p, n, 1);
    for (int i = 0; i < n; i++) {
        cd qi = conj(i ? p[n - i] : p[0]);
        a[i] = (p[i] + qi) / cd(2);
        b[i] = (qi - p[i]) * I / cd(2);
    }
}

const int M = 1 << 16;

vector<int> mul(vector<int> &AA, vector<int> &BB) {
    int n = AA.size();
    int m = BB.size();
    int cnt = 1;
    while (cnt <= n + m) cnt <<= 1;
    vector<cd> A(cnt), B(cnt), T(cnt);
    for (int i = 0; i < n; i++) A[i] = AA[i] % M;
    for (int i = 0; i < n; i++) B[i] = AA[i] / M;
    for (int i = 0; i < m; i++) T[i] = cd(BB[i] % M, BB[i] / M);

    doubleDFT(A, B, cnt), fft(T, cnt, 1);
    for (int i = 0; i < cnt; i++) {
        A[i] *= T[i], B[i] *= T[i];
    }
    fft(A, cnt, -1), fft(B, cnt, -1);
    AA.resize(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        A[i] /= cnt, B[i] /= cnt;
        int x0 = (llround(A[i].real()));
        int x1 = (llround(A[i].imag() + B[i].real())) % mod * M;
        int x2 = (llround(B[i].imag())) % mod * M % mod * M;
        AA[i] = (x0 + x1 + x2) % mod;
    }
    return AA;
}
