#ifndef DBMW_INCLUDE_DAY11_HPP_
#define DBMW_INCLUDE_DAY11_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day11{


	struct octopus{

		octopus(unsigned initialEnergy)
		{
			energy=initialEnergy;
			timesFlashed=0;
			flashed=false;
		}



		bool readyToFlash() const{
			return !flashed&&energy>9;
		}

		void flash(){
			timesFlashed++;
			energy=0;
			flashed=true;
		}

		void finish(){
			if(flashed)
			{
				energy=0;
				flashed=false;
			}
		}

		unsigned energy;
		unsigned timesFlashed;
		bool flashed;

	};
	using oboard=board<octopus>;
	day11(const std::string& st="input/input11"){
		for(auto line:fiterator(st,'\n'))
		{
			std::vector<octopus> row;
			for(auto c:line)
				row.emplace_back(c-'0');
			b.addRow(row);
		}
	}

	void iterate(){
		for(auto oc:b)
			oc->energy++;

		bool keepGoing=true;

		while(keepGoing)
		{
			keepGoing=false;
			for(auto it=b.begin();it!=b.end();++it)
				if((*it)->readyToFlash())
				{
					keepGoing=true;;
					(*it)->flash();
					for(auto e:it.around8())
						if(e.inBounds())
							(*e)->energy++;
				}
		}

		for(auto oc:b)
			oc->finish();

	}

	void firstStar(bool print=true){
		auto cb=b;

		for(unsigned e=0;e<100;e++)
			iterate();
		std::cout<<"day 11, star 1, times flashed: "<<std::accumulate(b.begin(),b.end(), 0l, [](const auto&a,const auto&b){
			return (*b).timesFlashed+a;
		})<<std::endl;

		b=cb;
	}


	void secondStar(){
		auto cb=b;
		unsigned step=0;
		bool br=true;;
		while(br)
		{
			br=false;
			step++;
			iterate();

			for(auto o:b)
				if(o->energy!=0)
				{
					br=true;
					break;
				}
		}
		b=cb;
		std::cout<<"Day 11, star2, all octopi flashed at step: "<<step<<std::endl;

	}

	board<octopus> b;

};



#endif
