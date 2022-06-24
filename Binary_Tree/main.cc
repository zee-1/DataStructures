#include "BTree.h"
#include <iostream>


using std::cout;
using std::endl;

int main(int argc, char const *argv[])
{
    BST<int> t({4,2,7,1,5,8});
    t.postorder_Rec(t.root);
    cout<<"-------------"<<endl;
    t.postorder();
    std::cout<<"-------------------"<<std::endl;
    std::cout<<""<<std::endl;
    t.inorder();
    std::cout<<"-------------------"<<std::endl;
    t.deletionByCopying(t.root);
    t.BreadthFisrt();
    t.findAndDeleteMerging(2);
    t.BreadthFisrt();
    return 0;
}
