class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int ans = 0, i = 0;
        for(;i<nums.size();i++){
            ans = ans^i^nums[i];
        }
        return ans^i;
    }
};