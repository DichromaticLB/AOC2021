#ifndef DBMW_INCLUDE_DAY19_HPP_
#define DBMW_INCLUDE_DAY19_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day19{

	struct point{
		point(int64_t x,int64_t y,int64_t z){
			this->x=x;
			this->y=y;
			this->z=z;

		}
		int64_t x,y,z;

		uint64_t manhattan(const point other)const{
			return abs(x-other.x)+abs(y-other.y)+abs(z-other.z);
		}

		void shift(int shift=1){

			switch(shift){
				case 0:
					*this= point(x,y,z);
					break;
				case 1:
					*this= point(x,z,y);
					break;
				case 2:
					*this= point(y,x,z);
					break;
				case 3:
					*this= point(y,z,x);
					break;
				case 4:
					*this= point(z,x,y);
					break;
				case 5:
					*this=point(z,y,x);
					break;
				default:
					throw runtime_error("Invalid shift");
			}
		}

		friend ostream& operator<<(ostream& o, const point&p ){
			o<<p.x<<","<<p.y<<","<<p.z;
			return o;
		}

		bool operator<(const point& o) const{
			if(x!=o.x)
				return x<o.x;
			if(y!=o.y)
				return y<o.y;
			return z<o.z;
		}

		static point null(){
			return point {0xdeadbeef,0xdeadbeef,0xdeadbeef};
		}

		bool isNull(){
			return x==0xdeadbeef&&y==0xdeadbeef&&z==0xdeadbeef;
		}

		point operator+(const point& o) const{
			return point(x+o.x,y+o.y,z+o.z);
		}

	};

	struct scanner{

		struct orientation{
			int shifts;
			int x,y,z;
		};

		struct mapping{
			scanner *e;
			mapping* ref;
			orientation o;
			int64_t shiftx,shifty,shiftz;
		};

		friend ostream& operator<<(ostream& o,const scanner& s){
			for(auto p:s.pt)
				o<<p<<endl;
			return o;
		}



		static std::vector<orientation> _buildShifts(){
			std::vector<orientation> res;
			vector<point> directions={
					{1,1,1},{1,1,-1},{1,-1,1},{1,-1,-1},
					{-1,1,1},{-1,1,-1},{-1,-1,1},{-1,-1,-1}
			};

			for(int shifts=0;shifts<6;shifts++){
				for(auto p:directions)
				{
					res.emplace_back();
					res.back().shifts=shifts;
					res.back().x=p.x;
					res.back().y=p.y;
					res.back().z=p.z;
				}
			}
			return res;
		}

		static const std::vector<orientation>& getShifts(){
			static const std::vector<orientation> shifts=_buildShifts();

			return shifts;
		}

		scanner getSwitch(orientation o){
			scanner res=*this;
			for(auto& p:res.pt)
			{
				p.x*=o.x;
				p.y*=o.y;
				p.z*=o.z;
				p.shift(o.shifts);
			}

			return res;
		}


		point tryIntersect(const scanner& o,unsigned minIntersections=12){
			set<point> reference;
			for(auto p:pt)
				reference.insert(p);

			for(auto p:o.pt)
				for(auto p2:reference)
				{
					int sx=p2.x-p.x;
					int sy=p2.y-p.y;
					int sz=p2.z-p.z;

					unsigned count=0;

					for(auto &p3:o.pt){
						if(reference.count(point(p3.x+sx,p3.y+sy,p3.z+sz)))
						{
							count++;

						}
						if(count==minIntersections)
						{
							return point(sx,sy,sz);
						}
					}

				}
			return point::null();
		}

		void offset(point &np)
		{
			for(auto& p:pt)
				p=p+np;

		}

		std::vector<point> pt;
	};



	day19(const std::string& st="input/input19"){
		for(auto line:fiterator(st,'\n'))
		{
			if(line.empty())
				continue;
			auto tk=tokenize(line,{','});

			if(tk.size()!=3)
			{
				scanners.emplace_back();
			}
			else
				scanners.back().pt.emplace_back(stoll(tk[0]),stoll(tk[1]),stoll(tk[2]));

		}
	}

	void firstStar(){
		set<scanner*> used;
		std::vector<scanner::mapping> configurations,buffer;
		configurations.reserve(128);
		buffer.reserve(128);

		used.insert(&scanners[0]);
		configurations.push_back(scanner::mapping{
			.e=&scanners[0],
			.ref=nullptr,
			.o=scanner::getShifts()[0],
			.shiftx=0,
			.shifty=0,
			.shiftz=0
		});

		while(used.size()!=scanners.size()){
			if(buffer.size())
			{
				configurations.push_back(buffer.back());
				buffer.pop_back();
			}

			scanner e=configurations.back().e->getSwitch(configurations.back().o);

			for(auto& sc:scanners){

				if(used.count(&sc))
					continue;

				for(auto &orient:e.getShifts())
				{
					auto twist=sc.getSwitch(orient);
					auto p=e.tryIntersect(twist, 12);
					if(!p.isNull())
					{
						used.insert(&sc);
						buffer.push_back(scanner::mapping{
							.e=&sc,
							.ref=&configurations.back(),
							.o=orient,
							.shiftx=p.x,
							.shifty=p.y,
							.shiftz=p.z
						});
						break;
					}

				}
			}
		}
		for(auto &c:buffer)
			configurations.push_back(c);


		set<point> world;
		map<scanner*,point> distances{{&scanners[0],point(0,0,0)}};

		while(distances.size()!=configurations.size())
			for(auto conf:configurations){
				if(!distances.count(conf.e)&&distances.count(conf.ref->e))
				{
					point pd=distances.at(conf.ref->e);
					pd=pd+point(conf.shiftx,conf.shifty,conf.shiftz);
					distances.emplace(conf.e,pd);
				}
			}

		for(auto conf:configurations)
		{
			auto  l=conf.e->getSwitch(conf.o);
			for(auto p:l.pt)
				world.insert(p+distances.at(conf.e));
		}
		cout<<"day 19, star 1, total beacons:"<<world.size()<<endl;;
	}



	void secondStar(){
		set<scanner*> used;
		std::vector<scanner::mapping> configurations,buffer;
		configurations.reserve(128);
		buffer.reserve(128);

		used.insert(&scanners[0]);
		configurations.push_back(scanner::mapping{
			.e=&scanners[0],
			.ref=nullptr,
			.o=scanner::getShifts()[0],
			.shiftx=0,
			.shifty=0,
			.shiftz=0
		});

		while(used.size()!=scanners.size()){
			if(buffer.size())
			{
				configurations.push_back(buffer.back());
				buffer.pop_back();
			}

			scanner e=configurations.back().e->getSwitch(configurations.back().o);

			for(auto& sc:scanners){

				if(used.count(&sc))
					continue;

				for(auto &orient:e.getShifts())
				{
					auto twist=sc.getSwitch(orient);
					auto p=e.tryIntersect(twist, 12);
					if(!p.isNull())
					{
						used.insert(&sc);
						buffer.push_back(scanner::mapping{
							.e=&sc,
							.ref=&configurations.back(),
							.o=orient,
							.shiftx=p.x,
							.shifty=p.y,
							.shiftz=p.z
						});
						break;
					}

				}
			}
		}
		for(auto &c:buffer)
			configurations.push_back(c);


		set<point> world;
		map<scanner*,point> distances{{&scanners[0],point(0,0,0)}};

		while(distances.size()!=configurations.size())
			for(auto conf:configurations){
				if(!distances.count(conf.e)&&distances.count(conf.ref->e))
				{
					point pd=distances.at(conf.ref->e);
					pd=pd+point(conf.shiftx,conf.shifty,conf.shiftz);
					distances.emplace(conf.e,pd);
				}
			}

		uint64_t max=0;
		for(auto &v:distances)
			for(auto &vv:distances)
				if(v.second.manhattan(vv.second)>max)
					max=v.second.manhattan(vv.second);

		cout<<"day 19, star 2, max manhattan distance: "<<max<<endl;
	}

	std::vector<scanner> scanners;

};



#endif
