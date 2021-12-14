#ifndef DBMW_INCLUDE_DAY14_HPP_
#define DBMW_INCLUDE_DAY14_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day14{


	day14(const std::string& st="input/input14"){
		for(auto line:fiterator(st,'\n'))
		{
			if(line.empty())
				continue;

			auto tokens=tokenize(line,{'>',' ','-'});
			if(tokens.size()>1)
				insertions[tokens[0]]=tokens.back();
			else
				polymer=line;

		}

	}

	string expandPolymer(const std::string &pol,unsigned iterations){
		string base=pol;
		for(unsigned e=0;e<iterations;e++)
		{
			string swap;
			for(unsigned i=0;i<base.size()-1;i++)
			{
				swap.push_back(base[i]);
				if(insertions.count(base.substr(i, 2)))
					swap.push_back(insertions[base.substr(i,2)][0]);
			}
			swap.push_back(base.back());
			base=swap;
		}
		return base;
	}



	void firstStar(bool print=true){
		string base=expandPolymer(polymer,10);

		vector<unsigned> ct(26,0);

		for(auto c:base)
			ct[c-'A']++;

		sort(ct.begin(),ct.end());

		for(auto& v:ct)
			if(v!=0)
			{
				cout<<"day 14 star 1: "<<ct[25]-v<<endl;
				break;
			}
	}

	using products=map<string,uint64_t>;

	void updateBuffer(map<string,products>&buffer,const std::string&key,const std::string&st){

		for(unsigned e=0;e<st.size()-1;e++)
			buffer[key][st.substr(e,2)]++;

	}

	void secondStar(){

		map<string,products> pr10buffer;
		products current;

		for(unsigned e=0;e<polymer.size()-1;e++)
			current[polymer.substr(e,2)]++;

		for(unsigned i=0;i<4;i++)
		{
			products swap;
			for(auto& v:current)
			{
				if(!pr10buffer.count(v.first))
					updateBuffer(pr10buffer, v.first,expandPolymer(v.first,10));

				for(auto& vv:pr10buffer[v.first])
				{
					swap[vv.first]+=vv.second*v.second;
				}
			}
			current=swap;
		}

		vector<uint64_t> ct(26,0);
		for(auto&v:current)
			for(auto c:v.first)
			{
				ct[c-'A']+=v.second;
			}

		sort(ct.begin(),ct.end());

		for(auto& v:ct)
			if(v!=0)
			{
				cout<<"day 14 star 2: "<<(ct[25]-v)/2<<endl;
				break;
			}

	}

	string polymer;
	map<string,string> insertions;


};



#endif
