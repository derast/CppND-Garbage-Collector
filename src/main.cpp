#include <iostream>
#include "LeakTester.h"
#include "Pointer.h"

int main()
{
    sp::Pointer<int>::showlist();
    sp::Pointer<int> p = new int(19);
    p = new int(21);
    p = new int(28);
    sp::Pointer<int>::showlist();

    return 0;
}