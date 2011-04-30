extern const int AnzahlBeispiele;

const int MaxTiefe = 30;


enum VerfahrensTyp { Trapezregel, Romberg, Bulirsch} ;

typedef double (*Funktion) (double x);
typedef double Vektor[MaxTiefe + 1];



void Start (int beispiel, bool genau, bool grafik,
		      VerfahrensTyp Verfahren, Funktion &f,
		      double &eps, double &a, double &b);

void Ausgabe (int stufe, Vektor Extrapol);

void Schluss (double Integralwert, double epsilon,
		     Vektor extrapol, int stufe);


