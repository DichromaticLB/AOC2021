#ifndef DBMW_INCLUDE_DAY3_HPP_
#define DBMW_INCLUDE_DAY3_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>


struct day3{

	day3(const std::string& st="input/input3"){
		for(auto s:fiterator(st,'\n'))
		{
			bits_per_number=s.size();
			nums.emplace_back();
			for(auto& c:s){
				nums.back()*=2;
				if(c=='1')
					nums.back()++;
			}
		}
	}

	void firstStar(){
		uint64_t g=0,e=0;
		for(unsigned it=0;it<bits_per_number;it++)
		{
			unsigned onecount=0;
			for(auto&n:nums)
			{
				if(n&(1l<<it))
					onecount++;
			}

			if(onecount>nums.size()/2)
				g|=1l<<it;
			else
				e|=1l<<it;
		}

		std::cout<<"Day 3 power consumption "<<g*e<<std::endl;
	}

	uint64_t oxygen_co2(bool oxygen){
		auto nums=this->nums;

		for(unsigned it=bits_per_number;it!=0;)
		{
			it--;
			unsigned onecount=0,zerocount=0;
			for(auto&n:nums)
			{
				if(n&(1l<<it))
					onecount++;
			}

			std::vector<uint64_t> newit;
			zerocount=nums.size()-onecount;

			if((oxygen&&onecount>=zerocount)||((!oxygen)&&onecount<zerocount))
			{
				for(auto&n:nums)
					if(n&(1l<<it))
						newit.push_back(n);
			}
			else
				for(auto&n:nums)
					if(!(n&(1l<<it)))
						newit.push_back(n);

			if(newit.size()==1)
				return newit.back();

			nums=newit;
		}

		return nums.back();
	}




	void secondStar(){
		std::cout<<"Day 3 CO2 scrubbing rating: "<<oxygen_co2(true)*oxygen_co2(false)<<std::endl;
	}

	std::vector<uint64_t> nums;
	unsigned bits_per_number;
};



#endif
