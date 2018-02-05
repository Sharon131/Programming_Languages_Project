#include "matrixes.hpp"

matrix::matrix(int x_w=1, int y_w=1):
	x(x_w),
	y(y_w)
{
	this->m = new double*[this->x];

	for (int v = 0; v < this->x; v++) {
		this->m[v] = new double[this->y];
		for (int c = 0; c < this->y; c++) {
			this->m[v][c] = 0;
		}
	}
}

matrix::matrix(int x_w, int y_w, double** t) :
	x(x_w),
	y(y_w)
{
	this->m = new double*[this->x];
	for (int v = 0; v < this->x; v++) {
		this->m[v] = new double[this->y];
		for (int c = 0; c < this->y; c++) {
			this->m[v][c] = t[v][c];
		}
	}
}

matrix::matrix():
	x(1),
	y(1)
{
	this->m = new double*[1];
	this->m[0] = new double;
}

matrix::matrix(const matrix &copy):
	x(copy.x),
	y(copy.y)
{
	this->m = copy.read();
}

matrix::matrix(matrix * old) :
	x(old->x),
	y(old->y)
{
	this->m = old->read();

	delete old;								
}

matrix::~matrix() {
	for (int v = 0; v < this->x; v++) {
		delete[] m[v];
	}

	delete[] m;
}

bool matrix::write(double value, int x_w, int y_w) {
	if (x_w <= this->x && y_w <= this->y) {
		this->m[x_w - 1][y_w - 1] = value;
		return true;
	}
	else return false;
}

double matrix::read(int x_w,int y_w) const  {
	if (x_w <= this->x && y_w <= this->y) {
		return m[x_w - 1][y_w - 1];
	}
	return 0;
}

double** matrix::read() const  {
	double** t = new double*[this->x];
	for (int v = 0; v < this->x; v++) {
		t[v] = new double[this->y];
		for (int c = 0; c < this->y; c++) {
			t[v][c] = this->m[v][c];
		}
	}
	return t;
}

void matrix::dosun(double **tab, int n, int w, int k, double** t) { //do poprawy i zamiany na move poza klasą
	for (int i = w + 1; i<n; i++) {
		for (int h = 0; h<n; h++) {
			t[i - 1][h] = tab[i][h];
		}
	}

	for (int g = 0; g<n; g++) {
		for (int j = k + 1; j<n; j++)
		{
			t[g][j - 1] = t[g][j];
		}
	}
}

double matrix :: det_rek(double** t, int n, int k) {
	if (n == 1) {
		return t[0][0];
	}
	double sum = 0;
	for (int c = 0; c<n; c++) {
		double aux = t[0][c];

		double **tab = new double*[n];
		for (int i = 0; i < n; i++) {
			tab[i] = new double[n];
		}

		dosun(t, n, 0, c, tab);
		if (c % 2 == 0) {

			sum += aux * det_rek(tab, n - 1, c);
		}
		if (c % 2 == 1) {
			sum -= aux * det_rek(tab, n - 1, c);
		}
	}
	return sum;
}

double matrix::det() {
	if (x == y) {
		double **t = this->read();
		return det_rek(t, x, -1);
	}
	else return 0;
}

double matrix::cofactor(int x_w, int y_w) {
	if (x_w <= x && y_w <= y) {
		double **t = new double*[x];
		for (int i = 0; i < x; i++) {
			t[i] = new double[y];
		}

		dosun(this->read(), x, x_w, y_w, t);			//move zamiast dosun
		if ((x_w + y_w) % 2 == 0) {
			return (this->read(x_w, y_w))*(this->det_rek(t,x,-1));
		}
		else {
			return (-1)*(this->read(x_w, y_w))*(this->det_rek(t, x, -1));
		}
	}
	else return 0;
}

int matrix::rank()
{
	int rank = 0;
	matrix new_m = this->triangle();
	double** t = new_m.read();
	int column = this->y;
	for (int v = 0; v < this->x; v++) {
		if (column<this->y && t[v][column]!=0) {
			continue;
		}
		for (int c = 0; c < this->y; c++) {
			if (t[v][c] != 0) {
				rank++;
				column = c;
				break;
			}
		}
	}
	return rank;
}

int matrix::def() {
	if (x>y) {
		return y - (this->rank());
	}
	else {
		return x - (this->rank());
	}
}

double matrix::trace() {
	if (this->x == this->y) {
		double aux = 1;
		for (int d = 0; d < this->x; d++) {
			aux *= this->read(d, d);
		}
		return aux;
	}
	else return 0;
}

bool matrix::operator ==(const matrix& second) const {
	if (this->x == second.x && this->y == second.y) {
		for (int v = 0; v < this->x; v++) {
			for (int c = 0; c < this->y; c++) {
				if (m[v][c] != second.read(v, c)) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

matrix* matrix::operator+(const matrix& second) {
	if (this->x == second.x && this->y == second.y) {
		matrix new_m(this->x, this->y);
		for (int v = 0; v < this->x; v++) {
			for (int c = 0; c < this->y; c++) {
				new_m.write(this->m[v][c] + second.read(v, c), v, c);
			}
		}
		return &new_m;
	}
	return NULL;
}

matrix* matrix::operator-(const matrix& second) {
	if (this->x == second.x && this->y == second.y) {
		matrix new_m(this->x, this->y);
		for (int v = 0; v < this->x; v++) {
			for (int c = 0; c < this->y; c++) {
				new_m.write(m[v][c] - second.read(v, c), v, c);
			}
		}
		return &new_m;
	}
	return NULL;
}

matrix* matrix::operator*(const matrix& second) {
	if (this->y == second.x) {
		matrix* new_m=new matrix(this->x, second.y);
		for (int v = 0; v < this->x; v++) {
			for (int c = 0; c < second.y; c++) {
				double aux = 0;
				for (int i = 0; i < y; i++) {
					aux += (this->read(v, i))*(second.read(i,c));
				}
				new_m->write(aux,v,c);
			}
		}
		
		return new_m;
	}
	return NULL;
}

matrix& matrix::operator-() {
	matrix new_m(this->x, this->y);
	for (int v = 0; v < this->x; v++) {
		for (int c = 0; c < this->y; c++) {
			new_m.write(-(this->m[v][c]), v, c);
		}
	}
	return new_m;
}

matrix& matrix::operator*(double number) {
	matrix new_m(this->x, this->y);
	for (int v = 0; v < this->x; v++) {
		for (int c = 0; c < this->y; c++) {
			new_m.write(number*(this->read(v,c)),v,c);
		}
	}
	return new_m;
}

matrix& matrix::operator /(double number) {
	matrix new_m(this->x,this->y);
	for (int v = 0; v < this->x; v++) {
		for (int c = 0; c < this->y; c++) {
			new_m.write(this->read(v, c)/number, v, c);
		}
	}
	return new_m;
}

matrix& matrix::transpose() {
	matrix new_m(this->y, this->x);
	for (int v = 0; v < this->x; v++) {
		for (int c = 0; c < this->y; c++) {
			new_m.write(this->read(v,c),c,v);
		}
	}
	return new_m;
}

matrix& matrix::triangle()
{
	double** t = this->read();
	
	for (int d = 0; d < this->x - 1; d++) {
		bool flag = zeros(t, this->x, this->y, d);
		for (int v = d + 1; v < this->x && flag; v++) {
			for (int c = this->y-1; c >=0; c--) {
				t[v][c] = t[v][c] - t[d][c] * t[v][d] / t[d][d];
			}
		}
	}

	matrix new_m(this->x, this->y, t);
	return new_m;
}

matrix & matrix::inverse_sq()
{
	// znalezienie macierzy trójkątnej i jednoczesne te same operacje na jednostkowej
	double** t = this->read();

	double** E = new double*[this->x];			//tworzenie macierzy jednostkowej
	for (int v = 0; v < this->x; v++) {
		E[v] = new double[this->y];
		for (int c = 0; c < this->y; c++) {
			if (c == v) {
				E[v][c] = 1;
			}
			else {
				E[v][c] = 0;
			}
		}
	}

	for (int d = 0; d < this->x - 1; d++) {
		bool flag = false;
		int row = d;
		while (d<this->y && row<this->x && t[row][d] == 0) {
			row++;
		}
		if (row<this->x) {
			swap_rows(t, this->x, this->y, d, row);
			swap_rows(E, this->x, this->y, d, row);
			flag=true;
		}
		
		for (int v = d + 1; v < this->x && flag; v++) {
			for (int c = this->y -1; c >=0; c--) {
				E[v][c] = E[c][v] - E[d][c] * t[v][d] / t[d][d];
				t[v][c] = t[c][v] - t[d][c] * t[v][d] / t[d][d];
			}
		}
	}

	for (int v = 0; v<this->x; v++) {
		for (int c = this->y - 1; c >= v; c--) {
			t[v][c] /= t[v][v];
		}
	}

	//odwrotny algorytm Gaussa

	for (int d = this->y - 1; d > 0; d--) {
		for (int v = d - 1; v >= 0; v--){
			double aux = t[v][d];
			for (int c = 0; c <this->x; c++) {
				E[v][c] = E[v][c] - E[d][c] * aux;
				t[v][c] = t[v][c] - t[d][c] * aux;
			}
		}
	}
	

	matrix new_m(this->x, this->y, E);
	return new_m;
}

/*matrix & matrix::inverse_rec()
{
	// znalezienie macierzy trapezowej i jednoczesne te same operacje na jednostkowej
}*/

matrix * matrix::inverse()
{
	if (this->det() == 0) {
		return NULL;
	}
	if (this->x == this->y) {
		return &(this->inverse_sq());
	}
	else {
		return NULL;
			//&(this->inverse_rec());
	}
}



