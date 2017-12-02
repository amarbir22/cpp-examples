#include "Edge.hpp"
#include<iostream>

Edge::Edge(Vertix in, Vertix out) {
    this->in = in;
    this->out = out;
};

void Edge::setIn(Vertix v) {
    in=v;
};

void Edge::setOut(Vertix v) {
    out=v;
};

Vertix Edge:: getIn()const{
    return in;
};

Vertix Edge:: getOut()const{
    return out;
};

std::ostream& operator<<(std::ostream &output,
                                    const Edge &E ) {
    output<<"{"<<E.getIn().getName()<<", "<<E.getOut().getName()<<"} ";    
	return output;                       	
}

bool Edge:: operator == (const Edge& E) {
	if(this->getIn()== E.getIn()  && this->getOut() == E.getOut()) {
		return true;
	}
	else {
		return false;
	}
}

