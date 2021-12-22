#ifndef DBMW_INCLUDE_DAY22_HPP_
#define DBMW_INCLUDE_DAY22_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day22{


	struct cube{
		int64_t x1,x2,y1,y2,z1,z2;

		static pair<int64_t,int64_t> intersect(int64_t p1l,int64_t p1r,int64_t p2l,int64_t p2r){
			pair<int64_t,int64_t> res{0,0};

			if(p1l>=p2l&&p1l<=p2r)
			{
				res.first=p1l;
				res.second=std::min(p1r,p2r)+1;
			}
			else if(p2l>=p1l&&p2l<=p1r)
			{
				res.first=p2l;
				res.second=std::min(p1r,p2r)+1;
			}

			return res;
		}

		bool operator<(const cube&o) const{

#define check(KEY) if(KEY!=o. KEY) \
	return KEY < o. KEY ;

			check(x1);
			check(x2);
			check(y1);
			check(y2);
			check(z1);

			return z2<o.z2;
		}

		bool operator!=(const cube&o) const{
#undef check
#define check(KEY) if(KEY!=o. KEY) \
	return true;
			check(x1);
			check(x2);
			check(y1);
			check(y2);
			check(z1);
			check(z2);

			return false;
		}

		bool bad()const{
			return x1==std::numeric_limits<int64_t>::max();
		}

		cube intersecction(const cube& other) const{
			cube res;
			res.x1=std::numeric_limits<int64_t>::max();

			auto p1=intersect(x1,x2,other.x1,other.x2);
			auto p2=intersect(y1,y2,other.y1,other.y2);
			auto p3=intersect(z1,z2,other.z1,other.z2);
			if(p1.first!=p1.second&&p2.first!=p2.second&&p3.first!=p3.second)
			{
				res.x1=p1.first;
				res.x2=p1.second-1;
				res.y1=p2.first;
				res.y2=p2.second-1;
				res.z1=p3.first;
				res.z2=p3.second-1;
			}
			return res;
		}

		int64_t area() const{
			return (1+x2-x1)*(1+y2-y1)*(1+z2-z1);
		}

		bool inBounds(){
			static const cube fifty{-50,50,-50,50,-50,50};
			auto intersect=intersecction(fifty);
			return !intersect.bad();
		}

		void clamp(){

			if(x1<-50)
				x1=-50;
			if(x2>50)
				x2=50;

			if(y1<-50)
				y1 = -50;
			if (y2 > 50)
				y2 = 50;

			if (z1 < -50)
				z1 = -50;
			if (z2 > 50)
				z2 = 50;
		}

		vector<cube> snap(const cube& sep)const{
			vector<cube> res;
			cube cp=*this;

			if(cp.y2>sep.y2)
			{
				cube top=cp;
				top.y1=sep.y2+1;
				cp.y2=sep.y2;
				res.push_back(top);
			}

			if(cp.y1<sep.y1)
			{
				cube bot=cp;
				bot.y2=sep.y1-1;
				cp.y1=sep.y1;
				res.push_back(bot);
			}

			if(cp.x2>sep.x2)
			{
				cube right=cp;
				right.x1=sep.x2+1;
				cp.x2=sep.x2;
				res.push_back(right);
			}

			if(cp.x1<sep.x1)
			{
				cube left=cp;
				left.x2=sep.x1-1;
				cp.x1=sep.x1;
				res.push_back(left);
			}

			if(cp.z2>sep.z2)
			{
				cube front=cp;
				front.z1=sep.z2+1;
				cp.z2=sep.z2;
				res.push_back(front);
			}

			if(cp.z1<sep.z1)
			{
				cube back=cp;
				back.z2=sep.z1-1;
				cp.z1=sep.z1;
				res.push_back(back);
			}

			return res;
		}

	};

	day22(const std::string& st="input/input22"){

		for(auto line:fiterator(st,'\n'))
		{
			switches.emplace_back();
			auto tokens=tokenize(line,{' '});
			switches.back().second=tokens[0]=="on";
			tokens=tokenize(tokens[1],{'.','=',','});
			switches.back().first.x1=stol(tokens[1]);
			switches.back().first.x2=stol(tokens[3]);
			switches.back().first.y1=stol(tokens[5]);
			switches.back().first.y2=stol(tokens[7]);
			switches.back().first.z1=stol(tokens[9]);
			switches.back().first.z2=stol(tokens[11]);

		}
	}



	void firstStar(){

		set<cube> on;

		for(auto v:switches)
		{
			if(v.first.inBounds())
			{
				cube cur=v.first;
				cur.clamp();
				set<cube> interOn;

				for(auto k:on){
					auto interc=k.intersecction(v.first);
					if(!interc.bad())
						interOn.insert(k);
				}

				for(auto& v:interOn)
				{
					auto it=v.intersecction(cur);
					auto snap=v.snap(it);
					on.erase(v);
					for(auto vv:snap)
						on.insert(vv);
				}

				if(v.second)
					on.insert(cur);
			}
		}

		cout<<"day 22, star1: "<<std::accumulate(on.begin(),on.end(),0l,[](unsigned long long e,const auto& c){
			return e+c.area();
		})<<endl;


	}


	void secondStar(){
		set<cube> on;

		for(auto v:switches)
		{
			cube cur=v.first;
			set<cube> interOn;
			for(auto k:on){
				auto interc=k.intersecction(v.first);
				if(!interc.bad())
					interOn.insert(k);
			}

			for(auto& v:interOn)
			{
				auto it=v.intersecction(cur);
				auto snap=v.snap(it);
				on.erase(v);
				for(auto vv:snap)
					on.insert(vv);
			}

			if(v.second)
				on.insert(cur);

		}

		cout<<"day 22, star2: "<<std::accumulate(on.begin(),on.end(),0l,[](unsigned long long e,const auto& c){
			return e+c.area();
		})<<endl;
	}


	vector<pair<cube,bool>> switches;

};



#endif
