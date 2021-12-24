#ifndef DBMW_INCLUDE_DAY24_HPP_
#define DBMW_INCLUDE_DAY24_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>
#include<cmath>

struct day24{

	static const vector<vector<int>>& process(){
		static const vector<vector<int>> pro=
			{{1  ,10 ,5},
			{1  ,13 ,9},
			{1  ,12 ,4},
			{26 ,-12,4},
			{1  ,11 ,10},
			{26 ,-13,14},
			{26	,-9 ,14},
			{26 ,-12,12},
			{1  ,14 ,14},
			{26 ,-9 ,14},
			{1  ,15 ,5},
			{1  ,11 ,10},
			{26 ,-16,8},
			{26 ,-2 ,15}
		};
		return pro;
	}


	enum ACT{
		INP,
		ADD,
		MUL,
		DIV,
		MOD,
		EQL
	};
	struct computer;

	struct operand{
		int64_t& getVal( computer&);
		int64_t v;
		bool imm;
	};

	struct instruction{
		instruction(const std::string&line)
		{
			static const map<string,ACT> mapping{
				{"inp",INP},
				{"add",ADD},
				{"mul",MUL},
				{"div",DIV},
				{"mod",MOD},
				{"eql",EQL},

			};

			auto t=tokenize(line,{' '});
			a=mapping.at(t[0]);
			l.imm=false;
			l.v=t[1][0]-'w';

			if(t.size()>2)
			{
				if(isalpha(t[2][0]))
				{
					r.imm=false;
					r.v=t[2][0]-'w';
				}
				else
				{
					r.imm=true;
					r.v=stoll(t[2]);
				}
			}
		}

		ACT a;
		operand l,r;
	};



	struct computer{
		computer():w(wxyz[0]),x(wxyz[1]),y(wxyz[2]),z(wxyz[3]){}

		void execute(instruction i, std::string& input){
			auto& tgt=i.l.getVal(*this);
			switch(i.a)
			{
				case INP:
					tgt=input.back()-'0';
					input.pop_back();
					break;
				case ADD:
					tgt=tgt+i.r.getVal(*this);
					break;
				case MUL:
					tgt=tgt*i.r.getVal(*this);
					break;
				case DIV:
					tgt=tgt/i.r.getVal(*this);
					break;
				case MOD:
					tgt=tgt%i.r.getVal(*this);
					break;
				case EQL:
					tgt=(tgt==i.r.getVal(*this))?1:0;
					break;
			}
		}

		void part(int c,int zdiv,int xadd,int yadd){                 //			{{1  ,10 ,5},
			w=c;                                                     //			{1  ,13 ,9},
                                                                     //			{1  ,12 ,4},
			x=(z%26)+xadd;                                           //			{26 ,-12,4},
			z/=zdiv;                                                 //			{1  ,11 ,10},
                                                                     //			{26 ,-13,14},
			if(x!=w)                                                 //			{26	,-9 ,14},
				z=z*26+w+yadd;                                       //			{26 ,-12,12},
                                                                     //			{1  ,14 ,14},
		}                                                            //			{26 ,-9 ,14},
                                                                     //			{1  ,15 ,5},
		void full(const vector<int> &el){                            //			{1  ,11 ,10},
                                                                     //			{26 ,-16,8},
			for(unsigned i=0;i<el.size();i++)                        //			{26 ,-2 ,15}
				part(el[i],process()[i][0],process()[i][1],process()[i][2]);
		}


		bool operator!=(const computer&o)const{
			return z!=o.z;
		}

		int64_t& w,&x,&y,&z;
		int64_t wxyz[4]={0,0,0,0};
	};

	using program=vector<instruction>;

	day24(const std::string& st="input/input24"){
		for(auto v:fiterator(st,'\n'))
		{
			pr.emplace_back(v);
			if(pr.back().a==INP)
				subprograms.emplace_back();
			subprograms.back().push_back(pr.back());

		}
	}

	vector<int> fromNum(uint64_t j){
		vector<int> res;
		while(j)
		{
			bool f=false;
			if((j%10)==0)
				f=true;
			res.push_back((j%10)+(f?1+(rand()%9):0));
			j/=10;

		}
		return res;
	}

	void check(){
		uint64_t base=100000000000000;
		while(true){
			computer c1,c2;
			auto v=fromNum(base);
			v.pop_back();
			auto v2=v;
			string st;
			while(v.size())
			{
				st.push_back(v.back()+'0');
				v.pop_back();
			}

			auto st2=st;
			c1.full(v2);
			for(auto i:pr)
				c2.execute(i,st);

			if(c1!=c2)
				cout<<"bad!"<<endl;
			else
				cout<<"success "<<st2<<endl;

		}
	}

	vector<int> vectorize(uint64_t j){
		vector<int> res;
		while(j)
		{
			if(!(j%10))
				return res;

			res.push_back(j%10);
			j/=10;

		}
		vector<int> r2(res.rbegin(),res.rend());
		return r2;
	}

	void firstStar(){
		return;
		uint64_t i=99919692000000;

		for(uint64_t ii=999999;ii!=111111;ii--)
		{
			auto v=vectorize(i+ii);
			if(v.size()!=14)
				continue;

			computer c;
			c.full(v);
			if(c.z==0)
			{
				cout<<i+ii<<endl;
				return;
			}
		}
	}


	void secondStar(){

		uint64_t i=81914111000000;
		for(uint64_t ii=111111;ii!=999999;ii++)
		{
			auto v=vectorize(i+ii);
			//auto v=vectorize(ii);
			if(v.size()!=14)
				continue;

			computer c;
			c.full(v);
			if(c.z==0)
			{

				cout<<i+ii<<endl;
				return;
			}
		}
	}

	program pr;
	vector<program> subprograms;

};

int64_t& day24::operand::getVal( computer&c){
	if(imm)
		return v;
	return c.wxyz[v];
}


#endif
