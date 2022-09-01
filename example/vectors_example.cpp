#include "frogs.h"

using namespace std;
using namespace frogs;

int32_t main()
{
    cout << "*****************************************" << endl;
    cout << "* This example shows how to use vectors *" << endl;
    cout << "*****************************************" << endl;
    cout << endl;

    /* Declaring position (distance) vectors */
    auto point0 = (10_m, 10_m, 10_m);
    auto point1 = (20_m, 30_m, 40_m);
    auto delta = point1 - point0;
    auto time = 0.5_sec;
    auto velocities = delta / time;
    auto velocity = Hypot(delta) / time;

    cout << "From " << point0 << " to " << point1 << " in " << time
         << " is " << velocity << " " << velocities << endl;

    return 0;
}
