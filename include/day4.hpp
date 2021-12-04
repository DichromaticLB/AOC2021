#ifndef DBMW_INCLUDE_DAY3_HPP_
#define DBMW_INCLUDE_DAY3_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>

struct day4{

	struct board{

		void addNumbers(const std::string&s){
			numbers.emplace_back();
			for(auto&v:tokenize(s))
			{
				if(v=="")
					continue;
				numbers.back().emplace_back(std::stoul(v),false);
			}
		}

		std::vector<std::vector<int>> winningRows(){
			std::vector<std::vector<int>> res;
			for(auto& v:numbers)
				if(std::all_of(v.begin(), v.end(),[](const auto&e1){return e1.second;}))
				{
					res.emplace_back();
					for(auto&val:v)
						res.back().push_back(val.first);
				}
			return res;
		}

		std::vector<std::vector<int>> winningCols(){
			std::vector<std::vector<int>> res;
			 for(unsigned e=0;e<numbers.back().size();e++)
				if(std::all_of(numbers.begin(), numbers.end(),[&](const auto&e1){return e1[e].second;}))
				{
					res.emplace_back();
					for(auto&val:numbers)
						res.back().push_back(val[e].first);
				}
			return res;
		}

		unsigned sum_unmarked(){
			unsigned res=0;
			for(auto&v:numbers)
				for(auto&num:v)
					if(!num.second)
						res+=num.first;
			return res;
		}

		void set(int num){
			for(auto& v:numbers)
				for(auto &n:v)
					if(n.first==num)
						n.second=true;
		}

		using row=std::vector<std::pair<int,bool>>;
		std::vector<row> numbers;
	};

	day4(const std::string& st="input/input4"){
		bool f=true;
		for(auto s:fiterator(st,'\n'))
		{
			if(f)
			{
				for(auto&v:tokenize(s,{','}))
					numbers.push_back(std::stoul(v));
				f=false;
			}
			else
			{
				if(s.length())
					boards.back().addNumbers(s);
				else
					boards.emplace_back();
			}

		}
	}

	void firstStar(){
		auto b=boards;
		for(auto& n:numbers)
		{
			for(auto& board:b)
				board.set(n);

			for(auto& board:b){
				auto cols=board.winningCols();
				auto rows=board.winningRows();
				if(cols.size()||rows.size()){

					std::cout<<"Winning score= "<<board.sum_unmarked()*n<<std::endl;
					return;
				}

			}
		}
	}




	void secondStar(){
		auto b=boards;
		std::vector<board> buffer;

		for(auto& n:numbers)
		{

			for(auto& board:b)
				board.set(n);

			for(auto& board:b){
				auto cols=board.winningCols();
				auto rows=board.winningRows();
				if(cols.size()||rows.size()){

					if(b.size()==1)
					{
						std::cout<<"Winning score 2nd star= "<<board.sum_unmarked()*n<<std::endl;
						return;
					}
				}
				else
					buffer.push_back(board);
			}
			b=buffer;
			buffer.clear();
		}
	}

	std::vector<unsigned> numbers;
	std::vector<board> boards;

};



#endif
