/**
 * Because the STL is not contain a struct of Tree
 * So I want to construct the Tree as a class
 * @author by PanYue
 * all @copyright reserved
 */

#include <iostream>
#include <cmath>

#define MAX 9999

using namespace std;

class Binary_Tree {

private:
    int pre[MAX] = {0}, in[MAX] = {0}, post[MAX] = {0};

    typedef struct binaryTreeNODE
    {
        int data;
        struct binaryTreeNODE *lchild;
        struct binaryTreeNODE *rchild;
    } BiNODE; //struct of node

    int size;
    int height = -1;
    bool tag_complete = true;

public:
    BiNODE *root;

    Binary_Tree();

    BiNODE *buildTree_pre_in();//construct: pre + in

    BiNODE *pre_in(int pre_begin, int in_begin, int length);//recursion: pre + in

    BiNODE *buildTree_post_in();//construct: post + in

    BiNODE *post_in(int post_begin, int in_begin, int length);

    void preorder(BiNODE *root);

    void preorderRecursive(BiNODE *root);

    //void inorder(BiNODE *root);

    void inorderRecursive(BiNODE *root); //递归中序遍历（*）

    //void postorder(BiNODE *root); //非递归后序遍历

    void postorderRecursive(BiNODE *root);//递归后序遍历（*）

    void layerOrder(BiNODE *root);//层次遍历（*）

    int getNodeNum(BiNODE *root);//求结点个数（*）

    int getTreeHeight(BiNODE *root);//求树的高度（*）

    bool isFull(BiNODE *root);//判断是否是满二叉树（*）

    bool isComplete(BiNODE *root);//判断是否是完全二叉树（*）

    //bool isBinarySearchTree(BiNODE *root);//判断是否是二叉搜索树（*）*/
};


int main(void)
{
    Binary_Tree test;

    cout<<"/*****************************************************/"<<endl<<"begin test:"<<endl<<endl;

    cout<<"test for preorder without recursive"<<endl;
    test.preorder(test.root);

    cout<<"test for preorder recursive:"<<endl;
    test.preorderRecursive(test.root);

    cout<<"test for inorder recursive:"<<endl;
    test.inorderRecursive(test.root);

    cout<<"test for postorder recursive:"<<endl;
    test.postorderRecursive(test.root);

    cout<<"test for layerOrder recursive"<<endl;
    test.layerOrder(test.root);

    cout<<"test for numbers of nodes"<<endl;
    int numbers = test.getNodeNum(test.root);
    cout<<numbers<<endl;

    cout<<"test for numbers of nodes"<<endl;
    int height = test.getTreeHeight(test.root);
    cout<<height<<endl;

    cout<<"test for the full of the binary tree"<<endl;
    if(test.isFull(test.root)) cout<<"Full"<<endl;
    else cout<<"Not full"<<endl;

    cout<<"test for the complete pf the binary tree"<<endl;
    if(test.isComplete(test.root)) cout<<"Complete"<<endl;
    else cout<<"Not complete"<<endl;



    system("pause");

    return 0;
}

Binary_Tree::Binary_Tree()//construct
{
    cout<<"/*****************************************************/"<<endl;
    cout<<"0: pre + in"<<endl;
    cout<<"1: post + in"<<endl;
    cout<<"Imput:"<<endl;

    int judge = 0;
    cin>>judge;

    cin>>size;

    this->root = !judge ? this->buildTree_pre_in() : this->buildTree_post_in();

}

Binary_Tree::BiNODE* Binary_Tree::buildTree_pre_in()
{
    for(int i = 0; i < 2 * size; i++)
    {
        if(i < size) cin>>pre[i];

        else cin>>in[i - size];
    }

    return pre_in(0, 0, size);
}

Binary_Tree::BiNODE* Binary_Tree::pre_in(int pre_begin, int in_begin, int length)//前序+中序递归建树
{
    if(length == 1) return new BiNODE {pre[pre_begin], nullptr, nullptr};//叶子节点

    int left_length = -1, right_length = 0;//左右子树长度
    int p_root = pre[pre_begin];//根节点

    BiNODE * r = new BiNODE {p_root, nullptr, nullptr};

    while(in[in_begin + ++left_length] != p_root); //求出左子树长度

    right_length = length - left_length - 1;//求出右子树长度

    if(left_length != 0) r->lchild = pre_in(pre_begin + 1, in_begin, left_length);
    if(right_length != 0) r->rchild = pre_in(pre_begin + 1 + left_length, in_begin + left_length + 1, right_length );

    return  r;
}

Binary_Tree::BiNODE* Binary_Tree::buildTree_post_in()
{
    for(int i = 0; i < 2 * size; i++)
    {
        if(i < size) cin>>post[i];

        else cin>>in[i - size];
    }

    return post_in(0, 0, size);
}

Binary_Tree::BiNODE* Binary_Tree::post_in(int post_begin, int in_begin, int length)//后序+中序递归建树
{
    if(length == 1) return new BiNODE {post[post_begin], nullptr, nullptr};//叶子节点

    int left_length = -1, right_length = 0;//左右子树长度
    int p_root = post[post_begin + length - 1];//根节点

    BiNODE * r = new BiNODE {p_root, nullptr, nullptr};

    while(in[in_begin + ++left_length] != p_root); //求出左子树长度

    right_length = length - left_length - 1;//求出右子树长度

    if(left_length != 0) r->lchild = post_in(post_begin, in_begin, left_length);
    if(right_length != 0) r->rchild = post_in(post_begin + left_length, in_begin + left_length + 1, right_length );

    return  r;
}

void Binary_Tree::preorder(BiNODE *root)
{
    BiNODE *stack[MAX];
    int top = -1;
    stack[++top] = root;
    while(top >= 0)
    {
        BiNODE *t = stack[top];
        cout<<stack[top--]->data<<endl;
        if(t->rchild != nullptr) stack[++top] = t->rchild;
        if(t->lchild != nullptr) stack[++top] = t->lchild;
    }
}

void Binary_Tree::preorderRecursive(BiNODE *root)//递归前序遍历
{
    if(root != nullptr)
    {
        cout<<root->data<<endl;
        preorderRecursive(root->lchild);
        preorderRecursive(root->rchild);
    }
}

void Binary_Tree::inorderRecursive(BiNODE *root)
{
    if(root != nullptr)
    {
        inorderRecursive(root->lchild);
        cout << root->data << endl;
        inorderRecursive(root->rchild);
    }
}

void Binary_Tree::postorderRecursive(BiNODE *root)
{
    if(root != nullptr)
    {
        postorderRecursive(root->lchild);
        postorderRecursive(root->rchild);
        cout << root->data << endl;
    }
}

void Binary_Tree::layerOrder(BiNODE *root)
{
    binaryTreeNODE queue[MAX];
    int front = 0, tail = 0;

    queue[tail++] = *root;
    int now_node_nums = 1;
    int next_node_nums = 0;
    bool empty_son = false;

    while(front != tail)
    {
        if((queue[front].lchild == nullptr || queue[front].rchild == nullptr) && !empty_son) empty_son = true;
        if((queue[front].lchild != nullptr || queue[front].rchild != nullptr) && empty_son) tag_complete = false;

        if (queue[front].lchild != nullptr)
        {
            queue[tail++] = *queue[front].lchild;
            next_node_nums++;
        }

        if (queue[front].rchild != nullptr)
        {
            queue[tail++] = *queue[front].rchild;
            next_node_nums++;
        }


        if(--now_node_nums == 0)
        {
            now_node_nums = next_node_nums;
            next_node_nums = 0;
            height++;
        }
        cout<<queue[front].data<<endl;
        front++;
    }
}

int Binary_Tree::getNodeNum(BiNODE *root)
{
    return size;
}

int Binary_Tree::getTreeHeight(BiNODE *root)
{
    return height;
}

bool Binary_Tree::isFull(BiNODE *root)
{
    int full = pow(2, height + 1 ) - 1;

    return full == size;
}

bool Binary_Tree::isComplete(BiNODE *root)
{
    return tag_complete;
}