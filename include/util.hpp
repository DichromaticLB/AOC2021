#ifndef DBMW_INCLUDE_UTIL_HPP_
#define DBMW_INCLUDE_UTIL_HPP_

#include<fstream>
#include<string>
#include<vector>

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


#endif
