#include "CVertex.h"

CVertex::CVertex(unsigned dis) : distance(dis)
{

}

CVertex::~CVertex()
{

}

std::string CVertex::getName() const
{
	return name;
}

unsigned CVertex::getId() const
{
	return id;
}

void CVertex::setName(const std::string & name)
{
	this->name = name;
}

void CVertex::setId(const unsigned & id)
{
	this->id = id;
}

unsigned CVertex::getDistance() const
{
	return distance;
}

void CVertex::setDistance(const unsigned & dis)
{
	distance = dis;
}
