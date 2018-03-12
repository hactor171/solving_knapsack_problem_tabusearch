#include <iostream>
#include <fstream>
#include <string>
#include "Plik.h"
#include "przeszukiwanieTabu.h"
#include "Timer.h"

using namespace std;
int main()
{
	Plik *plik = new Plik();
	przeszukiwanieTabu *tabu = new przeszukiwanieTabu();
	Timer* timer = new Timer();
	int * sciezka;
	char w;
	bool a, b;
	a = b = true;
	while (a) {
		cout << endl;
		cout << "\n== Menu Glowne ==\n" << endl;
		cout << "Wybierz:" << endl;
		cout << "-1-. Praca z danymi" << endl;
		cout << "-2-. Algorytm" << endl;
		cout << "-3-. Zakonc program" << endl;
		cout << "\nWpisz potrzebne: ";
		cin >> w;
		cout << endl;
		system("cls");
		switch (w) {
		case '1': {
			b = true;
			while (b)
			{
				cout << "\n<<Menu - Generowania danych>>\n" << endl;
				cout << "Wybierz opcje:" << endl;
				cout << "-1- Wczytaj dane z pliku(atsp):" << endl;
				cout << "-2- Wczytaj dane z pliku(tsp):" << endl;
				cout << "\n-a- Powrot do ==Menu Glowne==\n" << endl;
				cout << "\nWpisz potrzebne: ";

				cin >> w;
				system("cls");
				switch (w)
				{
				case '1': {
					string nazwa;
					cout << "Podaj nazwe pliku:";
					cin >> nazwa;
					plik->atsp(nazwa);
					break;
				}
				case '2': {
					string nazwa;
					cout << "Podaj nazwe pliku:";
					cin >> nazwa;
					plik->tsp(nazwa);
					break;
				}
				case 'a': {
					b = false;
					break;
				}
				}

			}
			break; 
		}
		case '2': {
			int it, optimal;
			string text = "";
			double dtabu, war_kryt;
			cout << "Podaj parametry:"<<endl;
			cout << "Ilosc iteracji:" << endl;
		 	cin >> it;
			cout << "Dlugosc tabu:" << endl;
		 	cin >> dtabu;
			cout << "Watunek krytyczny:" << endl;
		 	cin >> war_kryt;
			cout << "Czy chcesz policzyc blad ? " << endl;
			cout << "Wpisz odpowiedz: ";
			cin >>text;
			cout << endl;
			if (text == "Tak" || text == "tak")
			{
				cout << "Wpisz optymalne rozwiazanie: ";
				cin >> optimal;
					timer->startTimer();
					sciezka = tabu->Algorytm(it, dtabu, war_kryt, plik->liczba_m, plik->odleglosc);
					timer->endTimer();
					cout << "Czas wykonania :" << timer->endTimer() << endl;
					tabu->wyswietlSciezke(sciezka, plik->odleglosc, plik->liczba_m);
					tabu->policzblad(sciezka, plik->odleglosc, plik->liczba_m, optimal);
				
			}else if (text == "Nie" || text == "nie")
			{
				timer->startTimer();
				sciezka = tabu->Algorytm(it, dtabu, war_kryt, plik->liczba_m, plik->odleglosc);
				timer->endTimer();
				cout << "Czas wykonania :" << timer->endTimer() << endl;
				tabu->wyswietlSciezke(sciezka, plik->odleglosc, plik->liczba_m);
			}
			break;
		}
		case '3':
		{
			a = false;
			break;
		}

		}
	}

}