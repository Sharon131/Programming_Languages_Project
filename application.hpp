#ifndef application
#define application
#include<Windows.h>
#include<windowsx.h>
#include"auxiliaries.hpp"
#include"matrixes.hpp"
#include<string>
#include<vector>

using namespace std;

//NR ID
#define ID_COMBOBOX1 301
#define ID_COMBOBOX2 302
#define ID_COMBOBOX3 303
#define ID_COMBOBOX4 304
#define ID_COMBOBOX5 305

#define ID_BUTTON1 401

#define ID_CHECKBOX1 501

//STAŁE:
const LPSTR ClassName = (LPSTR)"Matrix";
const int MAXSIZE = 1000;
//FUKNCJE:
HWND WindowMatrix(HINSTANCE hInstance);

void OnClose(HWND);
void OnDestroy(HWND);

void SetComboBox(HWND);
void SetComboOperation(HWND);

matrix* GetTextMatrix(char[MAXSIZE], int, int, HWND);
matrix* GetComboOperation(HWND, matrix &, matrix &);  //, matrix, matrix
#endif
