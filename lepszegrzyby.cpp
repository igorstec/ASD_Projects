/**@author Bajtazar Ba jto cki ( b . bajtocki@students . mimuw . edu . pl )
* @brief Rozwiązanie zadania XYZ * @date 2022 −01 −16 */
#include <iostream>
#include <tuple>
#include <vector>
#include <math.h>
#include <map>
#include <tuple>
#include <iostream>
#include <chrono>
#include <thread>
#include <csignal> // dla raise()
using namespace std;
using namespace chrono;

#define MOD 1000000000

// Funkcja do potęgowania modulo
long long szybkiePotegowanieModulo(long long podstawa, long long wykladnik, long long modulo) {
    podstawa %= modulo;
    long long wynik = 1;

    while (wykladnik > 0) {
        if (wykladnik % 2 == 1) {
            wynik = (wynik * podstawa) % modulo;
        }
        wykladnik /= 2;
        podstawa = (podstawa * podstawa) % modulo;
    }
    return wynik;
}

vector<int> przesun_z_powtorzeniem(const vector<int> &v, int przesuniecie) {
    vector<int> wynik(v.size());

    for (size_t i = 0; i < v.size(); ++i) {
        if (i < przesuniecie) {
            // Pierwsze 'przesuniecie' pozycji - powtórz wartość z indeksu 0
            wynik[i] = v[0];
        } else {
            // Pozostałe pozycje - weź wartość z (i - przesuniecie)
            wynik[i] = v[i - przesuniecie];
        }
    }
    return wynik;
}

vector<int> DP(int wyborPrawo, int kolumna, int minKolumna, int zebrane_grzyby_w_kolumnie,
               const int &k, const int &n,
               const int &m, vector<vector<short> > &grzyby, vector<vector<vector<int> > > &zapamietaneStany) {
    if (kolumna == m - 1 || kolumna == minKolumna) {
        return przesun_z_powtorzeniem(zapamietaneStany[wyborPrawo][m-1], zebrane_grzyby_w_kolumnie);
    }
    // cout << "licze: " << wyborPrawo << " : " << kolumna << " ";
    // fflush(stdout);
    int original_kolumn = kolumna;
    while (kolumna + 2 < minKolumna && grzyby[0][kolumna] == 0 && grzyby[0][kolumna + 1] == 0) {
        //cout<<"Pominieto pusta kolumne: "<<kolumna<<endl;
        kolumna++;
    }
    // cout << "licze: " << wyborPrawo << " : " << kolumna << " ";
    // fflush(stdout);
    vector<int> to_return(k + 1, 0);
    for (int i = 0; i < n; i++) {
        int nieliczoneGrzyby = max(wyborPrawo, i) < n - 1 ? grzyby[max(wyborPrawo, i) + 1][kolumna] : 0;
        int nowe_zebrane_grzyby = grzyby[min(wyborPrawo, i)][kolumna] - nieliczoneGrzyby;
        //cout<<"nowe_grzyby "<<nowe_zebrane_grzyby<<" ";
        // if(wyborPrawo==1 && kolumna == 4) {
        //     cout<<"nowegrzyby: "<<nowe_zebrane_grzyby<<endl;
        // }


        vector<int> wynik = wyborPrawo > 0
                                ? (przesun_z_powtorzeniem(zapamietaneStany[i][kolumna + 1], nowe_zebrane_grzyby))
                                : DP(i, kolumna + 1, minKolumna, nowe_zebrane_grzyby, k, n, m, grzyby, zapamietaneStany);
        for (int j = 0; j <= k; j++) {
            // if(wyborPrawo==1 && kolumna == 4) {
            //     cout<<"stan: "<<j <<" ";
            //     for(int pp=0; pp<=k; pp++) {
            //         cout<<to_return
            //     }
            // }
            to_return[j] = (to_return[j] + wynik[j]) % MOD;
        }
    }
    // cout << "wyliczylem: " << wyborPrawo << " : " << kolumna << " ";
    // fflush(stdout);
    zapamietaneStany[wyborPrawo][kolumna] = to_return;
    if (kolumna != original_kolumn) {
        zapamietaneStany[wyborPrawo][original_kolumn] = to_return;
    }
    return przesun_z_powtorzeniem(to_return, zebrane_grzyby_w_kolumnie);
}

int main() {
    long long ILOSC_SCIERZEK = 0;

    int n, m, k, g;
    cin >> n >> m >> k >> g;

    vector zapamietaneStany(n, vector(m, vector<int>(k + 1, -1)));

    vector grzyby(n, vector<short>(m, 0));
    int minKolumnaBezGrzybaPozniaj= 0;
    for (int i = 0; i < g; i++) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if (b + 1 > minKolumnaBezGrzybaPozniaj) {
            minKolumnaBezGrzybaPozniaj = b + 1;
        }
        for (int j = a; j >= 0; j--) {
            grzyby[j][b]++;
        }
    }
    int ilePustychKolumn = 0;
    for (int j = 0; j < m - 2; j++) {
        if (grzyby[0][j] == 0 && grzyby[0][j + 1] == 0) {
            ilePustychKolumn++;
        }
    }

    vector<int> temp(k + 1, 0);
    for (int j = grzyby[0][m - 1]; j >= 0; j--) {
        temp[j] = 1;
    }
    zapamietaneStany[0][m - 1] = temp;
    zapamietaneStany[0][minKolumnaBezGrzybaPozniaj-1] = temp;


    for (int i = 1; i < n; i++) {
        int ile = grzyby[i][m - 1];
        zapamietaneStany[i][m - 1] = zapamietaneStany[i - 1][m - 1];
        if (grzyby[i - 1][m - 1] == ile) {
            continue;
        }
        zapamietaneStany[i][m - 1][ile] = 0;
        zapamietaneStany[i][minKolumnaBezGrzybaPozniaj-1] = zapamietaneStany[i][m-1];
    }

    /*cout grzyby*/
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         if (i == n - 1)cout << grzyby[i][j] << " ";
    //         else
    //             cout << grzyby[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //- grzyby[i + 1][j]


    ILOSC_SCIERZEK = DP(0, 0, minKolumnaBezGrzybaPozniaj, 0, k, n, m, grzyby, zapamietaneStany)[k];

    /*cout zapamietane grzyby*/
    // cout << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < m; j++) {
    //         for (int p = 0; p < k + 1; p++) {
    //             cout << zapamietaneStany[i][j][p];
    //         }
    //         cout << " || ";
    //     }
    //     cout << endl;
    // }

    //cout << endl;
    long long mnoznik = szybkiePotegowanieModulo(n, ilePustychKolumn, MOD);
    mnoznik = (mnoznik * ILOSC_SCIERZEK) % MOD;
    cout << mnoznik << endl;

    return 0;
}
