#ifndef DBMW_INCLUDE_DAY10_HPP_
#define DBMW_INCLUDE_DAY10_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day10{


	day10(const std::string& st="input/input10"){
		for(auto line:fiterator(st,'\n'))
		{
			lines.push_back(line);
		}
	}

	void firstStar(bool print=true){
		static const std::map<char,unsigned> points{{']',57},{'}',1197},{'>',25137}};

		uint64_t ct=0;
		goodlines.clear();
		for(auto line:lines)
		{
			std::vector<char> stack;
			bool go=true;
			goodlines.push_back(line);
			for(auto c:line)
			{
				if(!go)
				{
					goodlines.pop_back();
					break;
				}

				switch(c)
				{
					case '(':
					case '<':
					case '[':
					case '{':
						stack.push_back(c);
						break;
					case ')':
						if(stack.back()=='(')
						{
							stack.pop_back();
						}
						else
						{
							go=false;
							ct+=3;
						}
						break;
					default:
						if(c-stack.back()==2)
						{
							stack.pop_back();
						}
						else
						{
							go=false;
							ct+=points.at(c);
						}
						break;

				}
			}
		}
		if(print)
			std::cout<<"day 10, star 1: syntax error score: "<<ct<<std::endl;
	}


	void secondStar(){
		static const std::map<char,unsigned> points{{'[',2},{'{',3},{'<',4},{'(',1}};
		std::vector<uint64_t> results;

		if(goodlines.empty())
			firstStar(false);

		for(auto line:goodlines)
		{
			std::vector<char> stack;
			for(auto c:line)
			{

				switch(c)
				{
					case '(':
					case '<':
					case '[':
					case '{':
						stack.push_back(c);
						break;

					default:
						stack.pop_back();
						break;
				}
			}
			uint64_t score=0;
			for(auto s=stack.rbegin();s!=stack.rend();s++)
			{
				score*=5;
				score+=points.at(*s);
			}
			results.push_back(score);
		}
		std::sort(results.begin(),results.end());
		std::cout<<"day 10, star 2: middle score: "<<results[results.size()/2]<<std::endl;
	}

	std::vector<std::string> lines;
	std::vector<std::string> goodlines;


};



#endif
