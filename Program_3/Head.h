#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// g��wna funkcja odczytuj�ca dane wej�ciowe z pliku tekstowego i zawierajaca w sobie pozosta�e funkcje
int odczyt_z_pliku(string nazwa_pliku);

// funkcja tworz�ca tablic� dynamiczn� jednowymiarow�
int *stworz_tablice_x1(int n);

// funkcja rekurencyjna rozwi�zuj�ca problem plecakowy
int rek(vector<int>&przedmioty, int M_max, int ilosc_elementow, int * tab_elementow, int n, int i, int pierwszy_element, int pojemnosc_plecaka);

// pomocnicza funkcja rekurencyjna odpowiedznialna za odejmowanie okre�lonych element�w z vectora
int wypakowanie(vector<int>&przedmioty, int i, int pierwszy_element, int * tab_elementow, int temp);

// pomocnicza funkcja rekurencyjna sprawdzaj�ca iterator danego elementu
int sprawdz_iterator(vector<int>& przedmioty, int * tab_elementow, int x);

#endif