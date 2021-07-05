#include "War300.h"
#include <iostream>
#include <string>

int main()
{
    int n;
    cin>>n;
    for(int j=1;j<=n;j++){
        Init();
        cout<<"Case:"<<j<<endl;
        int M,cost[5];
        cin>>M;
        for(int i=0;i<5;i++){
            cin>>cost[i];
        }
        Base red(M,1),blue(M,0);
        Base::start(red,blue,cost);
    }
}