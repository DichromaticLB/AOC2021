#ifndef DBMW_INCLUDE_DAY16_HPP_
#define DBMW_INCLUDE_DAY16_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day16{


	day16(const std::string& st="input/input16"){
		for(auto line:fiterator(st,'\n'))
		{
			for(auto c:line)
			{
				char num=0;
				if(c>='A')
					num=c-'A'+10;
				else
					num=c-'0';
				for(int i=4;i!=0;)
				{
					i--;
					bitstring.push_back((num>>i)&1);
				}
			}
		}


	}

	struct packet{
		using bits=deque<uint8_t>;

		int read(bits&b,int count)
		{
			if(b.size()<(unsigned)count)
				throw runtime_error("Not enought bits to read");

			int res=0;
			while(count)
			{
				res<<=1;
				res|=b.front();
				b.pop_front();
				count--;
			}
			return res;
		}


		int64_t readNumber(bits&b,int &count)
		{
			int64_t res=0;
			int rd=0;
			do{
				rd=read(b,5);
				res<<=4;
				res|=rd&0xf;
				count+=5;
			}while(rd&0x10);

			return res;
		}

		int subpacketcount(){
			int res=subpackets.size();
			for(auto& p:subpackets)
				res+=p.subpacketcount();
			return res;
		}

		int64_t reduce() const{
			switch(id)
			{
				case 4:
					return data;
				case 0:
					return accumulate(subpackets.begin(),subpackets.end(),0l,
							[](auto b,const packet&a){
								return a.reduce()+b;
					});
				case 1:
					return accumulate(subpackets.begin(),subpackets.end(),1l,
							[](auto b,const packet&a){
								return a.reduce()*b;
					});
				case 2:
				case 3:
				{
					int64_t min=numeric_limits<int64_t>::max(),max=0;
					for(auto& v:subpackets){
						auto e=v.reduce();
						min=std::min(min,e);
						max=std::max(max,e);
					}
					if(id==2)
						return min;
					return max;
				}
				case 5:
				{
					return subpackets[0].reduce()>subpackets[1].reduce()?1:0;
				}
				case 6:
				{
					return subpackets[0].reduce()<subpackets[1].reduce()?1:0;
				}
				case 7:
				{
					return subpackets[0].reduce()==subpackets[1].reduce()?1:0;
				}
				default:
					throw runtime_error("Unknwon operation for packets "+std::to_string(id));
			}

		}

		packet(bits & b)
		{
			version=id=data=0;
			int bitsRead=6;

			version=read(b,3);
			id=read(b,3);

			switch(id)
			{
				case 4:
					data=readNumber(b, bitsRead);
					break;
				default:
				{
					bool packettotal=b.front();
					b.pop_front();
					if(packettotal)
					{
						data=read(b,11);
						while(subpackets.size()!=(unsigned)data)
						{
							packet k(b);
							subpackets.push_back(k);
						}
					}
					else
					{
						data=read(b,15);
						uint64_t target=b.size()-data;
						while(b.size()!=target)
						{
							packet k(b);
							subpackets.push_back(k);
						}

					}
					break;
				}
			}
		}

		int version;
		int id;
		int64_t data;
		vector<packet> subpackets;
	};

	int addVersion(const packet& p){
		int res=p.version;
		for(auto& v:p.subpackets)
			res+=addVersion(v);
		return res;
	}

	void firstStar(){
		auto bitstring=this->bitstring;
		packet p(bitstring);
		cout<<"day 16 star 1, sum of versions: "<<addVersion(p)<<endl;
	}

	void secondStar(){
		auto bitstring=this->bitstring;
		packet p(bitstring);
		cout<<"day 16 star 2, result: "<<p.reduce()<<endl;
	}

	deque<uint8_t> bitstring;

};



#endif
