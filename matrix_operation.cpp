#include <iostream>
#include<omp.h>
#include<time.h>
#define n 1000
static int A[n][n],B[n][n],C[n][n];
using namespace std;
int main(){
    for(int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            A[i][j]=10;
            B[i][j]=15;
        }
    }
    double seq_time[4];
    double par_time[4];
    double speed_up[4];
    // matrix addition 
    double start_seq,end_seq;
    start_seq=omp_get_wtime();
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        C[i][j]=A[i][j]+B[i][j];
    }
}
 end_seq=omp_get_wtime();
seq_time[0]=end_seq-start_seq;

// matrix substraction
    start_seq=omp_get_wtime();
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        C[i][j]=A[i][j]-B[i][j];
    }
}
 end_seq=omp_get_wtime();
seq_time[1]=end_seq-start_seq;

// matrix multiplication
start_seq=omp_get_wtime();
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        C[i][j]=0;
        for(int k=0;k<n;k++){
            C[i][j]+=A[i][j]*B[i][j];
        }
    }
}
 end_seq=omp_get_wtime();
seq_time[2]=end_seq-start_seq;

// matrix transpose
start_seq=omp_get_wtime();
for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
        C[i][j]=A[j][i];
    }
}
end_seq=omp_get_wtime();
seq_time[3]=end_seq-start_seq;


omp_set_nested(1);
// parallel region
#pragma omp parallel
{
#pragma omp single
{
    // task 1 addition
    #pragma omp task
    
    {
        double t1=omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            C[i][j]=A[i][j]+B[i][j];
    }
}
    double t2=omp_get_wtime();
    par_time[0]=t2-t1;
    }

// task 2 substraction
    #pragma omp task

    {
        double t1=omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            C[i][j]=A[i][j]-B[i][j];
    }
}
    double t2=omp_get_wtime();
    par_time[1]=t2-t1;
    }

    // task 3 multiplication
    #pragma omp task

    {
        double t1=omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                    C[i][j]=0;
                for(int k=0;k<n;k++){
                    C[i][j]+=A[i][j]*B[i][j];
    }
}
}
    double t2=omp_get_wtime();
    par_time[2]=t2-t1;
    }

    // tranpose
    #pragma omp task

    {
        double t1=omp_get_wtime();
        #pragma omp parallel for collapse(2)
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
            C[i][j]=A[j][i];
    }
}
    double t2=omp_get_wtime();
    par_time[3]=t2-t1;
    }

    #pragma omp taskwait
}
}

cout<<"matrix addition \n "<<"sequintal time "<<seq_time[0]<<"\nparallell time  "<<par_time[0]<< "\nspeed up is "<<seq_time[0]/par_time[0];
cout<<"\n----------------------------";
cout<<"\n matrix substraction  \n sequential time "<<seq_time[1]<<"  \nparallell time  "<<par_time[1]<< " \nspeed up is "<<seq_time[1]/par_time[1];
cout<<"\n----------------------------";
cout<<"\nmatrix multiplication \n sequential time "<<seq_time[2]<<"  \nparallell time  "<<par_time[2]<< " \nspeed up is "<<seq_time[2]/par_time[2];
cout<<"\n----------------------------";
cout<<"\nmatrix transpose \n sequential time "<<seq_time[3]<<"  \nparallell time  "<<par_time[3]<< " \nspeed up is "<<seq_time[3]/par_time[3];
cout<<"\n----------------------------";
return 0;
}