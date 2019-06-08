//PosType.h 二维坐标位置类型结构体及重载的运算符
#ifndef _POSTYPE_H_
#define _POSTYPE_H_
struct PosType
{
	int x, y;
};
PosType operator+(const PosType p1, const PosType p2)
{
	PosType p;
	p.x=p1.x+p2.x;
	p.y=p1.y+p2.y;
	return p;
}
bool operator==(const PosType p1, const PosType p2)
{
	return p1.x==p2.x && p1.y==p2.y;
}
#endif

