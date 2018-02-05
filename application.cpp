#include "application.hpp"

//GENEROWANIE OKNA
HWND WindowMatrix(HINSTANCE hInstance)
{
	HWND hwnd;

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, ClassName, "Kalkulator macierzy", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 675, 780, NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Problemy z aplikacją. Spróbuj uruchomić ponownie", "Uwaga!", MB_ICONEXCLAMATION);
		return hwnd;
	}

	//Tworzenie ramek
	HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_CENTER, 20, 10, 300, 20, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic, "Witaj w kalkulatorze macierzy!!");

	//Deklaracje ramek
	HWND Frame1;
	HWND Frame2;
	HWND Frame3;
	HWND Frame4;

	//Generowanie ramki nr 1
	Frame1 = CreateWindowEx(0, "BUTTON", "Macierz A", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 35, 300, 300, hwnd, NULL, hInstance, NULL);
	HWND hStatic1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 20, 130, 20, Frame1, NULL, hInstance, NULL);
	SetWindowText(hStatic1, "Wymiary macierzy:");
	HWND hStatic2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 185, 20, 15, 20, Frame1, NULL, hInstance, NULL);
	SetWindowText(hStatic2, " x");
	HWND hStatic3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 45, 130, 20, Frame1, NULL, hInstance, NULL);
	SetWindowText(hStatic3, "Wartości macierzy:");

	//Ramka nr 2
	Frame2 = CreateWindowEx(0, "BUTTON", "Macierz B", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		340, 35, 300, 300, hwnd, NULL, hInstance, NULL);

	HWND hStatic4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 43, 130, 20, Frame2, NULL, hInstance, NULL);
	SetWindowText(hStatic4, "Wymiary macierzy:");
	HWND hStatic5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 185, 43, 15, 20, Frame2, NULL, hInstance, NULL);
	SetWindowText(hStatic5, " x");
	HWND hStatic6 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 10, 66, 130, 20, Frame2, NULL, hInstance, NULL);
	SetWindowText(hStatic6, "Wartości macierzy:");

	//Ramka nr 3
	Frame3 = CreateWindowEx(0, "BUTTON", "Wybierz działanie", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 350, 620, 60, hwnd, NULL, hInstance, NULL);

	//Ramka nr 4
	Frame4 = CreateWindowEx(0, "BUTTON", "Wynik", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
		20, 420, 620, 300, hwnd, NULL, hInstance, NULL);

	return hwnd;
}

//WYPEŁNIANIE COMBOBOXÓW
void SetComboBox(HWND hCombo)
{
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "1");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "2");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "3");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "4");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "5");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "6");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "7");
}

void SetComboOperation(HWND hCombo) {
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Dodawanie macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Odejmowanie macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Mnożenie macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Transponowanie macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Macierz trójkątna");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Macierz dopełnień");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Macierz odwrotna");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Wyznacznik z macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Rząd macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Ślad macierzy");
	SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Defekt macierzy");

}

//FUNKCJE PROCEDURY OBSŁUGUJĄCEJ OKNO
void OnClose(HWND hwnd) {
	DestroyWindow(hwnd);
}

void OnDestroy(HWND hwnd) {
	PostQuitMessage(0);
}


void CheckBoxCommand(HWND hwnd)
{
	if (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_CHECKED) {
		CheckDlgButton(hwnd, ID_CHECKBOX1, BST_UNCHECKED);
	}
	else {
		CheckDlgButton(hwnd, ID_CHECKBOX1, BST_CHECKED);
	}
}

matrix* GetTextMatrix(char matrix_s[MAXSIZE], int w, int k, HWND hwnd)
{
	
	double** tab = new double*[w];

	for (int i = 0; i < w; i++) {
		tab[i] = new double[k];
	}

	int index = 0;
	int v = 0;
	int c = 0;
	//char matrix_result[MAXSIZE];

	while (matrix_s[index] != '\0') {
		c = 0;
		while (matrix_s[index] != '\0' && matrix_s[index] != '\n') {
			vector <char> number_s;
			while (matrix_s[index] != '\0' && matrix_s[index] != ' ' && matrix_s[index] != '\n') {
				number_s.push_back(matrix_s[index]);
				//matrix_result[index] = matrix_s[index];
				//matrix_result[index + 1] = '\0';
				index++;
			}
			double* aux=str_double(number_s, hwnd);
			if (aux == NULL)
			{
				MessageBox(hwnd, "NULL.", "Uwaga!", MB_ICONWARNING | MB_OK);
				return NULL;
			}
			tab[v][c]=*aux;
			if (matrix_s[index] == ' ') {
				//matrix_result[index] = matrix_s[index];
				//matrix_result[index + 1] = '\0';
				index++;
			}
			c++;
		}
		if (matrix_s[index] == '\n') index++;

		if (c != k) {
			MessageBox(hwnd, "Niezgodność liczby kolumn z określoną.", "Uwaga!", MB_ICONINFORMATION);
			return NULL;
		}
		v++;
	}

	if (v != w || c != k)
	{
		MessageBox(hwnd, "Niezgodność liczby wierszy z określoną.", "Uwaga!", MB_ICONWARNING);
		return NULL;
	}

	matrix Matrix(w,k,tab);
	matrix* M = &Matrix;

	return M;
}

matrix* GetComboOperation(HWND hCombo, matrix &Matrix_A, matrix &Matrix_B)
{
	matrix* Matrix_C = NULL;;

	switch (ComboBox_GetCurSel(hCombo)) {
	case 0:
	{
		//Dodawanie macierzy
		Matrix_C = Matrix_A + Matrix_B;
		break;
	}
	case 1:
	{
		//Odejmowanie macierzy
		Matrix_C = Matrix_A - Matrix_B;
		break;
	}
	case 2:
	{
		//Mnożenie macierzy
		Matrix_C = Matrix_A * Matrix_B;
		break;
	}
	case 3:
	{
		//Transponowanie macierzy
		Matrix_C = &(Matrix_A.transpose());
		break;
	}
	case 4:
	{
		// Macierz trójkątna
		Matrix_C = &(Matrix_A.triangle());
		break;
	}
	case 5:
	{
		//Macierz dopełnień
		//Na razie nie, ponieważ nie mamy takiego działania zdefiniowanego
		break;
	}
	case 6:
	{
		//Macierz odwrotna
		Matrix_C = Matrix_A.inverse();
		break;
	}
	case 7:
	{
		//Wyznacznik z macierzy
		double** tab=new double*[1];
		tab[0] = new double[1];
		tab[0][0]= Matrix_A.det();
		matrix M(1,1,tab);
		Matrix_C = &M;
		break;
	}
	case 8:
	{
		//Rząd macierzy
		double** tab = new double*[1];
		tab[0] = new double[1];
		tab[0][0] = Matrix_A.rank();
		matrix M(1, 1, tab);
		Matrix_C = &M; 
		break;
	}
	case 9:
	{
		//Ślad macierzy
		double** tab = new double*[1];
		tab[0] = new double[1];
		tab[0][0] = Matrix_A.trace();
		matrix M(1, 1, tab);
		Matrix_C = &M; 
		break;
	}
	case 10:
	{
		//Defekt macierzy
		double** tab = new double*[1];
		tab[0] = new double[1];
		tab[0][0] = Matrix_A.def();
		matrix M(1, 1, tab);
		Matrix_C = &M; 
		break;
	}
	default:
		return NULL;
	}

	return Matrix_C;
}
