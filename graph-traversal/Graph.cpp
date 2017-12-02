#include "Graph.h"
#include <exception>

using namespace std;

//Utility Function (Not a member function)

void printEdge(vector<Edge> edges) {
	//Print edges
    cout<<"E = {";
    for(int i = 0; i<edges.size(); i++) {
        cout<<"{";
        cout<<edges[i].getIn().getName();
        cout<<", ";
        cout<<edges[i].getOut().getName();
        cout<<"} ";

        if(i!=edges.size()-1)
            cout<<", ";
    }
    cout<<"}"<<endl;
}

//Exception Handling Methods
struct NoVertixException : public exception {
   const char * what () const throw () {
      return "Vertix not found";
   }
};



Graph :: Graph() {

}

ostream& operator<<( std::ostream &output,
                              const Graph &G ){
    output << "V = {";
    for (int i = 0; i < G.vertices.size(); i++) {
        output << G.vertices[i].getName();
        if (i != G.vertices.size() - 1)
            output << ", ";
    }
    output << "}" << endl;
    
    //Print edges
    output<<"E = {";
    for(int i = 0; i<G.edges.size(); i++) {
        output<<"{";
        output<<G.edges[i].getIn().getName();
        output<<", ";
        output<<G.edges[i].getOut().getName();
        output<<"} ";
        
        if(i!=G.edges.size()-1)
            output<<", ";
    }
    output<<"}"<<endl;
    
    return output;
    
}

bool Graph :: isVertixExist(int name) {
	//Linear search to find the vertix
	for(int i =0 ; i<vertices.size(); i++) {
		if(vertices[i].getName() == name)
			return true;
	}
	return false;
}

bool Graph :: isEdgeExists(Edge E) {
		//Linear search to find the vertix
	for(int i =0 ; i<edges.size(); i++) {
		if(edges[i]== E)
			return true;
	}
	return false;
}

void Graph :: addVertix(Vertix vertix) {
	if(!isVertixExist(vertix.getName())) {
		vertices.push_back(vertix);
		cout<<"Info Vertix Added: "<<vertix<<endl;
	} else {
		cerr<<"Error: Vertix with name: "<<vertix.getName()<<" already exist \n";
	}
}

/**
 * Method searches for vertix and returns addres if found otherwise returns NULL
 */
Vertix Graph :: getVertixByName(int name) {
	for(int i = 0; i<vertices.size() ; i++) {
		if(vertices[i].getName() == name) {
			return vertices[i];
		}
	}

	return INVALID_VERTIX ;
}

//Implementation for directed graph only. Un directed graph will do his own implementation
void Graph :: addEdge(int vertixNameIn, int vertixNameOut) {
	
	if(vertixNameIn == vertixNameOut) {
		cout<<"Info: Adding self pointing edge "<<vertixNameIn<<endl;
	}

	//Locate the required vertices for the edge
	try {
	
	Vertix in = getVertixByName(vertixNameIn);
	Vertix out = getVertixByName(vertixNameOut);
	
	if(in == INVALID_VERTIX || out == INVALID_VERTIX) {
		throw NoVertixException();
	}

		Edge edge(in, out);
		edges.push_back(edge);
	} catch(std::exception& e) {
		cerr<<"An Exception has occured while adding Edge "<<vertixNameIn<<":"<<vertixNameOut<<endl;
		cerr<<"Exception: "<<e.what()<<endl;
	}
}

/**
 * Method traverses the graph and returns all possible paths from argument name vertix.
 * Method traverses graph as directed
 * Checks if the first edge is stack in name matches and has not been visited
 * puts the edge on return stack and repeates on out vertix till no more vertices to analyze
 */
void Graph :: DFT(int name) {

    for(int i = 0; i<edges.size();i++) {

        if(edges[i].getIn().getName()==name && !(edges[i].getIn().getIsVisited()) ) {
            edges[i].getIn().setIsVisited(true);
            cout<<edges[i];
            DFT(edges[i].getOut().getName());
        }
    }
}

void Graph :: removeVertix(int name) {
	bool found =false;
	for(int i = 0 ; i<vertices.size(); i++) {
		
		if(vertices[i].getName()== name) {
			found = true;
			cout<<"Info Vertix removed: "<<vertices[i]<<endl;
			vertices.erase (vertices.begin()+i);
			
			//Also remove all associated edges
			for(int j = 0 ; j<edges.size(); j++) {
				if(edges[j].getIn().getName() == name || edges[j].getOut().getName() == name ) {							
					removeEdge(edges[i]);
				}
			}
		
		}
	
	}	
	if(!found){
		cerr<<"Unable to remove vertix with name: "<<name<<endl;
	}
}

void Graph :: removeEdge(int inName, int outName) {

	removeEdge(Edge(inName, outName))	;
}

void Graph :: removeEdge(Edge E) {
		bool found =false;
	for(int i = 0 ; i<edges.size(); i++) {
		
		if(edges[i] == E ) {
			found = true;
			cout<<"Info Edge Removed: "<<E<<endl;
			edges.erase(edges.begin()+i);
			
		}
	}
	
	if(!found){
		cerr<<"Unable to remove Edge : "<<E<<endl;
	}
}

Graph :: ~Graph() {
	//CLean up edges and vertices
	edges.clear();
	vertices.clear();
}




