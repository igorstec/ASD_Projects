#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>
#include <stdbool.h>

using namespace std;
using namespace chrono;

#define MOD 1000000000

long long szybkiePotegowanieModulo(long long podstawa, long long wykladnik, long long modulo) {
    podstawa %= modulo;
    long long wynik = 1;
    while (wykladnik > 0) {
        if (wykladnik & 1) {
            wynik = (wynik * podstawa) % modulo;
        }
        wykladnik >>= 1;
        podstawa = (podstawa * podstawa) % modulo;
    }
    return wynik;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, g;
    cin >> n >> m >> k >> g;

    vector grzyby(n, vector<bool>(m, false));

    for (int i = 0; i < g; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        grzyby[a][b] = true;;
    }

    if (k == 0) {
        cout << szybkiePotegowanieModulo(n, m - 1, MOD) << '\n';
        return 0;
    }

    vector<vector<int> > nastepnaKolumna(n, vector<int>(k + 1, 0));
    vector<vector<int> > nastepnaTemp(n, vector<int>(k + 1, 0));
    vector<vector<int> > obecnaKolumna(n, vector<int>(k + 1, 0));

    if (grzyby[0][0]) {
        obecnaKolumna[0][1]++;
    } else {
        obecnaKolumna[0][0]++;
    }

    int ile = grzyby[0][0];
    for (int i = 1; i < n; i++) {
        if (!grzyby[i][0]) {
            obecnaKolumna[i] = obecnaKolumna[i - 1];
        } else {
            ile = ile < k ? ile + 1 : k;
            obecnaKolumna[i][ile]++;
        }
    }

    for (int kolumna = 1; kolumna < m; kolumna++) {
        // Wylicz wartosci w nastepnej kolumnie po przejsciu bez posrednio z poprzedniej kolumny i zapisz wynik w obecnejKolumnie
        for (int i = 0; i < n; i++) {
            if (grzyby[i][kolumna]) {
                for (int j = k - 1; j >= 1; j--) {
                    nastepnaTemp[i][j] = obecnaKolumna[i][j - 1];
                }
                nastepnaTemp[i][k] = (obecnaKolumna[i][k - 1] + obecnaKolumna[i][k]) % MOD;
                nastepnaTemp[i][0] = 0;
            } else {
                for (int j = 0; j <= k; j++) {
                    nastepnaTemp[i][j] = obecnaKolumna[i][j];
                }
            }
        }

        nastepnaKolumna = nastepnaTemp;
        obecnaKolumna = nastepnaKolumna;

        for (int i = 1; i < n; i++) {
            if (grzyby[i][kolumna] == false) {
                for (int j = 0; j <= k; j++) {
                    nastepnaTemp[i][j] = (nastepnaTemp[i][j] + nastepnaTemp[i - 1][j]) % MOD;
                }
            } else {
                nastepnaTemp[i][0] = 0;
                for (int j = 1; j <= k; j++) {
                    nastepnaTemp[i][j] = (nastepnaTemp[i][j] + nastepnaTemp[i - 1][j - 1]) % MOD;
                    if (j == k) {
                        nastepnaTemp[i][j] = (nastepnaTemp[i][j] + nastepnaTemp[i - 1][j]) % MOD;
                    }
                }
            }
        }

        for (int i = n - 2; i >= 0; i--) {
            if (grzyby[i][kolumna] == false) {
                for (int j = 0; j <= k; j++) {
                    nastepnaKolumna[i][j] = (nastepnaKolumna[i][j] + nastepnaKolumna[i + 1][j]) % MOD;
                }
            } else {
                nastepnaKolumna[i][0] = 0;
                for (int j = 1; j <= k; j++) {
                    nastepnaKolumna[i][j] = (nastepnaKolumna[i][j] + nastepnaKolumna[i + 1][j - 1]) % MOD;
                    if (j == k) {
                        nastepnaKolumna[i][j] = (nastepnaKolumna[i][j] + nastepnaKolumna[i + 1][j]) % MOD;
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= k; j++) {
                nastepnaKolumna[i][j] = (nastepnaKolumna[i][j] - obecnaKolumna[i][j] + MOD) % MOD;
                nastepnaKolumna[i][j] = (nastepnaKolumna[i][j] + nastepnaTemp[i][j]) % MOD;
            }
        }
        obecnaKolumna = nastepnaKolumna;
    }

    cout << obecnaKolumna[n - 1][k] << '\n';

    return 0;
}
