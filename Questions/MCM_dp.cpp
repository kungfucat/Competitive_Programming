// matrix chain multiplication
//top down O(N3)
class Solution{
public:
int dp[101][101];
    int fun(int*arr,int s,int e){
        if(s==e)return 0;
        int ans=INT_MAX;
        if(dp[s][e]!=-1)return dp[s][e];
        for(int j=s;j<e;j++){
            ans=min(fun(arr,s,j)+arr[s-1]*arr[j]*arr[e] + fun(arr,j+1,e),ans);
        }
        return dp[s][e]=ans;
    }
    int matrixMultiplication(int N, int arr[])
    {
        // code here
            memset(dp,-1,sizeof(dp));
            return fun(arr,1,N-1);
    }
};  
// tabulation 