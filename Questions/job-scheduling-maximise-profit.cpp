bool comp(vector<int>a, vector<int>b)
{
    if(a[1]!=b[1])
        return a[1]<b[1];
    return a[0]<b[0];
}
int fin(vector<vector<int>>&arr, int i, int j, int t)
{
    int m;
    int ind = INT_MIN;
    while(i<=j)
    {
        m = (i+j)/2;
        if(arr[m][1]<=t)
        {
            ind = max(ind, m);
            i = m+1;
        }
        else
        {
            j = m-1;
        }
    }
    return ind==INT_MIN?-1:ind;
}
int solve(vector<vector<int>>& arr) 
{
    sort(arr.begin(), arr.end(), comp);
    int n = arr.size();    
    vector<int>dp(n, INT_MAX);
    dp[0] = arr[0][2];
    for(int i=1;i<n;i++)
    {
        dp[i] = max(dp[i-1], arr[i][2]);
        int ind = fin(arr, 0, i-1, arr[i][0]);
        if(ind!=-1)
        {
            dp[i] = max(dp[i], dp[ind] + arr[i][2]);
        }
    }
    return dp[n-1];
}