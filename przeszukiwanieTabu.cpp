#include "przeszukiwanieTabu.h"



przeszukiwanieTabu::przeszukiwanieTabu()// konstruktor
{
}
przeszukiwanieTabu::~przeszukiwanieTabu()// destruktor
{
}
int* przeszukiwanieTabu::Algorytm(int ilosc_i, int dlugosc_tabu1, int war_kryt1, int liczba_m1, double**odleglosc1) const // funkcja jaka wykonuje caly algorytm i zwraca najlepsza sciezke
{
	int ilosc_iter = ilosc_i;
	int dlugosc_tabu = dlugosc_tabu1;
	int war_cryt = war_kryt1;
	int liczba_m = liczba_m1;
	int podnies = 0;
	int podnies1 = 0;
	double** odleglosc = odleglosc1;
	int **tabuLista = new int*[liczba_m]; // tworzenie  tabu listy 
	for (int i = 0; i < liczba_m; i++)
	{
		tabuLista[i] = new int[liczba_m];
		for (int j = 0; j < liczba_m; j++)
		{
			tabuLista[i][j] = 0;// wyzerowanie tabu listy
		}
	}
	bool czyznalezione = false;
	bool czyznalezione1 = false;
	int *optymalna_sciezka = znajdzOpt(liczba_m, odleglosc);// znalezenie optymalnej sciezki 
	int *lokalna_sciezka = new int[liczba_m];
	int *l_optymalna_sciezka = new int[liczba_m];
	int *najlepsza_sciezka = new int[liczba_m];

	double koszt_lokalna_sciezka = 0;
	double koszt_l_optymalna_sciezka = 0;
	double koszt_najlepsza_sciezka = 0;
	double koszt_optymalna_sciezka = koszt_najlepsza_sciezka = policzDlugoscS(optymalna_sciezka, odleglosc, liczba_m); // znalezenie kosztu optymalnej sciezki

	while (++podnies1 < ilosc_iter)// 
	{
		koszt_l_optymalna_sciezka = koszt_optymalna_sciezka;
		for (int i = 0; i < liczba_m - 1; i++)
		{
			for (int j = i + 1; j < liczba_m; j++)
			{
				przekopiujTabele(optymalna_sciezka, lokalna_sciezka, liczba_m);
				zamien(optymalna_sciezka, lokalna_sciezka, i, j);
				koszt_lokalna_sciezka = policzDlugoscS(lokalna_sciezka, odleglosc, liczba_m);
				if ((koszt_lokalna_sciezka < koszt_l_optymalna_sciezka && tabuLista[optymalna_sciezka[i]][optymalna_sciezka[j]] == 0) || koszt_lokalna_sciezka < koszt_optymalna_sciezka)
					// sprawdzamy czy jest jakies lepsze rozwiazanie i czy nie jest wniesione do tabu
				{
					dodajdotabu(optymalna_sciezka[i], optymalna_sciezka[j], dlugosc_tabu, tabuLista);
					koszt_l_optymalna_sciezka = koszt_lokalna_sciezka;
					przekopiujTabele(lokalna_sciezka, l_optymalna_sciezka, liczba_m);
					czyznalezione = true;
				}
			}
		}
		obnizTabu(tabuLista, liczba_m);

		if (koszt_l_optymalna_sciezka < koszt_optymalna_sciezka)// sprawdzamy czy znaleziony koszt jest lepszy od optymalnego
			// jak jest to zapisujemy go jako nowe 
			// jak nie to podniesc na 1 i szukac dalej
		{
			koszt_optymalna_sciezka = koszt_l_optymalna_sciezka;
			przekopiujTabele(l_optymalna_sciezka, optymalna_sciezka, liczba_m);
			podnies = 0;
			if (koszt_optymalna_sciezka < koszt_najlepsza_sciezka)
			{
				przekopiujTabele(optymalna_sciezka, najlepsza_sciezka, liczba_m);
				czyznalezione1 = true;
				koszt_najlepsza_sciezka = koszt_optymalna_sciezka;
				podnies1 = 0;
			}
		}

			if (++podnies > war_cryt)// jak do tej pory nie zostalo znalezione lepsze rozwizanie, to usun tabu zapisz dotej pory znalezione
				// szukaj ponownie
			{
				
				zamienOptymalne(najlepsza_sciezka, optymalna_sciezka, liczba_m);
				
				koszt_optymalna_sciezka = policzDlugoscS(optymalna_sciezka, odleglosc, liczba_m);
				usunTabu(tabuLista, liczba_m);
				podnies = 0;
			}
	}

	delete[]lokalna_sciezka;
	delete[]l_optymalna_sciezka;
	if (czyznalezione == false)// jesli nie znalazlo zadnego rozwiazania oproc optymalnego to zwroc go
		// jak nie to zwroc najlepsze rozwiazanie
		return optymalna_sciezka;
	else
		return najlepsza_sciezka;
	delete[]optymalna_sciezka;
}

int* przeszukiwanieTabu::znajdzOpt(int liczba_m, double** odleglosc) const // funkcja ktora znajduje optymalne rozwiazanie z losowego wieszchowka
{
	int nastepny_ind = 0;
	int los_wierz = (rand() % liczba_m) + 0;// losujemy wieszchowek z przedzielu od 0 do liczby miast
	double najlepsze_przejscie;
	int *sciezka = new int[liczba_m]; // tworzymy pustą sciezke
	bool *odwiedzone = new bool[liczba_m];
	for (int i = 0; i < liczba_m; i++)
	{
		odwiedzone[i] = false; // ozanaczamy wszystkie jako nieodwiedzone
	}
	sciezka[0] = los_wierz;
	odwiedzone[los_wierz] = true;
	for (int j = 1; j < liczba_m; j++)
	{
	  najlepsze_przejscie = MAX; 
		for (int k = 0; k < liczba_m; k++)
		{

			if (odwiedzone[k] == true)// jak jest false to szukaj optymalna sciezke, jak nie to poweikszaj k dopoki nie bedzie false
			{
				continue;
			}
			else if (najlepsze_przejscie > odleglosc[sciezka[j - 1]][k]) // sprawdzenie czy jest jakas krotsza odleglosc 
			{
				nastepny_ind = k;// nadanie nastepnemu indeksu indeks najkrotszej dlugosci
				najlepsze_przejscie = odleglosc[sciezka[j - 1]][k]; // nadanie najkrotszej dlugosci 
			}

		}
		odwiedzone[nastepny_ind] = true; // oznaczany jako odwiedzone zeby znowu nie wejsc
		sciezka[j] = nastepny_ind; // zapisujemy do sciezki 
	}
	return sciezka;// zwaracamy optymalna sciezke
}

void przeszukiwanieTabu::przekopiujTabele(int *zrodlowy, int *docelowy, int liczba_m)// funkcja kopiowania tablicy 
{
	if (zrodlowy == nullptr || docelowy == nullptr) // sprawdzenie czy nie sa zerowe
	{
		return;
	}
	for (int i = 0; i < liczba_m; i++)
	{
		docelowy[i] = zrodlowy[i];// nadanie danych jednej tabeli do drugiej
	}
}


void przeszukiwanieTabu::zamienOptymalne(int *sciezka, int *n_sciezka, int liczba_m) const // funkcja zamiany dwoch randomowych wieszchowkow 
{

	int drugi, pierwszy = rand() % (liczba_m) + 0;
	while ((drugi = rand() % (liczba_m) + 0) == pierwszy);
	for (int i = 0; i < liczba_m; i++)
	{
		n_sciezka[i] = sciezka[i];
	}
	int i1 = (pierwszy < drugi) ? pierwszy : drugi;
	int j1 = (pierwszy > drugi) ? pierwszy : drugi;
	for (int i = i1, j = j1; i < j; i++, j--)
	{
		n_sciezka[i] = sciezka[j];
		n_sciezka[j] = sciezka[i];
	}

}

void przeszukiwanieTabu::obnizTabu(int** tabu, int liczba_m) const // funkcja obnizenia tabu
{
	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			if (tabu[i][j] > 0)// w kazdym gdzie jest wiecej niz 0 obniz na 1
			{
				tabu[i][j]--;
			}
		}
	}
}


void przeszukiwanieTabu::dodajdotabu(int pierwszy, int drugi, int dlugosc_war_kryt, int** tabu)// dodanie do tabu listy
{
	tabu[pierwszy][drugi] = dlugosc_war_kryt; // nadanie dlugosci warunka krytycznego
	tabu[drugi][pierwszy] = dlugosc_war_kryt;
}



void przeszukiwanieTabu::zamien(int* optymalny, int* localny, int i, int j) const // zamiana dwoch sasiednich wieszchowkow
{
	localny[i] = optymalny[j];// i zmieniamy na j, a j na i
	localny[j] = optymalny[i];
}


void przeszukiwanieTabu::usunTabu(int **tabu, int liczba_m) const // funkcja ktora wyzerowuje cala liste tabu
{
	for (int i = 0; i < liczba_m; i++)
	{
		for (int j = 0; j < liczba_m; j++)
		{
			tabu[i][j] = 0;
		}
	}
}

double przeszukiwanieTabu::policzDlugoscS(int *sciezka, double **odleglosc, int liczba_m) const // funkcja jaka liczy dlugosc sciezki 
{
	double dlugosc = 0;
	for (int i = 1; i < liczba_m; i++)
		dlugosc = dlugosc + odleglosc[sciezka[i - 1]][sciezka[i]];
	dlugosc = dlugosc + odleglosc[sciezka[liczba_m - 1]][sciezka[0]];
	return dlugosc; // zwracamy poprawna dlugosc
}

void przeszukiwanieTabu::policzblad(int*sciezka, double** odleglosc, int liczba_m, int dobryW)// funkcja licznia bladu, dobry wynik musi byc podany z konsoli 
{
	cout << "Blad wynosi: " << (policzDlugoscS(sciezka, odleglosc, liczba_m) - dobryW) * 100 / dobryW << " %" << endl;
}

void przeszukiwanieTabu::wyswietlSciezke(int *sciezka, double** odleglosc,int liczba_m) const // funkcja wyswietlenia sciezki
{
	for (int i = 0; i < liczba_m; i++)
	{
		cout << sciezka[i] << " -> ";
	}
	cout << sciezka[0] << endl;
	cout << "Dlugosc sciezki: " << policzDlugoscS(sciezka, odleglosc, liczba_m) << endl;
}

