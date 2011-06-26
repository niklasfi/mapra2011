#pragma once
#include <map>
#include <vector>
#include "hufftree.h"

class huffFlatTree{
	huffFlatTree* insertionTraversal(std::vector<unsigned char> query, int start, unsigned char color){
		huffFlatTree* next = this;
		for(unsigned int i = start; i < query.size(); i++){
			huffFlatTree* nuChild = new huffFlatTree();
			next->children[query[i]] = nuChild;
			next = nuChild;
		}			
		next->color = color;
		return next;
	}
	
	
	public:
	
	huffFlatTree(){}
	huffFlatTree(const huffTree& h){
		std::vector<std::vector<unsigned char>> tab = h.code_table();
		
		for(unsigned int i = 0; i < tab.size(); i++)
			traverse(tab[i],true,i);
	}
	~huffFlatTree(){
		for(std::map<unsigned char, huffFlatTree*>::iterator it = children.begin();
			it != children.end();
			it ++
		)
			delete it->second;
	}
	
	
	huffFlatTree* traverse(std::vector<unsigned char> query,bool create = false, unsigned char color = 0){
		huffFlatTree* next = this;
		for(unsigned int i = 0; i < query.size(); i++){
			std::map<unsigned char,huffFlatTree*>::iterator it=next->children.find(query[i]);
			if(it==next->children.end()){
				if(create) return next->insertionTraversal(query,i,color);
				else       return 0;
			}
			next = it->second;
		}
		return next;
	}
	
	bool leaf(){ return !children.size(); }
	
	unsigned char color;	
	std::map<unsigned char,huffFlatTree*> children;
};