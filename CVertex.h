#ifndef CVERTEX_H_
#define CVERTEX_H_

#include <iostream>
#include <limits>
#define INFINITY 65535

class CVertex
{
public:
	//Ĭ�Ϲ��캯��
	CVertex(unsigned distance = INFINITY);
	//��������
	~CVertex();
private:
	std::string name;
	unsigned int id;
	unsigned distance;


public:
	std::string getName()const;
	unsigned getId()const;
	void setName(const std::string & name);
	void setId(const unsigned & id);
	unsigned getDistance()const;
	void setDistance(const unsigned & dis);

private:




};



#endif



