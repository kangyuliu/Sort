#include "DireGraph.h"
#include <queue>
#include <limits>
DireGraph::DireGraph()
{
	/*for(unsigned int i=0; i < m_numVertexes;i++)
	{
		m_graTable.push_back(std::vector<unsigned int>());
	}*/
}



DireGraph::DireGraph(unsigned int numVertexes) : m_numVertexes(numVertexes),m_numEdges(0)
{
	for(unsigned int i=0; i< m_numVertexes; i++)
	{
		m_graMatrix.push_back(std::vector<unsigned int>(m_numVertexes,INFINITY));
	}

	
}

DireGraph::~DireGraph()
{

}



void DireGraph::initVertexes(const std::map<std::string, std::vector<std::string> > & myMap)
{
	std::set<std::string> mySet;		//存放图中的节点

	//遍历图中的节点
	std::map<std::string, std::vector<std::string> >::const_iterator map_iter;
	for(map_iter = myMap.begin(); map_iter != myMap.end(); map_iter++)
	{
		mySet.insert(map_iter->first);
		for(size_t i=0; i< map_iter ->second.size(); i++)
		{
			mySet.insert(map_iter->second[i]);
		}
	}

	m_numVertexes = mySet.size();


	//初始化m_graTable
	for(unsigned int i=0; i < m_numVertexes;i++)
	{
		m_graTable.push_back(std::vector<unsigned int>());
	}


	//初始化m_graMatrix
	for(unsigned int i=0; i < m_numVertexes; i++)
	{
		m_graMatrix.push_back(std::vector<unsigned int>(m_numVertexes,INFINITY));
	}

	for(size_t i=0; i < m_graMatrix.size(); i++)
	{
		for(size_t j=0; j < m_graMatrix[i].size(); j++)
		{
			if(i == j)
				m_graMatrix[i][j] = 0;
		}
	}



	std::set<std::string>::iterator set_iter;
	unsigned int i=0;
	for(set_iter = mySet.begin(); set_iter!= mySet.end(); set_iter++,i++)
	{
		CVertex v;
		v.setName(*set_iter);
		v.setId(i);
		m_vertexes.push_back(v);

		
	}


	

}


void DireGraph::initGraphTable(const std::map<std::string, std::vector<std::string> > & myGra)
{
	std::map<std::string, std::vector<std::string> >::const_iterator iter;
	for(iter = myGra.begin(); iter != myGra.end(); iter++)
	{

		unsigned int x = getIdByName(iter->first);
		for(size_t i=0; i < iter->second.size(); i++)
		{
			unsigned int y = getIdByName(iter->second[i]);
			addEdge(x,y);
		}
	}
}


void DireGraph::initGraphMatrix(unsigned int **myMatrix, unsigned int rows, unsigned int cols)
{
	for(unsigned int row = 0; row < rows; row++)
	{
		for(unsigned int col=0; col < cols; col++)
		{
			m_graMatrix[row][col] = myMatrix[row][col];
		}
	}
}

void DireGraph::initGraphMatrix(std::vector<std::vector<unsigned int> > & myMatrix)
{
	m_graMatrix = myMatrix;
}

void DireGraph::printGraTable()
{
	for(unsigned int i=0; i < m_graTable.size(); i++)
	{
		std::cout << i << ": ";
		for(size_t j=0; j < m_graTable[i].size(); j++)
		{
			std::cout << m_graTable[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void DireGraph::printGraMatrix()
{
	for(size_t row = 0; row < m_graMatrix.size(); row++)
	{
		for(size_t col = 0; col < m_graMatrix[row].size(); col++)
		{
			std::cout << m_graMatrix[row][col] << "	";
		}
		std::cout << std::endl;
	}
}

std::string DireGraph::getNameById(const unsigned & id)
{
	assert(id < m_numVertexes);
	for(size_t i=0; i < m_vertexes.size(); i++)
	{
		if(m_vertexes[i].getId() == id)
		{
			return m_vertexes[i].getName();
		}
			
	}
}

unsigned DireGraph::getIdByName(const std::string & name)
{
	for(size_t i=0; i < m_vertexes.size(); i++)
	{
		if(m_vertexes[i].getName() == name)
		{
			return m_vertexes[i].getId();
		}
	}
}

unsigned int DireGraph::getVertexes()
{
	return m_numVertexes;
}


//返回图中边数量
unsigned int DireGraph::getEdges()
{
	return m_numEdges;
}

void DireGraph::addEdge(unsigned int x, unsigned int y)
{
	assert(x < m_numVertexes);
	assert(y < m_numVertexes);
	//release assert 不好使
	m_graTable[x].push_back(y);
	m_numEdges++;
}


bool DireGraph::hasEdge(unsigned int x, unsigned int y)
{
	assert(x < m_numVertexes);
	assert(y < m_numVertexes);
	for(size_t i=0; i<m_graTable[x].size(); i++)
	{
		if(m_graTable[x][i] == y)
			return true;
	}
	return false;
}

//Kahn算法
bool DireGraph::isTopologySortingByKahn()
{	
	std::list<unsigned int> result;	//存储结果
	std::queue<unsigned int> setOfZeroIndegree;	//存储入度为0的顶点
	std::vector<unsigned int> indegrees(m_numVertexes,0);
		
	//初始化每个顶点的入度
	for(size_t i=0; i<m_graTable.size(); i++)
	{
		for(size_t j=0; j < m_graTable[i].size();j++)
		{
			indegrees[m_graTable[i][j]]++;
				
		}
	}

	for(size_t i=0; i < indegrees.size(); i++)
	{
		if(indegrees[i] == 0)
			setOfZeroIndegree.push(i);
	}


	while(!setOfZeroIndegree.empty())
	{
		unsigned int x = setOfZeroIndegree.front();
		setOfZeroIndegree.pop();
		result.push_back(x);

		for(size_t y=0; y < m_graTable[x].size();y++)
		{
			m_numEdges--;
			if(--indegrees[m_graTable[x][y]] == 0)
			{
				setOfZeroIndegree.push(m_graTable[x][y]);
			}
		}
	}
		
	if(m_numEdges == 0)
	{
		std::list<unsigned int>::iterator iter;
		for(iter = result.begin(); iter != result.end(); iter++)
		{
			res.push_back(getNameById(*iter));
		}
		return true;
	}

	return false;
}

//DFS算法
bool DireGraph::isTopologySortingByDFS()
{
	std::vector<bool> visited(m_numVertexes,false);
	std::vector<bool> onStack(m_numVertexes,false);
	std::vector<unsigned int> edgeTo(m_numVertexes,false);
	std::stack<unsigned int> reversePost;
	std::stack<unsigned int> cycle;	//存放环

	for(size_t i=0; i< m_graTable.size();i++)
	{
		if(!visited[i])
			depthFirstSearchCore(i,visited,onStack,edgeTo,reversePost,cycle);
	}


	if(cycle.empty())
	{ 
		while(!reversePost.empty())
		{
			unsigned int top = reversePost.top();
			reversePost.pop();
			std::string str = getNameById(top);
			res.push_back(str);
		}
		return true;
	}

	return false;

}

//*************************图的遍历****************************************
	//1. 深度优先遍历DFS
std::vector<unsigned int> DireGraph::DFSByRecursion(const unsigned int & v) const
{
	std::vector<bool> marked(m_numVertexes,false);  //标记顶点是否被访问
	std::vector<unsigned int> ordered;	//存放遍历顺序

	DFSByRecursionCore(v, marked, ordered);

	return ordered;
}

std::vector<unsigned> DireGraph::BFS(const unsigned & v) const
{
	std::vector<bool> marked(m_numVertexes, false);
	std::vector<unsigned> ordered;
	std::queue<unsigned> que;

	
	ordered.push_back(v);
	que.push(v);
	marked[v] = true;

	while(!que.empty())
	{
		unsigned front = que.front();
		que.pop();
		for(size_t i=0; i < m_graTable[front].size(); i++)
		{
			if(!marked[m_graTable[front][i]])
			{
				ordered.push_back(m_graTable[front][i]);
				que.push(m_graTable[front][i]);
				marked[m_graTable[front][i]] = true;
			}
			

		}
	}
	
	return ordered;
}

std::vector<unsigned int> DireGraph::shortestPathByBFS(const unsigned & src)
{
	assert(src < m_numVertexes);

	std::vector<bool> marked(m_numVertexes, false);
	std::queue<unsigned int> que;

	std::vector<unsigned int> dis(m_numVertexes,INFINITY);	//初始所有节点的距离为无穷大
	dis[src] = 0;  //源节点距离为0

	


	marked[src] = true;
	que.push(src);

	while(!que.empty())
	{
		unsigned int front = que.front();
		que.pop();
		for(size_t i=0; i < m_graTable[front].size(); i++)
		{
			if(!marked[m_graTable[front][i]])
			{
				marked[m_graTable[front][i]] = true;
				dis[m_graTable[front][i]] = dis[front]+1;
				que.push(m_graTable[front][i]);
			}
			
		}
	}

	return dis;

}

std::vector<unsigned int> DireGraph::shortestPathByDijkstra(const unsigned & src)
{
	assert(src < m_numVertexes);
	std::vector<unsigned int> dis(m_numVertexes,INFINITY); //初始源点到其他顶点距离为无穷大
	dis[src] = 0;
	std::vector<bool> visited(m_numVertexes, false);
	
	for(unsigned int i =0; i < m_numVertexes; i++)
	{	
		unsigned int u = -1;
		unsigned int minVal = INFINITY;
		for(unsigned int j=0; j< m_numVertexes; j++)
		{
			if(!visited[j] && dis[j] < minVal)
			{
				u = j;
				minVal = dis[j];
			}
		}

		if(u == -1)
			break;

		visited[u] = true;

		for(unsigned int v = 0; v < m_numVertexes; v++)
		{
			if(!visited[v] && dis[u]+m_graMatrix[u][v] < dis[v])
			{
				dis[v] = dis[u] + m_graMatrix[u][v];
			}
		}

	}


	return dis;
}

void DireGraph::depthFirstSearchCore(unsigned int &ver, std::vector<bool> &visited, std::vector<bool> &onStack, std::vector<unsigned int> &edgeTo,std::stack<unsigned int> &reversePost, std::stack<unsigned int> &cycle)
{
	visited[ver] = true;
	onStack[ver] = true;

	for(size_t i=0; i < m_graTable[ver].size(); i++)
	{
		if(!cycle.empty())
			return;
		if(m_graTable[ver][i] == ver)
			continue;
		if(!visited[m_graTable[ver][i]])
		{
			edgeTo[m_graTable[ver][i]] = ver;
			depthFirstSearchCore(m_graTable[ver][i],visited,onStack,edgeTo,reversePost,cycle);
		}
		//已经被访问，且处于调用栈时，即存在环路
		else if(onStack[m_graTable[ver][i]])
		{
			cycle.push(m_graTable[ver][i]);
			for(unsigned int start = ver; start != m_graTable[ver][i]; start = edgeTo[start])
			{
				cycle.push(start);
			}
			cycle.push(m_graTable[ver][i]);
		}
	}

	reversePost.push(ver);
	onStack[ver] = false;
}

void DireGraph::DFSByRecursionCore(const unsigned int & v, std::vector<bool> & marked, std::vector<unsigned> & ordered) const
{
	marked[v] = true;
	ordered.push_back(v);
	for(size_t i=0; i < m_graTable[v].size(); i++)
	{
		//邻接顶点未被访问
		if(!marked[m_graTable[v][i]])
		{
			DFSByRecursionCore(m_graTable[v][i], marked, ordered);
		}
	}
}
