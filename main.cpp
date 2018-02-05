#include "application.hpp"
#include<string>
#include<iostream>
#include<windowsx.h>

MSG Komunikat;
//Deklaracje pól tekstowych
HWND hText1;
HWND hText2;
HWND hText3;
//Deklaracje Comboxów:
HWND hCombo1;
HWND hCombo2;
HWND hCombo3;
HWND hCombo4;
HWND hCombo5;

HWND hButton1;

HWND hCheckBox1;
//FUNKCJE:
bool RegisterClass_Win(HINSTANCE);
//FUNKCJA STERUJĄCA OKNEM:
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void OnCommand(HWND, int, HWND, UINT);
void CheckBoxCommand(HWND);
void ButtonCommand(HWND);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	RegisterClass_Win(hInstance);

	// TWORZENIE OKNA
	HWND hwnd = WindowMatrix(hInstance);

	if (hwnd == NULL) return 1;

	//PRZYCISKI NA WPISANIE WYMIARÓW MACIERZY
	hCombo1 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		CBS_DROPDOWNLIST, 160, 50, 45, 200, hwnd, (HMENU)ID_COMBOBOX1, hInstance, NULL);
	hCombo2 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		CBS_DROPDOWNLIST, 220, 50, 45, 200, hwnd, (HMENU)ID_COMBOBOX2, hInstance, NULL);
	SetComboBox(hCombo1);
	SetComboBox(hCombo2);

	//MACIERZ A
	hText1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |
		CBS_DROPDOWNLIST, 40, 105, 250, 200, hwnd, NULL, hInstance, NULL);

	//WYBRANIE DZIAŁANIE NA MACIERZACH
	hCombo3 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		CBS_DROPDOWNLIST, 150, 375, 200, 300, hwnd, (HMENU)ID_COMBOBOX3, hInstance, NULL);
	SetComboOperation(hCombo3);

	//PRZYCISK POBIERAJĄCY DANE
	hButton1 = CreateWindowEx(0, "BUTTON", "Oblicz!", WS_CHILD | WS_VISIBLE,
		400, 372, 100, 30, hwnd, (HMENU)ID_BUTTON1, hInstance, NULL);

	//UWZGLĘDNIENIE MACIERZY B W OBLICZENIACH
	hCheckBox1 = CreateWindowEx(0, "BUTTON", "Uwzględnij w obliczeniach", WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
		350, 55, 200, 20, hwnd, (HMENU)ID_CHECKBOX1, hInstance, NULL);

	//PRZYCISKI NA WPISANIE WYMIARÓW MACIERZY
	hCombo4 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		CBS_DROPDOWNLIST, 480, 75, 45, 200, hwnd, (HMENU)ID_COMBOBOX4, hInstance, NULL);
	hCombo5 = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		CBS_DROPDOWNLIST, 540, 75, 45, 200, hwnd, (HMENU)ID_COMBOBOX5, hInstance, NULL);
	SetComboBox(hCombo4);
	SetComboBox(hCombo5);

	//MACIERZ B
	hText2 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE |
		CBS_DROPDOWNLIST, 365, 125, 250, 200, hwnd, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	// Pętla komunikatów
	while (GetMessage(&Komunikat, NULL, 0, 0))
	{
		TranslateMessage(&Komunikat);
		DispatchMessage(&Komunikat);

	}

	return Komunikat.wParam;
}

bool RegisterClass_Win(HINSTANCE hInstance) {
	// WYPEŁNIANIE STRUKTURY
	WNDCLASSEX Win;

	Win.cbSize = sizeof(WNDCLASSEX);
	Win.style = 0;
	Win.lpfnWndProc = WndProc;
	Win.cbClsExtra = 0;
	Win.cbWndExtra = 0;
	Win.hInstance = hInstance;
	Win.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Win.hCursor = LoadCursor(NULL, IDC_ARROW);
	Win.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	Win.lpszMenuName = NULL;
	Win.lpszClassName = ClassName;
	Win.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	return RegisterClassEx(&Win);
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id) {
	case ID_CHECKBOX1:
	{
		CheckBoxCommand(hwnd);
		break;
	}
	case ID_BUTTON1:
	{
		ButtonCommand(hwnd);
		break;
	}
	default:
		return;
	}
}

void ButtonCommand(HWND hwnd) {

	char matrix1[MAXSIZE];
	char matrix2[MAXSIZE];
	char matrix_result[MAXSIZE];
	bool IsFilled = false;

	int Dim_A1 = ComboBox_GetCurSel(hCombo1) + 1;
	int Dim_A2 = ComboBox_GetCurSel(hCombo2) + 1;
	int Dim_B1 = ComboBox_GetCurSel(hCombo4) + 1;
	int Dim_B2 = ComboBox_GetCurSel(hCombo5) + 1;

	matrix* Matrix_A=NULL;
	matrix* Matrix_B=NULL;

	int len1 = GetWindowTextLength(hText1);
	int len2 = GetWindowTextLength(hText2);

	if (len1 <= 0 || (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_CHECKED && len2 <= 0)) {
		MessageBox(hwnd, "Nie wpisano wartości macierzy.", "Uwaga!", MB_ICONWARNING);
		return;
	}

	GetWindowText(hText1, (LPSTR)matrix1, GetWindowTextLength(hText1) + 1);
	Matrix_A = GetTextMatrix(matrix1, Dim_A1, Dim_A2, hwnd);
	GetTextMatrix(matrix1, Dim_A1, Dim_A2, hwnd);

	if (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_UNCHECKED && len2 > 0) {
		IsFilled = MessageBox(hwnd, "Do macierzy B wpisano wartości, ale nie zaznaczono, aby te dane uwzględnić w obliczeniach. Uwzględnić mimo to?",
			"Uwaga!", MB_YESNO | MB_ICONQUESTION) == IDYES;
	}

	if (IsDlgButtonChecked(hwnd, ID_CHECKBOX1) == BST_CHECKED || IsFilled) {
		GetWindowText(hText2, (LPSTR)matrix2, GetWindowTextLength(hText2) + 1);
		IsFilled = true;
		Matrix_B=GetTextMatrix(matrix2, Dim_B1, Dim_B2, hwnd);
	}

	//Wywalenie message boxa, jak coś się nie zgadza. Na tym etapie powinno się wszystko zgadzać.

	//if(Matrix_A==NULL) MessageBox(hwnd, "MacierzA.", "Uwaga!", MB_ICONWARNING | MB_OK);
	//if (Matrix_B == NULL) MessageBox(hwnd, "MacierzB.", "Uwaga!", MB_ICONWARNING | MB_OK);


	if (Matrix_A==NULL ||(Matrix_B==NULL && IsFilled)) {		//zgłoszenie wyjątku, gdy nie zgadzają się wpisane znaki
	MessageBox(hwnd,"Coś jest nie tak we wpisanej macierzy. Prawdopodobnie został wpisany znak inny niż liczba. Spróbuj ponownie.","Uwaga!",MB_ICONWARNING | MB_OK);
	return;
	}

	matrix* Matrix_C=GetComboOperation(hCombo3,*Matrix_A,*Matrix_B);		//result
	
	if (Matrix_C == NULL) {
	MessageBox(hwnd, "Błąd w obliczaniu zadanego działania. Spróbuj ponownie.", "Uwaga!", MB_ICONWARNING | MB_OK);
	return;
	}



	char matrix_ch[MAXSIZE];
	matrix_ch[0] = '\0';
	double** matrix_d = Matrix_C->read();

	int index = 0;

	for (int v = 0; v < Matrix_C->x;v++) {
		for (int c = 0; c < Matrix_C->y;c++) {
			string aux= double_str(matrix_d[v][c]);
			for (int i = 0; i<aux.length(); i++) {
				matrix_ch[index] = aux[i];
				index++;
			}
			matrix_ch[index+1]=' ';
			index += 2;
		}
		matrix_ch[index]='\n';
		index++;
	}
	matrix_ch[index]='\0';

	//Nadpisywanie okna ( dodawania elementów)
	HINSTANCE hInstance = GetModuleHandle(NULL);

	HWND hStatic7 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 30, 440, 300, 100, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic7, "Wynik wybranego działania jest nastepujący:");
	HWND hStatic8 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
		SS_LEFT, 30, 440, 300, 100, hwnd, NULL, hInstance, NULL);
	SetWindowText(hStatic8, (LPSTR)matrix_ch);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hwnd, WM_CLOSE, OnClose);
		HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
