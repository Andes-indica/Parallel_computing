
// to calculate the time spent in the parallel region 
// doube start ,end;

// start = omp_get_wtime();
// {
//     //parallel code 
// }
// end =omp_get_wtime();

// cout<<"%f",start-end;
//  -----------------------

#include <iostream>
#include<omp.h>
#include<math.h>
#include<vector>
#include<ctime>
using namespace std;
// int n = pow(2,16);
long n= pow(2,24);
double a=2.0;
int main(){
    vector<double> x(n,1.0) ;
    vector<double> y(n,2.0);
    cout<< "executing in a serial region ";
    auto start =clock();
    for(int i=0;i<n;i++){
        x[i]=a*x[i]+y[i];
    }
    auto duration = ((clock()-start)/double(CLOCKS_PER_SEC));
    cout<<"serial execution time taken for this is"<<duration<<"\n";
     vector<double> x1(n,1.0);
     vector<double> y1(n,2.0);
    for(int threads=2;threads <=32;threads *=2){
        omp_set_num_threads(threads);
        double start ,end ;
        start = omp_get_wtime();
        
          #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            x1[i] = a * x1[i] + y1[i];
        }
        end =omp_get_wtime();
        double executed_time=end-start;
        double speedup=duration/executed_time;
        cout<<"threads used "<<threads<<endl<<"time taken= "<<executed_time<<endl<<"speedup is "<<speedup<<"\n";
    }
return 0;
}
//  here we can see that after parallelize the code also we are unable to achive the speed up 
//  but we increase the n then we can see the significant change in the speed up 
// so we can conclude that if the problem is more complex then the parallization will give the noticing results 
