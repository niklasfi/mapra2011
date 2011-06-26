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
	
	std::vector<std::vector<unsigned char>> code_table(){
		std::vector<std::vector<unsigned char>> hist(256);
		code_table(0,31,hist);
		return hist;
	}
	
	void code_table(unsigned int till_here,unsigned char next_bit, std::vector<std::vector<unsigned char>>& hist){
		if(!children){
			std::vector<unsigned char>& target = hist[color];
			target.push_back  (till_here & 0xff000000);
			if(next_bit < 24)
				target.push_back(till_here & 0x00ff0000);
			if(next_bit < 16)
				target.push_back(till_here & 0x0000ff00);
			if(next_bit < 8)
				target.push_back(till_here & 0x000000ff);
			
			return;
		}

		children[0]->code_table(till_here                 , next_bit-1, hist);
		children[1]->code_table(till_here | (1<<next_bit) , next_bit-1, hist);
		return;
	}
};