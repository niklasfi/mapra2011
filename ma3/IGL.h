// =====================================================
// This file is part of the IGPM graphics library "IGL"
// Version 0.98, May 2006
// by V. Reichelt, IGPM RWTH Aachen
// =====================================================

#ifndef _IGL_H // IGL.h nicht doppelt benutzen
#define _IGL_H

#include<cstddef> // fuer size_t

// ===== Farben =====

#define IGL_White 1,1,1
#define IGL_Grey 0.5,0.5,0.5
#define IGL_Black 0,0,0
#define IGL_Red 1,0,0
#define IGL_Yellow 1,1,0
#define IGL_Magenta 1,0,1
#define IGL_Light_Red 1,0.5,0.5
#define IGL_Green 0,1,0
#define IGL_Light_Green 0.5,1,0.5
#define IGL_Blue 0,0,1
#define IGL_Light_Blue 0.5,0.5,1
#define IGL_Yellow 1,1,0
#define IGL_Dflt_Back 0.7,0.7,0.7

namespace IGL
{

// ============================================================================
// Default-Werte und Konstanten
// ============================================================================

static const size_t DfltWidth=400, DfltHeight=300;
enum DrawMode { Buffer, Immediate };
enum Marker   { Crss, Plus, Sqr, Rhmb, Tri_Up, Tri_Dn, Tri_Lt, Tri_Rt,
                Sqr_Fl, Rhmb_Fl, Tri_Up_Fl, Tri_Dn_Fl, Tri_Lt_Fl, Tri_Rt_Fl };

// ============================================================================
// Klasse zum Starten der IGL
// ============================================================================

// Will man vor Beginn von "main" einen Thread starten, der ein Fenster
// oeffnet, so sollte man vorher ein DummyWin erzeugen, damit es kein
// Rennen bei der Initialisierung der Event-Schleife gibt.

class DummyWin
{
  public:
    DummyWin(); // Startet die IGL
};


// ============================================================================
// Schnittstelle zur Fenster-Klasse
// ============================================================================

// Diese Klasse bildet die Benutzerschnittstelle zur eigentlichen
// Fenster-Klasse "BaseWin", die hinter der Referenz "PWin" versteckt ist.

class IGLWin
{
  private:
    class BaseWin& PWin; // Hier ist das eigentliche Fenster versteckt ;-)

  public:
    // Konstruktor (mit Default-Breite, Hoehe) und Destruktor
    IGLWin  (size_t W=DfltWidth, size_t H=DfltHeight);
    ~IGLWin ();

    // Aktuelle Parameter auslesen
    size_t GetWidth  () const;     // Fensterbreite
    size_t GetHeight () const;     // und -hoehe
    bool   IsOpen    () const;

    // Fenster manipulieren
    void DrawWindow   ();                    // Expose-Event erzeugen
    void OpenWindow   ();                    // Fenster oeffnen,
    void CloseWindow  ();                    // schliessen,
    void ClearWindow  ();                    // sauber wischen,
    void ResizeWindow (size_t W, size_t H);  // Groesse aendern

    // Globale Eigenschaften
    void SetName        (const char Name[]);            // Name
    void SetBackColor   (float R, float G, float B);    // Hintergrundfarbe
    void SetDrawingMode (DrawMode Mode);                // gepuffert etc.?

    // Lokale Parameter setzen
    void SetAxis      (float XMin, float XMax,
                       float YMin, float YMax,
                       float ZMin=-1.0, float ZMax=1.0); // Bildausschnitt
    void Scale        (float X, float Y, float Z);
    void Translate    (float X, float Y, float Z);
    void Rotate       (float X, float Y, float Z);
    void SetPointSize (float Size);
    void SetMarkSize  (float Size);
    void SetLineWidth (float Width);
    void SetColor     (float R, float G, float B);

    // Zeichnen
    void Mark2D     (float X1, float Y1, int Mode=0);
    void Point2D    (float X1, float Y1);
    void Point3D    (float X1, float Y1, float Z1);
    void Line2D     (float X1, float Y1, float X2, float Y2);
    void Line3D     (float X1, float Y1, float Z1,
                     float X2, float Y2, float Z2);
    void Tri2D      (float X1, float Y1,
                     float X2, float Y2,
                     float X3, float Y3);
    void Tri3D      (float X1, float Y1, float Z1,
                     float X2, float Y2, float Z2,
                     float X3, float Y3, float Z3);
    void TriNorm3D  (float X1, float Y1, float Z1,
                     float X1n, float Y1n, float Z1n,
                     float X2, float Y2, float Z2,
                     float X2n, float Y2n, float Z2n,
                     float X3, float Y3, float Z3,
                     float X3n, float Y3n, float Z3n);
    void Rect2D     (float LUx, float LUy, float ROx, float ROy);
    void Quad3D     (float X1, float Y1, float Z1,
                     float X2, float Y2, float Z2,
                     float X3, float Y3, float Z3,
                     float X4, float Y4, float Z4);
    void QuadNorm3D (float X1, float Y1, float Z1,
                     float X1n, float Y1n, float Z1n,
                     float X2, float Y2, float Z2,
                     float X2n, float Y2n, float Z2n,
                     float X3, float Y3, float Z3,
                     float X3n, float Y3n, float Z3n,
                     float X4, float Y4, float Z4,
                     float X4n, float Y4n, float Z4n);
};


// ============================================================================
// Hilfsfunktionen
// ============================================================================

void NormalVec (const float PRef[3], const float P1[3], const float P2[3],
                float Nrml[3]);

}

#endif
