#ifndef DBMW_DAY1_HPP_
#define DBMW_DAY1_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>

struct day1{


	day1(const std::string& st="input/input1"){
		for(auto s:fiterator(st,'\n'))
			depths.push_back(std::stoul(s));
	}

	void firstStar(){
		unsigned ct=0;
		for(unsigned e=1;e<depths.size();e++)
			if(depths[e]>depths[e-1])
				ct++;
		std::cout<<"Increments day1: "<<ct<<std::endl;
	}

	unsigned sumAt(unsigned e){
		return depths[e]+depths[e-1]+depths[e-2];
	}

	void secondStar(){
		unsigned ct=0;
		for(unsigned e=3;e<depths.size();e++)
			if(sumAt(e)>sumAt(e-1))
				ct++;
		std::cout<<"Increments sum day1: "<<ct<<std::endl;
	}

	std::vector<unsigned> depths;

};



#endif
