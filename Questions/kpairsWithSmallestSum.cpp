struct comp{
    bool operator()(const vector<int>& a, const vector<int>& b) const{
        return (a[0] < b[0] || (a[0]==b[0] && a[1] < b[1]));
    }
};

class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& a, vector<int>& b, int k) {
        if(a.size() ==0 || b.size()==0 || k==0) return {{}};
        int lo1 = 0, lo2 = 0;
        vector<vector<int>> ans;
//         first value = sum, id1, id2
        map< vector<int>, pair<int, int>, comp> mpi;
        
        for(int i=0;i<a.size() && i<k;i++){
            mpi[{a[i] + b[0], i, 0}] = {i, 0};
        }
        
        while(k-- && mpi.size() > 0){
            auto smallestsum = *mpi.begin();
            
            int sm = smallestsum.first[0];
            int id1 = smallestsum.second.first;
            int id2 = smallestsum.second.second;
            
            vector<int> temp = {a[id1], b[id2]};
            ans.push_back(temp);
            
            mpi.erase({sm, id1, id2});
            
            id2++;
            if(id2==b.size())   continue;
            mpi[{a[id1] + b[id2], id1, id2}] = {id1, id2};
        }
        return ans;
        
    }
};