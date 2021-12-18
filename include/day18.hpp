#ifndef DBMW_INCLUDE_DAY18_HPP_
#define DBMW_INCLUDE_DAY18_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day18{

	struct snailfishnum{
		snailfishnum(
				const std::string& s,
				unsigned& index,
				snailfishnum* parent=nullptr)
		{
			this->parent=parent;
			pair=false;
			num=0;
			rightnode=leftnode=nullptr;

			if(s[index]=='[')
			{

				index++;
				pair=true;
				leftnode=new snailfishnum(s,index,this);
				index++;//comma
				rightnode=new snailfishnum(s,index,this);
				index++;//]
			}
			else
			{
				while(isdigit(s[index]))
				{
					num*=10;
					num+=s[index]-'0';
					index++;
				}
			}
		}

		snailfishnum(unsigned n,snailfishnum* parent){
			leftnode=rightnode=nullptr;
			pair=false;
			this->parent=parent;
			num=n;
		}

		snailfishnum(snailfishnum* l,snailfishnum *r){
			leftnode=rightnode=nullptr;
			pair=true;
			num=0;
			this->parent=nullptr;
			leftnode=l;
			rightnode=r;
			leftnode->parent=this;
			rightnode->parent=this;
		}

		void reduce(){
			if(!pair)
			{
				unsigned l=num/2;
				unsigned r=num/2+(num%2);
				pair=true;
				leftnode=new snailfishnum(l,this);
				rightnode=new snailfishnum(r,this);

			}
			else
			{
				if(leftnode->pair||rightnode->pair)
					throw runtime_error("Trying to split pairs");

				unsigned ls=leftnode->num;
				unsigned rs=rightnode->num;
				parent->addLeft(ls, this);
				parent->addRight(rs, this);

				num=0;
				pair=false;
			}
		}

		void addLeft(unsigned num,snailfishnum* src){

			if(leftnode==src)
			{
				if(parent)
					parent->addLeft(num, this);
			}
			else
				leftnode->sl(num);
		}

		void sl(unsigned num)
		{
			if(!pair)
				this->num+=num;
			else
				rightnode->sl(num);
		}

		void addRight(unsigned num,snailfishnum* src){
			if(rightnode==src)
			{
				if(parent)
					parent->addRight(num, this);
			}
			else
				rightnode->sr(num);
		}

		void sr(unsigned num)
		{
			if(!pair)
				this->num+=num;
			else
				leftnode->sr(num);
		}

		snailfishnum* searchSplit(unsigned level){

			if(!pair)
				return nullptr;

			if(level>3&&!leftnode->pair&&!rightnode->pair)
				return this;

			auto r=leftnode->searchSplit(level+1);
			if(r)
				return r;

			r=rightnode->searchSplit(level+1);
			if(r)
				return r;


			return nullptr;
		}

		snailfishnum* searchExplode(){

			if(!pair)
			{
				if(num>9)
					return this;
				return nullptr;
			}

			auto r=leftnode->searchExplode();

			if(r)
				return r;

			r=rightnode->searchExplode();

			if(r)
				return r;

			return nullptr;
		}

		void fullreduce(){
			snailfishnum* sptr=nullptr;
			do{
				sptr=nullptr;
				sptr=searchSplit(0);
				if(!sptr)
					sptr=searchExplode();

				if(sptr)
					sptr->reduce();

			}while(sptr);
		}

		uint64_t magnitude(){

			if(pair)
				return leftnode->magnitude()*3+rightnode->magnitude()*2;

			return num;
		}


		friend ostream& operator<<(ostream&o,const snailfishnum&c ){
			if(!c.pair)
				o<<c.num;
			else
			{
				o<<'['<<(*c.leftnode)<<","<<(*c.rightnode)<<"]";
			}

			return o;
		}

		bool pair;
		unsigned num;
		snailfishnum* parent;
		snailfishnum*  leftnode,*rightnode;
	};


	day18(const std::string& st="input/input18"){
		for(auto line:fiterator(st,'\n'))
			srcs.emplace_back(line);

		reset();
	}

	void reset(){
		numbers.clear();
		numbers.reserve(512);
		for(auto line:srcs)
		{
			unsigned ct=0;
			numbers.emplace_back(line,ct);

		}
	}

	void firstStar(){
		snailfishnum* bf=&numbers[0];
		for(unsigned e=1;e<numbers.size();e++)
		{
			bf=new snailfishnum(bf,&numbers[e]);
			bf->fullreduce();
		}
		cout<<"day 18, star1 magnitude: "<<bf->magnitude()<<endl;

	}

	uint64_t getManitude(unsigned i,unsigned j){
		reset();
		auto* bf=new snailfishnum(&numbers[i],&numbers[j]);
		bf->fullreduce();
		return bf->magnitude();
	}

	void secondStar(){
		unsigned max=0;
		for(unsigned i=0;i<numbers.size();i++)
			for(unsigned j=0;j<numbers.size();j++)
			{
				if(i==j)
					continue;

				unsigned magres=getManitude(i, j);
				if(magres>max)
					max=magres;
				magres=getManitude(j, i);
				if(magres>max)
					max=magres;
			}

		cout<<"day 18, star2 magnitude: "<<max<<endl;
	}

	vector<snailfishnum> numbers;
	vector<string> srcs;

};



#endif
