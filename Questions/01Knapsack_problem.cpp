.................O(N*W)...........
// memoize dp

int dp[1001][1001]={0};
//memset(dp,0,sizeof(dp));
int help(int W, int wt[], int val[], int n) 
{ 
    // base cases 
    if(n==0 || W==0)return 0;
    
   // Your code here
   if(dp[n][W])return dp[n][W];
   if(W-wt[n-1]>=0)
   return dp[n][W]=max(help(W-wt[n-1],wt,val,n-1)+val[n-1],help(W,wt,val,n-1));
    else return dp[n][W]=help(W,wt,val,n-1);
    
}
int knapSack(int W, int wt[], int val[], int n) 
{ 
    // base cases 
    
    memset(dp,0,sizeof(dp));
    help(W,wt,val,n);
    return dp[n][W];
}

// tabulation

int knapSack(int W, int wt[], int val[], int n) 
{ 
   // Your code here
   int dp[n+1][W+1];
   
   for(int i=0;i<=n;i++){
       for(int w=0;w<=W;w++){
           if(i==0 || w==0)dp[i][w]=0;
           else if(w-wt[i-1]>=0){
               dp[i][w]=max(val[i-1]+dp[i-1][w-wt[i-1]],dp[i-1][w]);
           }
           else{
               dp[i][w]=dp[i-1][w];
           }
       }
   }
   return dp[n][W];
}