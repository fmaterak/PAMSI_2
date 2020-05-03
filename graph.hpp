#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>

//base class, representaing any kind of graph
class Graph {

protected:
	int m_V, m_E; //amount of Vertices and Edges
	double m_density; //density of graph

public:
	const int& getV() const { return m_V; }
	const int& getE() const { return m_E; }

	virtual void fillGraph(const bool allowLoops) const = 0; //fills graph in random way
	virtual void printGraph() const =  0; //prints graph representation into console
	virtual const int readFromFile() = 0; //fills graph based on input from file
	virtual void createInput(const int t_startNode) const = 0; //creates artificial input file so user can copy it to
													//external graph-visualization tool
	virtual ~Graph() {};
	explicit Graph(int t_V, int t_E, double t_density) : m_V(t_V), m_E(t_E), m_density(t_density) {}
	Graph() {}; //Unparametrized constructor, so program can crete a graph without initialization.
};				//This is beacause program must be able to crete graph based on the input file infomations.

//represents weighted edge between two nodes
struct Edge {

	//source node of edge; destination node of edge; weight of edge
	int source, dest, weight;
};


//graph in an adjency list representation
class ListGraph : public Graph {

	Edge* edge; //array of all adges in the graph

public:
	//those methods have comments in the Graph class
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int t_startNode) const override;

	const Edge* getStruct() const { return edge; }
	void addEdge(int t_guardNumber, int t_number, int t_weight, int flag) const; //adds node at the flag position
	bool detectIfExist(int t_guardNumber, int t_nodeNumber) const; //detects wheter given connection exists

	explicit ListGraph(int t_V, double t_density)
		:Graph(t_V, static_cast<int>(t_density* t_V* (t_V - 1)), t_density),
		 edge(new Edge[static_cast<int>(t_density* t_V* (t_V - 1))]) {}
	ListGraph() : Graph() {};
	~ListGraph() { delete[] edge; }
};

class MatrixGraph : public Graph {

	std::unique_ptr<std::unique_ptr<int[]>[]> matrix; //dynamic array of dynamic arrays;
														//main container of graph
public:
	//those methods have comments in the Graph class
	void fillGraph(const bool allowLoops) const override;
	void printGraph() const override;
	const int readFromFile() override;
	void createInput(const int t_startNode) const override;

	//returns value of given cell in matrix array
	const int& getWeight(int t_row, int t_column) const { return matrix[t_row][t_column]; }

	explicit MatrixGraph(int t_V, double t_density);
	MatrixGraph() : Graph() {};
};
