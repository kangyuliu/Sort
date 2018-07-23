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
	//���캯��
	DireGraph();

	DireGraph(unsigned int numVertexes);
	//��������
	~DireGraph();
private:
	unsigned int m_numVertexes;   //ͼ�Ľڵ�����
	unsigned int m_numEdges;	//ͼ�ıߵ�����
	
	std::vector<CVertex> m_vertexes; //���㼯

	std::vector<std::vector<unsigned int> > m_graTable;	//�ڽӱ�ֵ��ʾ��Ӧ����ı��

	std::vector<std::vector<unsigned int> > m_graMatrix;	//�ڽӾ��� ֵ��ʾ��Ӧ�ߵ�Ȩֵ
	


public:
	std::list<std::string> res;	//����������޻�ͼ�������������Ľ��

public:
	//��string��Ӧ��int
	void initVertexes(const std::map<std::string, std::vector<std::string> > & myMap);

	//��ʼ��ͼ���ڽӱ�Ϊͼ�����
	void initGraphTable(const std::map<std::string, std::vector<std::string> > & myGra);
	
	//��ʼ��ͼ���ڽӾ��������Ȩ��
	void initGraphMatrix(unsigned int **myMatrix, unsigned int rows, unsigned int cols);
	void initGraphMatrix(std::vector<std::vector<unsigned int> > & myMatrix);
	//��ӡͼm_graTable
	void printGraTable();
	void printGraMatrix();
	//ͨ������ı�ŷ�������
	std::string getNameById(const unsigned & id);
	//ͨ����������Ʒ��ر��
	unsigned getIdByName(const std::string & name);
	//����ͼ�нڵ�����
	unsigned int getVertexes();
	

	//����ͼ�б�����
	unsigned int getEdges();
	
	

	void addEdge(unsigned int x, unsigned int y);
	


	bool hasEdge(unsigned int x, unsigned int y);
	

	//Kahn�㷨
	bool isTopologySortingByKahn();
	//DFS�㷨
	bool isTopologySortingByDFS();

	//*************************ͼ�ı���****************************************
	//1. ������ȱ���DFS
	std::vector<unsigned> DFSByRecursion(const unsigned int & v)const;
	//2.������ȱ���BFS
	std::vector<unsigned> BFS(const unsigned & v)const;


	//******************************���·��**********************************
	//1. ����BFS�ĵ�Դ���·���㷨
	std::vector<unsigned int> shortestPathByBFS(const unsigned & src);


	//2.1 Dijkstra�㷨

	std::vector<unsigned int> shortestPathByDijkstra(const unsigned & src);

private:
	void depthFirstSearchCore(unsigned int &ver, std::vector<bool> &visited, std::vector<bool> &onStack, std::vector<unsigned int> &edgeTo,std::stack<unsigned int> &reversePost, std::stack<unsigned int> &cycle);
	
	void DFSByRecursionCore(const unsigned int & v, std::vector<bool> & marked, std::vector<unsigned> & ordered) const;

	
};




#endif
