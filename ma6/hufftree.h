#pragma once
#include <algorithm>

class huffTree{
	public:
	int pixelcount;
	huffTree** children;
	unsigned char color;
	
	huffTree(unsigned char color, unsigned int pixelcount):
		pixelcount(pixelcount),children(0),color(color){}
	
	huffTree(huffTree& left,huffTree& right):
		pixelcount(left.pixelcount+right.pixelcount),
		color(std::min(left.color,right.color))
	{
		if(left < right)
			children = new huffTree*[2]{&left,&right};
		else 
			children = new huffTree*[2]{&right,&left};
	}
				
	huffTree(const huffTree& h):
		pixelcount(h.pixelcount),
		children(
			new huffTree*[2]{
				new huffTree(*h.children[0]),
				new huffTree(*h.children[1])
			}),
		color(h.color){}
		
	~huffTree(){
		if(!children) return;
		
		for(int i = 0; i < 2; i++)
			delete children[i];
		delete[] children;
		children = 0;
	}
				
	bool operator<(huffTree& t) const{
		if (pixelcount == t.pixelcount)
			return color < t.color;
		else return (pixelcount < t.pixelcount);
	}
	
	std::vector<std::vector<bool>> code_table() const{
		std::vector<std::vector<bool>> hist(256);
		code_table(std::vector<bool>(),hist);
		return hist;
	}
	
	void code_table(std::vector<bool> here, std::vector<std::vector<bool>>& hist) const{
		if(!children){
			hist[color] = here;
			return;
		}

		std::vector<bool> here0(here), here1(here);
		here0.push_back(0); here1.push_back(1);

		children[0]->code_table(here0, hist);
		children[1]->code_table(here1 ,hist);
		return;
	}
	
	huffTree* traverse(bool query){
		return children[(int) query];
	}
	
	bool is_leaf(){
		return !children;
	}
};
