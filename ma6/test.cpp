#include <string>
#include <fstream>
#include <iostream>

//#include <unistd.h> //gives us sleep

#include "greyscale.h"
//#include "unit6.h"

using namespace std;

// globale Konstanten, die die Darstellung des Bildes kontrollieren

int  ZoomFac=2;  // Vergroesserungsfaktor
bool Show=true;  // Bild anzeigen oder nicht


// Die Funktion "Display" dient als Verbindung zwischen der "Greyscale"-Klasse
// und der Funktion "ShowImage" aus "unit7". Hier wird der Datentyp "float"
// in den Datentyp "byte" (inclusive Clamping) umgewandelt. Je nach dem Wert
// von "ZoomFac" werden aus einem "float"-Pixel ein oder mehrere "byte"-Pixel.

/*void Display ( const GreyScale &Pic, int Id, const char Text[] )
{
  if (!Show) return;                           // Bild nicht anzeigen

  byte  Pixel[Pic.GetWidth()*Pic.GetHeight()*ZoomFac*ZoomFac];

  for (int j=0; j<Pic.GetHeight(); j++ )      // Fuer alle Bildpunkte ...
    for (int i=0; i<Pic.GetWidth(); i++ )
    {
      float gr=Pic(i,j)*255+0.5;               // [0,1] auf [0,255] skalieren
      if (gr>255) gr=255; else if (gr<0) gr=0; // clampen
      if (ZoomFac==1)                          // behandle den Fall ZoomFac==1
        Pixel[i+j*Pic.GetWidth()]=byte(gr);    // der Effizienz wegen einzeln
      else
        for ( int k=0; k<ZoomFac; k++ )          
          for ( int l=0; l<ZoomFac; l++ )
            Pixel[(i*ZoomFac+k)+(j*ZoomFac+l)*Pic.GetWidth()*ZoomFac]=byte(gr);
    }

  ShowImage(Pic.GetWidth()*ZoomFac,Pic.GetHeight()*ZoomFac,Pixel,Id,Text);
}*/


int main(){
	GreyScale pic;
  fstream   file;
  char      name[] = "Bilder/barcode.pgm";
	
	file.open(name,ios::in);
	if (file.rdstate())
		cerr << "Error: Couldn't open '" << name << "'!\n";
	else
	{
		file >> pic;
		
		std::stringstream ss;
		
		ss << pic;
		
	}
	file.close();
	
	return 0;
}