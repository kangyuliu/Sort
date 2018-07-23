#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <limits>
#include "DireGraph.h"



//≤‚ ‘”√¿˝
void test01()
{
	DireGraph dg;
	std::map<std::string, std::vector<std::string> >  myGra;
	//myGra["d0"].push_back("d0");
	myGra["d0"].push_back("d1");
	myGra["d1"].push_back("d2");
	myGra["d1"].push_back("d4");
	//myGra["d2"].push_back("d0");
	//myGra["d2"].push_back("d2");
	myGra["d2"].push_back("d3");
	myGra["d2"].push_back("d4");
	myGra["d3"].push_back("d5");



	dg.initVertexes(myGra);
	dg.initGraphTable(myGra);
	dg.printGraTable();

	std::cout << "edges = " << dg.getEdges() << std::endl;
	std::cout << "is topological: " <<  dg.isTopologySortingByDFS() << std::endl;

	std::vector<unsigned> ordered = dg.DFSByRecursion(0);
	std::cout << "DFS:\n";
	for(size_t i=0; i< ordered.size(); i++)
		std::cout << ordered[i] << " ";
	std::cout << std::endl;

	ordered = dg.BFS(0);
	std::cout << "BFS:\n";
	for(size_t i=0; i< ordered.size(); i++)
		std::cout << ordered[i] << " ";
	std::cout << std::endl;

	std::cout << "res:\n";
	auto iter = dg.res.begin();
	for(;iter != dg.res.end(); iter++)
		std::cout << *iter << " ";
	std::cout << std::endl;

	std::cout << "shortest path:\n";
	std::vector<unsigned int> dis = dg.shortestPathByBFS(1);

	for(size_t i=0; i<dis.size();i++)
		std::cout << dis[i] << " ";
	std::cout << std::endl;
}

void test02()
{
	
	unsigned int arr1[] = {0,1,12,INFINITY,INFINITY,INFINITY};
	unsigned int arr2[] = {INFINITY,0,9,3,INFINITY,INFINITY};
	unsigned int arr3[] =	{INFINITY,INFINITY,0,INFINITY,5,INFINITY};
	unsigned int arr4[] =	{INFINITY,INFINITY,4,0,13,15};
	unsigned int arr5[] =	{INFINITY,INFINITY,INFINITY,INFINITY,0,4};
	unsigned int arr6[] =	{INFINITY,INFINITY,INFINITY,INFINITY,INFINITY,0};

	
	std::vector<unsigned int> v1(arr1,arr1+6);
	std::vector<unsigned int> v2(arr2,arr2+6);
	std::vector<unsigned int> v3(arr3,arr3+6);
	std::vector<unsigned int> v4(arr4,arr4+6);
	std::vector<unsigned int> v5(arr5,arr5+6);
	std::vector<unsigned int> v6(arr6,arr6+6);


	std::vector<std::vector<unsigned int> > myMatrix;
	myMatrix.push_back(v1);
	myMatrix.push_back(v2);
	myMatrix.push_back(v3);
	myMatrix.push_back(v4);
	myMatrix.push_back(v5);
	myMatrix.push_back(v6);

	DireGraph dg(6);
	dg.initGraphMatrix(myMatrix);
	dg.printGraMatrix();
	std::vector<unsigned int> dis = dg.shortestPathByDijkstra(0);
	for(size_t i=0; i < dis.size();i++)
		std::cout << dis[i] << " ";
	std::cout << std::endl;
}
//÷˜∫Ø ˝
int main()
{
	

	//test01();
	test02();
	return 0;
}