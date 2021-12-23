#ifndef DBMW_INCLUDE_DAY23_HPP_
#define DBMW_INCLUDE_DAY23_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>
#include<cmath>

struct day23{

#define val(c) pow(10,c-'A')

	struct room{
		char pos1=0;
		char pos2=0;

		char homeOf;

		bool full(char c) const{
			return (pos1&&pos2)||c!=homeOf||(pos2&&pos2!=c);
		}

		bool empty()const{
			return (pos1==0&&pos2==0)||(pos1==homeOf&&pos2==homeOf);
		}

		char& toLeave(){
			if(full1())
				return pos1;
			return pos2;
		}

		bool full1()const{
			return pos1;
		}

		bool empty2()const{
			return !pos2;
		}

		char& getEmpty(){
			if(!pos2)
				return pos2;
			return pos1;
		}

		bool operator<(const room& o)const{
			if(pos1!=o.pos1)
				return pos1<o.pos1;
			return pos2<o.pos2;
		}
		bool operator!=(const room& o)const{
			return pos1!=o.pos1||pos2!=o.pos2;
		}

		bool done()const{
			return pos1==homeOf&&pos2==homeOf;
		}
	};

	struct hall{
		hall(){
			h.resize(7,0);
			rooms.resize(4);
			cost=0;

			for(int i=0;i<4;i++)
				rooms[i].homeOf='A'+i;

		}

		vector<char> h;
		vector<room> rooms;
		int64_t cost;

		bool operator<(const hall& o) const{
			for(unsigned i=0;i<h.size();i++)
				if(h[i]!=o.h[i])
					return h[i]<o.h[i];
			for(unsigned i=0;i<rooms.size();i++)
				if(rooms[i]!=o.rooms[i])
					return rooms[i]<o.rooms[i];


			return rooms.back()<o.rooms.back();
		}

		bool done()const{
			for(auto r:rooms)
				if(!r.done())
					return false;
			return true;
		}

		void bad(){
			cost=numeric_limits<int64_t>::max();
		}

		bool isBad() const{
			return cost==numeric_limits<int64_t>::max();
		}

		pair<int,int> rlr(int ri) const{
			switch(ri)
			{
			case 0:
				return pair<int,int>(1,2);
			case 1:
				return pair<int,int>(2,3);
			case 2:
				return pair<int,int>(3,4);
			default:
				return pair<int,int>(4,5);
			}

		}

		int charcost(char c) const{
			return pow(10,c-'A');
		}


		static unsigned hcost(
				unsigned from,unsigned to){
			map<pair<unsigned,unsigned>,unsigned> _hcosts{
				{{0,1},1},
				{{1,2},2},
				{{2,3},2},
				{{3,4},2},
				{{4,5},2},
				{{5,6},1}

			};

			if(from>to)
				std::swap(from,to);

			unsigned res=0;

			while(from!=to)
			{
				res+=_hcosts.at({from,from+1});
				from++;
			}

			return res;
		}

		int pathClearh2r(int hi,int ri) const{
			auto rl=rlr(ri);

			if(hi<=rl.first)
			{
				for(int i=hi+1;i<=rl.first;i++)
				{
					if(h[i])
						return -1;

				}
				return 2+(rooms[ri].empty2()?1:0)+hcost(hi,rl.first);
			}
			else
			{
				for(int i=hi-1;i>=rl.second;i--)
				{
					if(h[i])
						return -1;

				}
				return 2+(rooms[ri].empty2()?1:0)+hcost(rl.second, hi);
			}
		}

		int pathClearr2h(int ri,int hi) const{
			auto rl=rlr(ri);

			if(hi<=rl.first)
			{
				for(int i=rl.first;i>=hi;i--)
					if(h[i])
						return -1;

				return 2+(rooms[ri].full1()?0:1)+hcost(rl.first, hi);
			}
			else
			{
				for(int i=rl.second;i<=hi;i++)
				{
					if(h[i])
						return -1;

				}
				return 2+(rooms[ri].full1()?0:1)+hcost(rl.second, hi);
			}
		}


		hall moveh2r(unsigned hallIndex,unsigned roomIndex) const{
			hall res=*this;

			if(!h[hallIndex]||rooms[roomIndex].full(h[hallIndex]))
			{
				res.bad();
				return res;
			}

			int cost=pathClearh2r(hallIndex,roomIndex);

			if(cost==-1)
			{
				res.bad();
				return res;
			}

			res.cost=charcost(h[hallIndex])*cost;
			res.rooms[roomIndex].getEmpty()=h[hallIndex];
			res.h[hallIndex]=0;

			return res;
		}

		hall mover2h(unsigned roomIndex,unsigned hallIndex) const{
			hall res=*this;

			if(h[hallIndex]||rooms[roomIndex].empty())
			{
				res.bad();
				return res;
			}

			int cost=pathClearr2h(roomIndex, hallIndex);

			if(cost==-1)
			{
				res.bad();
				return res;
			}

			char& pt=res.rooms[roomIndex].toLeave();

			res.cost=charcost(pt)*cost;
			res.h[hallIndex]=pt;
			pt=0;

			return res;
		}

		vector<hall> states() const{
			vector<hall> res;
			for(unsigned i=0;i<h.size();i++)
				for(unsigned j=0;j<rooms.size();j++)
				{
					auto p1=moveh2r(i, j);
					auto p2=mover2h(j, i);

					if(!p1.isBad())
					{
						res.push_back(p1);
					}
					if(!p2.isBad())
					{
						res.push_back(p2);
					}
				}

			return res;
		}
	};


#define val(c) pow(10,c-'A')

	struct bigroom{
		char pos1=0;
		char pos2=0;
		char pos3=0;
		char pos4=0;

		char homeOf;

		bool full(char c) const{
			return (pos1&&pos2&&pos3&&pos4)||c!=homeOf||(pos2&&pos2!=c)||(pos3&&pos3!=c)||(pos4&&pos4!=c);
		}

		bool empty()const{
			return (pos1==0&&pos2==0&&pos3==0&&pos4==0)||(pos1==homeOf&&pos2==homeOf&&pos3==homeOf&&pos4==homeOf);
		}

		char& toLeave(){
			if(full1())
				return pos1;
			if(full2())
				return pos2;
			if(full3())
				return pos3;
			return pos4;
		}

		bool full1()const{
			return pos1;
		}
		bool full2()const{
			return pos2;
		}
		bool full3()const{
			return pos3;
		}

		bool empty2()const{
			return !pos2;
		}
		bool empty3()const{
			return !pos3;
		}
		bool empty4()const{
			return !pos4;
		}

		unsigned costToBottom()const{
			if(empty4())
				return 3;
			else if(empty3())
				return 2;
			else if(empty2())
				return 1;
			return 0;
		}

		unsigned costToTop()const{
			if(full1())
				return 0;
			if(full2())
				return 1;
			if(full3())
				return 2;
			return 3;
		}

		char& getEmpty(){
			if(!pos4)
				return pos4;
			if(!pos3)
				return pos3;
			if(!pos2)
				return pos2;
			return pos1;
		}

		bool operator<(const bigroom& o)const{
			if(pos1!=o.pos1)
				return pos1<o.pos1;
			if(pos2!=o.pos2)
				return pos2<o.pos2;
			if(pos3!=o.pos3)
				return pos3<o.pos3;
			return pos4<o.pos4;
		}

		bool operator!=(const bigroom& o)const{
			return pos1!=o.pos1||pos2!=o.pos2||pos3!=o.pos3||pos4!=o.pos4;
		}

		bool done()const{
			return pos1==homeOf&&pos2==homeOf&&pos3==homeOf&&pos4==homeOf;
		}


	};

	struct bighall{
		bighall(){
			h.resize(7,0);
			rooms.resize(4);
			cost=0;

			for(int i=0;i<4;i++)
				rooms[i].homeOf='A'+i;

		}

		vector<char> h;
		vector<bigroom> rooms;
		int64_t cost;

		bool operator<(const bighall& o) const{
			for(unsigned i=0;i<h.size();i++)
				if(h[i]!=o.h[i])
					return h[i]<o.h[i];
			for(unsigned i=0;i<rooms.size();i++)
				if(rooms[i]!=o.rooms[i])
					return rooms[i]<o.rooms[i];


			return rooms.back()<o.rooms.back();
		}

		bool done()const{
			for(auto r:rooms)
				if(!r.done())
					return false;
			return true;
		}

		void bad(){
			cost=numeric_limits<int64_t>::max();
		}

		bool isBad() const{
			return cost==numeric_limits<int64_t>::max();
		}

		pair<int,int> rlr(int ri) const{
			switch(ri)
			{
			case 0:
				return pair<int,int>(1,2);
			case 1:
				return pair<int,int>(2,3);
			case 2:
				return pair<int,int>(3,4);
			default:
				return pair<int,int>(4,5);
			}

		}

		int charcost(char c) const{
			return pow(10,c-'A');
		}


		static unsigned hcost(
				unsigned from,unsigned to){
			map<pair<unsigned,unsigned>,unsigned> _hcosts{
				{{0,1},1},
				{{1,2},2},
				{{2,3},2},
				{{3,4},2},
				{{4,5},2},
				{{5,6},1}

			};

			if(from>to)
				std::swap(from,to);

			unsigned res=0;

			while(from!=to)
			{
				res+=_hcosts.at({from,from+1});
				from++;
			}

			return res;
		}

		int pathClearh2r(int hi,int ri) const{
			auto rl=rlr(ri);

			if(hi<=rl.first)
			{
				for(int i=hi+1;i<=rl.first;i++)
				{
					if(h[i])
						return -1;

				}
				return 2+rooms[ri].costToBottom()+hcost(hi,rl.first);
			}
			else
			{
				for(int i=hi-1;i>=rl.second;i--)
				{
					if(h[i])
						return -1;

				}
				return 2+rooms[ri].costToBottom()+hcost(rl.second, hi);
			}
		}

		int pathClearr2h(int ri,int hi) const{
			auto rl=rlr(ri);

			if(hi<=rl.first)
			{
				for(int i=rl.first;i>=hi;i--)
					if(h[i])
						return -1;

				return 2+rooms[ri].costToTop()+hcost(rl.first, hi);
			}
			else
			{
				for(int i=rl.second;i<=hi;i++)
				{
					if(h[i])
						return -1;

				}
				return 2+rooms[ri].costToTop()+hcost(rl.second, hi);
			}
		}


		bighall moveh2r(unsigned hallIndex,unsigned roomIndex) const{
			bighall  res=*this;

			if(!h[hallIndex]||rooms[roomIndex].full(h[hallIndex]))
			{
				res.bad();
				return res;
			}

			int cost=pathClearh2r(hallIndex,roomIndex);

			if(cost==-1)
			{
				res.bad();
				return res;
			}

			res.cost=charcost(h[hallIndex])*cost;
			res.rooms[roomIndex].getEmpty()=h[hallIndex];
			res.h[hallIndex]=0;

			return res;
		}

		bighall  mover2h(unsigned roomIndex,unsigned hallIndex) const{
			bighall  res=*this;

			if(h[hallIndex]||rooms[roomIndex].empty())
			{
				res.bad();
				return res;
			}

			int cost=pathClearr2h(roomIndex, hallIndex);

			if(cost==-1)
			{
				res.bad();
				return res;
			}

			char& pt=res.rooms[roomIndex].toLeave();

			res.cost=charcost(pt)*cost;
			res.h[hallIndex]=pt;
			pt=0;

			return res;
		}

		vector<bighall > states() const{
			vector<bighall > res;
			for(unsigned i=0;i<h.size();i++)
				for(unsigned j=0;j<rooms.size();j++)
				{
					auto p1=moveh2r(i, j);
					auto p2=mover2h(j, i);

					if(!p1.isBad())
					{
						res.push_back(p1);
					}
					if(!p2.isBad())
					{
						res.push_back(p2);
					}
				}

			return res;
		}

	};




	day23(const std::string& st="input/input23"){

		unsigned dex=0;
		for(auto line:fiterator(st,'\n'))
		{
			std::vector<room*> r={&h.rooms[3],&h.rooms[2],&h.rooms[1],&h.rooms[0]};
			if(dex==2)
			{
				auto t=tokenize(line,{'#'});
				for(auto c:t)
				{
					if(!c.empty()&&c[0]!=' ')
					{
						r.back()->pos1=c[0];
						r.pop_back();
					}
				}
			}
			if(dex==3)
			{
				auto t=tokenize(line,{'#'});
				for(auto c:t)
				{
					if(!c.empty()&&c[0]!=' ')
					{
						r.back()->pos2=c[0];
						r.pop_back();
					}
				}
			}
			dex++;

		}

	}


	void firstStar(){
		std::map<hall,unsigned> costs{{h,0}};
		deque<hall> toVisit{h};

		while(toVisit.size()){
			hall e=toVisit.front();
			toVisit.pop_front();
			for(auto&v:e.states())
			{
				if(!costs.count(v)||costs[v]>v.cost+costs[e])
				{
					costs[v]=v.cost+costs[e];
					if(!v.done())
						toVisit.push_back(v);
				}
			}
		}
		for(auto& h:costs)
		{
			if(h.first.done())
				cout<<"day 23, star1: "<<endl<<"cost "<<h.second<<endl;
		}

	}


	void secondStar(){
		bighall h;
		unsigned i=0;
		for(auto& v:this->h.rooms)
		{
			h.rooms[i].pos1=v.pos1;
			h.rooms[i].pos4=v.pos2;
//#D#C#B#A#
//#D#B#A#C#
			switch(i)
			{
				case 0:
					h.rooms[i].pos2='D';
					h.rooms[i].pos3='D';
					break;
				case 1:
					h.rooms[i].pos2='C';
					h.rooms[i].pos3='B';
					break;
				case 2:
					h.rooms[i].pos2='B';
					h.rooms[i].pos3='A';
					break;
				case 3:
					h.rooms[i].pos2='A';
					h.rooms[i].pos3='C';
					break;
			}

			i++;
		}


		std::map<bighall,unsigned> costs{{h,0}};
		deque<bighall> toVisit{h};

		while(toVisit.size()){
			bighall e=toVisit.front();
			toVisit.pop_front();
			for(auto&v:e.states())
			{
				if(!costs.count(v)||costs[v]>v.cost+costs[e])
				{
					costs[v]=v.cost+costs[e];
					if(!v.done())
						toVisit.push_back(v);
				}
			}
		}
		for(auto& h:costs)
		{
			if(h.first.done())
				cout<<"day 23, star 2: "<<endl<<"cost "<<h.second<<endl;
		}
	}

	hall h;

};



#endif
