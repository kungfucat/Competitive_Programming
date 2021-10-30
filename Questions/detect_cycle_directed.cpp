// detect cycle i directed graph



// dfs backedge 
class Solution {
public:

    bool fun(int src,bool*vis,bool*recS,vector<int> adj[]){
      if(!vis[src]) { vis[src]=1;
        recS[src]=1;
        for(auto ch:adj[src]){
            if(recS[ch] || (vis[ch]==0&&fun(ch,vis,recS,adj)))return true;
        }
        recS[src]=0;
        return false;}
    }
    
	bool isCyclic(int V, vector<int> adj[]) {
	   	// code here
	   	bool recS[V];
	   	bool vis[V];
	   	memset(recS,0,sizeof(recS));
	   	memset(vis,0,sizeof(vis));
	   	bool ans=false;
	   	for(int i=0;i<V;i++){
	   	    ans=(ans||fun(i,vis,recS,adj));
	   	}
	   	 return ans;
	}
};


