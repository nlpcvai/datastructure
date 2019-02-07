template <class T>
class SLinkList
{
private:
    struct Tcomp
    {
        T data;
        int cur;
    };
    Tcomp *sls;
    int av;
    int sl;
    int maxlen;
public:
    SLinkList(int maxsz = 100);
    ~SLinkList();
    void CreateList(int n);
    void Insert(int i, T e);
    T Delete(int i);
    T GetElem(int i);
    int Locate(T e);
    int Empty();
    int Full();
    int Length();
    void Clear();
    void ListDisplay();

};

template <class T>
SLinkList<T>::SLinkList(int maxsz):maxlen(maxsz)
{
    sls = new Tcomp[maxlen];
    sl = -1;
    for(int i = 0; i < maxlen; i++
    sls[maxlen-1].cur = -1;
    av = 0;
}
template <class T>
SLinkList<T>::~SLinkList()
{
    delete[] sls;
}

template <class T>
void SLinkList<T>::CreateList(int n)
{
    int value;
    if(n > maxlen) throw "parameter is illegal";
    cout<<"please input"<<n<<"elements value: "<<endl;
    for(int i = 1; i <= n; i++)
    {
        cin>>value;
        Insert(i, value);
    }
}
