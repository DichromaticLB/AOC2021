#ifndef DBMW_INCLUDE_DAY5_HPP_
#define DBMW_INCLUDE_DAY5_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>

struct day5{



	struct path{
		std::vector<uint32_t> getOverlaps(bool ignoreDiagonals=true) const{

			std::vector<uint32_t> res;
			if(ignoreDiagonals&&x1!=x2&&y1!=y2)
				return res;

			path me=*this;
			bool first=true;
			while(!me)
			{
				if(first)
					first=false;
				else
					me.converge();
				res.emplace_back();
				res.back()|=me.x1;
				res.back()<<=16;
				res.back()|=me.y1;
			};

			return res;
		}

		void converge(){
			if(x1<x2)
				x1++;
			else if(x1>x2)
				x1--;

			if(y1<y2)
				y1++;
			else if(y1>y2)
				y1--;
		}

		operator bool() const{
			return x1==x2&&y1==y2;
		}

		uint16_t x1,y1;
		uint16_t x2,y2;
	};


	day5(const std::string& st="input/input5"){
		for(auto s:fiterator(st,'\n'))
		{
			auto p=tokenize(s,{'-','>',' ',','});
			paths.emplace_back();
			paths.back().x1=std::stoul(p[0]);
			paths.back().y1=std::stoul(p[1]);
			paths.back().x2=std::stoul(p[p.size()-2]);
			paths.back().y2=std::stoul(p.back());
		}
	}

	void firstStar(){
		std::map<uint32_t,uint32_t> count;
		for(auto& path:paths)
			for(auto& p:path.getOverlaps())
				count[p]++;
		unsigned ct=0;
		for(auto& v:count)
			if(v.second>1)
				ct++;

		std::cout<<"day5 overlapping points star1: "<<ct<<std::endl;
	}




	void secondStar(){
		std::map<uint32_t,uint32_t> count;
		for(auto& path:paths)
			for(auto& p:path.getOverlaps(false))
				count[p]++;
		unsigned ct=0;
		for(auto& v:count)
			if(v.second>1)
				ct++;

		std::cout<<"day5 overlapping points star2: "<<ct<<std::endl;
	}

	std::vector<path> paths;

};



#endif
