#include <iostream>
#include <math.h>
#include <vector>
#include <unistd.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class SumTree {
    vector<TreeNode*> roots_;
    int time_;
    int size_;

    TreeNode* makeTree(int n) {
        if(n == 0){
            return nullptr;
        }
        time_=1;
        size_ = 1 << n;
        auto* Node = new TreeNode(0);
        Node->left = makeTree(n-1);
        Node->right = makeTree(n-1);
        return std::move(Node);
    }

    TreeNode* updateNode(TreeNode* node, int idx) {
        if (!node) {
            return nullptr;
        }
        auto* newNode = new TreeNode(node->val + 1);
        if (idx < size_ / 2) {
            newNode->left = updateNode(node->left, idx);
            newNode->right = node->right;
        } else {
            newNode->left = node->left;
            newNode->right = updateNode(node->right, idx - size_ / 2);
        }
        return std::move(newNode);
    }

public:
    // n is height of the tree
    explicit SumTree(int n) {
        auto* root = new TreeNode(0);
        root->left = makeTree(n-1);
        root->right = makeTree(n-1);
        roots_.push_back(std::move(root));
    }

    void update(int idx) {
        time_++;
        auto* Node = new TreeNode(0);
        if(idx >= size_)
            return;
        if(idx >= size_ /2) {
            Node -> left = roots_.back()->left;
            Node->right = updateNode(roots_.back()->right, idx - size_/2);
        }else{
            Node -> right = roots_.back()->right;
            Node->left = updateNode(roots_.back()->left, idx);
        }
        roots_.push_back(std::move(Node));
    }

    int rangeQuery(int l, int r, int when_l, int when_r) {
        if (l > r || when_l >= roots_.size() || when_r >= roots_.size()) {
            return 0;
        }

        TreeNode* node_r = roots_[when_r];
        TreeNode* node_l = roots_[when_l];

        int sum = 0;
        int left = 0;
        int right = size_ - 1;

        while (node_r && node_l) {
            if (r < left || l > right) {
                break;
            }
            if (l <= left && right <= r) {
                sum += node_r->val - node_l->val;
                break;
            }
            int mid = left + (right - left) / 2;

            node_r = node_r->left;
            node_l = node_l->left;
            right = mid;

            if (r > mid) {
                sum += (node_r ? node_r->val : 0) - (node_l ? node_l->val : 0);
                node_r = roots_[when_r]->right;
                node_l = roots_[when_l]->right;
                left = mid + 1;
                right = size_ - 1;
            }
        }

        return sum;
    }
};

//Offline implementation
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin>>n >> m;
    vector<int> stock_index(n);
    SumTree tree = SumTree(log2(n));
    for(int i=0; i<n; i++){
        cin>>stock_index[i];
        tree.update(stock_index[i]);
    }
    //Process data
    for(int i=0; i<m; i++){
        int s,e,l,h;
        cin>>s>>e>>l>>h;
        int C_query=tree.rangeQuery(l,h, s-1, e);
        int Q_query=0;
        //Check C and Q query
        cout<<Q_query<<" "<<C_query<<"\n";
    }

    return 0;
}
