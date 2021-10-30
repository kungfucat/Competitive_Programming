int solve(vector<int>& nums) 
{
    stack<int>st;
    int ans = 0;
    int i=0, n = nums.size();
    while(i<n)
    {
        if(st.empty() || nums[st.top()]<=nums[i])
            st.push(i++);
        else
        {
            int ind = st.top();
            st.pop();
            int h = nums[ind];
            int len = st.empty()?i:i-st.top()-1;
            int ar = h*len;
           // cout<<ar<<" ";
            ans = max(ans, ar);
        }
    }    
    while(!st.empty())
    {
        int ind = st.top();
        st.pop();
        int h = nums[ind];
        int len = st.empty()?i:i-st.top()-1;
        int ar = h*len;
       // cout<<ar<<" ";
        ans = max(ans, ar);
    }
    return ans;
}