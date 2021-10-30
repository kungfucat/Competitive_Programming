
  class Tree {
      public:
         int val;
         Tree *left;
        Tree *right;
 };
pair<int, int>fn(Tree* root)
{
    if(root==NULL)
        return {0, 0};
    if(root->left==NULL && root->right==NULL)
        return {root->val, 0};
    pair<int, int>x = fn(root->left);
    pair<int, int>y = fn(root->right);
    int inc = root->val + max(x.second + y.second, max(y.second, x.second));
    int exc = max(x.first + y.first, max(x.first+y.second, max(y.first + x.second, y.second + x.second)));
    pair<int, int>ans = {inc, exc};
    return ans;
}
int solve(Tree* root) 
{
    pair<int, int>ans = fn(root);
    return max(ans.first, ans.second);    
}