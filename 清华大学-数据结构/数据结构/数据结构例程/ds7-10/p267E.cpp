//¶Ôp267µÄ²¹³ä
#include "P267.cpp"
template <class NameType, class DistType> 
void Graph<NameType,DistType>::InsertVertex ( const NameType & vertex )
{
	NodeTable[NumVertices].data=vertex;
	NodeTable[NumVertices].adj=NULL;
	NumVertices++;
}
template <class NameType, class DistType> 
void Graph<NameType,DistType>::InsertEdge ( const int v1, const int v2, const DistType weight )
{
	Edge<NameType,DistType> *p=new Edge<NameType,DistType>;
	p->dest=v2;
	p->cost=weight;
	p->link=NodeTable[v1].adj;
	NodeTable[v1].adj=p;
	NumEdges++;
}
