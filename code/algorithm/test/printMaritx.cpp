#include <iostream>
#include <vector>
using namespace std;

void printCircus(vector<vector<int> >& data, vector<int>& ret, int row, int column, int start){
   int endX = column - 1 - start;
   int endY = row - 1 - start;

   //从左到右
   for(int i=start; i<=endX; i++){
       ret.push_back(data[start][i]); 
   } 

   //从上到下
   if(start<endY){
        for(int i=start + 1; i<=endY; i++){
            ret.push_back(data[i][endX]); 
        }
   }

   //从右到左
   if(start<endX && start<endY){
        for(int i=endX-1; i>=start; i--){
            ret.push_back(data[endY][i]); 
        }
   }

   //从下到上
   if(start<endX && start<endY-1){
        for(int i=endY-1; i>start ; i--){
            ret.push_back(data[i][start]);
        }
   }
}

vector<int> Maritx(vector<vector<int> > v){
    vector<int> ret;
    ret.clear();
    int row = v.size();
    if( row == 0){
       return ret; 
    }
    
    int column = v[0].size();

    int start = 0;

    while(row > 2*start && column > 2*start){
        printCircus(v, ret, row, column, start); 
        start++;
    }
    return ret;
}

//s = 4;
vector<vector<int> > genMaritx(vector<int> data, int s){
    int end = s/2;
    int pointer = 0;
    int endX = 0;
    int endY = 0;

    vector<vector<int> > maritx{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};

    for(int start = 0; start<end; start++){
        endX = s  - start - 1;
        endY = s  - start - 1;
       for(int j=start; j<=endX; j++){
           maritx[start][j] = data[pointer++]; 
       } 
       std::cout << "pointer = " << pointer << std::endl;
       
        if(start < endY){
            for(int j=start + 1; j<=endY; j++){
                maritx[j][endX] = data[pointer++];
            }    
        }

       std::cout << "pointer = " << pointer << std::endl;
        if(start < endY && start < endX){
            for(int j=endX-1; j>=start; j-- ){
                 maritx[endY][j] = data[pointer++];
            }
        }
       std::cout << "pointer = " << pointer << std::endl;

        if(start < endY - 1 && start <endX){
            for(int j=endY-1; j>start; j--){
                maritx[j][start] = data[pointer++]; 
            }
        }
       std::cout << "pointer = " << pointer << std::endl;
    } 
    return maritx;
}




















































int main(){
    vector<int> a, b, c, d;
    for(int i=0; i<4; i++){
        a.push_back(i+1);
    }
    for(int i=4; i<8; i++){
        b.push_back(i+1);
    }
    for(int i=8; i<12; i++){
        c.push_back(i+1);
    }
    for(int i=12; i<16; i++){
        d.push_back(i+1);
    }

    vector<int> ff;
    for(int i=1; i<= 4  * 4 ; i++){
       ff.push_back(i); 
    }

    vector<vector<int> > data;
    data.push_back(a);
    data.push_back(b);
    data.push_back(c);
    data.push_back(d);

    a = Maritx(data);

    for(vector<int>::iterator it=a.begin(); it<a.end(); it++){
        std::cout << "=>" << *it;
    }
    std::cout << std::endl;

    vector<vector<int> > tt = genMaritx(ff, 4);

    a = Maritx(tt);
    for(vector<int>::iterator it=a.begin(); it<a.end(); it++){
        std::cout << "=>" << *it;
    }
    return 0;
}
