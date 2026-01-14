#include <iostream>
using namespace std;
int main(){
    int s, l, n;
            cout << "Введите расстояние на полном баке (S): ";
            cin >> s;
            cout << "Введите общее расстояние (L): ";
            cin >> l;
            cout << "Введите количество участков между заправками: ";
            cin >> n;

            int* d = new int[n];
            cout << "Введите расстояния между заправками: ";
            for (int i = 0; i < n; i++) {
                cin >> d[i];
            }

            int fuel = s;
            int stations_count = 1;
            int* stations = new int[n + 2];
            stations[0] = 1;

            for (int i = 0; i < n; i++) {
                if (fuel >= d[i]) {
                    fuel -= d[i];
                } else {
                    stations[stations_count] = i + 2;
                    stations_count++;
                    fuel = s - d[i];
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

            delete[] d;
            delete[] stations;
        return 0;
}
