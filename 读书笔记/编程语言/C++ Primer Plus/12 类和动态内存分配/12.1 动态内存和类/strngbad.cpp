# include <cstring>
# include <iostream>
# include "strngbad.h"
using std::cout;

void callme1(StringBad &);
void callme2(StringBad);

int StringBad::num_strings=0;

StringBad::StringBad(const char * s)
{
    len=std::strlen(s);
    str=new char[len+1];
    std::strcpy(str,s);
    num_strings++;
    cout << num_strings<<": \" "<< str <<"\"object created\n";

}

StringBad::StringBad()
{
    len=4;
    str=new char[4];
    std::strcpy(str,"C++");
    num_strings++;
    cout<<num_strings << ":\" "<< str <<"\"default object created\n";

}

StringBad::~StringBad()
{
        cout << "\" "<<str <<"\" object deleted,";
        --num_strings;
        cout<< num_strings<<"left \n";
        delete [] str;
}

std::ostream & operator << (std:: ostream & os,const StringBad & st)
{
    os << st.str;
    return os;
}


int main(){
    using std::endl;
    {
        cout<<"String an inner block.\n";
        StringBad headline1("Celery Stalks at Midnight");
        StringBad headline2("Lettuce Prey");
        StringBad sports("Spinach Leaves Bowl for Dollars");
        
        cout <<"headline1:"<<headline1<<endl;
        cout <<"headline2:"<<headline2<<endl;
        cout <<"sports:"<<sports<<endl;

        callme1(headline1);
        cout <<"headline1:"<<headline1<<endl;
        callme2(headline2);
        cout <<"headline2:"<<headline2<<endl;
        
        cout<<"Initialize one object to anothor:\n";

        StringBad sailor=sports;
        cout<<"sailor:"<<sailor<<endl;
        cout<< "Assign one object to anothor:\n";

        StringBad knot;
        knot=headline1;
        cout<<"knot:"<<knot<<endl;
        cout<<"Exiting the block.\n";
    }

    cout<<"End of main()\n";
    return 0;

}

void callme1(StringBad & rsb)
{
    cout << "String passed by referencr:\n";
    cout<<"  \" " << rsb << "\" \n";
}

void callme2(StringBad sb)
{
    cout << "String passed by value:\n";
    cout << " \" " << sb << "\" \n";
}