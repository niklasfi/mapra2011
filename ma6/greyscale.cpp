#include "greyscale.h"

#include <ctype.h> //liefert ascii isspace
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>
#include "hufftree.h"
#include "huffflattree.h"

GreyScale::GreyScale(int width, int height, Encoding enc):
	data(width*height),width(width),height(height),targetEncoding(enc){}

GreyScale::GreyScale(const GreyScale& o):
	data(o.data),width(o.width),height(o.height),targetEncoding(o.targetEncoding){}

GreyScale& GreyScale::operator=(const GreyScale& o){
	Resize(o.width, o.height);
	
	data = o.data;
	
	return *this;
}

float& GreyScale::operator()(int x, int y){
	return at(x,y);
}

float GreyScale::operator()(int x, int y) const{
	return at(x,y);
}

float& GreyScale::at(int x,int y){
	if(x>=width) assert(false);//x = width-1;
	if(x < 0    )assert(false);// x = 0;
	
	if(y>=height) assert(false);//y = height-1;
	if(y < 0    ) assert(false);//y = 0;
	
	return data[y*width + x];
}

float GreyScale::at(int x,int y) const{
	if(x>=width) x = width-1;
	if(x< 0    ) x = 0;
	
	if(y>=height) y = height-1;
	if(y < 0    ) y = 0;
	
	return data[y*width + x];
}

GreyScale& GreyScale::operator+=(const GreyScale& g){
	assert(g.height == height);
	assert(g.width == width);
	
	for(int i = 0; i < height * width; i++)
		data[i] += g.data[i];

	return *this;
}

GreyScale& GreyScale::operator-=(const GreyScale& g){
	assert(g.height == height);
	assert(g.width == width);
	
	for(int i = 0; i < height * width; i++)
		data[i] -= g.data[i];
	
	return *this;
}

GreyScale GreyScale::operator+(const GreyScale& g) const{
	GreyScale a(*this);
	return a += g;
}

GreyScale GreyScale::operator-(const GreyScale& g) const{
	GreyScale a(*this);
	return a -= g;
}

GreyScale GreyScale::Binarize(float c) const{
	GreyScale g(*this);
	for(int i = 0; i < width*height; i++)
		g.data[i] = (data[i]>c ? 1 : 0);
	return g;
}

GreyScale GreyScale::Blur() const{
	float mask[]{
		  0  ,1./5.,  0,
		1./5.,1./5.,1./5.,
		  0  ,1./5.,  0
	};
	return Convolve(mask);
}

GreyScale GreyScale::Clamp() const{
	GreyScale g(*this);
	for(int i = 0; i < width*height; i++){
		if     (g.data[i] > 1) g.data[i] = 1;
		else if(g.data[i] < 0) g.data[i] = 0;
	}
	return g;
}

GreyScale GreyScale::Contrast() const{

	float min = 1.0/0.0, max = -1.0/0.0;
	
	for(int i = 0; i < width*height; i++){
		if(data[i]<min) min = data[i];
		if(data[i]>max) max = data[i];
	}
	
	if(min==max || min==1.0/0.0) return GreyScale(*this);
	return LinTrans(1.0/(max-min),-min/(max-min));
}

float matrixAt(const float mask[], int size, int xPos ,int yPos){
	int x = xPos+size/2, y = yPos + size/2;
	return mask[y*size+x];
}

float GreyScale::convolveAt(int x, int y, const float mask[], int size) const{
	float sum = 0;
	for(int i = -size/2; i <= size/2; i++)
		for(int j = -size/2; j <= size/2; j++)
			sum += at(x+i,y+j)*matrixAt(mask,size,i,j);
	return sum;
}

GreyScale GreyScale::Convolve(const float mask[], int size) const{
	GreyScale g(width, height, targetEncoding);
	
	for(int j = 0; j < width; j ++)
		for(int i = 0; i < height; i++)
			g(j,i)=convolveAt(j,i,mask,size);

	return g;
}

GreyScale GreyScale::Kirsch() const{
	float mask[]{
		 1, 3, 3,
		-1, 0, 1,
		-3,-3,-1
	};
	return Convolve(mask);
}

GreyScale GreyScale::Laplace() const{
	float mask[]{0,-1,0,-1,4,-1,0,-1,0};
	return Convolve(mask);
}

GreyScale GreyScale::LinTrans(float a, float b) const{
	GreyScale g(*this);
	for(int i = 0; i < width*height; i++)
		g.data[i] = a*g.data[i]+b;
	return g;
}

GreyScale GreyScale::Median() const{ 
	std::vector<float> myvals(9);
	GreyScale g(width, height, targetEncoding);
	
	for(int j = 0; j < width; j++)
		for(int i = 0; i < height; i++){
			for(int x = -1; x <= 1; x++)
				for(int y = -1; y <= 1; y++)
					myvals[(y+1)*3+(x+1)] = at(j+x,i+y);
			std::sort<std::vector<float>::iterator>(myvals.begin(),myvals.end());
			g(j,i)=myvals[5];
		}
			
	return g;
}

GreyScale	GreyScale::Sobel() const{
	float dx[]{
		-1, 0, 1,
		-2, 0, 2,
		-1, 0, 1
	};
	
	float dy[]{
		  1, 2, 1,
		  0, 0, 0,
		 -1,-2,-1
	};
	
	GreyScale medx(Convolve(dx));
	GreyScale medy(Convolve(dy));
	GreyScale g(width, height, targetEncoding);
	
	for(int j = 0; j < width; j++)
		for(int i = 0; i < height; i++)
			g(j,i) = sqrt(medx(j,i)*medx(j,i)+medy(j,i)*medy(j,i));
	
	return g;
}

int GreyScale::GetWidth() const{
	return width;
}

int GreyScale::GetHeight() const{
	return height;
}

GreyScale& GreyScale::Resize(int w, int h){
	if(height != h || width != w){
		width = w; height = h;
		data.resize(width*height);
	}
	
	return *this;
}

unsigned int GreyScale::GetFormat() const{
	return targetEncoding;
}
GreyScale& GreyScale::SetFormat(Encoding enc){
	targetEncoding = enc;
	return *this;
}

bool skipcomment(std::istream& s){	
	if(s.peek() != '#') return false;
	while(s.get() != '\n');
	skipcomment(s); //kommentar direkt hinter einem Kommentar
	return true;
}

bool skipspace(std::istream& s){
	while(isspace(s.peek()))
		s.get();
	return true;
}

bool skip(std::istream& s){
	do{
		skipspace(s);
	}while(skipcomment(s));
	return true;
}

struct huffTree_compare : public std::binary_function<huffTree*, huffTree*, bool>{
	bool operator()(huffTree* a, huffTree* b) const{
		return *b < *a;
	}
};
huffTree* buildTree(const std::vector<unsigned short>& histogram){
	std::priority_queue<huffTree*, std::vector<huffTree*>, huffTree_compare> q;
	
	for(unsigned int i = 0; i < histogram.size(); i++)
		if(histogram[i]>0)
			q.push(new huffTree((unsigned char)i,histogram[i]));
	
	huffTree* tree;
	while(true){
		tree = q.top(); q.pop();
		if(q.empty()) break;
		huffTree* second = q.top(); q.pop();
		q.push(new huffTree(*tree,*second));
	}
	
	return tree;
}
std::istream& GreyScale::parseRaw(std::istream& s){
	s >> width;
	if(s.rdstate()) assert(false);
	s >> height;
	if(s.rdstate()) assert(false);
	
	{
		short maxval;
		s >> maxval;
		if(maxval > 255) assert(false); //bpm Variante mit shorts
		if(s.rdstate()) assert(false);
	}
	
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++){
			skip(s);
			(*this)(x,y) = s.get();
		}
	
	return s;
}

std::istream& GreyScale::parseAscii(std::istream& s){
	unsigned int w, h;
	skip(s);
	s >> w;
	if(s.rdstate()) assert(false);
	skip(s);
	s >> h;
	if(s.rdstate()) assert(false);
	
	skip(s);
	short maxval;
	s >> maxval;
	if(maxval > 255) assert(false); //bpm Variante mit shorts
	if(s.rdstate()) assert(false);
	
	Resize(w,h);
	
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++){
			skip(s);
			unsigned int value;
			s >> value;
			at(x,y) = (1.0*value)/maxval;
			if(s.rdstate()) assert(false);
		}
	
	targetEncoding = Ascii;
	return s;
}

std::istream& GreyScale::parseHuffmanA(std::istream& is){
	short w, h;
	is.read((char*)&w, 2);
	is.read((char*)&h, 2);
	
	Resize(w,h);
	
	std::vector<unsigned short> histogram(256);
	for(unsigned int i = 0; i < histogram.size(); i++)
		is.read((char*)&histogram[i],2);
	
	huffFlatTree root = huffFlatTree(*buildTree(histogram));
		
	for(int i = 0; i < w * h; i++){
		huffFlatTree* current = &root;
		while(!current->leaf()){
			unsigned char read;
			is.read((char*)&read,1);
			current = current->traverse(std::vector<unsigned char>(1,read));
		}
		data[i] = current->color;
	}
	
	return is;
}

std::istream& GreyScale::parseHuffmanB(std::istream&){
	//TODO
	assert(false);
}

std::vector<unsigned char> GreyScale::pixmap(unsigned char& max) const{
	std::vector<unsigned char> Pixel(width*height);
	max = 0;

  for (int j=0; j<width; j++ )      // Fuer alle Bildpunkte ...
    for (int i=0; i<height; i++ ){
      unsigned char gr=at(j,i)*255+0.5;               // [0,1] auf [0,255] skalieren
			
			Pixel[j+i*width]=gr; 
			
			if (gr > max) max = gr;
    }
	return Pixel;
}

std::ostream& GreyScale::serializeRaw(std::ostream& o) const{
	unsigned char max;
	std::vector<unsigned char> Pixel(pixmap(max));
	
	o << "P5\n" 
		<< width << " "<< height << "\n"
		<< max << "\n";
	
	for( int i = 0; i < height; i++){
		for( int j = 0; j < width; j++)
			o.put(Pixel[j + i*width]);
	}
		
	return o;
}

std::ostream& GreyScale::serializeAscii(std::ostream& o) const{
	unsigned char max;
	std::vector<unsigned char> Pixel(pixmap(max));
	
	o << "P2\n" 
		<< width << " "<< height << "\n"
		<< max << "\n";
	
	for( int i = 0; i < height; i++){
		for( int j = 0; j < width; j++)
			o << (int)Pixel[j + i*width] << " ";
		o << "\n";
	}
		
	return o;
}

std::ostream& GreyScale::serializeHuffman(std::ostream& o, bool compress) const{
	std::vector<unsigned char> Pixel(pixmap());
	std::vector<unsigned short> histogram(256,0);
	for(unsigned int i = 0; i < data.size(); i++){
		histogram[Pixel[i]]++;
	}
	
	std::vector<std::vector<unsigned char>> outmap = buildTree(histogram)->code_table();
		
	o << "MHa";
	
	o.write((char*)&width, 2);
	o.write((char*)&height,2);
	
	o.flush();
	
	for(unsigned int i = 0; i < histogram.size(); i++)
		o.write((char*) &histogram[i],2);
	
	o.flush();
	
	for(int i = 0; i < width * height; i++){
		std::vector<unsigned char>& val = outmap[Pixel[i]];
		for(unsigned int j = 0; j < val.size(); j++)
			o.write((char*) &val[j],1);
	}
	
	return o;
}

std::ostream& operator<<(std::ostream& s, const GreyScale& x){
	switch (x.GetFormat()){
		case GreyScale::Raw: x.serializeRaw(s); break;
		case GreyScale::Ascii: x.serializeAscii(s); break;
		case GreyScale::HuffmanA: x.serializeHuffman(s,false); break;
		case GreyScale::HuffmanB: x.serializeHuffman(s,true); break;
		default: assert(false);
	}
	return s;
}

std::istream& operator>>(std::istream& s, GreyScale& x){
	char magic = s.get();
	if(magic == 'P'){
		magic = s.get();
		if( magic == '2')
			return x.parseAscii(s);
		else if( magic == '5')
			return x.parseRaw(s);
		else assert(false);
	}
	else if(magic == 'M' && s.get() == 'H'){
		magic = s.get();
		if( magic == 'a')
			return x.parseHuffmanA(s);
		else if( magic == 'b')
			return x.parseHuffmanB(s);
		else assert(false);
	}
	return s;
}