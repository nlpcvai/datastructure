#include <iostream.h>
#include <stdlib.h>
#include <string.h>
#define NULL  0
#define HEAD  0
#define INTGR 1
#define CH    2
#define LST   3

class GenList;

class GenListNode{
  friend class GenList;
  private:
    int utype;
    GenListNode * tlink;
    union{
      int ref;
      int intgrinfo;
      char charinfo;
      GenListNode * hlink;
      } value;
  public:
    GenListNode(int v):tlink(NULL){utype=1;value.intgrinfo=v;}
    GenListNode(char c):tlink(NULL){utype=2;value.charinfo=c;}
    void print(){if(utype==1)cout<<value.intgrinfo<<endl;if(utype==2)cout<<value.charinfo<<endl;}
    GenListNode(){}
    GenListNode & Info(GenListNode * elem);
    int nodetype(GenListNode * elem){
      return elem->utype;
      }
    void setInfo(GenListNode * elem,GenListNode & x);
  };

  GenListNode & GenListNode::Info(GenListNode *elem){
    GenListNode * pitem=new GenListNode;
    pitem->utype=elem->utype;
    pitem->value=elem->value;
    return * pitem;
    }

  void GenListNode::setInfo(GenListNode * elem,GenListNode & x){
    elem->utype=x.utype;
    elem->value=x.value;
    }


class GenList{
  private:
    GenListNode * first;
    GenListNode * Copy(GenListNode * ls);
    int depth(GenListNode * ls);
    int equal(GenListNode * s,GenListNode * t) const;
    void Remove(GenListNode * ls);
  public:
    GenList();
    ~GenList();
    GenListNode & Head();
    GenListNode * Tail();
    GenListNode * First();
    GenListNode * Next(GenListNode * elem);
    void Push(GenListNode & x);
    GenList & Addon(GenList & list,GenListNode & x);
    void setHead(GenListNode & x);
    void setNext(GenListNode * elem1,GenListNode * elem2);
    void setTail(GenList & list);
    void Copy(const GenList &l);
    int depth();
    int Creatlist(GenListNode * ls,char * s);
    void delvalue(GenListNode *,const int);
    int sever(char *,char *);
    friend int operator == (const GenList &,const GenList &);
    void print();
  };
  void GenList::print(){
    GenListNode *temp;
    temp=first->tlink;
    while(temp!=NULL){
     if(temp->utype==1)cout<<temp->value.intgrinfo<<endl;
     if(temp->utype==2)cout<<temp->value.charinfo<<endl;
      temp=temp->tlink;
     }
  }

  GenList::GenList(){
    GenListNode * first=new GenListNode;
    first->utype=0;
    first->value.ref=0;
    first->tlink=NULL;
    }

  GenListNode & GenList::Head(){
    GenListNode * temp;
    if(first->tlink==NULL){
      cout<<"Illegal head operation."<<endl;
      exit(1);
      }
      else{
	temp=new GenListNode;
	temp->utype=first->tlink->utype;
	if(temp->utype==0)
	  temp->value.ref=first->tlink->value.ref;
	  else if(temp->utype==1)
		 temp->value.intgrinfo=first->tlink->value.intgrinfo;
		 else if(temp->utype==2)
			temp->value.charinfo=first->tlink->value.charinfo;
			else temp->value.hlink=first->tlink->value.hlink;
      }
      return * temp;
    }


  GenListNode * GenList::Tail(){
    if(first->tlink==NULL){
      cout<<"Illegal tail operation."<<endl;
      exit(1);
      }
      return first->tlink;
    }

  GenListNode * GenList::First(){
    if(first->tlink==NULL) return NULL;
    else return first->tlink;
    }

  GenListNode * GenList::Next(GenListNode * elem){
    if(elem->tlink==NULL) return NULL;
      else return elem->tlink;
    }

  void GenList::Push(GenListNode & x){
    if(first->tlink==NULL)first->tlink=& x;
      else{
	x.tlink=first->tlink;
	first->tlink=& x;
	  }
    }

  GenList & GenList::Addon(GenList & list,GenListNode & x){
    GenList * newlist= new GenList;
    newlist->first->tlink=Copy(list.first);
    x.tlink=newlist->first->tlink;
    newlist->first->tlink=& x;
    return * newlist;
  }

  void GenList::setHead(GenListNode & x){
    first->tlink->utype=x.utype;
    if(x.utype==0)first->tlink->value.ref=x.value.ref;
      else if(x.utype==1)first->tlink->value.intgrinfo=x.value.intgrinfo;
	else if(x.utype==2)first->tlink->value.charinfo=x.value.charinfo;
	  else first->tlink->value.hlink=x.value.hlink;
    }

  void GenList::setNext(GenListNode * elem1,GenListNode * elem2){
    GenListNode * temp;
    while(elem1->tlink!=NULL){
      temp=elem1->tlink;
      elem1->tlink=temp->tlink;
      delete temp;
      }
    elem1->tlink=elem2;
    }

  void GenList::setTail(GenList & list){
    GenListNode * temp,* tem;
    temp=first->tlink->tlink;
    first->tlink->tlink=list.first->tlink;
    delete list.first;
    while(temp!=NULL){
      tem=temp;
      temp=temp->tlink;
      delete tem;
      }
    }

  void GenList::Copy(const GenList & l){
    first->tlink=Copy(l.first);
    }

  GenListNode * GenList::Copy(GenListNode * ls){
    GenListNode * q=NULL;
    if(ls!=NULL){
      q=new GenListNode;
      q->utype=ls->utype;
      switch(ls->utype){
	case HEAD:     q->value.ref=ls->value.ref;                   break;
	case INTGR:    q->value.intgrinfo=ls->value.intgrinfo;       break;
	case CH:       q->value.charinfo=ls->value.charinfo;         break;
	case LST:      q->value.hlink=Copy(ls->value.hlink);         break;
	}
      q->tlink=Copy(ls->tlink);
      }
    return q;
    }

  int GenList::depth(){
    return depth(first);
    }

  int GenList::depth(GenListNode * ls){
    if(ls->tlink==NULL)      return 1;
    GenListNode * temp=ls->tlink;
    int m=0;
    while(temp!=NULL){
      if(temp->utype==LST){
	int n=depth(temp->value.hlink);
	if(m<n)m=n;
	}
      temp=temp->tlink;
    }
    return m+1;
  }

  int operator == (const GenList & l,const GenList & m){
    return l.equal(l.first,m.first);
    }

  int GenList::equal(GenListNode * s,GenListNode * t) const {
    int x;
    if(s->tlink==NULL && t->tlink==NULL)         return 1;
    if(s->tlink!=NULL && t->tlink==NULL && s->tlink->utype==t->tlink->utype){
      if(s->tlink->utype==INTGR)
	if(s->tlink->value.intgrinfo==t->tlink->value.intgrinfo) x=1;
	  else x=0;
	else if(s->tlink->utype==CH)
	       if(s->tlink->value.charinfo==t->tlink->value.charinfo) x=1;
		 else x=0;
	  else x=equal(s->tlink->value.hlink,t->tlink->value.hlink);
      if(x) return equal(s->tlink,t->tlink);
      }
    return 0;
    }

  void GenList::delvalue(GenListNode * ls,const int x){
    if(ls->tlink!=NULL){
      GenListNode * p=ls->tlink;
      while(p!=NULL && (p->utype==INTGR||p->utype==CH) && (p->value.charinfo==x||p->value.intgrinfo==x)){
	ls->tlink=p->tlink;
	delete p;
	p=ls->tlink;
	}
      if(p!=NULL){
	if(p->utype==LST)delvalue(p->value.hlink,x);
	delvalue(p,x);
	}
      }
    }

  GenList::~GenList(){
    Remove(first);
    }

  void GenList::Remove(GenListNode * ls){
    ls->value.ref --;
    if(!ls->value.ref){
      GenListNode * y=ls;
      while(y->tlink!=NULL){
	y=y->tlink;
	if(y->utype==LST) Remove(y->value.hlink);
	}
      }
     else{
       GenListNode * y=ls,* temp;
       while(y!=NULL){
	 temp=y;
	 y=y->tlink;
	 delete temp;
	 }
      }
    }

  int GenList::Creatlist(GenListNode * ls,char * s){
    char * sub,* hsub;
    int tag;
    ls=new GenListNode();
    ls->utype=HEAD;
    ls->value.ref=1;
    if(strlen(s)==0||!strcmp(s,"()"))ls->tlink=NULL;
      else{
	for(int i=0;i<strlen(s)-1;i++)  *(sub+i)=*(s+i+1);
	GenListNode * p=ls;
	while(strlen(sub)!=0){
	  p=p->tlink=new GenListNode();
	  if(sever(sub,hsub)){
	    if(hsub[0]!='('&&hsub[0]!='\''){
	      p->utype=INTGR;
	      p->value.intgrinfo=atoi(hsub);
	      }
	      else if(hsub[0]!='('&&hsub[0]!='\''){
		p->utype=CH;
		p->value.charinfo=*hsub;
		}
		else{
		  p->utype=LST;
		  this->Creatlist(p->value.hlink,hsub);
		  }
		}
		else return 0;
	      }
	    p->tlink=NULL;
	  }
	return 1;
      }

  int GenList::sever(char * str1,char * hstr1){
    char ch=str1[0];
    int n=strlen(str1);
    int i=0,k=0;
    while(i<n&&(ch!=','||k!=0)){
      ch=str1[i];
      i++;
      if(ch==')')k--;
      }
    if(i<n){
      for(int m=0;m<i;m++) hstr1[m]=str1[m];
      str1=str1+i;
      return 1;
      }
    else if(k!=0)return 0;
	   else{
	      strcpy(hstr1,str1);
	      str1=0;
	      return 1;
	      }
    }





void main(){
  GenListNode g1(34),g2('f'),g3(100),*p;
  GenList* gl=new GenList();
  GenList* gm=new GenList();
  (*gl).Push(g1);
  (*gl).print();
  (*gl).setHead(g1);
  (*gl).print();
  (*gl).setNext(&g1,&g2);
  (*gl).print();
  cout<<(*gl).depth()<<endl;
  (*gm).setHead(g3);
  (*gm).print();
  (*gl).setTail(*gm);
  (*gl).print();
  }