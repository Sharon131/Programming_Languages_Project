//Plik z fukncjami pomocniczymi do metod na macierzach
//Oznaczenia ogólne, będące ważne w każdym miejscu kodu:
// w- ilość wierszy w tablicy
// k-ilość kolumn w tablicy
// v - aktualny wiersz w tablicy. Również w pętlach.
// c - aktualna kolumna w tablicy. Również w pętlach.
// d - odpowiedni element na diagonali. Do pętl głównie
// diagonal - jak wyżej, tylko że jako argument, nie do pętli.
// aux - zmienna pomocnicza do wykonywania oblczeń zamieniania wartości itp.

//Dodać funkcję dosuń tutaj!!

#ifndef auxiliary
#define auxiliary
#include<string>
#include<vector>
#include<Windows.h>
using namespace std;

void move(double**, int, int, int);				//odpowiednik funkcji dosun z klasy, do zaimplementowania od nowa. 
												//Ponadto, zaprzyjaźniona funkcja z klasą, by był dostęp do macierzy, czy przez read?
void swap_rows(double**, int, int, int, int);
bool zeros(double**,int, int, int);
int char_int(char, HWND);					//pomocnicze. Do zamiany zaledwie jednej cyfry
char int_char(int);
double* str_double(vector <char>, HWND);							//string to double
string double_str(double);							// double to string


#endif
