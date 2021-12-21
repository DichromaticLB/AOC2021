#ifndef DBMW_INCLUDE_DAY21_HPP_
#define DBMW_INCLUDE_DAY21_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day21{

	struct die{
		virtual ~die()=default;
		virtual int roll(){
			return 1+(rand()%100);
		}
	};

	struct ddie:public die{
		virtual ~ddie()=default;
		virtual int roll(){
			return 1+(iter++%100);
		}

		unsigned iter=0;
	};

	struct game{

		game(const std::vector<int>& players)
		{
			player1=players[0]-1;
			player2=players[1]-1;
			score1=score2=0;
			iteration=0;
		}

		void iterate(die* d){
			int add=d->roll()+d->roll()+d->roll();
			player1=(player1+add)%10;
			score1+=(player1+1);
			iteration+=3;
			if(score1>=1000)
				return;
			add=d->roll()+d->roll()+d->roll();
			player2=(player2+add)%10;
			score2+=(player2+1);
			iteration+=3;

		}

		void updateP1(unsigned v){
			player1=((player1+v)%10);
			score1+=player1+1;
		}

		void updateP2(unsigned v){
			player2=((player2+v)%10);
			score2+=player2+1;
		}


		bool operator<(const game& other)const{
			if(player1!=other.player1)
				return player1<other.player1;
			if(player2!=other.player2)
				return player2<other.player2;
			if(score1!=other.score1)
				return score1<other.score1;
			return score2<other.score2;
		}

		bool over() const{
			return score1>=21||score2>=21;
		}

		uint64_t player1,score1;
		uint64_t player2,score2;
		uint64_t iteration;
	};

	day21(const std::string& st="input/input21"){

		for(auto line:fiterator(st,'\n'))
		{
			auto t=tokenize(line, {' '});
			startingPos.push_back(stol(t.back()));
		}
	}

	void firstStar(){
		game g(startingPos);
		ddie e;
		while(g.score1<1000&&g.score2<1000)
			g.iterate(&e);


		if(g.score1<1000)
			cout<<"day 21, star1: "<<(g.iteration*g.score1)<<endl;
		else
			cout<<"day 21, star1: "<<((g.iteration)*g.score2)<<endl;


	}

	void setSources(){
		for(unsigned e=1;e<4;e++)
			for(unsigned e2=1;e2<4;e2++)
				for(unsigned e3=1;e3<4;e3++)
								sources[e+e2+e3]++;
	}


	void fillMap(){
		while(true)
		{
			unsigned dex=states.rbegin()->first;
			states[dex+1];
			for(auto &state:states[dex])
			{
				if(state.first.over())
					continue;

				for(auto&s:sources)
				{
					game g(state.first);
					if(dex%2)
						g.updateP2(s.first);
					else
						g.updateP1(s.first);

					states[dex+1][g]+=s.second*state.second;
				}
			}

			if(states[dex+1].empty())
				break;

		}
	}

	void secondStar(){
		game g(startingPos);
		states[0]={{g,1}};
		setSources();
		fillMap();
		std::vector<uint64_t> p1Victories(states.size(),0),p2Victories(states.size(),0);
		for(auto& v:states)
		{
			if(v.first!=0)
			{
				p1Victories[v.first]=p1Victories[v.first-1];
				p2Victories[v.first]=p2Victories[v.first-1];
			}

			for(auto& vv:v.second)
			{
				if(vv.first.over())
				{
					if(v.first%2)
						p2Victories[v.first]+=vv.second;
					else
						p1Victories[v.first]+=vv.second;
				}
			}
		}


		cout<<"day 21, star 2:"<<std::max(p1Victories.back(),p2Victories.back())<<endl;


	}

	map<unsigned,map<game,uint64_t>> states;
	map<unsigned,unsigned> sources;
	vector<int> startingPos;

};



#endif
