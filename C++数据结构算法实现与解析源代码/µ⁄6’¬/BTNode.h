//BTNode.h B树的3种模板结构
#ifndef _BTNODE_H_
#define _BTNODE_H_
template<typename D>struct Record
{
	KeyType key;
	D others;
};
template<typename D>struct BTNode
{
	int keynum;
	BTNode<D> *parent;
	BTNode<D> *children[m+1];
	KeyType key[m+1];
	Record<D> *recptr[m+1];
};
template<typename D>struct Result
{
	BTNode<D> *pt;
	int i;
	bool tag;
};
#endif

