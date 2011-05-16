#include "matrix.h"
#include "vektor.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

Matrix::Matrix  (const int h, const int w):Zeil(h),Spalt(w){
	if (h <= 0 || w <= 0)
	MatFehler("Nur Matrizen mit positiver Größe!");

    Mat = new(nothrow) double[h*w];
    if (Mat == NULL)
	MatFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < h*w; i++)
		Mat[i] = 0;
}
Matrix::Matrix  (const Matrix& m):Zeil(m.Zeil),Spalt(m.Spalt){
	Mat = new(nothrow) double[Zeil*Spalt];
	if (Mat == NULL)
	MatFehler("Nicht genuegend Speicher!");
	
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] = m.Mat[i];
}         // Kopierkonstruktor

double& Matrix::operator () (const int i, const int j){
	#ifndef NOBOUNDS
	std::cout << "hi\n";
	if(i<0 || i>Zeil) MatFehler("Index i out of bounds when accessing Matrix(i,j)");
	if(j<0 || j>Spalt) MatFehler("Index j out of bounds when accessing Matrix(i,j)");
	#endif
	return Mat[i*Spalt+j];
}
double  Matrix::operator () (const int i, const int j) const{
	#ifndef NOBOUNDS
	std::cout << "ho\n";
	if(i<0 || i>Zeil) MatFehler("Index i out of bounds when accessing Matrix(i,j)");
	if(j<0 || j>Spalt) MatFehler("Index j out of bounds when accessing Matrix(i,j)");
	#endif
	return Mat[i*Spalt+j];
}  // Zugriff auf falls Matrix const

Matrix& Matrix::operator =  (const Matrix& x){
    if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] = x.Mat[i];

    return *this;
};  // Zuweisung
Matrix& Matrix::operator += (const Matrix& x){
	if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix += Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] += x.Mat[i];

    return *this;
}
Matrix& Matrix::operator -= (const Matrix& x){
	if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix -= Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] -= x.Mat[i];

    return *this;
}
Matrix& Matrix::operator *= (const double d){
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] *= d;
	
	return *this;
}
Matrix& Matrix::operator /= (const double d){
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] /= d;
	
	return *this;
}

Matrix& Matrix::ReDim(const int h, const int w){
	if(Mat) delete[] Mat;
	
	if (h <= 0 || w <= 0) MatFehler("Nur Matrizen mit positiver größe!");
	
	Zeil = h;
	Spalt = w;
	
    Mat = new(nothrow) double[h*w];
    if (Mat == NULL) MatFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < h*w; i++) 
    	Mat[i] = 0;
    
    return *this;
}                // neue Größe festlegen
double  Matrix::Norm2   () const{
	double res = 0;
	for (int i = 0; i < Spalt*Zeil; i++)
		res += Mat[i]*Mat[i];
	return sqrt(res);
}                   // Euklidische Norm des Matrixs

double  Matrix::NormMax () const{
	int max = 0;
    return NormMax(max);
}                  // Maximum-Norm des Matrixs

double Matrix::NormMax(int& max) const{
	max = 0;
	for (int i = 0; i < Spalt*Zeil; i++)
    	if(fabs(Mat[i])>fabs(Mat[max])) max = i;
    return fabs(Mat[max]);
}

void Matrix::MatFehler (const char str[]){
    cerr << "\nMatrixfehler: " << str << '\n' << endl;
    exit(1);
}   // Fehlermeldung ausgeben

Matrix   operator +  (const Matrix& x, const Matrix& y){
	Matrix z = x;
	return z += y;
} // Addition
Matrix   operator -  (const Matrix& x, const Matrix& y){
	Matrix z = x;
	return z -= y;
} // Subtraktion
Matrix   operator -  (const Matrix& x){
	Matrix z = x;
	return z *= -1;
}               // Vorzeichen

Matrix operator *  (const Matrix& x, const Matrix& y){
	if(x.Spalt != y.Zeil) Matrix::MatFehler("Dimensionsfehler bei der Multiplikation von Matrizen");
	
	Matrix m(x.Zeil,y.Spalt);
	
	for(int i = 0; i < x.Zeil; i++)
		for( int j = 0; j < y.Spalt; j++){
			m(i,j) = 0;
			for( int k = 0; k < x.Spalt; k++)
				m(i,j)+= x(i,k)*y(k,j);
		}
	
	return m;
} // Matrixprdukt
Matrix   operator *  (const double d,  const Matrix& m){
	Matrix z = m;
	return z *= d;
} // Vielfache
Matrix   operator *  (const Matrix& m, const double d){
	return d*m;
}
Matrix   operator /  (const Matrix& m, const double d){
	Matrix z = m;
	return z /= d;
}

bool     operator == (const Matrix& a, const Matrix& b){
	if( a.Zeil != b.Zeil || a.Spalt != b.Spalt) return false;
	for(int i = 0; i< a.Zeil*a.Spalt; i++)
		if(a.Mat[i] != b.Mat[i]) return false;
	return true;
} // Vergleich
bool     operator != (const Matrix& a, const Matrix& b){
	return !( a == b);
}

std::istream& operator >> (std::istream& is, Matrix& x){
	cout << setiosflags(ios::right);
    for (int i = 0; i < x.Zeil; i++) {
    	cout << "\n";
    	for( int j = 0; j < x.Spalt; j++){
			cout << "\t(" << setw(4) << i << ", " << setw(4) << j << ") ";
			is >> x(i,j);
		}
		cout << "\n";
    }
    return is;
}       // Eingabe
std::ostream& operator << (std::ostream& os, const Matrix& x){
	os << "\n";
	for(int i = 0; i < x.Zeil; i++) {
		os << "[";
		for(int j = 0; j < x.Spalt; j++)
			os << setw(9) << x(i,j) << " ";
		os << "]\n";
	}
	os << "\n";
	return os;
}

Vektor   operator *  (const Matrix& m, const Vektor& v){
	//std::cout << m << v;

	if(m.Spalt != v.Laeng){
		std::cout << "Matrix: " << m.Zeil << "x" << m.Spalt << "\n"
			<< "Vektor: " << v.Laeng;
		Matrix::MatFehler("Dimensionsfehler bei der Multiplikation von Matrix+Vektor");
	}
	Vektor z(m.Zeil);
	
	for(int i = 0; i < m.Zeil; i++){
		for( int k = 0; k < m.Spalt; k++)
			z(i)+= m(i,k)*v(k);
	}
	
	return z;
} // Multiplikation

Vektor   operator *  (const Vektor& v, const Matrix& m){
	//std::cout << v << m;

	if(m.Zeil != v.Laeng) Matrix::MatFehler("Dimensionsfehler bei der Multiplikation von Vektor+Matrix");
	
	Vektor z(m.Spalt);
	
	for(int j = 0; j < m.Spalt; j++)
		for(int i = 0; i < m.Zeil; i++)
			z(j) += v(i)*m(i,j);
	
	return z;
} // Multiplikation
