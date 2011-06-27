#include "greyscale.h"

#include <ctype.h> //liefert ascii isspace
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include "hufftree.h"


GreyScale::GreyScale(int width, int height, Encoding enc):
	data(width*height),width(width),height(height),targetEncoding(enc){}

GreyScale::GreyScale(const GreyScale& o):
	data(o.data),width(o.width),height(o.height),targetEncoding(o.targetEncoding){}

GreyScale::GreyScale(const char filename[]){
	std::fstream   file;
	
	file.open(filename,std::ios::in);
	if (file.rdstate())
		assert(false);
	else
	{
		file >> *this;
	}
	file.close();
}
		
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
	float mask[]{
		 0,-1, 0,
		-1, 4,-1,
		 0,-1, 0
	};
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
			std::sort(myvals.begin(),myvals.end());
			g(j,i)=myvals[4];
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

bool GreyScale::ToFile(const char filename[]){
  std::fstream   file(filename,std::ios::out | std::ios::trunc | std::ios::binary);
	if (file.rdstate())
		assert(false);
	else
	{
		file << *this;
		if(file.rdstate()) assert(false);
	}
	file.close();
	return true;
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
huffTree* buildTree(const std::vector<unsigned int>& histogram){
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
std::vector<unsigned char> huffmanDecompress(const std::vector<unsigned char>& pixmap, short width, short height){
	std::vector<unsigned char> p2(pixmap);
	for(int i = 1; i < height; i++)
		for(int j = 1; j < width-1; j++){
			p2[i*width+j] = (unsigned char)(
			( 
				( (short)pixmap[width*(i-1)+j-1]
				 +(short)pixmap[width*(i-1)+j]
				 +(short)pixmap[width*(i-1)+j+1]
				 +(short)pixmap[width*i+j-1]
				)/4 
				 - pixmap[width*i+j]
			)% 256);
		}
	return p2;
}
std::vector<unsigned char> huffmanCompress(std::vector<unsigned char>& pixmap, short width, short height){
	for(int i = 1; i < height; i++)
		for(int j = 1; j < width-1; j++){
			pixmap[i*width+j] = (unsigned char)(
			( 
				( (short)pixmap[width*(i-1)+j-1]
				 +(short)pixmap[width*(i-1)+j]
				 +(short)pixmap[width*(i-1)+j+1]
				 +(short)pixmap[width*i+j-1]
				)/4 
				 - pixmap[width*i+j]
			)% 256);
		}
	return pixmap;
}

std::istream& GreyScale::parseRaw(std::istream& s){
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
			(*this)(x,y) = s.get()/256.0;
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
			at(x,y) = value/255.0;
			if(s.rdstate()) assert(false);
		}
	
	targetEncoding = Ascii;
	return s;
}

std::istream& GreyScale::parseHuffman(std::istream& is, bool compress){
	short w, h;
	is.read((char*)&w, 2);
	is.read((char*)&h, 2);
	
	Resize(w,h);
	
	std::vector<unsigned int> histogram(256);
	for(unsigned int i = 0; i < histogram.size(); i++)
		is.read((char*)&histogram[i],4);
	
	huffTree& root = *buildTree(histogram);
	
	std::vector<unsigned char> Pixel(width*height);
	
	unsigned char byte;
	
	int curbit = -1;
	
	for(int i = 0; i < width * height; i++){
		huffTree* current = &root;
		while(!current->is_leaf()){
			if(curbit == -1){
				is.read((char*)&byte,1);
				curbit = 7;
			}
			bool thisbit = (byte >> curbit--) % 2;
			current = current->traverse(thisbit);
		}
		Pixel[i] = current->color;
	}
	
	if(compress) Pixel = huffmanDecompress(Pixel,width,height);
	
	for(unsigned int i = 0; i < Pixel.size(); i++)
		data[i] = Pixel[i]/256.0;
	
	delete &root;
	
	return is;
}

std::vector<unsigned char> GreyScale::pixmap(unsigned char& max) const{
	std::vector<unsigned char> Pixel(width*height);
	max = 0;

  for (int j=0; j<width; j++ )      // Fuer alle Bildpunkte ...
    for (int i=0; i<height; i++ ){
      float gr0=(at(j,i)*255+0.5);               // [0,1] auf [0,255] skalieren
			if      (gr0 > 255) gr0 = 255;
			else if (gr0 < 0  ) gr0 = 0;
			unsigned char gr = gr0;
			
			Pixel[j+i*width]=gr; 
			
			if (gr > max) max = gr;
    }
	return Pixel;
}

std::ostream& GreyScale::serializeRaw(std::ostream& o) const{
	std::vector<unsigned char> Pixel(pixmap());
	
	o << "P5\n" 
		<< width << " "<< height << "\n255\n";
	
	for( int i = 0; i < height; i++){
		for( int j = 0; j < width; j++)
			o.put(Pixel[j + i*width]);
	}
		
	return o;
}

std::ostream& GreyScale::serializeAscii(std::ostream& o) const{
	std::vector<unsigned char> Pixel(pixmap());
	
	o << "P2\n" 
		<< width << " "<< height << "\n255\n";
	
	for(unsigned int i = 0; i < data.size(); i++){
		o << " ";
		o.fill(' ');
		o.width(3);
		o <<(int)Pixel[i];
		if((i+1) % 16 == 0) o << "\n";
	}
	
	o << "\n";
	
	/*for( int i = 0; i < height; i++){
		for( int j = 0; j < width; j++)
			o << (int)Pixel[j + i*width] << " ";
		o << "\n";
	}*/
		
	return o;
}

std::ostream& GreyScale::serializeHuffman(std::ostream& o, bool compress) const{
	std::vector<unsigned char> Pixel(pixmap());
	
	if(compress) Pixel = huffmanCompress(Pixel,width,height);
	
	std::vector<unsigned int> histogram(256,0);
	for(unsigned int i = 0; i < data.size(); i++){
		histogram[Pixel[i]]++;
	}
	
	std::vector<std::vector<bool>> outmap = buildTree(histogram)->code_table();
		
	o << "MH";
	
	if(compress) o << "b";
	else         o << "a";
	
	o.write((char*)&width, 2);
	o.write((char*)&height,2);
	
	o.flush();
	
	for(unsigned int i = 0; i < histogram.size(); i++)
		o.write((char*) &histogram[i],4);
	
	o.flush();
	
	unsigned char curbyte = 0;
		int curpos = 7;
	
	for(int i = 0; i < width * height; i++){
		std::vector<bool>& val = outmap[Pixel[i]];
		
		for(unsigned int j = 0; j < val.size(); j++){
			curbyte |= val[j] << curpos--;
			if(curpos == -1){
				o.write((char*) &curbyte,1);
				curbyte = 0; curpos = 7;
			}
		}
	}
	if(curpos!=7)
			o.write((char*) &curbyte,1);
	
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
			return x.parseHuffman(s,false);
		else if( magic == 'b')
			return x.parseHuffman(s,true);
		else assert(false);
	}
	return s;
}