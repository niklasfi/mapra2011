#include "tmatrix.h"
#include "tvektor.h"
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;


template < typename T >
TMatrix<T>::TMatrix  (const int h, const int w):Zeil(h),Spalt(w){
	if (h <= 0 || w <= 0)
	MatFehler("Nur Matrizen mit positiver Größe!");

    Mat = new(nothrow) T[h*w];
    if (Mat == NULL)
	MatFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < h*w; i++)
		Mat[i] = 0;
}		// Konstruktor


template < typename T >
TMatrix<T>::TMatrix  (const TMatrix<T> & m):Zeil(m.Zeil),Spalt(m.Spalt){
	Mat = new(nothrow) T[Zeil*Spalt];
	if (Mat == NULL)
	MatFehler("Nicht genuegend Speicher!");
	
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] = m.Mat[i];
}         // Kopierkonstruktor


template < typename T >
T & TMatrix<T>::operator () (const int i, const int j){
	#ifndef NOBOUNDS
	std::cout << "hi\n";
	if(i<0 || i>Zeil) MatFehler("Index i out of bounds when accessing Matrix(i,j)");
	if(j<0 || j>Spalt) MatFehler("Index j out of bounds when accessing Matrix(i,j)");
	#endif
	return Mat[i*Spalt+j];
}		// Schreib- und Lesezugriff


template < typename T >
T TMatrix<T>::operator () (int i, int j) const {
	#ifndef NOBOUNDS
	std::cout << "ho\n";
	if(i<0 || i>Zeil) MatFehler("Index i out of bounds when accessing Matrix(i,j)");
	if(j<0 || j>Spalt) MatFehler("Index j out of bounds when accessing Matrix(i,j)");
	#endif
	return Mat[i*Spalt+j];
}  // Zugriff auf falls Matrix const


template < typename T >
TMatrix<T>& TMatrix<T>::operator =  (const TMatrix<T>& x){
    if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix = Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] = x.Mat[i];

    return *this;
};  // Zuweisung


template < typename T >
TMatrix<T>& TMatrix<T>::operator += (const TMatrix<T>& x){
	if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix += Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] += x.Mat[i];

    return *this;
}


template < typename T >
TMatrix<T>& TMatrix<T>::operator -= (const TMatrix<T>& x){
	if (Zeil != x.Zeil || Spalt != x.Spalt)
		MatFehler("Inkompatible Dimensionen fuer 'Matrix -= Matrix'!");

    for (int i = 0; i < Spalt*Zeil; i++)
		Mat[i] -= x.Mat[i];

    return *this;
}


template < typename T >
TMatrix<T>& TMatrix<T>::operator *= (const T d){
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] *= d;
	
	return *this;
}


template < typename T >
TMatrix<T>& TMatrix<T>::operator /= (const T d){
	for(int i = 0; i < Zeil*Spalt; i++)
		Mat[i] /= d;
	
	return *this;
}


template < typename T >
TMatrix<T>& TMatrix<T>::ReDim(const int h, const int w){
	if(Mat) delete[] Mat;
	
	if (h <= 0 || w <= 0) MatFehler("Nur Matrizen mit positiver größe!");
	
	Zeil = h;
	Spalt = w;
	
    Mat = new(nothrow) T[h*w];
    if (Mat == NULL) MatFehler("Nicht genuegend Speicher!");

    for (int i = 0; i < h*w; i++) 
    	Mat[i] = 0;
    
    return *this;
}	// neue Größe festlegen

//#include "maxnorm.cpp" //jee siang's matrix norm


template < typename T >
void TMatrix<T>::MatFehler (const char str[]){
    cerr << "\nMatrixfehler: " << str << '\n' << endl;
    exit(1);
}   // Fehlermeldung ausgeben


template < typename T >
TMatrix<T>   operator +  (const TMatrix<T>& x, const TMatrix<T>& y){
	TMatrix<T> z = x;
	return z += y;
} // Addition


template < typename T >
TMatrix<T>   operator -  (const TMatrix<T>& x, const TMatrix<T>& y){
	TMatrix<T> z = x;
	return z -= y;
} // Subtraktion


template < typename T >
TMatrix<T>   operator -  (const TMatrix<T>& x){
	TMatrix<T> z = x;
	return z *= -1;
}               // Vorzeichen


template < typename T >
TMatrix<T> operator *  (const TMatrix<T>& x, const TMatrix<T>& y){
	if(x.Spalt != y.Zeil) TMatrix<T>::MatFehler("Dimensionsfehler bei der Multiplikation von Matrizen");
	
	TMatrix<T> m(x.Zeil,y.Spalt);
	
	for(int i = 0; i < x.Zeil; i++)
		for( int j = 0; j < y.Spalt; j++){
			m(i,j) = 0;
			for( int k = 0; k < x.Spalt; k++)
				m(i,j)+= x(i,k)*y(k,j);
		}
	
	return m;
} // Matrixprdukt


template < typename T >
TMatrix<T>   operator *  (const T d,  const TMatrix<T>& m){
	TMatrix<T> z = m;
	return z *= d;
} // Vielfache


template < typename T >
TMatrix<T>   operator *  (const TMatrix<T>& m, const T d){
	return d*m;
}


template < typename T >
TMatrix<T>   operator /  (const TMatrix<T>& m, const T d){
	TMatrix<T> z = m;
	return z /= d;
}


template < typename T >
bool     operator == (const TMatrix<T>& a, const TMatrix<T>& b){
	if( a.Zeil != b.Zeil || a.Spalt != b.Spalt) return false;
	for(int i = 0; i< a.Zeil*a.Spalt; i++)
		if(a.Mat[i] != b.Mat[i]) return false;
	return true;
} // Vergleich


template < typename T >
bool     operator != (const TMatrix<T>& a, const TMatrix<T>& b){
	return !( a == b);
}


template < typename T >
std::istream& operator >> (std::istream& is, TMatrix<T>& x){
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


template < typename T >
std::ostream& operator << (std::ostream& os, const TMatrix<T>& x){
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


template < typename T >
TVektor<T>   operator *  (const TMatrix<T>& m, const TVektor<T>& v){
	//std::cout << m << v;

	if(m.Spalt != v.Laenge()){	// Laeng -> Laenge()
		std::cout << "Matrix: " << m.Zeil << "x" << m.Spalt << "\n"
			<< "Vektor: " << v.Laenge();	// Laeng -> Laenge()
		TMatrix<T>::MatFehler("Dimensionsfehler bei der Multiplikation von Matrix+Vektor");
	}
	TVektor<T> z(m.Zeil);
	
	for(int i = 0; i < m.Zeil; i++){
		for( int k = 0; k < m.Spalt; k++)
			z(i)+= m(i,k)*v(k);
	}
	
	return z;
} // Multiplikation


template < typename T >
TVektor<T>   operator *  (const TVektor<T>& v, const TMatrix<T>& m){
	//std::cout << v << m;

	if(m.Zeil != v.Laenge()) TMatrix<T>::MatFehler("Dimensionsfehler bei der Multiplikation von Vektor+Matrix");
			// Laeng -> Laenge()
	TVektor<T> z(m.Spalt);
	
	for(int j = 0; j < m.Spalt; j++)
		for(int i = 0; i < m.Zeil; i++)
			z(j) += v(i)*m(i,j);
	
	return z;
} // Multiplikation
