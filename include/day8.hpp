#ifndef DBMW_INCLUDE_DAY7_HPP_
#define DBMW_INCLUDE_DAY7_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>
struct day8{

	struct message{
		void normalize(){
			using namespace std;
			mappings=vector<string>(7,"abcdefg");
			string one,seven,four;

			for(auto&v:patterns)
				if(v.size()==2)
					one=v;
				else if(v.size()==3)
					seven=v;
				else if(v.size()==4)
					four=v;

			mappings[0].clear();

			std::set_difference(
							seven.begin(),seven.end(),
							one.begin(),one.end(),
							std::inserter(mappings[0], mappings[0].begin()));

			auto ct=ccount();
			for(auto& kv:ct)
			{

				if(kv.second==8&&kv.first!=mappings[0][0])
					mappings[2]=kv.first;
				if(kv.second==6)
					mappings[1]=kv.first;
				if(kv.second==4)
					mappings[4]=kv.first;
				if(kv.second==9)
					mappings[5]=kv.first;
			}

			std::set<char> good;
			for(auto& v:mappings)
				if(v.size()==1)
					good.insert(v[0]);

			for(auto& c:four)
				if(!good.count(c))
				{
					mappings[3]=c;
					good.insert(c);
					break;
				}

			for(char c='a';c<='g';c++)
				if(!good.count(c))
				{
					mappings[6]=c;
					break;
				}

			remap();

		}

		void remap(){
			std::map<char,char> lt;
			char g='a';
			for(auto&v:mappings)
				lt[v[0]]=g++;

			for(auto& st:patterns)
			{
				for(auto& c:st)
				{
					c=lt[c];
				}
				std::sort(st.begin(),st.end());
			}
			for(auto& st:value)
			{
				for(auto& c:st)
				{
					c=lt[c];
				}
				std::sort(st.begin(),st.end());
			}
		}

		std::map<char,unsigned> ccount(){
			std::map<char,unsigned> res;
			for(auto&v:patterns)
				for(auto c:v)
					res[c]++;
			return res;
		}



		std::vector<std::string> patterns;
		std::vector<std::string> value;
		std::vector<std::string> mappings;
	};

	day8(const std::string& st="input/input8"){
		for(auto line:fiterator(st,'\n'))
		{
			messages.emplace_back();

			auto v=tokenize(line, {'|'});

			for(auto pattern : tokenize(v[0]))
				if(pattern.length()){
					std::sort(pattern.begin(),pattern.end());
					messages.back().patterns.push_back(pattern);
				}


			for(auto pattern : tokenize(v[1]))
				if(pattern.length()){
					std::sort(pattern.begin(),pattern.end());
					messages.back().value.push_back(pattern);
				}
			messages.back().normalize();
		}
	}



	void firstStar(){
		unsigned ct=0;
		for(auto& m:messages)
			for(auto& o:m.value)
			{
				if(o.length()==2||o.length()==3||o.length()==4||o.length()==7)
					ct++;
			}
		std::cout<<"day 8, star 1 number of 1,4,7,8: "<<ct<<std::endl;

	}


	void secondStar(){
		const std::map<std::string,unsigned> s2i={
				{"abcefg",0},
				{"cf",1},
				{"acdeg",2},
				{"acdfg",3},
				{"bcdf",4},
				{"abdfg",5},
				{"abdefg",6},
				{"acf",7},
				{"abcdefg",8},
				{"abcdfg",9}
		};
		uint64_t total=0;
		for(auto& m:messages)
		{
			uint64_t ct=0;
			for(auto i:m.value)
			{
				ct*=10;
				ct+=s2i.at(i);
			}
			total+=ct;
		}

		std::cout<<"day 8, star 2, sum: "<<total<<std::endl;
	}


	std::vector<message> messages;
};



#endif
