bool isvalid(int i, int j, int n, int m)
{
    if(i<0 || j<0 || i>=n || j>=m)
        return false;
    return true;
}

int solve(vector<vector<int>>& matrix) 
{
    set<vector<pair<int, int>>>st;
    if(matrix.size()==0)
        return 0;
    int n = matrix.size();
    int m = matrix[0].size();
    vector<vector<int>>vis(n, vector<int>(m, false));
    int dir[4][2] = {
        {1, 0}, {0, 1}, {-1, 0}, {0, -1},
    };
    int i, j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        {
            if(!vis[i][j] && matrix[i][j]==1)
            {
                queue<pair<int, int>>q;
                pair<int, int>p;
                int x, y, nx, ny;
                q.push({i, j});
                vector<pair<int, int>>t;
                while(!q.empty())
                {
                    p = q.front();
                    q.pop();
                    x = p.first;
                    y = p.second;
                    t.push_back({i-x, j-y});
                    vis[x][y] = true;
                    for(int k=0;k<4;k++)
                    {
                        nx = x + dir[k][0];
                        ny = y + dir[k][1];
                        if(isvalid(nx, ny, n, m) && !vis[nx][ny] && matrix[nx][ny]==1)
                        {
                            q.push({nx, ny});
                            vis[nx][ny] = true;
                        }
                    }
                }
                st.insert(t);
            }
        }
    }    
    return st.size();
}