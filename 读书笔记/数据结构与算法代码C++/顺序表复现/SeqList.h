# include <cstdlib>
# include <iostream>
using namespace std;



const int defaultSize=100;

template <class T>
class SeqList{

    private:
        int last;
        T * data;
        int maxSize;
    public:
        SeqList(int sz=defaultSize);

        ~SeqList(){delete [] data;}

        void input();
        void output();

};