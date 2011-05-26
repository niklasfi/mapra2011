/*****************************************************
*  Name       : test4.cpp                            *
*  Verwendung : Testsuite fuer Vektor-/Matrixklasse  *
*  Autor      : V. Reichelt, IGPM RWTH Aachen        *
*  Datum      : Mai '97 - Mai '00                    *
*****************************************************/

#include "tvektor.h"
#include "tmatrix.h"
#include <cmath>
#include <iostream>

using namespace std;

const int BigLen=1000, SmallLen=10, Big1=500, Big2=4;
const double eps=1e-11;

int main()
{
  int i, j;
  
  cout << "\nDieses Programm ueberprueft in gewissen Grenzen die Funktionalitaet einiger"
       << "\nFunktionen Ihrer Vektor-/Matrixklasse. Nach jedem einzelnen Test sollte die"
       << "\nMeldung 'Ok.' erscheinen. Zum Schluss sollten Sie die Meldung 'Alle Tests"
       << "\nbestanden!' erhalten. Andernfalls gab es irgendwo Probleme. Alle Tests sind"
       << "\nrelativ kurz; wenn also eine Weile lang nichts passiert, ist das Programm"
       << "\nwahrscheinlich abgestuerzt, was auf einen Fehler in einer Klasse schliessen"
       << "\nlaesst. :-("
       << "\nAuch wenn hier keine Fehler aufgetreten sein sollten, bedeutet das nicht,"
       << "\ndass die Klassen fehlerfrei sind, sondern nur, dass die Fehler gut versteckt"
       << "\nsind. ;-) Beispielsweise wird nicht ueberprueft, ob die Klassen irgendwelche"
       << "\nFehler (z.B. negative Indizes) abfangen."
       << "\nViel Glueck! :-)";

  cout << "\n\nZunaechst wird die Vektorklasse getestet:\n\n"
       << "Vektoren erzeugen und wieder loeschen." << flush;

  for (i=0; i<1000; i++)
  { Vektor x(i+1); }

  cout << " Ok.\nVektorelemente schreiben und lesen." << flush;
  { 
    Vektor x(BigLen), y(SmallLen);

    for (i=0; i<BigLen; i++)
      x(i)=2*i+0.5;
    for (i=0; i<SmallLen; i++)
      y(i)=3*i+0.7;

    for (i=0; i<BigLen; i++)
      if (fabs(x(i)-2*i-0.5)>eps) Vektor::VekFehler("Falsche Vektorelemente");
    for (i=0; i<SmallLen; i++)
      if (fabs(y(i)-3*i-0.7)>eps) Vektor::VekFehler("Falsche Vektorelemente");
  }

  cout << " Ok.\nFeld von Vektoren erzeugen." << flush;
  { Vektor x[10]; }

  cout << " Ok.\nVektor neu dimensionieren." << flush;
  {
    Vektor x;
    for (i=1; i<BigLen; i++)
    { 
      x.ReDim(i+1);
      x(i)=6*i-1.3; 
      if (fabs(x(i)-6*i+1.3)>eps || x(i-1)!=0) 
        Vektor::VekFehler("Fehler im redimensionierten Vektor!");
    }
  }

  cout << " Ok.\nVektor zuweisen." << flush;
  { 
    Vektor x(BigLen), y(BigLen);

    for (i=0; i<BigLen; i++)
      x(i)=0.5*i+0.8;

    y=x;
    for (i=0; i<BigLen; i++)
      if (fabs(y(i)-0.5*i-0.8)>eps) Vektor::VekFehler("Falsche Vektorelemente");
  }

  cout << " Ok.\nVektoren addieren." << flush;
  {
    Vektor x(BigLen), y(BigLen), z(BigLen);

    for (i=0; i<BigLen; i++)
    { x(i)=5*i-17.6; y(i)=13*i-5.4; }

    z=x+y;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)-18*i+23)>eps) Vektor::VekFehler("Fehler bei der Addition!");
    cout << " Ok.\nVektor erhoehen." << flush;

    z+=x;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)-23*i+40.6)>eps) Vektor::VekFehler("Fehler bei der Addition!");
    cout << " Ok.\nVektoren subtrahieren." << flush;

    z=x-y;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)+8*i+12.2)>eps) Vektor::VekFehler("Fehler bei der Subtraktion!");
    cout << " Ok.\nVektor erniedrigen." << flush;

    z-=x;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)+13*i-5.4)>eps) Vektor::VekFehler("Fehler bei der Subtraktion!");
    cout << " Ok.\nVorzeichen wechseln." << flush;

    z=-x;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)+5*i-17.6)>eps) Vektor::VekFehler("Fehler beim Vorzeichenwechsel!");
    cout << " Ok.\nVektor skalieren." << flush;

    z=1.1*y;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)-14.3*i+5.94)>eps) Vektor::VekFehler("Fehler beim Skalieren!");
    cout << " Ok.\nNochmal skalieren." << flush;

    z=x*3.0;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)-15*i+52.8)>eps) Vektor::VekFehler("Fehler beim Skalieren!");
    cout << " Ok.\nEin letztes Mal skalieren." << flush;

    z=y/0.5;
    for (i=0; i<BigLen; i++)
      if (fabs(z(i)-26*i+10.8)>eps) Vektor::VekFehler("Fehler beim Skalieren!");

    cout << " Ok.\nSkalarprodukt." << flush;
    if (fabs(z*y-112357521720.0)>1e-3) Vektor::VekFehler("Fehler beim Skalarprodukt!");

    cout << " Ok.\nLaenge." << flush;
    if (x.Laenge()!=BigLen) Vektor::VekFehler("Fehler bei der Laengenbestimmung!");

    cout << " Ok.\nMaximumnorm." << flush;
    x(17)=-8000;
    if (fabs(x.NormMax()-8000)>eps) Vektor::VekFehler("Fehler bei der Maximumnorm!");

    cout << " Ok.\nEuklidische Norm." << flush;
    if (fabs(x.Norm2()-91089.1361)>1e-4) Vektor::VekFehler("Fehler bei der Euklidischen Norm!");
  }

  cout << " Ok.\n\nJetzt wird die Matrixklasse getestet:\n\n"
       << "Matrizen erzeugen und wieder loeschen." << flush;

  for (i=0; i<Big1; i++)
    for (j=0; j<Big2; j++)
    { Matrix A(i+1,j+1); }

  cout << " Ok.\nMatrixelemente schreiben und lesen." << flush;
  { 
    Matrix A(Big1,Big2), B(Big2,Big1);

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        A(i,j)=2*i+0.5+j;
    for (i=0; i<Big2; i++)
      for (j=0; j<Big1; j++)
        B(i,j)=3*i+0.7-j;

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(A(i,j)-2*i-0.5-j)>eps) Matrix::MatFehler("Falsche Matrixelemente");
    for (i=0; i<Big2; i++)
      for (j=0; j<Big1; j++)
        if (fabs(B(i,j)-3*i-0.7+j)>eps) Matrix::MatFehler("Falsche Matrixelemente");
  }

  cout << " Ok.\nFeld von Matrizen erzeugen." << flush;
  { Matrix A[10]; }

  cout << " Ok.\nMatrix neu dimensionieren." << flush;
  {
    Matrix A;

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
      { 
        A.ReDim(i+1,j+1);
        A(i,j)=6*i-1.3+1.3*j; 
        if (fabs(A(i,j)-6*i+1.3-1.3*j)>eps) 
          Matrix::MatFehler("Fehler im redimensionierten Matrix!");
      }
  }

  cout << " Ok.\nMatrix zuweisen." << flush;
  { 
    Matrix A(Big1,Big2), B(Big1,Big2);

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        A(i,j)=0.5*i+0.8-0.3*j;

    B=A;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(B(i,j)-0.5*i-0.8+0.3*j)>eps) Matrix::MatFehler("Falsche Matrixelemente");
  }

  cout << " Ok.\nMatrizen addieren." << flush;
  {
    Matrix A(Big1,Big2), B(Big1,Big2), C(Big1,Big2);

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
      { A(i,j)=5*i-17.6+0.1*j; B(i,j)=13*i-5.4+0.3*j; }

    C=A+B;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)-18*i+23-0.4*j)>eps) Matrix::MatFehler("Fehler bei der Addition!");
    cout << " Ok.\nMatrix erhoehen." << flush;

    C+=A;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)-23*i+40.6-0.5*j)>eps) Matrix::MatFehler("Fehler bei der Addition!");
    cout << " Ok.\nMatrizen subtrahieren." << flush;

    C=A-B;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)+8*i+12.2+0.2*j)>eps) Matrix::MatFehler("Fehler bei der Subtraktion!");
    cout << " Ok.\nMatrix erniedrigen." << flush;

    C-=A;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)+13*i-5.4+0.3*j)>eps) Matrix::MatFehler("Fehler bei der Subtraktion!");
    cout << " Ok.\nVorzeichen wechseln." << flush;

    C=-A;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)+5*i-17.6+0.1*j)>eps) Matrix::MatFehler("Fehler beim Vorzeichenwechsel!");
    cout << " Ok.\nMatrix skalieren." << flush;

    C=1.1*B;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)-14.3*i+5.94-0.33*j)>eps) Matrix::MatFehler("Fehler beim Skalieren!");
    cout << " Ok.\nNochmal skalieren." << flush;

    C=A*3.0;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)-15*i+52.8-0.3*j)>eps) Matrix::MatFehler("Fehler beim Skalieren!");
    cout << " Ok.\nEin letztes Mal skalieren." << flush;

    C=B/0.5;
    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        if (fabs(C(i,j)-26*i+10.8-0.6*j)>eps) Matrix::MatFehler("Fehler beim Skalieren!");

    cout << " Ok.\nZeilen." << flush;
    if (A.Zeilen()!=Big1) Matrix::MatFehler("Fehler bei der Zeilenbestimmung!");

    cout << " Ok.\nSpalten." << flush;
    if (A.Spalten()!=Big2) Matrix::MatFehler("Fehler bei der Spaltenbestimmung!");
  }

  cout << " Ok.\n\nZum Schluss wird die Matrix--Vektor--Multiplikation getestet:" << endl;
  {
    Matrix A(Big1,Big2), B(Big2,3), C(Big1,3);
    Vektor x(Big2), y(Big1); 

    for (i=0; i<Big1; i++)
      for (j=0; j<Big2; j++)
        A(i,j)=i+2*j+3; 
    for (i=0; i<Big2; i++)
      for (j=0; j<3; j++)
        B(i,j)=3*i-2*j-1; 
    for (i=0; i<Big2; i++)
      x(i)=0.5*i;
    cout << "\nMatrix * Vektor." << flush;

    y=A*x;
    for (i=0; i<Big1; i++)
      if (fabs(y(i)-3*i-23)>eps) Vektor::VekFehler("Fehler bei Matrix * Vektor!");    
    cout << " Ok.\nVektor * Matrix." << flush;

    for (i=0; i<Big1; i++)
      y(i)=1.5*i;

    x=y*A;
    for (i=0; i<Big2; i++)
      if (fabs(x(i)-374250*i-62874000)>eps) Vektor::VekFehler("Fehler bei Vektor * Matrix!");    
    cout << " Ok.\nMatrix * Matrix." << flush;

    C=A*B;
    for (i=0; i<Big1; i++)
      for (j=0; j<3; j++) 
        if (fabs(C(i,j)-14*i+8*i*j+48*j-114)>eps) Matrix::MatFehler("Fehler bei Matrix * Matrix!");    
  }

  cout << " Ok.\n\nAlle Tests bestanden!" << endl;

  return 0;
}
