#ifndef DBMW_INCLUDE_DAY6_HPP_
#define DBMW_INCLUDE_DAY6_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
struct day6{

	day6(const std::string& st="input/input6"){
		fish.resize(9);
		for(auto s:fiterator(st,','))
		{
			fish[std::stoul(s)]++;
		}
	}

	void firstStar(){
		auto copy=*this;

		for(int e=0;e!=80;e++)
			copy.iterate();

		std::cout<<"Day6 star1, total fish: "<<
				std::accumulate(copy.fish.begin(), copy.fish.end(), 0)<<std::endl;
	}


	void secondStar(){
		auto copy=*this;

		for(int e=0;e!=256;e++)
			copy.iterate();

		std::cout<<"Day6 star2, total fish: "<<
				std::accumulate(copy.fish.begin(), copy.fish.end(), 0l)<<std::endl;
	}

	void iterate(){
		std::vector<uint64_t> fish2(9,0);
		for(unsigned e=8;e;e--)
			fish2[e-1]=fish[e];
		fish2[6]+=fish[0];
		fish2[8]=fish[0];
		fish=fish2;
	}

	std::vector<uint64_t> fish;

};



#endif
