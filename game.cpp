#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int max_size = 10;

int map[max_size][max_size]; // mảng lưu trữ bản đồ mìn
bool opened[max_size][max_size]; // mảng lưu trữ các ô đã được mở hay chưa

// Hàm khởi tạo bản đồ mìn
void initMap(int m, int n, int K) {
    srand(time(NULL)); // khởi tạo seed cho hàm sinh số ngẫu nhiên
    int cout = 0;
    while (cout < K) { // sinh K quả mìn
        int i = rand() % m;
        int j = rand() % n;
        if (map[i][j] == 0) { // nếu ô này chưa có mìn thì đặt mìn vào
            map[i][j] = -1;
            cout++;
        }
    }
}

// Hàm đếm số mìn xung quanh ô (i, j)
int countMinesAround(int i, int j, int m, int n) {
    int cout = 0;
    for (int x = max(i-1, 0); x <= min(i+1, m-1); x++) {
        for (int y = max(j-1, 0); y <= min(j+1, n-1); y++) {
            if (map[x][y] == -1) cout++;
        }
    }
    return cout;
}

// Hàm in bản đồ với các ô đã được mở
void printMap(int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (opened[i][j]) {
                if (map[i][j] == -1) cout << "* ";
                else cout << countMinesAround(i, j, m, n) << " ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

int main() {
    int m, n, K;
    cout << "Enter m, n, K (m, n < 10, K < m*n): ";
    cin >> m >> n >> K;

    initMap(m, n, K);

    while (true) {
        int x, y;
        cout << "Enter coordinate (x, y): ";
        cin >> x >> y;

        if (map[x][y] == -1) { // trường hợp đúng vào ô có mìn
            cout << "YOU'RE DEAD!" << endl;
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (map[i][j] == -1) cout << "* ";
                    else cout << countMinesAround(i, j, m, n) << " ";
                }
                cout << endl;
            }
            break;
        } else {
            opened[x][y] = true;
            printMap(m, n);
        }
    }

    return 0;
}
