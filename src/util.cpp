#include"util.hpp"

fiterator::fiterator(const std::string &filename,const char& separator){

	f.open(filename);

	if(!f.is_open())
		throw std::runtime_error("Failed to create fiterator from "+filename);

	this->sep=separator;

}

fiterator::_iter fiterator::begin(){
	_iter res;
	res.src=this;
	return res;
}

fiterator::_iter fiterator::end(){
	return begin();
}

std::string fiterator::next(){

	std::string res;
	int c;
	while(f.good()&&(c=f.get())!=EOF&&c!=sep)
		res.push_back(c);

	return res;
}


std::string fiterator::_iter::operator*() const{
	return src->next();
}

fiterator::_iter& fiterator::_iter::operator++(){return *this;}

bool fiterator::_iter::operator!=(const _iter& other) const{
	return src->f.good()&& src->f.peek()!=EOF;
}
