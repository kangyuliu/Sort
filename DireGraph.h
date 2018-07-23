#ifndef DIREGRAPH_H_
#define DIREGRAPH_H_

#include <iostream>
#include <vector>
#include <cassert>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <string>
#include <set>

#include "CVertex.h"




class DireGraph
{
public:
	//构造函数
	DireGraph();

	DireGraph(unsigned int numVertexes);
	//析构函数
	~DireGraph();
private:
	unsigned int m_numVertexes;   //图的节点数量
	unsigned int m_numEdges;	//图的边的数量
	
	std::vector<CVertex> m_vertexes; //顶点集

	std::vector<std::vector<unsigned int> > m_graTable;	//邻接表：值表示对应顶点的编号

	std::vector<std::vector<unsigned int> > m_graMatrix;	//邻接矩阵： 值表示对应边的权值
	


public:
	std::list<std::string> res;	//如果是有向无环图，存放拓扑排序的结果

public:
	//将string对应成int
	void initVertexes(const std::map<std::string, std::vector<std::string> > & myMap);

	//初始化图，邻接表，为图添加线
	void initGraphTable(const std::map<std::string, std::vector<std::string> > & myGra);
	
	//初始化图，邻接矩阵，添加有权线
	void initGraphMatrix(unsigned int **myMatrix, unsigned int rows, unsigned int cols);
	void initGraphMatrix(std::vector<std::vector<unsigned int> > & myMatrix);
	//打印图m_graTable
	void printGraTable();
	void printGraMatrix();
	//通过顶点的编号返回名称
	std::string getNameById(const unsigned & id);
	//通过顶点的名称返回编号
	unsigned getIdByName(const std::string & name);
	//返回图中节点数量
	unsigned int getVertexes();
	

	//返回图中边数量
	unsigned int getEdges();
	
	

	void addEdge(unsigned int x, unsigned int y);
	


	bool hasEdge(unsigned int x, unsigned int y);
	

	//Kahn算法
	bool isTopologySortingByKahn();
	//DFS算法
	bool isTopologySortingByDFS();

	//*************************图的遍历****************************************
	//1. 深度优先遍历DFS
	std::vector<unsigned> DFSByRecursion(const unsigned int & v)const;
	//2.广度优先遍历BFS
	std::vector<unsigned> BFS(const unsigned & v)const;


	//******************************最短路径**********************************
	//1. 基于BFS的单源最短路径算法
	std::vector<unsigned int> shortestPathByBFS(const unsigned & src);


	//2.1 Dijkstra算法

	std::vector<unsigned int> shortestPathByDijkstra(const unsigned & src);

private:
	void depthFirstSearchCore(unsigned int &ver, std::vector<bool> &visited, std::vector<bool> &onStack, std::vector<unsigned int> &edgeTo,std::stack<unsigned int> &reversePost, std::stack<unsigned int> &cycle);
	
	void DFSByRecursionCore(const unsigned int & v, std::vector<bool> & marked, std::vector<unsigned> & ordered) const;

	
};




#endif
