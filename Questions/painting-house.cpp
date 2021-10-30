int fn(vector<vector<int>>&m, vector<vector<int>>&dp, int i, int j, int r, int c)
{
    if(i==r)
        return 0;
    if(dp[i][j]!=INT_MAX)
        return dp[i][j];
    int xx = INT_MAX;
    for(int l=0;l<c;l++)
    {
        if(l!=j)
        {
            int y = fn(m, dp, i+1, l, r, c);
            xx = min(xx, m[i][j] + y);
        }
    }
    dp[i][j] = xx;
    return dp[i][j];
}

int solve(vector<vector<int>>& m) 
{
    int r = m.size();
    if(r==0)
        return 0;
    int c = m[0].size();
    vector<vector<int>>dp(r+1, vector<int>(c+1, INT_MAX));
    int i, j;
    int x = INT_MAX, y;
    for(i=0;i<c;i++)
    {
        dp[0][i] = fn(m, dp, 0, i, r, c);
        x = min(x, dp[0][i]);
    }    
    return x;
}