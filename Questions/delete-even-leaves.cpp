
  class Tree {
      public:
         int val;
         Tree *left;
        Tree *right;
 };

Tree* solve(Tree* root) 
{
    if(root==NULL)
        return NULL;
    if(!root->left && !root->right)
    {
        if(root->val%2==0)
            return NULL;
        return root;
    }    
    Tree* x = solve(root->left);
    Tree* y = solve(root->right);
    if(!x && !y && root->val%2==0)
        return NULL;
    root->left = x;
    root->right = y;
    return root;
}