#include <iostream>
#include "SLink.h"
#include "SNode.h"

using namespace std;

int main()
{
    SLink<double> a;
    a.Insert(1.01); 
    a.Insert(2.02);
    a.Insert(3.03);
    a.Traverse(true);

    a.Insert(2, 0.95);
    a.Traverse(true);
}
