#include <iostream>


// n > 1
int cut_line(int n){
    int max = 0;
    if (n==2){
        return 1; 
    } 

    if( n==3 ){
        return 2;
    }

    int max = 0;
    int value[] = new int[n+1];
    value[1] = 1;
    value[2] = 1;
    value[3] = 2;
    for(int i=4; i<=n; i++){
        max = 0;
        for(int j=1; j<n/2; j++){
           int v = value[j] * value[n-j]; 
           max = v > max ? v: max;
        }
        value[i] = max;
    }
    max = value[n];
    return max;
}
