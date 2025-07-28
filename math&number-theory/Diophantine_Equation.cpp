bool Diophantine_Equation(int a, int b, int c, int &x0, int &y0) {
    int g = Ex_Euc(a, b, x0, y0);
    if (c % g) return false;
    x0 *= c / g;
    y0 *= c / g;
    return true;
}
