// O(n^2) soln
class Job{
    public:
    int profit;
    int dead;
};


bool compare(Job x,Job y){
    return x.profit>y.profit;
}
pair<int,int> JobScheduling(Job arr[], int n) 
{ 
    // your code here
    int slot[n]={0};
    sort(arr,arr+n,compare);
    int s=0,ans=0;
    for(int i=0;i<n;i++){
        for(int j=min(n,arr[i].dead)-1;j>=0;j--){
            if(slot[j]==0){
                ans+=arr[i].profit;
                slot[j]++;
                s++;
                break;
            }
        }
    }
    return {s,ans};
} 