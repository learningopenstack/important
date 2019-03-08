#include <unordered_map>
#include <iostream>
#include <vector>

using namespace std;

class Solution{
private:
    vector<int>  _twoSum(vector<int>& nums, int target){
        vector<int> v(2, 0);
        unordered_map<int, int> hash;

        for(int i=nums.size(); i--; hash[nums[i]] = i){
            if (hash.find(target-nums[i])==hash.end()) continue;
            for(unordered_map<int, int>::iterator i=hash.begin(); i!=hash.end(); i++){
                std::cout<< "key:" << i->first << "; value:"  << i->second << std::endl;  
            }
            v[0] = 1 + i;
            v[1] = 1 + hash[target-nums[i]];
            std::cout << "v[0]=" << v[0] << "; v[1]="<< v[1] << std::endl; 
            break;
        }
        return v;
    }

public:
    vector<int> twoSum(vector<int>& nums, int target){
        return _twoSum(nums, target);
    }

};

void threeSum(int* nums, int size, int target){
   // 
}


int main(){
    Solution s;
    vector<int> nums = {2, 7, 11, 15, 4};
    int target = 19;
    vector<int> result = s.twoSum(nums, target);
    for(vector<int>::iterator i=result.begin(); i != result.end(); i++){
        std::cout<< "result:" << *i << std::endl;
    }
}

