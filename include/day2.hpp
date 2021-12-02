#ifndef DBMW_INCLUDE_DAY2_HPP_
#define DBMW_INCLUDE_DAY2_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>


struct day2{

	day2(const std::string& st="input/input2"){
		for(auto s:fiterator(st,'\n'))
			depths.emplace_back(s[0],s.back()-'0');
	}

	void firstStar(){
		int x=0,y=0;
		for(auto&v:depths){
			switch(v.first){
				case 'f':
					x+=v.second;
					break;
				case 'd':
					y+=v.second;
					break;
				case 'u':
					y-=v.second;
					break;
				default:
					throw std::runtime_error("Invalid op "+v.first);
			}
		}
		std::cout<<"day2 star1 res: "<<x*y<<std::endl;

	}



	void secondStar(){
		int x=0,y=0,aim=0;
		for(auto&v:depths){
			switch(v.first){
				case 'f':
					x+=v.second;
					y+=v.second*aim;
					break;
				case 'd':
					aim+=v.second;
					break;
				case 'u':
					aim-=v.second;
					break;
				default:
					throw std::runtime_error("Invalid op "+v.first);
			}
		}
		std::cout<<"day2 star2 res: "<<x*y<<std::endl;
	}

	std::vector<std::pair<char,unsigned>> depths;

};



#endif
