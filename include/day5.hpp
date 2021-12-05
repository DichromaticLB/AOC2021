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
		std::vector<uint32_t> getOverlaps(bool ignoreDiagonals=true){

			std::vector<uint32_t> res;
			if(ignoreDiagonals&&x1!=x2&&y1!=y2)
				return res;

			uint16_t xit=x1,yit=y1;
			std::vector<uint16_t> xpoints,ypoints;

			while(xit!=x2){
				xpoints.push_back(xit);
				if(xit<x2)
					xit++;
				else
					xit--;
			}
			xpoints.push_back(xit);

			while(yit!=y2){
				ypoints.push_back(yit);
				if(yit<y2)
					yit++;
				else
					yit--;
			}
			ypoints.push_back(yit);

			while(xpoints.size()<ypoints.size())
				xpoints.push_back(xpoints.front());

			while(ypoints.size()<xpoints.size())
				ypoints.push_back(ypoints.front());


			for(unsigned i=0;i<xpoints.size();i++)
			{
				res.emplace_back();
				res.back()|=xpoints[i];
				res.back()<<=16;
				res.back()|=ypoints[i];
			}

			return res;
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
