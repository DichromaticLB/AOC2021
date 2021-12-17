#ifndef DBMW_INCLUDE_DAY17_HPP_
#define DBMW_INCLUDE_DAY17_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day17{

	struct targetArea{
			int x1,x2,y1,y2;
			bool intersections(int x,int y){
				int cx=0,cy=0;

				while((cx<=x2&&cy>=y2))
				{
					if(cx>=x1&&cy<=y1)
						return true;
					cx+=x;
					cy+=y;

					if(x>0)
						x--;
					else if(x<0)
						x++;
					y--;

					if(x==0&&cx<x1)
						break;
				}
				return false;
			}

			bool inXrange(int x){
				return x>=x1&&x<=x2;
			}

			bool inYrange(int y){
				return y<=y1&&y>=y2;
			}

	};

	day17(const std::string& st="input/input17"){
		for(auto line:fiterator(st,'\n'))
		{
			auto tokens=tokenize(line,{'=','.',','});
			area.x1=stol(tokens[1]);
			area.x2=stol(tokens[3]);
			area.y2=stol(tokens[5]);
			area.y1=stol(tokens[7]);
		}


	}


	void firstStar(){
		int highest=0;
		for(int i=1;i<0xff;i++)
		{
			int e=i;
			int distance=0;
			while(distance>=area.y2)
			{
				distance+=e;
				e--;
				if(area.inYrange(distance)&&i>highest)
					highest=i;
			}
		}

		int res=0;
		while(highest!=0)
		{
			res+=highest;
			highest--;
		}

		cout<<res<<endl;

	}

	void secondStar(){
		map<unsigned,set<int>> xintersect;
		map<unsigned,set<int>> xperpetual;
		map<unsigned,set<int>> yintersect;

		for(int i=1;i<=area.x2;i++)
		{
			int e=i;
			int distance=0;
			unsigned step=1;
			while(e&&distance<area.x2)
			{
				distance+=e;
				e--;
				if(area.inXrange(distance))
					xintersect[step].insert(i);
				step++;
			}

			if(e==0&&area.inXrange(distance))
				xperpetual[step].insert(i);
		}

		for(int i=area.y2;i<=0xff;i++)
		{
			int e=i;
			int distance=0;
			unsigned step=1;
			while(distance>=area.y2)
			{
				distance+=e;
				e--;
				if(area.inYrange(distance))
					yintersect[step].insert(i);
				step++;
			}
		}

		set<pair<int,int>> valids;

		for(auto& v:yintersect)
		{
			for(auto& yvel:v.second)
			{
				for(auto& xvel:xintersect[v.first])
				{
					valids.emplace(xvel,yvel);
				}

				for(auto& xperp:xperpetual)
					if(xperp.first<=v.first)
						for(auto& xvel:xperp.second)
						{
							valids.emplace(xvel,yvel);
						}
			}
		}

		cout<<valids.size()<<endl;
	}


	targetArea area;
};



#endif
