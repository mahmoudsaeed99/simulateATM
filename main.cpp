#include <iostream>
#include <random>
#include <bits/algorithmfwd.h>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>
#include <map>
using namespace std;
double IAT;
double AT;
double SST;
double ST;
double WT;
double CT;
double TIS;
double TIS_1=0;
double TIS_2=0;
double TIS_3=0;
double AM1;
double AM2;
double AM3;
vector<double>inter_arrival_time;
vector<double>arrival_time;
vector<double>start_service_time;
vector<double>service_time;
vector<double>wating_time;
vector<double>completion_time;
vector<double>time_in_system;
vector<double>Atm1;
vector<double>Atm2;
vector<double>Atm3;
double total_waiting_time=0;
int waiting=0;
int wait_1=0;
double max_wait=0;
double uti_1=0;
double uti_2=0;
double uti_3=0;

double gene_IAT(){

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    exponential_distribution<double> distribution(1);
    double number = distribution(generator);
    return number;
}

double gene_ST_Atm1(){

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
    double random;
    random = (double)rand() / (double)(RAND_MAX);
    double ST=2+(random*(4-2));
    return ST;
}
piecewise_linear_distribution<double> triangular_distribution (double min, double peak, double max){

    array<double, 3> i{min, peak, max};
    array<double, 3> w{0, 1, 0};
    return piecewise_linear_distribution<double>{i.begin(), i.end(), w.begin()};
}

double gene_ST_Atm2(){

   unsigned seed = chrono::system_clock::now().time_since_epoch().count();
   mt19937 gen(seed);
   auto dist = triangular_distribution(2, 3.3, 4);
   double ST = dist(gen);
   return ST;
}

double gene_ST_Atm3(){

    double ST;
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    normal_distribution<double> distribution(3,0.5);
    ST=distribution(generator);
    return ST;
}

bool comp(int a, int b)
{
    return (a < b);
}

int main()
{
    int check;

    cout<<"IAT        AT         SST          ST        WT        CT        TIS        ATM1          ATM2        ATM3     "<<endl;

    for(int i=0 ;i<100 ;i++){

    IAT=gene_IAT();
    inter_arrival_time.push_back(IAT);
    cout<<inter_arrival_time[i]<<"     |";

        if( i==0 ){
            AT=inter_arrival_time[i];
            arrival_time.push_back(AT);
            cout<<arrival_time[i]<<"     |";
            SST=arrival_time[i];
            start_service_time.push_back(SST);
            cout<<start_service_time[i]<<"     |";
            ST=gene_ST_Atm1();
            service_time.push_back(ST);
            cout<<service_time[i]<<"     |";
            check=1;

        }
        else{
            AT=arrival_time[i-1]+inter_arrival_time[i];
            arrival_time.push_back(AT);
            cout<<arrival_time[i]<<"     |";
            SST=max(arrival_time[i] , min( {Atm1[i-1] , Atm2[i-1] , Atm3[i-1]} , comp ) );
            start_service_time.push_back(SST);
            cout<<start_service_time[i]<<"     |";
            if( Atm1[i-1] <= Atm2[i-1]  && Atm1[i-1] <= Atm3[i-1] )
            {

                ST=gene_ST_Atm1();
                service_time.push_back(ST);
                cout<<service_time[i]<<"     |";
                check=1;
            }

                else if( Atm2[i-1] < Atm1[i-1]  && Atm2[i-1] < Atm3[i-1] )
            {
                    ST=gene_ST_Atm2();
                    service_time.push_back(ST);
                    cout<<service_time[i]<<"     |";
                    check=2;
            }

                else{
                    ST=gene_ST_Atm3();
                    service_time.push_back(ST);
                    cout<<service_time[i]<<"     |";
                    check=3;
            }
        }
    if( start_service_time[i]-arrival_time[i] > 0){
            WT=start_service_time[i]-arrival_time[i];
            waiting+=1;
            if( WT > max_wait )
               max_wait=WT;
            if(start_service_time[i]-arrival_time[i] > 1)
                wait_1+=1;
     }
    else
            WT=0;
    //cout<<"wataing time is :"<<fixed<<WT<<endl;

    wating_time.push_back(WT);
    cout<<wating_time[i]<<"     |";
    total_waiting_time+=WT;

    CT=start_service_time[i]+service_time[i];
    completion_time.push_back(CT);
    cout<<completion_time[i]<<"     |";

    TIS=completion_time[i]-arrival_time[i];
    time_in_system.push_back(TIS);
    cout<<time_in_system[i]<<"     |";

    if( i==0 ){
        Atm1.push_back(CT);
        Atm2.push_back(0);
        Atm3.push_back(0);
        cout<<Atm1[i]<<"     |";
        cout<<Atm2[i]<<"     |";
        cout<<Atm3[i]<<"     "<<endl;
        uti_1+=ST;
        TIS_1+=TIS;

    }

    else{

        if (check == 1){
            Atm1.push_back(CT);
            Atm2.push_back(Atm2[i-1]);
            Atm3.push_back(Atm3[i-1]);
            cout<<Atm1[i]<<"     |";
            cout<<Atm2[i]<<"     |";
            cout<<Atm3[i]<<"     "<<endl;
            uti_1+=ST;
            TIS_2+=TIS;
        }

        else if (check == 2){
            Atm2.push_back(CT);
            Atm3.push_back(Atm3[i-1]);
            Atm1.push_back(Atm1[i-1]);
            cout<<Atm1[i]<<"     |";
            cout<<Atm2[i]<<"     |";
            cout<<Atm3[i]<<"     "<<endl;
            uti_2+=ST;
            TIS_3+=TIS;
        }

        else{
            Atm3.push_back(CT);
            Atm2.push_back(Atm2[i-1]);
            Atm1.push_back(Atm1[i-1]);
            cout<<Atm1[i]<<"     |";
            cout<<Atm2[i]<<"     |";
            cout<<Atm3[i]<<"     "<<endl;
            uti_3+=ST;
        }

    }




    }      //bracket of for loop

cout<<endl<<endl<<endl<<endl;
cout<<"Average Waiting Time is : "<<total_waiting_time/100<<endl;
cout<<"Probability of waiting  is : "<<(double)waiting/100<<endl;
cout<<"Probability of waiting more than 1 minute is : "<<(double)wait_1/100<<endl;
cout<<"maximum minutes of waiting is : "<<max_wait<<endl;
cout<<"Utilization of First ATM is : "<<uti_1/TIS_1<<endl;
cout<<"Utilization of Second ATM is : "<<uti_2/TIS_2<<endl;
cout<<"Utilization of Third ATM is : "<<uti_3/TIS_3<<endl;
cout<<"Utilization of Third ATM is : "<<uti_3/TIS_3<<endl;

    return 0;
}
