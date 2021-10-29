class Solution {
public:
    vector<int> productExceptSelf(vector<int>& arr) {
        vector<int> ans(arr.size(), 1);
        int beg = 1;
        int end = 1;
        for(int i=0;i<arr.size();i++){
            
            ans[i] = ans[i]*beg;
            beg = beg*arr[i];
            
            int opposite = arr.size() - i - 1;
            ans[opposite] = ans[opposite]*end;
            end=end*arr[opposite];
        }   
        return ans;
    }
};