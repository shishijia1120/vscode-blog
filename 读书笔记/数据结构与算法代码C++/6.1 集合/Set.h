
template <class T>
class Set{
    public:
        virtual Set()=0;
        virtual makeEmpty()=0;
        virtual bool addMember(const T x)=0;
        virtual bool delMember(const T x)=0;
        virtual Set<T> intersectWith(const Set<T>& R)=0;
        virtual Set<T> unionWith(const Set<T>& R)=0;
        virtual Set<T> differenceFrom(const Set<T>& R)=0;
        virtual bool Contains(const T x)=0;
        virtual bool subSet(const Set<T>& R)=0;
        virtual bool oprerator == (const Set<T>& R)=0;
};