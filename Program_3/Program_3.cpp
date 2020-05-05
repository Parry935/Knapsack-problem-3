// Pepaś Dominik - 11:00

#include "pch.h"
#include "Head.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	string nazwa_piku;
	
	cout << "Podaj nazwe pliku z ktorego chcesz odczytac dane: " << endl;
	cin >> nazwa_piku;
	cout << endl;

	odczyt_z_pliku(nazwa_piku);

	return 0;
}


