#ifndef DBMW_INCLUDE_DAY7_HPP_
#define DBMW_INCLUDE_DAY7_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
struct day7{

	day7(const std::string& st="input/input7"){
		for(auto v:fiterator(st,','))
			crabs[std::stoul(v)]++;

	}

	void firstStar(){
		std::vector<uint32_t> left(crabs.rbegin()->first+1);

		uint64_t tcrabs=0,cost=0;

		for(uint32_t i=0;i<left.size();i++){
			cost+=tcrabs;
			tcrabs+=crabs[i];
			left[i]=cost;
		}
		tcrabs=0,cost=0;
		for(uint32_t i=left.size();i!=0;){
			i--;
			cost+=tcrabs;
			tcrabs+=crabs[i];
			left[i]+=cost;
		}

		std::cout<<"day 7 star 1, minamial cost: "<<*std::min_element(left.begin(), left.end())<<std::endl;

	}


	void secondStar(){
		std::vector<uint32_t> left(crabs.rbegin()->first+1);

		uint64_t tcrabs=0,cost=0,bcrabs=0;

		for(uint32_t i=0;i<left.size();i++){
			cost+=tcrabs;
			bcrabs+=crabs[i];
			tcrabs+=bcrabs;
			left[i]=cost;
		}
		tcrabs=0,cost=0,bcrabs=0;
		for(uint32_t i=left.size();i!=0;){
			i--;
			cost+=tcrabs;
			bcrabs+=crabs[i];
			tcrabs+=bcrabs;
			left[i]+=cost;
		}

		std::cout<<"day 7 star 2, minamial cost: "<<*std::min_element(left.begin(), left.end())<<std::endl;
	}

	std::map<unsigned,unsigned> crabs;
};



#endif
