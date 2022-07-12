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

    /* The transformation is done in the same order
     * as the code. Usually we scale/rotate first
     * and then translate.
     */
    Mat4 mat;
    mat.rotate(45_deg, 0, 0, 1);
    mat.scale(2.0);
    mat.translate(50_m, 50_m);

    cout << "Shape After Transformation:" << endl;
    cout << mat * shape << endl;

    return 0;
}
