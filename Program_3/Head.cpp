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

	for (int i = 0; i < ilosc_zestawow; i++) //wykonywanie si� podanych zestaw�w z pliku tekstowego
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

		//wypisanie rozw�zania

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
	if (M_max == 0) //jesli masa b�dzie rowna 0 zako�cz funkcj� (zwr�� 0)
		 return 0;

	if (M_max != 0 && ilosc_elementow == 0) //je�li masa nie b�dzie r�wna zero i ilo�� sprawdzanych element�w sko�czy si� zako�cz funkcj� (zwr�� 1)
		return 1;

	if (ilosc_elementow <= n-pierwszy_element) //je�li zabraknie element�w przy danym przej�ciu
		{
			i++;
			n = 0;

			if (i >= ilosc_elementow - 1) //je�li zabraknie element�w dla okre�lonego elementu pocz�tkowego
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
		//sprawdzanie czy element mo�na zapakowa�

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

		if (i + pierwszy_element - 1 >= iterator) //je�li iterator jest mniejszy ko�czymy funkcj� wypakowywuj�c�
			return temp; //zwracamy wag� wszystkich wypakowanych element�w
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
	if (przedmioty.back() == tab_elementow[x]) //je�li znajdziemy okre�lony element w tablicy ko�czymy funkcj� i zwracamy iterator okre�lonego elementu
		return x;

	else
		sprawdz_iterator(przedmioty, tab_elementow, x + 1);
}
