#ifndef DBMW_INCLUDE_DAY20_HPP_
#define DBMW_INCLUDE_DAY20_HPP_

#include"util.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<map>
#include<numeric>
#include<set>

struct day20{

	using dataline=vector<char>;

	void pad(dataline& v,unsigned len)
	{
		while(len--)
			v.push_back(0);
	}

	day20(const std::string& st="input/input20"){
		bool parsingImage=false;
		int usePad=51;
		for(auto line:fiterator(st,'\n'))
		{
			if(line.empty())
			{
				parsingImage=true;
				continue;
			}

			if(parsingImage)
			{
				dataline data;
				pad(data,usePad);
				for(auto& c:line)
					data.push_back(c=='#'?1:0);
				pad(data,usePad);
				if(!image.height())
				{
					dataline padrow(data.size(),0);
					for(auto i=0;i<usePad;i++)
						image.addRow(padrow);

				}
				image.addRow(data);
			}
			else
				for(auto c:line)
					transform.push_back((c=='#')?1:0);
		}

		dataline padrow(image.width(),0);
		for(auto i=0;i<usePad;i++)
			image.addRow(padrow);

		image.prepareBuffer();

	}

	void iterate(){
		for(auto e=image.begin();e!=image.end();++e)
		{
			const static vector<int> order={0,1,2,7,-1,3,6,5,4};
			auto ar=e.around8();
			unsigned index=0;

			for(auto v:order)
			{
				index<<=1;
				if(v==-1)
					index|=**e;
				else if(ar[v].inBounds())
					index|=**ar[v];
				else if(iteration%2&&transform[0]==1)
					index|=1;
			}

			*e.bufferAccess()=transform[index];
		}
		image.swapBuffer();
		iteration++;

	}

	void firstStar(){
		iterate();
		iterate();
		cout<<"day 20, star1: "<<std::accumulate(image.begin(), image.end(), 0l,[](auto l,auto p){
			return l+*p;
		})<<endl;
	}



	void secondStar(){
		while(iteration<50)
			iterate();
		cout<<"day 20, star2: "<<std::accumulate(image.begin(), image.end(), 0l,[](auto l,auto p){
			return l+*p;
		})<<endl;
	}

	vector<unsigned char> transform;
	board<char> image;
	int iteration=0;

};



#endif
