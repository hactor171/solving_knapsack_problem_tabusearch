#pragma once
#include<iostream>
#include"Plik.h"
class przeszukiwanieTabu
{	
public:
	przeszukiwanieTabu();
	int* Algorytm(int, int, int, int, double**) const;
	int* znajdzOpt(int, double**) const;
	
	double policzDlugoscS(int*, double**, int) const;

	static void przekopiujTabele(int*, int*, int);
	static void dodajdotabu(int, int, int, int**);

	void zamienOptymalne(int*, int*, int) const;
	void zamien(int*, int*, int, int) const;
	void obnizTabu(int**, int) const;
	void usunTabu(int **, int) const;
	void wyswietlSciezke(int*,double**,int) const;
	void policzblad(int*,double**,int, int);
	~przeszukiwanieTabu();
};

