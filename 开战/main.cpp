#include "War300.h"
#include <iostream>
#include <string>

int main()
{
    cout<<fixed;
    cout.precision(2);
    int t;cin>>t;
    for(int j=1;j<=t;j++){
        Init();
        cout<<"Case:"<<j<<endl;
        int M,N,K,T;
        cin>>M>>N>>K>>T;
        City::set_totalCity(N);
        int cost[5];
        for(int i=0;i<5;i++){
            cin>>cost[i];
        }
        int force[5];
        for (int i = 0; i < 5; i++) {
            cin>>force[i];
        }
        Dragon::set_force(force[0]);Ninja::set_force(force[1]);Iceman::set_force(force[2]);Lion::set_force(force[3]);Wolf::set_force(force[4]);
        Base red(M,1),blue(M,0);
        Lion::set_loyaltyLoss(K);
        Base::start(red,blue,cost,T);
    }
}