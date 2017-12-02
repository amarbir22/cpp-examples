#ifndef Edge_hpp
#define Edge_hpp
#include "Vertix.hpp"
#include <iostream>

class Edge {
    Vertix in;
    Vertix out;
    
public:
    
    Edge(Vertix in, Vertix out);
    void setIn(Vertix v);
    void setOut(Vertix v);
    Vertix getIn()const;
    Vertix getOut()const;
    bool isEdgeExists(Edge);
    
     //Overloaded Methods
    friend std::ostream &operator<<( std::ostream &output,
                                    const Edge &E );
    bool operator == (const Edge& E);
};

#endif /* Edge_hpp */
