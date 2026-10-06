/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val){
        this->val=val;
        this->left=nullptr;
        this->right=nullptr;
    }
    TreeNode(){
        this->val=0;
        this->left=nullptr;
        this->right=nullptr;
    }
    
};

// 1.Creating a BST
TreeNode* insertNode(TreeNode* root,int val){
    if(root == nullptr){
        root = new TreeNode(val);
        return root;
    }
    if(val > (root->val)){
        root->right = insertNode(root->right,val);
    }else{
        root->left = insertNode(root->left,val);
    }
    return root;
}

// 2.search in a BST
TreeNode* search(TreeNode* root,int val){
    if(root== nullptr){
        return root;
    }
    if(root-> val == val){
        return root;
    }
    if(val > (root->val)){
        return search(root->right,val);
    }else{
        return search(root->left,val);
    }
}    

//3. Print preorder,inorder,postorder 

void inorder(TreeNode* root,vector<int> &vv){
    if(root==nullptr){
        return;
    }
    inorder(root->left,vv);
    vv.push_back(root->val);
    inorder(root->right,vv);
}


void preorder(TreeNode* root,vector<int> &vv){
    if(root==nullptr){
        return;
    }
    vv.push_back(root->val);
    preorder(root->left,vv);
    preorder(root->right,vv);
}

void postorder(TreeNode* root,vector<int> &vv){
    if(root==nullptr){
        return;
    }
    postorder(root->left,vv);
    postorder(root->right,vv);
    vv.push_back(root->val);
}
//4.Height of Tree
int height(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    int temp1 = height(root->left);
    int temp2 = height(root->right);
    int temp = temp1>temp2? temp1:temp2;
    return temp+1;
}
//5.Count of leaf nodes
int leafNodes(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    if(root->left==nullptr && root->right==nullptr){
        return 1;
    }
    return leafNodes(root->left)+leafNodes(root->right);
}
//6. Count of Parent Node
int parentNode(TreeNode* root){
    if(root==nullptr){
        return 0;
    }
    if(root->left!=nullptr && root->right!=nullptr){
        return 1+parentNode(root->left)+parentNode(root->right);
    }else if(root->left!=nullptr){
        return 1+parentNode(root->left);
    }else{
        return 1+parentNode(root->right);
    }
}

//7. deleteNode with value
TreeNode* findMinNode(TreeNode* root){
    if(root==nullptr){
        return root;
    }
    if(root->left==nullptr){
        return root;
    }
    return findMinNode(root->left);
}
//7. deleteNode with value
TreeNode* deleteNode(TreeNode* root,int val){
    if(root==nullptr){
        return root;
    }
    if( val> (root->val)){
        root->right = deleteNode(root->right,val);
    }else if( val<(root->val)){
        root->left = deleteNode(root->left,val);
    }else{
        if(root->left==nullptr){
            
            return root->right;
        }else if(root->right==nullptr){
            return root-> left;
        }else{
            TreeNode* temp = findMinNode(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right,root->val);
        }
    }
    return root;
}

//8. Level order traversal DFS
void levelOrderTraversalDFS(TreeNode* root,vector<vector<int>> &vv,int depth){
    if(root==nullptr){
        return;
    }
    if(vv.size()==depth){
        vector<int> temp;
        vv.push_back(temp);
    }
    vv[depth].push_back(root->val);
    if(root->left!= nullptr){
        levelOrderTraversalDFS(root->left,vv,depth+1);
    }
    if(root->right!=nullptr){
        levelOrderTraversalDFS(root->right,vv,depth+1);
    }
}

//9. Level order traversal BFS
void levelOrderTraversalBFS(TreeNode* root,vector<vector<int>> &vv){
    if(root==nullptr)
        return;
    
    queue<TreeNode*> que;
    que.push(root);
    
    while(!que.empty()){
        int n=que.size();
        vector<int> level(n,0);
        
        for(int i=0;i<n;i++){
            TreeNode* temp=que.front();
            level[i]=temp->val;
            
            if (temp->left != nullptr) {
                que.push(temp->left);
            }
            if (temp->right != nullptr) {
                que.push(temp->right);
            }
            que.pop();
        }
        vv.push_back(level);
    }
}

// 10. Left side View
vector<int> leftView(TreeNode* root){
    vector<int> res;
    vector<vector<int>> vv;
    levelOrderTraversalBFS(root,vv);
    
    for(int i=0;i<vv.size();i++){
        res.push_back(vv[i][0]);
    }
    
    return res;
}

//11. Right Side View
vector<int> rightView(TreeNode* root){
    vector<int> res;
    vector<vector<int>> vv;
    levelOrderTraversalBFS(root,vv);
    
    for(int i=0;i<vv.size();i++){
        res.push_back(vv[i][vv[i].size()-1]);
    }
    return res;
}
//12.
// --------------------------------------------------
// Helper functions for runner
// --------------------------------------------------

void printVector(const vector<int>& vv) {
    for (int x : vv) {
        cout << x << " ";
    }
    cout << endl;
}

void print2DVector(const vector<vector<int>>& vv) {
    for (const auto& level : vv) {
        cout << "[ ";
        for (int x : level) {
            cout << x << " ";
        }
        cout << "] ";
    }
    cout << endl;
}



int main()
{
    
    // -----------------------------------------------
    // 1. Creating BST
    // -----------------------------------------------

    TreeNode* root = nullptr;

    vector<int> values = {
        50, 30, 70, 20, 40, 60, 80
    };

    for (int val : values) {
        root = insertNode(root, val);
    }

    cout << "========== BST CREATED ==========" << endl;
    cout << "Inserted values: ";
    printVector(values);


    // -----------------------------------------------
    // 2. Search
    // -----------------------------------------------

    cout << "\n========== SEARCH ==========" << endl;

    int searchValue = 40;

    TreeNode* found = search(root, searchValue);

    if (found != nullptr) {
        cout << searchValue << " found in BST" << endl;
    } else {
        cout << searchValue << " not found in BST" << endl;
    }


    searchValue = 100;

    found = search(root, searchValue);

    if (found != nullptr) {
        cout << searchValue << " found in BST" << endl;
    } else {
        cout << searchValue << " not found in BST" << endl;
    }


    // -----------------------------------------------
    // 3. Tree Traversals
    // -----------------------------------------------

    cout << "\n========== TRAVERSALS ==========" << endl;

    vector<int> in;
    vector<int> pre;
    vector<int> post;

    inorder(root, in);
    preorder(root, pre);
    postorder(root, post);

    cout << "Inorder   : ";
    printVector(in);

    cout << "Preorder  : ";
    printVector(pre);

    cout << "Postorder : ";
    printVector(post);


    // -----------------------------------------------
    // 4. Height
    // -----------------------------------------------

    cout << "\n========== HEIGHT ==========" << endl;

    cout << "Height of tree = " << height(root) << endl;


    // -----------------------------------------------
    // 5. Leaf Nodes
    // -----------------------------------------------

    cout << "\n========== LEAF NODES ==========" << endl;

    cout << "Number of leaf nodes = "
         << leafNodes(root) << endl;


    // -----------------------------------------------
    // 6. Parent Nodes
    // -----------------------------------------------

    cout << "\n========== PARENT NODES ==========" << endl;

    cout << "Number of parent nodes = "
         << parentNode(root) << endl;


    // -----------------------------------------------
    // 7. Find Minimum Node
    // -----------------------------------------------

    cout << "\n========== MINIMUM NODE ==========" << endl;

    TreeNode* minNode = findMinNode(root);

    if (minNode != nullptr) {
        cout << "Minimum value = "
             << minNode->val << endl;
    }


    // -----------------------------------------------
    // 8. Level Order Traversal - DFS
    // -----------------------------------------------

    cout << "\n========== LEVEL ORDER DFS ==========" << endl;

    vector<vector<int>> levelDFS;

    levelOrderTraversalDFS(root, levelDFS, 0);

    print2DVector(levelDFS);


    // -----------------------------------------------
    // 9. Level Order Traversal - BFS
    // -----------------------------------------------

    cout << "\n========== LEVEL ORDER BFS ==========" << endl;

    vector<vector<int>> levelBFS;

    levelOrderTraversalBFS(root, levelBFS);

    print2DVector(levelBFS);


    // -----------------------------------------------
    // 10. Left Side View
    // -----------------------------------------------

    cout << "\n========== LEFT SIDE VIEW ==========" << endl;

    vector<int> left = leftView(root);

    cout << "Left view: ";
    printVector(left);


    // -----------------------------------------------
    // 11. Right Side View
    // -----------------------------------------------

    cout << "\n========== RIGHT SIDE VIEW ==========" << endl;

    vector<int> right = rightView(root);

    cout << "Right view: ";
    printVector(right);


    // -----------------------------------------------
    // 12. Delete Node
    // -----------------------------------------------

    cout << "\n========== DELETE NODE ==========" << endl;

    int deleteValue = 70;

    cout << "Deleting node: " << deleteValue << endl;

    root = deleteNode(root, deleteValue);

    cout << "Inorder after deletion: ";

    vector<int> afterDelete;
    inorder(root, afterDelete);

    printVector(afterDelete);


    // -----------------------------------------------
    // Check views again after deletion
    // -----------------------------------------------

    cout << "\n========== AFTER DELETION ==========" << endl;

    cout << "Height = " << height(root) << endl;

    cout << "Leaf nodes = " << leafNodes(root) << endl;

    cout << "Parent nodes = " << parentNode(root) << endl;

    cout << "Left view = ";
    printVector(leftView(root));

    cout << "Right view = ";
    printVector(rightView(root));


    

    return 0;
}


========== BST CREATED ==========
Inserted values: 50 30 70 20 40 60 80 

========== SEARCH ==========
40 found in BST
100 not found in BST

========== TRAVERSALS ==========
Inorder   : 20 30 40 50 60 70 80 
Preorder  : 50 30 20 40 70 60 80 
Postorder : 20 40 30 60 80 70 50 

========== HEIGHT ==========
Height of tree = 3

========== LEAF NODES ==========
Number of leaf nodes = 4

========== PARENT NODES ==========
Number of parent nodes = 7

========== MINIMUM NODE ==========
Minimum value = 20

========== LEVEL ORDER DFS ==========
[ 50 ] [ 30 70 ] [ 20 40 60 80 ] 

========== LEVEL ORDER BFS ==========
[ 50 ] [ 30 70 ] [ 20 40 60 80 ] 

========== LEFT SIDE VIEW ==========
Left view: 50 30 20 

========== RIGHT SIDE VIEW ==========
Right view: 50 70 80 

========== DELETE NODE ==========
Deleting node: 70
Inorder after deletion: 20 30 40 50 60 80 

========== AFTER DELETION ==========
Height = 3
Leaf nodes = 3
Parent nodes = 6
Left view = 50 30 20 
Right view = 50 80 60 


