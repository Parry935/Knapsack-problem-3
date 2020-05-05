#include "pch.h"
#include "Head.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


int odczyt_z_pliku(string nazwa_pliku)
{
	fstream file;
	file.open(nazwa_pliku.c_str(), ios::in);
	if (file.good() == false)
	{
		cout << "Nie udalo sie otworzyc pliku" << endl;
		exit(0);
	}

	int ilosc_zestawow = 0;
	
	file >> ilosc_zestawow;

	for (int i = 0; i < ilosc_zestawow; i++) //wykonywanie siê podanych zestawów z pliku tekstowego
	{
		//odczyt z pliku danych wejsciowych

		int M_max = 0;
		int ilosc_elementow = 0;

		file >> M_max;
		file >> ilosc_elementow;

		int *tab_elementow = stworz_tablice_x1(ilosc_elementow);

		for (int j = 0; j < ilosc_elementow; j++)
		{
			file >> tab_elementow[j];
		}

		int zero = 0;

		int pojemnosc_plecaka = M_max;
		vector<int>przedmioty;

		bool brak_wypelnienia;

		brak_wypelnienia = rek(przedmioty, M_max, ilosc_elementow, tab_elementow, zero, zero, zero, pojemnosc_plecaka);

		//wypisanie rozw¹zania

		if (brak_wypelnienia == true)
			cout << "BRAK";
		else
		{
			cout << pojemnosc_plecaka << " = ";
			for (int i = 0; i < przedmioty.size(); i++)
			{
				cout << przedmioty[i] << " ";
			}
		}

		cout << endl;
	}

	file.close();

	return 0;
}

int *stworz_tablice_x1(int n)
{
	int *T = nullptr;
	
	T = new int[n];

	return T;
}



int rek(vector<int>&przedmioty, int M_max, int ilosc_elementow, int * tab_elementow, int n, int i, int pierwszy_element, int pojemnosc_plecaka)
{
	if (M_max == 0) //jesli masa bêdzie rowna 0 zakoñcz funkcjê (zwróæ 0)
		 return 0;

	if (M_max != 0 && ilosc_elementow == 0) //jeœli masa nie bêdzie równa zero i iloœæ sprawdzanych elementów skoñczy siê zakoñcz funkcjê (zwróæ 1)
		return 1;

	if (ilosc_elementow <= n-pierwszy_element) //jeœli zabraknie elementów przy danym przejœciu
		{
			i++;
			n = 0;

			if (i >= ilosc_elementow - 1) //jeœli zabraknie elementów dla okreœlonego elementu pocz¹tkowego
			{
				przedmioty.clear();
				i = 0;
				pierwszy_element++;

				return rek(przedmioty, pojemnosc_plecaka , ilosc_elementow - 1, tab_elementow, n + pierwszy_element, i, pierwszy_element, pojemnosc_plecaka);
			}

			else
			{
				int suma = 0;

				if (!przedmioty.empty())
				{
					int temp = 0;
					suma = wypakowanie(przedmioty, i, pierwszy_element, tab_elementow, temp);
				}

				return rek(przedmioty, M_max + suma, ilosc_elementow, tab_elementow, n + pierwszy_element + 1 + i, i, pierwszy_element, pojemnosc_plecaka);
			}
		}

	else
	{
		//sprawdzanie czy element mo¿na zapakowaæ

		if (tab_elementow[n] > M_max)
			return rek(przedmioty, M_max, ilosc_elementow, tab_elementow, n + 1, i, pierwszy_element, pojemnosc_plecaka);

		else
		{
			przedmioty.push_back(tab_elementow[n]);
			return rek(przedmioty, M_max - tab_elementow[n], ilosc_elementow, tab_elementow, n + 1, i, pierwszy_element, pojemnosc_plecaka);
		}

	}

}

int wypakowanie(vector<int>& przedmioty, int i, int pierwszy_element, int * tab_elementow, int temp)
{
	if (!przedmioty.empty())
	{
		int x = 0;
		int iterator = sprawdz_iterator(przedmioty,tab_elementow,x);

		if (i + pierwszy_element - 1 >= iterator) //jeœli iterator jest mniejszy koñczymy funkcjê wypakowywuj¹c¹
			return temp; //zwracamy wagê wszystkich wypakowanych elementów
		else
		{
			temp += przedmioty.back();
			przedmioty.pop_back();
			wypakowanie(przedmioty, i, pierwszy_element, tab_elementow, temp);
		}
	}

	else
		return temp;
}

int sprawdz_iterator(vector<int>& przedmioty, int * tab_elementow, int x)
{
	if (przedmioty.back() == tab_elementow[x]) //jeœli znajdziemy okreœlony element w tablicy koñczymy funkcjê i zwracamy iterator okreœlonego elementu
		return x;

	else
		sprawdz_iterator(przedmioty, tab_elementow, x + 1);
}
