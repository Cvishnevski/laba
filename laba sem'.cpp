#include <iostream>
#include <cmath>
using namespace std;

double f(double x) {
    return log(x) - 5 * cos(x);
}

double lagrange(double x, double* xi, double* yi, int m) {
    double result = 0;
    for (int i = 0; i < m; i++) {
        double term = yi[i];
        for (int j = 0; j < m; j++) {
            if (i != j) {
                term *= (x - xi[j]) / (xi[i] - xi[j]);
            }
        }
        result += term;
    }
    return result;
}

int main() {
    setlocale(0, "");
    const int m = 4;
    const int n = 4;
    const int numPoints = 21;
    double a = 1;
    double b = 8;

    double xi[m];
    double yi[m];
    for (int i = 0; i < m; i++) {
        xi[i] = a + i * (b - a) / (m - 1);
        yi[i] = f(xi[i]);
    }

    double xj[numPoints];
    double fj[numPoints];


    for (int j = 0; j < numPoints; j++) {
        xj[j] = a + j * (b - a) / (numPoints - 1);
        fj[j] = f(xj[j]);

    }

    // Вывод результатов в консоль
    cout << "Таблица значений:" << endl;
    cout << "xj" << "\t" << "fj" << "\t" << "  " << endl;
    cout.precision(3);
    for (int j = 0; j < numPoints; j++) {
        cout << xj[j] << "\t" << fj[j] << "\t" << endl;
    }

    cout << "Корни уравнения:" << endl;
    for (int i = 0; i < m - 1; i++) {
        double x1 = xi[i];
        double x2 = xi[i + 1];
        if (f(x1) * f(x2) < 0) {
            double c = (x1 + x2) / 2;
            double tc = lagrange(c, xi, yi, m);
            double eps = 1e-6;
            int iter = 0;
            while (abs(f(c)) > eps && iter < 100) {
                if (f(c) * f(x1) < 0) {
                    x2 = c;
                }
                else {
                    x1 = c;
                }
                c = (x1 + x2) / 2;
                tc = lagrange(c, xi, yi, m);
                iter++;
            }
            cout << c << endl;
        }
    }

    return 0;
}
