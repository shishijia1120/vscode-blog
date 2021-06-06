# include <iostream>

const int ArSize=8;

int sum_arr(int arr[], int n);

int main(){
    using namespace std;
    int cookies[ArSize]={1,2,3,4,5,6,7,8};

    int sum=sum_arr(cookies,ArSize);
    cout<<"Total cookies eaten:"<<sum<<"\n";

    return 0;
}

int sum_arr(int arr[] ,int n){
    int total=0;
    for(int i=0;i<n;i++){
        total=total+arr[i];
    }
    return total;
}