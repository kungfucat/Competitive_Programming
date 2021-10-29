class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        if (s.size() == 0)	return 0;
        map<char, int> mpi;
        int prev = 0, ans = 1;
        mpi[s[0]] = 0;
        
        for(int i=1;i<s.size();i++){
            if(mpi.find(s[i]) == mpi.end()){
                mpi[s[i]] = i;
                continue;
            }
            if(mpi[s[i]] < prev){
                mpi[s[i]] = i;
                continue;
            }
            ans = max(ans, i - prev);
            prev = mpi[s[i]] + 1;
            mpi[s[i]] = i;
        }
        ans = max(ans, int(s.size() - prev));
        return ans;
    }
};