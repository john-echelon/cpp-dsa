#include <iostream>
#include <assert.h>
#include <cstdio>
#include <iterator>
#include "tree.h"
#include "../linked-list/linked-list.h"
using namespace std;

void insert_test() {
    AVLTree<int> tree;
    tree.insert(21);
    tree.insert(31);
    tree.insert(41);
    tree.insert(7);
    assert(tree.root->key == 21);
    assert(tree.root->left->key == 7);
    assert(tree.root->right->key == 31);
    assert(tree.root->right->right->key == 41);

}

void left_descendant_test() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(21);
    tree.insert(15);
    tree.insert(13);
    assert(tree.next(tree.root)->key == 13);
}

void right_ancestor_test() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(21);
    tree.insert(15);
    tree.insert(13);
    tree.insert(5);
    tree.insert(6);
    tree.insert(8);
    
    TreeNode<int> * n = tree.search(8);
    assert(tree.next(n)->key == 10);
}

void no_right_ancestor_test() {
    AVLTree<int> tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(9);
    tree.insert(8);
    TreeNode<int> * n = tree.search(9);
    assert(tree.next(n) == NULL);
    
}
void range_test() {
     AVLTree<int> tree;
    tree.insert(10);
    tree.insert(21);
    tree.insert(15);
    tree.insert(13);
    tree.insert(5);
    tree.insert(6);
    tree.insert(8);
    tree.insert(17);
    tree.insert(3);

    LinkedList<const TreeNode<int>*> list = tree.range(7, 14);
    // for(LinkedList<const TreeNode<int>*>::iterator ptr = list.begin(); ptr != list.end(); ptr++ )
    //     cout << (*ptr)->key<< " ";
    // cout << endl;
    LinkedList<const TreeNode<int>*>::iterator ptr = list.begin();
    assert((*ptr)->key == 8);
    assert((*++ptr)->key == 10);
    assert((*++ptr)->key == 13);
}

void remove_test() {
    AVLTree<int> tree;
    tree.insert(10);
    tree.insert(21);
    tree.insert(15);
    tree.insert(13);
    tree.insert(5);
    tree.insert(7);
    tree.insert(6);
    tree.insert(8);
    tree.insert(17);
    tree.insert(3);
    // right is null scenarios: 8,21
    // right is not null scenarios: 5, 10
    TreeNode<int> * s;
    s = tree.search(8);
    tree.remove(s);
    s = tree.search(21);
    tree.remove(s);
    s = tree.search(5);
    tree.remove(s);
    s = tree.search(10);
    tree.remove(s);
    LinkedList<const TreeNode<int>*> list = tree.range(1, 21);
    for(LinkedList<const TreeNode<int>*>::iterator ptr = list.begin(); ptr != list.end(); ptr++ )
        cout << (*ptr)->key<< " ";
    cout << endl;
}

void show_node(TreeNode<int> *s){
    int pk = s->parent != NULL ? s->parent->key: -1;
    int lk = s->left != NULL ? s->left->key : -1;
    int rk = s->right != NULL ? s->right->key : -1;
    cout << "key:" << s->key << " height:" << s->height << endl;
    cout << pk << " " << lk << " " << rk << endl;
}

void avl_insert_single_rotation_r() {
    AVLTree<int> tree;
    tree.avl_insert(30);
    tree.avl_insert(35);
    tree.avl_insert(15);
    // tree.avl_insert(25);
    tree.avl_insert(10);
    show_node(tree.search(30));
    show_node(tree.search(35));
    show_node(tree.search(15));
    show_node(tree.search(25));
    show_node(tree.search(10));
    tree.avl_insert(13); //5, 13
    cout << "after rebalancing\n";
    show_node(tree.search(30));
    show_node(tree.search(35));
    show_node(tree.search(15));
    show_node(tree.search(25));
    show_node(tree.search(10));
    show_node(tree.search(13));
}

void avl_insert_double_rotation_lr() {
    AVLTree<int> tree;
    tree.avl_insert(30);
    tree.avl_insert(35);
    tree.avl_insert(15);
    tree.avl_insert(25);
    tree.avl_insert(10);
    show_node(tree.search(30));
    show_node(tree.search(35));
    show_node(tree.search(15));
    show_node(tree.search(25));
    show_node(tree.search(10));
    tree.avl_insert(20); //27, 20 
    cout << "after rebalancing\n";
    show_node(tree.search(30));
    show_node(tree.search(35));
    show_node(tree.search(15));
    show_node(tree.search(25));
    show_node(tree.search(10));
    show_node(tree.search(20));
}

void avl_insert_single_rotation_l() {
    AVLTree<int> tree;
    tree.avl_insert(20);
    tree.avl_insert(30);
    tree.avl_insert(10);
    tree.avl_insert(25);
    tree.avl_insert(35);
    show_node(tree.search(20));
    show_node(tree.search(30));
    show_node(tree.search(10));
    show_node(tree.search(25));
    show_node(tree.search(35));
    tree.avl_insert(37); // 33, 37 
    cout << "after rebalancing\n";
    show_node(tree.search(20));
    show_node(tree.search(30));
    show_node(tree.search(10));
    show_node(tree.search(25));
    show_node(tree.search(35));
    show_node(tree.search(37));
}

void avl_insert_double_rotation_rl() {
    AVLTree<int> tree;
    tree.avl_insert(20);
    tree.avl_insert(30);
    tree.avl_insert(10);
    tree.avl_insert(25);
    tree.avl_insert(35);
    show_node(tree.search(20));
    show_node(tree.search(30));
    show_node(tree.search(10));
    show_node(tree.search(25));
    show_node(tree.search(35));
    tree.avl_insert(23); // 23, 27
    cout << "after rebalancing\n";
    show_node(tree.search(20));
    show_node(tree.search(30));
    show_node(tree.search(10));
    show_node(tree.search(25));
    show_node(tree.search(35));
    show_node(tree.search(23));
}
// n has no right children; n has no parent.
void avl_remove_test_1() {
    AVLTree<int> tree;
    tree.avl_insert(20);
    tree.avl_insert(10);
    show_node(tree.search(10));
    tree.avl_remove(tree.search(20));
    show_node(tree.search(10));
    
}

// n has no right children; n has a parent.
void avl_remove_test_2() {
    AVLTree<int> tree;
    tree.avl_insert(20);
    tree.avl_insert(30);
    tree.avl_insert(10);
    tree.avl_insert(5);
    show_node(tree.search(20));
    tree.avl_remove(tree.search(10));
    show_node(tree.search(20));
}

// n has right children; x->p = n and n has no parent.
void avl_remove_test_3() {
    AVLTree<int> tree;
    tree.avl_insert(20);
    tree.avl_insert(30);
    tree.avl_insert(10);
    show_node(tree.search(30));
    tree.avl_remove(tree.search(20));
    show_node(tree.search(30));
}
// n has right children; x->p = n, n has a parent.
void avl_remove_test_4() {
    AVLTree<int> tree;
    tree.avl_insert(10);
    tree.avl_insert(5);
    tree.avl_insert(20);
    tree.avl_insert(30);
    show_node(tree.search(10));
    tree.avl_remove(tree.search(20));
    show_node(tree.search(10));
}

// TODO: n has right children; x->p != n, n has a parent.
void avl_remove_test_5() {
    AVLTree<int> tree;
    tree.avl_insert(50);
    
    tree.avl_insert(25);
    tree.avl_insert(75);
    
    tree.avl_insert(12);
    tree.avl_insert(37);
    tree.avl_insert(62);
    tree.avl_insert(87);
    
    tree.avl_insert(6);
    tree.avl_insert(18);
    tree.avl_insert(31);
    tree.avl_insert(43);
    tree.avl_insert(56);
    tree.avl_insert(68);
    tree.avl_insert(81);
    tree.avl_insert(93);
    
    tree.avl_insert(3);
    tree.avl_insert(9);
    tree.avl_insert(15);
    tree.avl_insert(21);
    tree.avl_insert(28);
    tree.avl_insert(34);
    tree.avl_insert(40);
    tree.avl_insert(46);
    tree.avl_insert(53);
    tree.avl_insert(59);
    tree.avl_insert(65);
    tree.avl_insert(71);
    tree.avl_insert(78);
    tree.avl_insert(84);
    tree.avl_insert(90);
    tree.avl_insert(96);
    
    tree.avl_insert(79);
    
    show_node(tree.search(81));
    tree.avl_remove(tree.search(75));
    show_node(tree.search(81));
}

int main() {
    insert_test();
    left_descendant_test();
    right_ancestor_test();
    no_right_ancestor_test();
    range_test();
    remove_test();
    // avl_insert_single_rotation_r();
    // avl_insert_double_rotation_lr();
    // avl_insert_single_rotation_l();
    // avl_insert_double_rotation_rl();
    avl_remove_test_1();
    avl_remove_test_2();
    avl_remove_test_3();
    avl_remove_test_4();
    avl_remove_test_5();
    cout << "finished\n";
}
