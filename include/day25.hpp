#ifndef DBMW_INCLUDE_DAY25_HPP_
#define DBMW_INCLUDE_DAY25_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>
#include<cmath>

struct day25{


	day25(const std::string& st="input/input25"){
		for(auto v:fiterator(st,'\n'))
		{
			vector<char> line(v.begin(),v.end());
			cucumbers.addRow(line);
		}
	}


	void firstStar(){
		auto cucumbers=this->cucumbers;

		unsigned steps=0;
		uint32_t count=0;
		do{
			count=0;
			cucumbers.prepareBuffer();
			for(auto e=cucumbers.begin();e!=cucumbers.end();++e)
			{

				if((**e)=='>'&&**(e.right())=='.')
				{
					count++;
					*e.right().bufferAccess()='>';
					*e.bufferAccess()='.';
				}
			}
			cucumbers.swapBuffer();
			cucumbers.prepareBuffer();
			for(auto e=cucumbers.begin();e!=cucumbers.end();++e)
			{
				if((**e)=='v'&&**(e.bot())=='.')
				{
					count++;
					*e.bot().bufferAccess()='v';
					*e.bufferAccess()='.';
				}
			}
			cucumbers.swapBuffer();
			steps++;
		}while(count!=0);

		cout<<"day 25, star1, first step no movement: "<<steps<<endl;

	}


	void secondStar(){


	}

	board<char,true> cucumbers;

};



#endif
