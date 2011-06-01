/**************************************************************
*  Name       : unit7.h                                       *
*  Verwendung : Schnittstelle zu Praktikumsumgebung (MAPRA),  *
*               Anzeigen von Grauwertbildern                  *
*  Autor      : V. Reichelt, IGPM RWTH Aachen                 *
*  Datum      : Jun '00                                       *
**************************************************************/

#ifndef UNIT7_H
#define UNIT7_H

// Datentyp der Laenge 1 Byte (kann Zahlen im Bereich 0 bis 255 darstellen).
// Da es sich aber - streng genommen - nicht um einen Zahlentyp, sondern um
// einen Zeichentyp handelt, muss man den Datentyp fuer eine Ausgabe mittels
// "<<" nach "short" oder "int" konvertieren (engl. casten) um eine Zahl als
// Ausgabe zu bekommen, z.B.:
//   byte x=76; cout << short(x) << endl;

typedef unsigned char byte;

// Die Funktion "ShowImage" zeigt ein Graustufenbild der Breite "Width"
// und Hoehe "Height" an. Die Grauwerte der einzelnen Bildpunkte werden
// (zeilenweise von links oben nach rechts unten) im Feld "Pixel" uebergeben.
// (Der Programmierer ist dafuer verantwortlich, dass das Feld mindestens
// die Dimension "Width*Height" hat.) Ferner bekommt das Fenster die
// Ueberschrift "Text".
// Der Parameter "Id" hat folgende Bedeutung: Hat keins der angezeigten
// Bilder dieselbe Identifikationsnummer "Id", so wird ein neues Fenster
// geoeffnet, andernfalls wird das Bild, das diese Nummer traegt, uebermalt.
// Man kann ein Fenster schliessen, indem man mindestens einen (am besten alle)
// der drei Parameter "Width", "Height" oder "Pixel" auf 0 bzw. NULL setzt.

void ShowImage ( int Width, int Height, const byte Pixel[],
                 int Id, const char Text[] );

#endif
