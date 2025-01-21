#include <stack>
#include <queue>
#include "Trie_Tree.h"
#include "Binary_Tree.h"
#include <iostream>

void add_zero_lvl(btree::ptrNODE node)
{
    if (!node) return;

    else if (!node->left && !node->right) 
    {
        node->left = new btree::NODE(0);
        node->right = new btree::NODE(0);
    }
    else
    {
        add_zero_lvl(node->left); add_zero_lvl(node->right);
    }
}
int sum_chet(btree::BTREE& t)
{
    int res{};
    std::stack<btree::ptrNODE> st;
    if (t.get_root()->info % 2 == 1) st.push(t.get_root());
    while (!st.empty())
    {
        btree::ptrNODE cur = st.top();
        st.pop();
        res += cur->info;
        if (cur->right != nullptr && cur->right->info % 2 == 1) 
            st.push(cur->right);
        if (cur->left != nullptr && cur->left->info % 2 == 1)
            st.push(cur->left);
    }

    return res;
}

void del_last_lvl(btree::ptrNODE node)
{
    bool check_r= 0;
    bool check_l= 0;
    if (!node) return;
    else 
    {
        if (node->left && !node->left->left && !node->left->right)
        {
            delete node->left;
            node->left = nullptr;
            check_l = 1;
        }

        if (node->right && !node->right->left && !node->right->right)
        {
            delete node->right;
            node->right = nullptr;
            check_r = 1;
        }

        if (!check_r)
        {
            del_last_lvl(node->right);
        }
        if (!check_l)
        {
            del_last_lvl(node->left);
        }
    }
}
int sum_lvl(btree::BTREE& t, int lvl)
{
    int res{}, cur_lvl{ 0 };
    std::queue<btree::ptrNODE> qe;
    qe.push(t.get_root());
    while (!qe.empty() && cur_lvl != lvl)
    {
        int levelSize = qe.size();
        for (int i = 0; i < levelSize; i++)
        {
            btree::ptrNODE cur = qe.front();
            qe.pop();

            res += cur->info;
            std::cout << cur->info << " ";
            if (cur->right)
                qe.push(cur->right);
            if (cur->left)
                qe.push(cur->left);
        }
        cur_lvl++;
    }

    return res;
}

void del_last(ttree::ptrNODE t)
{
    if (t->eow)
        delete t;
    for (int i = 0; i < 26; i++)
        if (t->ptrs[i])
            del_last(t->ptrs[i]);
}

A operator+ (A a1, A a2) 
{
    A a3(a1.geta() + a2.geta(), a1.getb() + a2.getb());
    return a3;
}

int main()
{
    A a1(2, 1);
    A a2(1, 2);
    a1.print(); a2.print();
    A a3 = a1 + a2;
    a3.print();


    ttree::TTREE trie("trie_test.txt");
    trie.print(0);
    //btree::BTREE tree("test.txt");
    //tree.print();
    std::cout << "//////////////////////////////////////////////////////\n";
    //add_zero_lvl(tree.get_root());
    //del_last_lvl(tree.get_root());
    //tree.print();
    //std::cout << sum_chet(tree);
    //std::cout << sum_lvl(tree, 3);


}

