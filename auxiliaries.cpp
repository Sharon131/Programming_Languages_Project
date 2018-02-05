#include "auxiliaries.hpp"
//#include"application.hpp"

void swap_rows(double** t, int w, int k, int v1, int v2) 
{
	if (v1 >= w || v2 >= w || v1 == v2) {
		return;
	}
	for (int c = 0; c<k; c++) {
		double pom = t[v1][c];
		t[v1][c] = t[v2][c];
		t[v2][c] = pom;
	}
}

bool zeros(double ** t, int w, int k, int diagonal)
{
	int row = diagonal;										
	while (diagonal<k && row<w && t[row][diagonal] == 0) {	
		row++;
	}
	if (row<w) {
		swap_rows(t, w, k, diagonal, row);
		return true;	
	}
	return false;
}

int char_int(char num_c) {
	
	switch (num_c) {
		case '0':
		{
			return 0;
		}
		case '1':
		{
			return 1;
		}
		case '2':
		{
			return 2;
		}
		case '3':
		{
			return 3;
		}
		case '4':
		{
			return 4;
		}
		case '5':
		{
			return 5;
		}
		case '6':
		{
			return 6;
		}
		case '7':
		{
			return 7;
		}
		case '8':
		{
			return 8;
		}
		case '9':
		{
			return 9;
		}
		//case '\0':
		//{
			//return 20;
		//}
		default:
		{
			//MessageBox(hwnd, (LPSTR)num_c, "Uwaga!", MB_ICONWARNING | MB_OK);
			return 10;
		}
	}
}

char int_char(int num_i)
{
	switch (num_i) {
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
		default:
			return '0';
	}
}

double* str_double(vector <char> num_s) {		//zamienić na funkcję przyjmującą wektor charów
	double num_d=0;
	int index = 0;

	while (index < num_s.size() && num_s[index] != '.' && num_s[index]!=',') {
		num_d *= 10;
		int aux=char_int(num_s[index]);
		if (aux == 10) return NULL;
		num_d += aux;
		index++;
	}
	index++;

	int pow = 10;
	while (index < num_s.size()) {
		double aux = char_int(num_s[index]);
		if (aux == 10) return NULL;
		num_d += aux / pow;
		pow *= 10;
		index++;
	}
	double* point = new double;
	*point = num_d;
	return point;
}

string double_str(double num_d) {
	int num_i = (int)num_d;
	string num_s = "";
	int pow = 1;

	while (num_i  > 9) {
		pow *= 10;
		num_i /= 10;
	}

	num_i = (int)num_d;
	while (pow>0) {
		num_s += int_char(num_i / pow);
		num_i = num_i % pow;
		pow /= 10;
	}
	
	num_i = (int)num_d;
	if (num_d - num_i > 0) {
		num_s += '.';
	}
	int aux = 0;
	while (num_d - num_i > 0 && aux < 5) {
		num_d = (num_d-num_i)*10;
		num_i = (int)num_d;
		if (num_d - num_i >= 0.9999999999) {
			num_i = ceil(num_d);
		}
		num_s += int_char(num_i);
		aux++;
	}
	return num_s;
}
