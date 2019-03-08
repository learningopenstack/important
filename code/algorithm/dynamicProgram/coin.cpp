#include <iostream>

void makeChange(int values[], int len, int total, int coinUsed[], int coinTrack[]){
    coinUsed[0] = 0;
    coinTrack[0] = 0;

    for(int i=1; i<= total; i++){
        int coin = i; 
        int last = 0;
        for(int j=0; j<len; j++){
            if(values[j] <= coin){
                if( coinUsed[i - values[j]] + 1 < coin ){
                    coin = coinUsed[i - values[j]] + 1;         
                    last = values[j];
                }
            }
        }
        coinUsed[i] = coin;
        coinTrack[i] = last;
    }

    std::cout << coinTrack[total] << std::endl;
    /*
    while(total > 0){
        std::cout << "total: " << total << std::endl;
        std::cout << "track: " << coinTrack[total] << std::endl ;
        total -= coinTrack[total];
    }*/
}

int main(){
    int value[]={1,2,5,21,25};
    size_t arr_s = sizeof(value)/sizeof(*value);
    int total = 63;

    int coinUsed[64];
    int coinTrack[64];
    makeChange(value, arr_s, total, coinUsed, coinTrack);
} 
