#include "Vertix.hpp"

void Vertix:: operator = (const Vertix &v ) {
    this->name = v.getName();
    this->isVisited = v.getIsVisited();
    this->isGrey = v.getIsGrey();
};

bool Vertix:: getIsGrey()const{
    return isGrey;
}

Vertix::Vertix()
{
    name = 0;
    isVisited = false;
    isGrey = false;
};

Vertix:: Vertix(int name) {
    this->name = name;
    this->isVisited = false;
};

Vertix :: Vertix (const Vertix& V) {
	*this = V; // uses overloaded = operator
}

bool Vertix::getIsVisited() const {
    return isVisited;
};

void Vertix::setIsGrey(bool isGrey) {
    this->isGrey = isGrey;
};

void Vertix:: setIsVisited(bool isVisited) {
    this->isVisited = isVisited;
};

int Vertix::getName() const {
    return name;
};

void Vertix::setName(int name) {
    this->name = name;
};

bool Vertix:: operator == (const Vertix &v) {
	if(this->getName() == v.getName()) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<( std::ostream &output, const Vertix &V ) {
	output<<V.getName();
	return output;
}					
