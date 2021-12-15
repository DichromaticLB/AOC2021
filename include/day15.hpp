#ifndef DBMW_INCLUDE_DAY15_HPP_
#define DBMW_INCLUDE_DAY15_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day15{


	day15(const std::string& st="input/input15"){
		for(auto line:fiterator(st,'\n'))
		{
			vector<unsigned> row;
			for(auto&c:line)
				row.push_back(c-'0');
			cave.addRow(row);
		}

	}


	void firstStar(){
		using it=board<unsigned>::iter;
		auto cost=cave.path(0, 0,cave.height()-1, cave.width()-1,
				[](const it& f,const it& t){return **t;},
				0, false);

		cout<<"day 15, star 1 smallest risk: "<<cost<<endl;
	}

	unsigned adjust(unsigned e,unsigned k){
		if(e+k>9)
			return (e+k+1)%10;
		return e+k;
	}

	void secondStar(){

		board<unsigned> supercave;
		vector<vector<unsigned>> superrow;
		for(auto& row:cave.bd)
		{
			vector<unsigned> r;
			for(unsigned i=0;i<5;i++)
				for(auto& v:row)
					r.push_back(adjust(v,i));
			superrow.push_back(r);
		}

		for(unsigned i=0;i<5;i++)
		{
			for(auto &r:superrow)
			{
				supercave.addRow(r);
				for(auto& i:r)
					i=adjust(i,1);
			}
		}
		using it=board<unsigned>::iter;
		auto cost=supercave.path(0, 0,
				supercave.width()-1, supercave.height()-1,
				[](const it& f,const it& t){return **t;},
				0, false);

		cout<<"day 15, star 2 smallest risk: "<<cost<<endl;

	}

	board<unsigned> cave;

};



#endif
