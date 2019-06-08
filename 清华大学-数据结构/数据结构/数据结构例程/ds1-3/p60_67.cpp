//Test is T60_67.cpp

#include <string.h>
#include <iostream.h>

const int maxLen = 128;			//�ַ�������󳤶�

class String {
	//����: ��������ַ���һ���������С�
public:
    String ( const String & ob);		//���ƹ��캯��, ��һ�����е��ַ�������ob����һ�����ַ�����
    String ( const char *init );		//���캯��, ����һ����󳤶�ΪmaxLen, ��init��ʼ�������ַ�����
    String ( );					//���캯��, ����һ����󳤶�ΪmaxLen, ʵ�ʳ���Ϊ0���ַ�����
    ~String ( ) { delete [ ] ch, f; }		//�����������ͷŶ�̬����Ĵ��ռ䡣
    int Length ( ) const { return curLen; }		//�������ش�*this�ĳ��ȡ�
    int String::fastFind ( String & pat ) const;
    void String::fail ( );
    String &operator ( ) ( int pos, int len );
	 //�� 0<=pos<=maxLen��0(len��pos+len<maxLen ʱ, ���ڴ�*this�д�pos��ָ��
	 //λ�ÿ�ʼ����ȡlen���ַ�����Ӵ����ء�
    int operator == ( const String &ob ) const { return strcmp (ch, ob.ch) == 0; }
	 //���Ƿ���ȡ�����*this��ob���, ��������1, ����������0��
    int operator != ( const String &ob ) const { return strcmp (ch, ob.ch) != 0; }
	 //���Ƿ񴮲���ȡ�����*this��ob�����, ��������1, ����������0��
    int operator ! ( ) const { return curLen == 0; }
	 //���Ƿ񴮿ա�����*thisΪ��, ��������1, ����������0��
    String &operator = ( const String & ob );
	 //��ob��ֵ����ǰ��*this
    String &operator += ( const String & ob );
	 //�� length(*this)+length(ob)<=maxLen, ��Ѵ�ob���ڴ�*this���档
    char &operator [ ] ( int i );
	 //ȡ*this�ĵ�i���ַ���
    int Find ( String &pat ) const;
	 //����pat�봮*this�е�ĳ���Ӵ�ƥ��, �������ص�1��ƥ��ʱ�Ӵ��ڴ�*this�е�
	 //λ�á�����patΪ�ջ��ڴ�*this��û��ƥ���Ӵ�, ��������-1��
    friend ostream & operator << (ostream& out , String s);
private:
    int curLen, *f ;								//���ĳ���
    char *ch;									//���������
};

#include <iostream.h>
#include <process.h>

String::String ( const String &ob ) {					//�����ƹ��캯��
    ch = new char[maxLen+1];						//�����ַ�������
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = ob.curLen;							//������
    strcpy ( ch, ob.ch );							//������
}

String::String ( const char *init ) {						//�����캯��
    ch = new char[maxLen+1];						//�����ַ�������
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = strlen (init);							//������
    strcpy ( ch, init );								//������
}

String::String ( ) {								//�����캯��
    ch = new char[maxLen+1];						//�����ַ�������
    if ( !ch ) { cout << "Allocation Error\n";  exit(1); }
    curLen = 0;								//������
    ch[0] = '\0';								//�մ�
}

String &String::operator ( ) ( int pos, int len ) { 				//���Ӵ�
    String *temp = new String;						//����һ���մ�
    if ( pos < 0 || pos+len-1 >= maxLen || len < 0 ) {			//������������ȡ�Ӵ�
       temp->curLen = 0;  temp->ch[0] = '\0';
    }
    else {
	 if ( pos+len-1>=curLen ) len = curLen - pos;			//�Ӵ��ַ���������ȡһ����
	 temp->curLen = len;
	 for ( int i=0, j=pos; i<len; i++, j++ ) temp->ch[i] = ch[j];
	 temp->ch[len] = '\0';
    }
    return *temp;
}

String &String::operator = ( const String &ob )	{			//�����ز���: ����ֵ
    if ( &ob != this ) {							//�����������Ϊ���Ҹ�ֵ
	delete [ ] ch;								//ɾȥ��ǰ��
	ch = new char [maxLen+1];						//���·��䣬��һ���ַ���"\0"
	if ( ! ch ) {	cerr << "Out Of Memory!\n ";  exit (1);	}	//chΪ�գ�����ʧ��
	curLen = ob.curLen;
	strcpy ( ch, ob.ch );							//����
    }
    else  cout << "Attempted assignment of a String to itself!\n";
    return *this;
}

String &String::operator += ( const String &ob ) { 			//�����ز���: ������
    char * temp =ch;								//���潫Ҫ�����ַ����ĵ�ַ
    curLen += ob.curLen;							//������ĳ���
    ch = new char [maxLen+1];						//Ϊ���������洢
    if ( ! ch ) { cerr << "Out Of Memory!\n ";  exit (1) ; }
    strcpy ( ch, temp );							//�������ǰһ����
    strcat ( ch, ob.ch );							//������ĺ�һ����
    delete [ ] temp;  return *this;						//�ͷžɴ洢�����ؽ����
}

char &String::operator [ ] ( int i ) {					//ȡ*this�ĵ�i���ַ�
    if ( i < 0 && i >= curLen ) { cout << "Out Of Boundary!\n ";  exit (1) ; }
    return ch[i];
}

int String::Find ( String &pat ) const {

//���ڴ�s(*this)���Ҳ����봮patƥ����Ӵ�, ��������
//-1, ���򷵻�pat��*this�е�һ��ƥ���λ�á�
     char *p = pat.ch, *s = ch;  int i = 0;		//i�ǿ�ʼλ��
     if ( *p && *s )					//������������
	while ( i <= curLen - pat.curLen )
	     if ( *p++ == *s++ ) {
		  if ( !*p ) return i;	  		//��patɨ����, *p = 0
	     }						//ƥ��ɹ�
	     else { i++;  s = ch+i;  p = pat.ch; }		//��ƥ��
	     //sָ���1, pָ��ص���ʼλ������һ�˱Ƚ�
     return -1;			//patΪ�ջ���s���Ҳ�����   		  ͼ2.14  ����2.13��ƥ�����
}

int String::fastFind ( String & pat ) const {
     int posP = 0,  posT = 0;					//��������ɨ��ָ��
     int lengthP = pat.curLen,  lengthT = curLen;			//ģʽ��Ŀ�괮�ĳ���
     while ( posP < lengthP && posT < lengthT )			//������ɨ��
	 if ( pat.ch[posP] == ch[posT] ) {				//��Ӧ�ַ�ƥ��
	    posP++;  posT++;
	 }
	 else if ( posP == 0 ) posT++;
	      else posP = pat.f [posP-1]+1;
     if ( posP < lengthP ) return -1;					//ƥ��ʧ��
     else return posT - lengthP;					//ƥ��ɹ�
}

void String::fail ( ) {								//��ģʽp(*this), ����ʧЧ����
    int lengthP = curLen;
    f [0] = -1;
    for ( int j=1; j<lengthP; j++ ) {					//����f [j]
	int i = f [j-1];
	while ( *(ch+j) != *(ch+i+1) && i >= 0 ) i = f [i];		//���Ƽ���f [j]
	if ( *(ch+j) == *(ch+i+1) ) f [j] = i+1;
	else f [j] = -1;
    }
}

ostream & operator << ( ostream & out, String s ) {
    if ( s.curLen == 0 ) out << "It is empty!";
    else {
	 for (int i=0 ; i < s.curLen ; i++ ) out << s.ch[i];
    }
    return out;
}
