#ifndef DBMW_INCLUDE_DAY13_HPP_
#define DBMW_INCLUDE_DAY13_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day13{

	using coord=pair<unsigned,unsigned>;
	using fold=pair<char,unsigned>;

	day13(const std::string& st="input/input13"){
		for(auto line:fiterator(st,'\n'))
		{
			if(line.empty())
				continue;

			auto t=tokenize(line,{','});
			if(t.size()>1)
				data.emplace(stol(t[0]),stol(t.back()));
			else
			{
				t=tokenize(line,{'='});
				folds.emplace_back(t[0].back(), stol(t.back()));
			}
		}
	}

	void foldX(set<coord>& d, uint32_t x){
		set<coord> res;
		for(auto& v:d){
			if(v.first<x)
				res.insert(v);
			else
				res.emplace(x+x-v.first,v.second);
		}
		d=res;
	}

	void foldY(set<coord>& d, uint32_t y){
		set<coord> res;
		for(auto& v:d){
			if(v.second<y)
				res.insert(v);
			else
				res.emplace(v.first,y+y-v.second);
		}
		d=res;
	}

	void firstStar(){
		set<coord> cpy=data;
		foldX(cpy,folds[0].second);
		cout<<"day 13, star1 visible dots:"<<cpy.size()<<endl;
	}


	void secondStar(){
		set<coord> cpy=data;
		for(auto f:folds)
		{
			if(f.first=='x')
				foldX(cpy, f.second);
			else
				foldY(cpy, f.second);
		}

		uint32_t mx=0,my=0;
		for(auto&v:cpy)
		{
			if(v.first>mx)
				mx=v.first;
			if(v.second>my)
				my=v.second;
		}
		cout<<"day 13, star2 msg:" <<endl;
		for(unsigned y=0;y<=my;y++)
		{
			for(unsigned x=0;x<=mx;x++)
			{
				if(cpy.count(coord(x,y)))
					cout<<"O";
				else
					cout<<" ";
			}
			cout<<endl;
		}
	}

	set<coord> data;
	vector<fold> folds;
};



#endif
