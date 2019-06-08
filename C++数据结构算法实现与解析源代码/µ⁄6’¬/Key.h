//Key.h 键树关键字和数据的结构及函数
#ifndef _KEY_H_
#define _KEY_H_
struct K
{
	char ch[MAX_KEY_LEN];
	int num;
};
template<typename D>struct Record
{
	K key;
	D others;
};
void InputKey(K &key)
{
	cin>>key.ch;
	key.num=strlen(key.ch);
}
#endif

