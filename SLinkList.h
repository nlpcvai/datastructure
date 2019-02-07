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
    
}
