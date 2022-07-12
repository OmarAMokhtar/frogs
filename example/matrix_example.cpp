#include "frogs.h"

using namespace std;
using namespace frogs;

int32_t main()
{
    cout << "******************************************" << endl;
    cout << "* This example shows how to use matrices *" << endl;
    cout << "******************************************" << endl;
    cout << endl;

    Shape2D shape;
    shape << (+1_m, +1_m);
    shape << (-1_m, +1_m);
    shape << (-1_m, -1_m);
    shape << (+1_m, -1_m);

    cout << "Shape Before Transformation:" << endl;
    cout << shape << endl;

    Mat4 mat;
    mat.rotate(45_deg, 0, 0, 1);
    mat.scale(2.0);

    cout << "Shape After Transformation:" << endl;
    cout << mat * shape << endl;

    return 0;
}
