#ifndef Vertix_hpp
#define Vertix_hpp

#include <iostream>
class Vertix {
    int name;
    bool isVisited;
    bool isGrey; //To anticipate reverse path for un directed graphs
    
public:
    
    bool getIsGrey()const;
    Vertix();
    Vertix(int name);
    Vertix(const Vertix&); //copy constructor
    bool getIsVisited()const;
    void setIsGrey(bool isGrey);
    void setIsVisited(bool isVisited);
    int getName()const;
    void setName(int name);
    
    //Assignment operator overloading
    void operator = (const Vertix &v );
    bool operator == (const Vertix &v);
    friend std::ostream &operator<<( std::ostream &output, const Vertix &V );
    
};

// a constant vertix to represent a invalid vertix for debugging
const Vertix INVALID_VERTIX(-999);

#endif /* Vertix_hpp */
