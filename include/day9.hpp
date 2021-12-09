#ifndef DBMW_INCLUDE_DAY9_HPP_
#define DBMW_INCLUDE_DAY9_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day9{


	day9(const std::string& st="input/input9"){
		for(auto v:fiterator(st,'\n'))
		{
			std::vector<unsigned> e;
			for(auto c:v)
				e.push_back(c-'0');
			b.addRow(e);
		}
	}

	void firstStar(){
		unsigned ct=0;
		for(auto e=b.begin();e!=b.end();++e)
		{
			bool low=true;
			for(auto v:e.around4())
			{
				if(*v&&**e>=**v)
				{
					low=false;
					break;
				}
			}
			if(low)
				ct+=1+**e;
		}
		std::cout<<"day 9 risk level: "<<ct<<std::endl;
	}


	void secondStar(){
		std::vector<unsigned> bassinSize;
		std::vector<board<unsigned>::iter> stack;
		std::set<board<unsigned>::iter> visited;

		for(auto e=b.begin();e!=b.end();++e){

			if(visited.count(e))
				continue;

			if(**e==9)
				continue;

			unsigned size=1;
			visited.insert(e);
			stack.push_back(e);

			while(stack.size()){
				auto s=stack.back();
				stack.pop_back();

				for(auto neighbor:s.around4())
					if(neighbor.inBounds()&&**neighbor!=9&&!visited.count(neighbor))
					{
						stack.push_back(neighbor);
						visited.insert(neighbor);
						size++;
					}
			}
			bassinSize.push_back(size);
		}
		std::sort(bassinSize.begin(), bassinSize.end());
		auto l=bassinSize.size();
		std::cout<<"day 9, star 2, bassin sizes: "<<
				bassinSize[l-1]*bassinSize[l-2]*bassinSize[l-3]<<std::endl;

	}

	board<unsigned> b;

};



#endif
