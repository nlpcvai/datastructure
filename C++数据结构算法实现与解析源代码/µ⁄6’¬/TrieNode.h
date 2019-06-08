//TrieNode.h Trie树结点的存储结构
#include "Key.h"
#ifndef _TrieNODE_H_
#define _TrieNODE_H_
template<typename D>struct TrieNode
{
	Record<D> *rcptr;
	TrieNode<D> *ptr[LENGTH];
	
	int pnum;
};
#endif

