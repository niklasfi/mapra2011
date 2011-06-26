#pragma once
#include <vector>
#include <sstream>

class GreyScale{
	public:
	
	enum Encoding {Raw, Ascii, HuffmanA, HuffmanB};
	
	GreyScale(int width = 0, int height = 0, Encoding = Raw);
	GreyScale(const GreyScale&);
	GreyScale(const char filename[]);
	~GreyScale(){};
	
	GreyScale& operator=(const GreyScale&);
	
	float& operator()(int x, int y);
	float operator()(int x, int y) const;
	
	float& at(int x, int y);
	float at(int x, int y) const;
	
	GreyScale& operator+=(const GreyScale&);
	GreyScale& operator-=(const GreyScale&);
	GreyScale operator+(const GreyScale&) const;
	GreyScale operator-(const GreyScale&) const;
	
	GreyScale Binarize(float c) const; //TODO
	GreyScale Blur() const; //TODO
	GreyScale Clamp() const; //TODO
	GreyScale Contrast() const; //TODO
	GreyScale Convolve(const float mask[], int size=3) const; //TODO
	GreyScale Kirsch() const; //TODO
	GreyScale Laplace() const; //TODO
	GreyScale LinTrans(float a, float b) const; //TODO
	GreyScale Invert() const{ return LinTrans(-1,1); }
	GreyScale Median() const; //TODO
	GreyScale	Sobel() const; //TODO
	
	int GetWidth() const;
	int GetHeight() const;
	GreyScale& Resize(int, int);
	
	unsigned int GetFormat() const;
	GreyScale& SetFormat(Encoding);
	
	bool ToFile(const char filename[]);
	
	private:
	
	std::vector<float> data;
	short width;
	short height;
	
	Encoding targetEncoding;
	
	/* convolveAt berechnet das Ergebnis der Faltung für einen bestimmten Pixel
	 * (x,y) mit der Maske mask */
	
	float convolveAt(int x, int y, const float mask[], int size) const;
	
	/* Diese Funktionen Parsen einen entsprechenden Input aus dem Istream, wobei
	 * sich dieser beim Aufruf genau hinter den MagicBits befinden muss. Danch
	 * Wird genau ein Bild gelesen. (Der Raw- bzw Huffman-Standard lässt auch
	 * mehrere Bilder pro Datei zu */
	
	std::istream& parseRaw(std::istream&);
	std::istream& parseAscii(std::istream&); //TODO
	std::istream& parseHuffman(std::istream&,bool compress= false); //TODO

	/* Diese Funktionen erstellen eine Repräsentation des Bildes als vector von
	 * unsigned char (hier wird data konvertiert). optional kann zusätzlich der
	 * maximalwert in einem Bild berechnet werden. hierzu muss max als referenz
	 * übergeben werden */

	std::vector<unsigned char> pixmap() const{ unsigned char max; return pixmap(max); }
	std::vector<unsigned char> pixmap(unsigned char& max) const;

	/* Diese Funktionen schreiben eine komplette Datei inklusive MagicBits */
	
	std::ostream& serializeRaw(std::ostream&) const; //TODO
	std::ostream& serializeAscii(std::ostream&) const; //TODO
	std::ostream& serializeHuffman(std::ostream&, bool compress = false) const; //TODO
	
	/* der ostream-Operator gibt ein Bild in dem encoding, welches durch 
	 * targetEncoding angegeben ist aus */
	
	friend std::ostream& operator<<(std::ostream& s, const GreyScale& x);
	friend std::istream& operator>>(std::istream& s, GreyScale& x); //TODO
	/* liest genau ein Bild aus dem Istream */
};