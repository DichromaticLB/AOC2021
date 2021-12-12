#ifndef DBMW_INCLUDE_DAY12_HPP_
#define DBMW_INCLUDE_DAY12_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day12{
	using path=vector<string>;

	day12(const std::string& st="input/input12"){
		for(auto line:fiterator(st,'\n'))
		{
			vector<string> tokens=tokenize(line,{'-'});
			connections[tokens[0]].push_back(tokens.back());
			connections[tokens.back()].push_back(tokens[0]);
		}
	}

	void walk(string at,path p,set<string> visited,std::vector<path>&finished)
	{
		p.push_back(at);
		if(at=="end")
		{
			finished.push_back(p);
			return;
		}

		if(islower(at[0]))
			visited.insert(at);

		for(auto& s:connections.at(at))
		{
			if(!visited.count(s))
			{
				walk(s,p,visited,finished);
			}
		}
	}

	void walk2(string at,path p,set<string> visited,std::vector<path>&finished,bool small_revisited=false)
	{
		p.push_back(at);
		if(at=="end")
		{
			finished.push_back(p);
			return;
		}

		if(islower(at[0]))
			visited.insert(at);

		for(auto& s:connections.at(at))
		{
			if(!visited.count(s))
			{
				walk2(s,p,visited,finished,small_revisited);
			}
			else if(!small_revisited&&s!="start")
			{
				walk2(s,p,visited,finished,true);
			}
		}
	}

	void firstStar(bool print=true){
		vector<path> finished;
		walk("start",path{},set<string>(),finished);
		cout<<"day 12, paths existing: "<<finished.size()<<endl;
	}


	void secondStar(){
		vector<path> finished;
		walk2("start",path{},set<string>(),finished);
		cout<<"day 12, star 2 paths existing: "<<finished.size()<<endl;

	}

	map<string,vector<string>> connections;

};



#endif
