#include "UnDirectedGraph.hpp"
#include<iostream>
using namespace std;


void UnDirectedGraph::DFT(int name) {
    for(int i = 0; i<edges.size();i++) {
        
        if(edges[i].getIn().getName()==name && !(edges[i].getIn().getIsGrey()))   {
            if(edges[i].getIn().getIsVisited()) {
                edges[i].getIn().setIsGrey(true);
            }
            edges[i].getIn().setIsVisited(true);
            cout<<edges[i];
			DFT(edges[i].getOut().getName());
        }
    }
}
