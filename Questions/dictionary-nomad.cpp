int solve(vector<string>& d, string st, string en) {
    unordered_set<string>s;
    for(auto &i: d)
        s.insert(i);
    if(st==en)
        return 1;
    int step = 0;
    queue<string>q;
    int sz;
    q.push(st);
    while(!q.empty())
    {
        sz = q.size();
        step++;
        while(sz--)
        {
            string t = q.front();
            if(t==en)
                return step;
            q.pop();
            s.erase(t);
            for(int i=0;i<t.size();i++)
            {
                char c = t[i];
                for(int j=0;j<26;j++)
                {
                    t[i] = j + 'a';
                    if(s.find(t)!=s.end())
                    {
                        q.push(t);
                    }
                }
                t[i] = c;
            }
        }
    }
    return -1;
}