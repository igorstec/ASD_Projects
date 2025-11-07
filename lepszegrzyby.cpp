#include <iostream>
#include <vector>
#include <map>
#include <chrono>
#include <thread>

using namespace std;
using namespace chrono;

#define MOD 1000000000

// Funkcja do potęgowania modulo
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

// Funkcja przesuwająca wektor w miejscu (bez kopiowania)
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
        for (int j = a; j >= 0; j--) {
            grzyby[j][b]++;
        }
    }

    // Liczenie pominiętych kolumn (optymalizacja)
    int ilePominietychKolumn = 0;
    for (int j = 0; j < m - 2; j++) {
        if (grzyby[0][j] == 0 && grzyby[0][j + 1] == 0) {
            ilePominietychKolumn++;
        }
    }

    vector<vector<int> > nastepnaKolumna(n, vector<int>(k + 1, 0));
    vector<vector<int> > obecnaKolumna(n, vector<int>(k + 1, 0));

    // Pomocnicza tablica do śledzenia przesunięć wynikających z zebranych grzybów
    vector<int> przesunieciaKolumny(m, 0);

    // KROK 1: Inicjalizacja ostatniej kolumny (m-1)
    for (int j = min(grzyby[0][m - 1], k); j >= 0; j--) {
        nastepnaKolumna[0][j] = 1;
    }

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

    // KROK 2: Iteracyjne przetwarzanie od m-2 do 0
    for (int kolumna = m - 2; kolumna >= 0; kolumna--) {
        //Optymalizacja pomijania pustych kolumn
        int faktycznaKolumna = kolumna;
        while (faktycznaKolumna >= 0 && faktycznaKolumna < m - 2 && grzyby[0][faktycznaKolumna] == 0 && grzyby[0][faktycznaKolumna+1] == 0) {
            //cout<<"Pomijam kolumne: "<< faktycznaKolumna <<endl;
            faktycznaKolumna--;
        }



        // Jeśli pominęliśmy kolumny, kopiujemy wyniki
        if (faktycznaKolumna != kolumna) {
            if(faktycznaKolumna < 0) {
                continue;
            }

            for (int wyborPrawo = 0; wyborPrawo < n; wyborPrawo++) {
                obecnaKolumna[wyborPrawo] = nastepnaKolumna[wyborPrawo];
            }
            kolumna = faktycznaKolumna;
        }

        // Przetwarzanie każdego możliwego wyboru wiersza (wyborPrawo)
        for (int wyborPrawo = 0; wyborPrawo < n; wyborPrawo++) {
            // Optymalizacja: sprawdzenie czy możemy skopiować z poprzedniego wiersza
            if (wyborPrawo > 0) {
                int grzyby_nie_liczone = wyborPrawo < n - 1 ? grzyby[wyborPrawo + 1][kolumna] : 0;
                if (grzyby[wyborPrawo - 1][kolumna] == grzyby_nie_liczone) {
                    obecnaKolumna[wyborPrawo] = obecnaKolumna[wyborPrawo - 1];
                    continue;
                }
            }

            // Inicjalizacja wektora wynikowego dla tego stanu
            fill(obecnaKolumna[wyborPrawo].begin(), obecnaKolumna[wyborPrawo].end(), 0);

            // Iteracja po wszystkich możliwych wyborach w następnej kolumnie
            for (int i = 0; i < n; i++) {
                int nieliczoneGrzyby = max(wyborPrawo, i) < n - 1 ? grzyby[max(wyborPrawo, i) + 1][kolumna] : 0;
                int nowe_zebrane_grzyby = grzyby[min(wyborPrawo, i)][kolumna] - nieliczoneGrzyby;

                // Tworzymy tymczasową kopię do przesunięcia
                vector<int> wynikZPrzesunieciem = nastepnaKolumna[i];
                przesunWMiejscu(wynikZPrzesunieciem, nowe_zebrane_grzyby);

                // Akumulacja wyników
                for (int j = 0; j <= k; j++) {
                    obecnaKolumna[wyborPrawo][j] = (obecnaKolumna[wyborPrawo][j] + wynikZPrzesunieciem[j]) % MOD;
                }
            }
        }

        // Swap: obecna kolumna staje się następną kolumną dla kolejnej iteracji
        //cout << "Kolumna: " << kolumna << endl;
        // for(int j=0; j<n; j++) {
        //     for(int i=0; i<=k; i++) {
        //         cout<< obecnaKolumna[j][i] << " ";
        //     }
        //     cout<<endl;
        // }
        // cout<<endl;

        swap(obecnaKolumna, nastepnaKolumna);
    }

    // KROK 3: Aplikacja początkowego przesunięcia (zebrane_grzyby_w_kolumnie = 0 dla kolumny 0)
    // nastepnaKolumna[0] zawiera teraz wynik dla DP(0, 0, ...)
    int ILOSC_SCIERZEK = nastepnaKolumna[0][k];

    //Mnożenie przez liczbę pominiętych kolumn
    long long mnoznik = szybkiePotegowanieModulo(n, ilePominietychKolumn, MOD);
    mnoznik = (mnoznik * ILOSC_SCIERZEK) % MOD;

    cout << mnoznik<< '\n';

    return 0;
}
