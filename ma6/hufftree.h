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
		code_table(0,31,hist);
		return hist;
	}
	
	void code_table(unsigned int till_here,unsigned char next_bit, std::vector<std::vector<bool>>& hist) const{
		if(!children){
			std::vector<bool>& target = hist[color];
			for(int i = 31; i > next_bit; i--)
				target.push_back (( till_here & (1 << i)) >> next_bit);
			
			return;
		}

		children[0]->code_table(till_here                 , next_bit-1, hist);
		children[1]->code_table(till_here | (1<<next_bit) , next_bit-1, hist);
		return;
	}
	
	huffTree* traverse(bool query){
		return children[(int) query];
	}
	
	bool is_leaf(){
		return !children;
	}
};