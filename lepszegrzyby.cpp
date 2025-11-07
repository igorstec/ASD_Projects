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


long long rekurencja(int wyborPrawo, const int &minkolumna, int kolumna, int zebrane_grzyby,
                     const int &k, const int &n,
                     const int &m, vector<vector<short> > &grzyby, vector<bool> &pustaKolumna, short pominieteKolumny,
                     vector<int> &grzybyNaPrawo, map<tuple<short, int, int>, long long> &zapamietaneStany) {
    if (zebrane_grzyby + grzybyNaPrawo[kolumna] < k) {
        // cout<<"Za malo grzybow mozliwych do zebrania w kolumnie: "<<kolumna<<" zebrane: "<<zebrane_grzyby<<" mozliwe do zebrania: "<<grzybyNaPrawo[kolumna]<<endl;
        return 0;
    }
    // auto elapsed = duration_cast<seconds>(steady_clock::now() - start);
    //
    // if (elapsed.count() >= 3) { // 3 sekund
    //     cout << "Czas minął! Zatrzymuję proces dla debuggera.\n";
    //
    //     // Opcja 1: przerwij dla debuggera (Windows)
    //     // __debugbreak();
    //
    //     // Opcja 2: przerwij przenośnie (POSIX, Linux, macOS)
    //     raise(SIGTRAP); // generuje przerwanie debuggera
    // }

    // zmapuj wybor prawo, kolumna, zebrane grzyby
    // jak jest juz to return i odaj zmapowanie
    tuple ID = make_tuple(grzyby[wyborPrawo][kolumna], kolumna, zebrane_grzyby);
    if (zapamietaneStany.contains(ID)){
        //cout<<"To juz bylo i wynosi"<<zapamietaneStany[tuple(wyborPrawo, kolumna, zebrane_grzyby)]<<endl;
        return zapamietaneStany[ID];
    }


    if (zebrane_grzyby >= k) {
        if (kolumna == m) {
            //cout<<"Dotarto do konca w kolumnie: "<<wyborPrawo<<endl;
            long long wynik = szybkiePotegowanieModulo(n, pominieteKolumny, MOD);
            zapamietaneStany[ID] = wynik;
            return wynik;
        }
        // int przed = ILOSC_SCIERZEK;
        // int po = ILOSC_SCIERZEK;
        // cout<<"Zebrane grzyby: "<<zebrane_grzyby<<" w kolumnie: "<<kolumna<<" dodalem: "<< po- przed<<" poszedlem:"<< wyborPrawo<<endl;
        long long wynik = szybkiePotegowanieModulo(n, m - 1 - kolumna + pominieteKolumny, MOD);
        zapamietaneStany[ID] = wynik;
        return wynik;
    }

    // if (kolumna >= minkolumna) {
    //     long long wynik = 0;
    //     zapamietaneStany[ID] = wynik;
    //     return 0;
    // }

    while (kolumna + 1 < m && pustaKolumna[kolumna] && pustaKolumna[kolumna + 1]) {
        //cout<<"Pominieto pusta kolumne: "<<kolumna<<endl;
        kolumna++;
        pominieteKolumny++;
    }

    zapamietaneStany[ID] = 0;

    for (int i = 0; i < n; i++) {
        if (kolumna == m - 1) {
            i = n - 1;
        }
        int nieliczoneGrzyby = min(wyborPrawo, i) - 1 >= 0 ? grzyby[min(wyborPrawo, i) - 1][kolumna] : 0;
        int nowe_zebrane_grzyby = grzyby[max(wyborPrawo, i)][kolumna] - nieliczoneGrzyby;
        nowe_zebrane_grzyby += zebrane_grzyby;
        zapamietaneStany[ID] += rekurencja(
            i, minkolumna, kolumna + 1, nowe_zebrane_grzyby, k, n, m, grzyby, pustaKolumna,
            pominieteKolumny, grzybyNaPrawo, zapamietaneStany)%MOD;
    }
    return zapamietaneStany[ID]%MOD;
}

int main() {
    long long ILOSC_SCIERZEK = 0;

    int n, m;
    int k;
    int g;
    cin >> n >> m >> k >> g;
    // string grzybki;
    vector<bool> pustaKolumna(m, true);
    vector<int> grzybyNaPrawo(m + 1, 0);
    grzybyNaPrawo[m] = 0;
    map<tuple<short, int, int>, long long> zapamietaneStany;

    vector grzyby(n, vector<short>(m, 0));
    int minKolumnaBezGrzybaWczesniej = 0;
    for (int i = 0; i < g; i++) {
        int a, b;
        cin >> a >> b;
        // grzybki.append(to_string(a)+" "+to_string(b)+" ");
        a--;
        b--;
        pustaKolumna[b] = false;
        if (b + 1 > minKolumnaBezGrzybaWczesniej) {
            minKolumnaBezGrzybaWczesniej = b + 1;
        }
        for (int j = a; j <= n - 1; j++) {
            grzyby[j][b]++;
        }
    }
    for (int i = m - 1; i >= 0; i--) {
        grzybyNaPrawo[i] = grzyby[n - 1][i] + grzybyNaPrawo[i + 1];
    }
    // cout<<grzybki<<endl;
    //return 0;
    //cout grzyby
    //  for (int i = 0; i < n; i++) {
    //      for (int j = 0; j < m; j++) {
    //          if (i == 0)cout << grzyby[i][j] << " ";
    //          else
    //              cout << grzyby[i][j] - grzyby[i - 1][j] << " ";
    //      }
    //      cout << endl;
    //  }
    // cout << minKolumnaBezGrzybaWczesniej << endl;
    //auto start = steady_clock::now();


    ILOSC_SCIERZEK = rekurencja(0, minKolumnaBezGrzybaWczesniej, 0, 0, k, n, m, grzyby, pustaKolumna, 0, grzybyNaPrawo,
                                zapamietaneStany);
    cout << ILOSC_SCIERZEK % MOD << endl;

    return 0;
}
