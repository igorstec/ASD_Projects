#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>

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

void przesunWMiejscu(vector<int> &v, int przesuniecie) {
    if (przesuniecie == 0 || v.empty()) return;
    int pierwszyElement = v[0];
    int rozmiar = v.size();

    for (int i = rozmiar - 1; i >= przesuniecie; --i) {
        v[i] = v[i - przesuniecie];
    }

    for (int i = 0; i < przesuniecie && i < rozmiar; ++i) {
        v[i] = pierwszyElement;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n, m, k, g;
    cin >> n >> m >> k >> g;

    vector<vector<int> > grzyby(n, vector<int>(m, 0));

    for (int i = 0; i < g; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        grzyby[a][b]++;
    }

    int iloscgrzybowpod = 0;
    for (int i = 0; i < m; i++) {
        for (int j = n - 1; j >= 0; j--) {
            iloscgrzybowpod += grzyby[j][i];
            grzyby[j][i] = iloscgrzybowpod;
        }
        iloscgrzybowpod = 0;
    }

    vector<vector<int> > nastepnaKolumna(n, vector<int>(k + 1, 0));
    vector<vector<int> > obecnaKolumna(n, vector<int>(k + 1, 0));

    for (int j = min(grzyby[0][m - 1], k); j >= 0; j--) {
        nastepnaKolumna[0][j] = 1;
    }

    //DP na ostatnia kolumne
    for (int i = 1; i < n; i++) {
        nastepnaKolumna[i] = nastepnaKolumna[i - 1];

        int ile = grzyby[i][m - 1];

        if (ile >= k || grzyby[i - 1][m - 1] == ile) {
            continue;
        }
        nastepnaKolumna[i][ile + 1] = 0;
    }
    // for(int j=0; j<n; j++) {
    //     //cout<<"nastepnaKolumna["<< j <<"] = ";
    //     for(int i=0; i<=k; i++) {
    //         cout<< nastepnaKolumna[j][i] <<" ";
    //     }
    //     cout<<endl;
    // }

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         if (i == n - 1)cout << grzyby[i][j] << " ";
    //         else
    //             cout << grzyby[i][j] - grzyby[i + 1][j]<< " ";
    //     }
    //     cout << endl;
    // }

    // cout<< "Rozpoczynam przetwarzanie kolumn..." << n << m << k << g <<endl;
    // fflush(stdout);

    //Pokolei wyliczamy scierzki
    for (int kolumna = m - 2; kolumna >= 0; kolumna--) {
        for (int wyborPrawo = 0; wyborPrawo < n; wyborPrawo++) {
            if (wyborPrawo > 0) {
                int grzyby_nie_liczone = wyborPrawo < n - 1 ? grzyby[wyborPrawo + 1][kolumna] : 0;
                if (grzyby[wyborPrawo - 1][kolumna] == grzyby_nie_liczone) {
                    obecnaKolumna[wyborPrawo] = obecnaKolumna[wyborPrawo - 1];
                    continue;
                }
            }

            fill(obecnaKolumna[wyborPrawo].begin(), obecnaKolumna[wyborPrawo].end(), 0);

            //dla kazdego kolejnego wyboru
            for (int i = 0; i < n; i++) {
                int nieliczoneGrzyby = max(wyborPrawo, i) < n - 1 ? grzyby[max(wyborPrawo, i) + 1][kolumna] : 0;
                int nowe_zebrane_grzyby = grzyby[min(wyborPrawo, i)][kolumna] - nieliczoneGrzyby;

                for (int j = 0; j <= k; j++) {
                    int ktory = j - nowe_zebrane_grzyby < 0 ? 0 : j - nowe_zebrane_grzyby;
                    obecnaKolumna[wyborPrawo][j] = (obecnaKolumna[wyborPrawo][j] + nastepnaKolumna[i][ktory]) % MOD;
                }
            }
        }
        swap(obecnaKolumna, nastepnaKolumna);
    }

    int ILOSC_SCIERZEK = nastepnaKolumna[0][k];

    cout << ILOSC_SCIERZEK << '\n';

    return 0;
}
