#include <iostream>
#include<omp.h>
#define n 1000
using namespace std;
static int A[n][n],B[n][n],C[n][n];

int main(){
    // #pragma omp parallel for num_threads(8)
    omp_set_nested(1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i][j]=1;
            B[i][j]=1;
            C[i][j]=0;
        }
    }
        
    //  #pragma omp parallel for num_threads(8)
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<n;j++){
    //         for(int k=0;k<n;k++){
    //             C[i][j]+=A[i][k]*B[k][j];
    //         }
    //     }
    // }

     #pragma omp parallel for num_threads(8)
    for(int i=0;i<n;i++){
     #pragma omp parallel for num_threads(8)
        for(int j=0;j<n;j++){
            for(int k=0;k<n;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
        }
    }

      for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
           cout<<C[i][j]<<" ";
        }
        cout<<endl;
    }

return 0;
}