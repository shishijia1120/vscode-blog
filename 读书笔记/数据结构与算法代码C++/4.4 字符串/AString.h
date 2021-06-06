// # ifndef ASTRING_H
// # define ASTRING_H

# include<iostream>
# include<string.h>

using namespace std;

const int defaultSize=128;

class AString {
    public:
        AString(int sz=defaultSize);

        AString(const char * init);

        AString(const AString& ob);

        ~AString(){delete []ch;}

        int Length()const{return curLength;}

        AString operator() (int pos,int len);

        int operator == (AString& ob)const {return strcmp(ch,ob.ch) == 0;}

        int operator != (AString& ob)const {return strcmp(ch,ob.ch) != 0;}

        int operator ! ()const {return curLength == 0;}

        AString& operator =(AString& ob);

        AString& operator += (AString& ob);

        char& operator [] (int i);

        int Find(AString& pat)const;

        void output();

        void input();

    private:
        char * ch;
        int curLength;
        int maxSize;
};





