//HString.h ×Ö·û´®µÄÀà£¨HStringÀà£©
#ifndef _HSTRING_H_
#define _HSTRING_H_
class HString
{
	friend class BMMatching;
private:
	char *ch;
	int length;
public:
	HString()
	{
		ch=NULL;
		length=0;
	}
	HString(const char* str)
	{
		length=strlen(str);
		ch=new char[length];
		assert(ch!=NULL);
		for(int i=0; i<length; i++)
			ch[i]=str[i];
	}
	HString(const HString &S)
	{
		length=S.length;
		ch=new char[length];
		assert(ch!=NULL);
		for(int i=0; i<length; i++)
			ch[i]=S.ch[i];
	}
	~HString()
	{
		ClearString();
	}
	void ClearString()
	{
		if(ch!=NULL)
		{
			delete[]ch;
			ch=NULL;
		}
		length=0;
	}
	void StrAssign(const char* str)
	{
		ClearString();
		length=strlen(str);
		if(length)
		{
			ch=new char[length];
			assert(ch!=NULL);
			for(int j=0; j<length; j++)
				ch[j]=str[j];
		}
	}
	void StrCopy(const HString &S)
	{
		ClearString();
		ch=new char[S.length];
		assert(ch!=NULL);
		for(int i=0; i<S.length; i++)
			ch[i]=S.ch[i];
		length=S.length;
	}
	bool StrEmpty()const
	{
		return length==0;
	}
	int StrCompare(const HString &S)const
	{
		for(int i=0; i<length && i<S.length; ++i)
			if(ch[i]!=S.ch[i])
				return ch[i]-S.ch[i];
		return length-S.length;
	}
	int StrLength()const
	{
		return length;
	}
	void Concat(const HString &S1, const HString &S2)
	{
		int i;
		ClearString();
		length=S1.length+S2.length;
		ch=new char[length];
		assert(ch!=NULL);
		for(i=0; i<S1.length; i++)
			ch[i]=S1.ch[i];
		for(i=0; i<S2.length; i++)
			ch[S1.length+i]=S2.ch[i];
	}
	bool SubString(HString &Sub, int pos, int len)const
	{
		if(pos<1 || pos>length || len<0 || len>length-pos+1)
			return false;
		Sub.ClearString();
		if(len)
		{
			Sub.ch=new char[len];
			assert(Sub.ch!=NULL);
			for(int i=0; i<len; i++)
				Sub.ch[i]=ch[pos-1+i];
				
			Sub.length=len;
		}
		return true;
	}
	bool StrInsert(int pos, const HString &S)
	{
		int i;
		char *p;
		if(pos<1 || pos>length+1)
			return false;
		if(S.length)
		{
			p=new char[length+S.length];
			
			assert(p!=NULL);
			length+=S.length;
			for(i=0; i<pos-1; i++)
				p[i]=ch[i];
			for(i=0; i<S.length; i++)
				p[pos-1+i]=S.ch[i];
			for(i=pos-1; i<length; i++)
				p[i+S.length]=ch[i];
			delete[]ch;
			ch=p;
		}
		return true;
	}
	bool StrDelete(int pos, int len)
	{
		int i;
		char *p;
		if(length<pos+len-1)
			return false;
		p=new char[length-len];
		assert(p!=NULL);
		for(i=0; i<pos-1; i++)
			p[i]=ch[i];
		for(i=pos-1; i<length-len; i++)
			p[i]=ch[i+len];
		length-=len;
		delete[]ch;
		ch=p;
		return true;
	}
	void StrPrint()const
	{
		for(int i=0; i<length; i++)
			cout<<ch[i];
		cout<<endl;
	}
	int Index(const HString &S, int pos)const
	{
	 
		HString sub;
		if(pos>0)
			for(int i=pos; i<=length-S.length+1; i++)
			{
				SubString(sub, i, S.length);
				
				if(sub.StrCompare(S)==0)
					return i;
			}
		return 0;
	}
	bool Replace(const HString &T, const HString &V)
	{
	 
		int i=1;
		if(!T.length)
			return false;
		while(i)
		{
			i=Index(T, i);
			if(i)
			{
				StrDelete(i, T.length);
				StrInsert(i, V);
				i+=V.length;
			}
		};
		return true;
	}
};
#endif

