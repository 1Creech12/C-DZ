#include <iostream>
using namespace std;
int main(){
    int S, L, N;
            cout << "Введите расстояние на полном баке (S): ";
            cin >> S;
            cout << "Введите общее расстояние (L): ";
            cin >> L;
            cout << "Введите количество участков между заправками: ";
            cin >> N;

            int* D = new int[N];
            cout << "Введите расстояния между заправками: ";
            for (int i = 0; i < N; i++) {
                cin >> D[i];
            }

            int fuel = S;
            int stations_count = 1;
            int* stations = new int[N + 2];
            stations[0] = 1;

            for (int i = 0; i < N; i++) {
                if (fuel >= D[i]) {
                    fuel -= D[i];
                } else {
                    stations[stations_count] = i + 2;
                    stations_count++;
                    fuel = S - D[i];
                }
            }

            if (stations_count > 0) {
                cout << "Минимальное количество заправок: " << stations_count - 1 << endl;
                cout << "Номера заправок: ";
                for (int j = 0; j < stations_count; j++) {
                    cout << stations[j] << " ";
                }
                cout << endl;
            }

            delete[] D;
            delete[] stations;
        return 0;
}
