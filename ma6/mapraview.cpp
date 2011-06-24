/********************************************************************
*  Name       : mapraview.cpp                                       *
*  Verwendung : Benutzerschnittstelle zu einer Bildklasse (MAPRA),  *
*               Bildbearbeitung: PGM-Format,                        *
*               Punktoperationen und lokale Filter                  *
*  Autor      : Sven Gross, Volker Reichelt, IGPM RWTH Aachen       *
*  Datum      : Jun '00                                             *
********************************************************************/

#include <fstream>
#include <iostream>

#include "greyscale.h"
#include "unit6.h"

using namespace std;

// globale Konstanten, die die Darstellung des Bildes kontrollieren

int  ZoomFac=1;  // Vergroesserungsfaktor
bool Show=true;  // Bild anzeigen oder nicht


// Die Funktion "Display" dient als Verbindung zwischen der "Greyscale"-Klasse
// und der Funktion "ShowImage" aus "unit7". Hier wird der Datentyp "float"
// in den Datentyp "byte" (inclusive Clamping) umgewandelt. Je nach dem Wert
// von "ZoomFac" werden aus einem "float"-Pixel ein oder mehrere "byte"-Pixel.

void Display ( const GreyScale &Pic, int Id, const char Text[] )
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
}


// Das Hauptprogramm besteht im wesentlichen aus einer Schleife, die auf
// die Benutzereingaben wartet und die Kommandos (in der switch-Anweisung)
// interpretiert (z.B. die Filter aus der Greyscale-Klasse aufruft oder die
// globalen Variablen "Show" und "ZoomFac" setzt und das Ergebnis anzeigt).

int main()
{
  GreyScale pic, newpic;
  fstream   file;
  char      name[200], c='h';

  do                // Main loop
  {
    switch (c)
    {
      case 'h':     // Help
        cout << "(h)elp (r)ead (w)rite (u)ndo (q)uit (d)isplay on/off (1) (2) (3) (4)\n"
             << "(+) (-) (<) (>) (b)inarize (B)lur (c)lamp (C)ontrast (i)nvert\n"
             << "(k)irsch (K)irsch+ (l)aplace (L)aplace+ (m)edian (s)obel (S)obel+" << endl;
        break;

      case 'r':     // Read
        cout << "Read image... Enter filename: ";
        cin >> name;
        file.open(name,ios::in);
        if (file.rdstate())
          cerr << "Error: Couldn't open '" << name << "'!\n";
        else
        {
          file >> newpic;
          Display(newpic,0,name);
          pic.Resize(0,0);
          Display(pic,1,"");
        }
        file.close();
        break;

      case 'w':     // Write
        cout << "Write image... Enter filename: ";
        cin >> name;
        file.open(name,ios::out);
        if (file.rdstate())
          cerr << "Error: Couldn't open '" << name << "'!\n";
        else
          file << newpic;
        file.close();
        break;

      case 'u':     // Undo
        cout << "Undo...\n";
        newpic=pic;
        Display(newpic,1,"Undo");
        break;

      case 'd':     // Display on/off
        Show=!Show;
        cout << "Display " << (Show?"on":"off") << " ...\n";
        Display(newpic,1,"Display");
        break;

      case '1':     // Zoom
      case '2':
      case '3':
      case '4':
        ZoomFac=c-48;
        cout << "Set zoom factor " << ZoomFac << "...\n";
        Display(newpic,1,"Zoom");
        break;

      case '+':     // Lighter
        cout << "Lighter...\n";
        pic=newpic;
        newpic=pic.LinTrans(1,0.1);
        Display(newpic,1,"Lighter");
        break;

      case '-':     // Darker
        cout << "Darker...\n";
        pic=newpic;
        newpic=pic.LinTrans(1,-0.1);
        Display(newpic,1,"Darker");
        break;

      case '<':     // Increase Contrast
        cout << "Increase Contrast...\n";
        pic=newpic;
        newpic=pic.LinTrans(1.1,-0.05);
        Display(newpic,1,"Increase Contrast");
        break;

      case '>':     // Decrease Contrast
        cout << "Decrease Contrast...\n";
        pic=newpic;
        newpic=pic.LinTrans(0.9,0.05);
        Display(newpic,1,"Decrease Contrast");
        break;

      case 'b':     // Binarize
        cout << "Binarize...\n";
        pic=newpic;
        newpic=pic.Binarize(0.5);
        Display(newpic,1,"Binarize");
        break;

      case 'B':     // Blur
        cout << "Blur...\n";
        pic=newpic;
        newpic=pic.Blur();
        Display(newpic,1,"Blur");
        break;

      case 'c':     // Clamp
        cout << "Clamp...\n";
        pic=newpic;
        newpic=pic.Clamp();
        Display(newpic,1,"Clamp");
        break;

      case 'C':     // Contrast
        cout << "Maximize Contrast...\n";
        pic=newpic;
        newpic=pic.Contrast();
        Display(newpic,1,"Maximize Contrast");
        break;

      case 'i':     // Invert
        cout << "Invert...\n";
        pic=newpic;
        newpic=pic.LinTrans(-1,1);
        Display(newpic,1,"Invert");
        break;

      case 'k':     // Kirsch
        cout << "Kirsch filter...\n";
        pic=newpic;
        newpic=pic.Kirsch();
        Display(newpic,1,"Kirsch");
        break;

      case 'K':     // Kirsch+
        cout << "Add Kirsch filter...\n";
        pic=newpic;
        newpic=pic.Kirsch().LinTrans(0.1,0);
        newpic+=pic;
        Display(newpic,1,"Add Kirsch");
        break;

      case 'l':     // Laplace
        cout << "Laplace filter...\n";
        pic=newpic;
        newpic=pic.Laplace();
        Display(newpic,1,"Laplace");
        break;

      case 'L':     // Laplace+
        cout << "Add Laplace filter...\n";
        pic=newpic;
        newpic=pic.Laplace().LinTrans(0.1,0);
        newpic+=pic;
        Display(newpic,1,"Add Laplace");
        break;

      case 'm':     // Median
        cout << "Median filter...\n";
        pic=newpic;
        newpic=pic.Median();
        Display(newpic,1,"Median");
        break;

      case 's':     // Sobel
        cout << "Sobel filter...\n";
        pic=newpic;
        newpic=pic.Sobel();
        Display(newpic,1,"Sobel");
        break;

      case 'S':     // Sobel+
        cout << "Add Sobel filter...\n";
        pic=newpic;
        newpic=pic.Sobel().LinTrans(0.1,0);
        newpic+=pic;
        Display(newpic,1,"Add Sobel");
        break;

      default:      // Error
        cout << "Warning: Ignored unknown command '" << c << "'\n";
        break;
    }

    cout << "Enter Command (h for help): ";
    cin  >> c;

  } while (c!='q'); // Quit

  return 0;
}
