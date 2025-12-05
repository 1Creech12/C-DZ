#include <iostream>
#include <vector>

using namespace std;

double det(vector<vector<double>> m) {
    int n = m.size();
    double d = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double f = m[j][i] / m[i][i];
            for (int k = i; k < n; k++) {
                m[j][k] -= f * m[i][k];
            }
        }
        d *= m[i][i];
    }
    
    return d;
}

vector<double> solve(vector<vector<double>> a, vector<double> b) {
    int n = a.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            double f = a[j][i] / a[i][i];
            for (int k = i; k < n; k++) {
                a[j][k] -= f * a[i][k];
            }
            b[j] -= f * b[i];
        }
    }
    
    vector<double> x(n);
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] /= a[i][i];
    }
    
    return x;
}

vector<vector<double>> inv(vector<vector<double>> a) {
    int n = a.size();
    vector<vector<double>> res(n, vector<double>(n, 0));
    
    for (int i = 0; i < n; i++) {
        vector<double> b(n, 0);
        b[i] = 1;
        vector<double> col = solve(a, b);
        for (int j = 0; j < n; j++) {
            res[j][i] = col[j];
        }
    }
    
    return res;
}

int main() {
    // Задание 1a
    vector<vector<double>> A1 = {
        {8.39, -8.99, -1.29},
        {-1.05, 1.89, 4.91},
        {-6.38, 8.36, 0.48}
    };
    vector<double> b1 = {8.86, 4.20, -5.06};
    
    vector<double> x = solve(A1, b1);
    cout << "Решение: ";
    for (double v : x) cout << v << " ";
    cout << endl;
    
    // Задание 2
    vector<vector<double>> A2 = {
        {6.44, 1.90, 0.35},
        {6.64, 5.24, -8.02},
        {1.39, -1.00, -0.20}
    };
    
    cout << "Определитель: " << det(A2) << endl;
    
    // Задание 3
    vector<vector<double>> A3 = {
        {8.47, 4.22, 4.07},
        {1.49, 6.92, 5.82},
        {2.42, -0.88, -5.24}
    };
    
    vector<vector<double>> invA = inv(A3);
    cout << "Обратная матрица:\n";
    for (auto row : invA) {
        for (double v : row) cout << v << " ";
        cout << endl;
    }
    
    return 0;
}