#ifndef DBMW_INCLUDE_UTIL_HPP_
#define DBMW_INCLUDE_UTIL_HPP_

#include<fstream>
#include<string>
#include<vector>

using namespace std;

struct fiterator{

	struct _iter{
		fiterator *src;

		std::string operator*() const;
		_iter& operator++();
		bool operator!=(const _iter& other) const;

	};

	fiterator(const std::string &filename,const char& separator=' ');

	_iter begin();
	_iter end();
	std::string next();

	char sep;
	std::ifstream f;
};

std::vector<std::string> tokenize(const std::string &st,std::vector<char> separators={' '});


template<class T>
struct board{

	using row=std::vector<T>;

	uint64_t width() const{
		if(bd.size()==0)
			throw std::runtime_error("Board: can't find width of empty board");
		return bd[0].size();
	}

	uint64_t height() const{
		return bd.size();
	}

	struct iter{

		board* src;
		int64_t x,y;

		iter& operator++(){
			if(x<(int64_t)src->width()-1)
				x++;
			else
			{
				x=0;
				y++;
			}


			return *this;
		}

		iter left(){
			iter res=*this;
			res.x--;
			return res;
		}

		iter right(){
			iter res=*this;
			res.x++;
			return res;
		}

		iter top(){
			iter res=*this;
			res.y--;
			return res;
		}

		iter top_left(){
			iter res=*this;
			res.y--;
			res.x--;
			return res;
		}

		iter top_right(){
			iter res=*this;
			res.y--;
			res.x++;
			return res;
		}

		iter bot(){
			iter res=*this;
			res.y++;
			return res;
		}

		iter bot_left(){
			iter res=*this;
			res.y++;
			res.x--;
			return res;
		}

		iter bot_right(){
			iter res=*this;
			res.y++;
			res.x++;
			return res;
		}

		std::vector<iter> around4(){
			return std::vector<iter>{
				top(),
				right(),
				bot(),
				left()
			};
		}

		std::vector<iter> around8(){
			return std::vector<iter>{
				top(),
				right(),
				bot(),
				left(),
				top_left(),
				top_right(),
				bot_left(),
				bot_right()
			};
		}

		bool operator<(const iter& other) const{
			if(y==other.y)
				return x<other.x;
			return y<other.y;
		}

		bool inBounds()const{
			return !(x<0||x>=(int64_t)src->width()||y<0||y>=(int64_t)src->height());
		}

		T* operator*() const{
			if(!inBounds())
				return nullptr;

			return &src->bd[y][x];
		}

		bool operator!=(const iter& other) const{
			return x!=other.x||y!=other.y;
		}

		bool operator==(const iter& other) const{
			return !(*this!=other);
		}
	};

	iter begin(){
		iter res;
		res.src=this;
		res.x=0;
		res.y=0;
		return res;
	}

	iter end(){
		iter res;
		res.src=this;
		res.x=0;
		res.y=height();
		return res;
	}

	void addRow(const std::vector<T>& data){
		if(bd.size()!=0&&bd[0].size()!=data.size())
			throw std::runtime_error("Trying to add row of different stride to board");
		bd.push_back(data);

	}

	std::vector<row> bd;
};

#endif
