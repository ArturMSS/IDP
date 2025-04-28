#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x, double A, double B, double C) {
    return A * x + B * sin(x) - C;
}

double df(double x, double A, double B) {
    return A + B * cos(x);
}

double encontrarX(double A, double B, double C) {
    double x = 0.0; // chute inicial
    const double epsilon = 1e-7;
    const int maxIter = 1000;

    for (int i = 0; i < maxIter; ++i) {
        double fx = f(x, A, B, C);
        double dfx = df(x, A, B);

        if (fabs(dfx) < 1e-10) {
            cerr << "Derivada muito próxima de zero, método pode falhar." << endl;
            break;
        }

        double xNovo = x - fx / dfx;

        if (fabs(xNovo - x) < epsilon)
            return xNovo;

        x = xNovo;
    }

    cerr << "Método de Newton-Raphson não convergiu." << endl;
    return x;
}

int main() {
    double A, B, C;
    cin >> A >> B >> C;

    double x = encontrarX(A, B, C);

    cout << fixed << setprecision(4);
    cout <<  x << endl;

    return 0;
}
