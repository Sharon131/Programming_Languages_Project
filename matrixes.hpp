#ifndef matrixes
#define matrixes
#include "auxiliaries.hpp"
//Dodać ewentualnie 

//Zrobione:
//macierz trójkątna-ulepszyć pod względem czytelności
//		dodać fukncję na zamienianie wierszy w macierzy
//macierz odwrotna -
//		na podstawie macierzy teójkątnej, dodać tylko dzielenie dla każdego wiersza, aby pierwszy niezarowy wyraz był równy 1
//		oraz dodać odwrótny algorytm Gaussa, czyli sprowadzanie macierzy trójkątnej górenj do jednostkowej
//		do tego jednoczesne operacje na macierzy jednostkowej, która po przekształceniach będzie macierzą odwrotną
//		dodać informację, czy da się w ogóle taką macierz znaleźć. Flaga przez referencję, czy może fukncja jako bool?
//poprawić mnożenie, dodawanie, odejmowanie dwóch macierzy - zwracać wskaźnik, jak nie da się policzyć, zwracanie NULLA

//Zrobić jeszcze:
//poprawić metody, które mogą być nie do obliczenia (jak np ślad macierzy), aby zwacały wskaźnik, a gdy nie da się danej wartośc
// obliczyć, to NULLA
//
//pozamieniać nazwy zmiennych w metodach  polskich na jakieś bardziejsze!!
//
//dokończyć macierz odwrotną - tym razem dla macierzy prostokątnej
//
//wszystie pomocnicze funkcje - do osbnego pliku nagłówkowego, aby nie bruździć
//	zamienić funkcję dosun na move, która będzie funkcją pomocniczą poza klasą w pliku aux


class matrix {
	double **m;
	void dosun(double**,int, int, int, double**);			//?? do obliczania wyznacznika z macierzy
	matrix& inverse_sq();									//obliczanie macierzy odwrotnej dla macierzy kwadratowej
	//matrix& inverse_rec();									//obliczanie macierzy pseudoodwrotnej dla macierzy prostokątnej

public:
	const int x, y;
	
	matrix(int, int);		//konstruktory
	matrix(int,int, double**);				//konstruktor przyjmujący od razu wymiary oraz tablicę wartości macierzy
	matrix();
	matrix(const matrix &);		//kopiujący
	matrix(matrix *);	//przenoszący
	~matrix();
	bool write(double, int, int);		//wpisanie wartości do konkretnej komórki. Funkcja zwraca true, gdy nadpisywanie się powiodło, false, gdy nie;
	double read(int, int) const;						//zwrócenie konkretnej wartości na pozycji x_w i y_w
	double** read() const ;							//zwrócenie całej macierzy w postaci tablicy;
	double det_rek(double**,int, int);							//pomocnicza do obliczenia wyznacznika macierzy rekurencyjna
	double det();						//wyznacznik
	double cofactor(int, int);				//znajdowanie algebraicznego dopełnienia zadanej macierzy o zadanych indeksach
	int rank();						//rząd macierzy
	int def();						//zwrócenie defektu macierzy (pełny opis w dokumencie k_macierze w tym samym folderze
	double trace();							//znajdowanie śladu macierzy (suma lementów na diagonali dla kwadratowych
	bool operator ==(const matrix &) const;			//porównanie dwóch macierzy ze sobą
	matrix* operator +(const matrix &);		//dodawanie
	matrix* operator -(const matrix &);		//odejmowanie
	matrix* operator *(const matrix &);		//mnożenie
	matrix& operator -();				//znak przeciwny
	matrix& operator *(double);			//mnożenie przez liczbę
	//matrix& operator +(double);			//dodanie liczby, czyli macierzy jednostkowej przemnożonej przez liczbę
	matrix& operator /(double);			//dzielenie przez liczbę
	matrix& transpose();			//transponowanie macierzy
	matrix& triangle();					//znajdowanie macierzy trójkątnej do zadanej
	matrix* inverse();					//znajdowanie macierzy odwrotnej do zadanej
};

#endif
