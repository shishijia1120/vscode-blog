


const int DefaultSize=26;
template<class Name,class Attribute>

class Dictionary{
    public:
        Dictionary(int size=DefaultSize);

        bool Member(Nmae name);

        Attribute * Search(Name name);

        void Insert(Name name,Attribute attr);

        void Remove(Name name);
};