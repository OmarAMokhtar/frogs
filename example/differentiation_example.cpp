#include "frogs.h"

using namespace std;
using namespace frogs;

int32_t main()
{
    cout << "*******************************************************" << endl;
    cout << "* This example shows how to differentiate expressions *" << endl;
    cout << "*******************************************************" << endl;
    cout << endl;

    /* Let's create the classic equation of getting the distance at a certain time.
     * Our variable is of type Time and initially at zero.
     */
    auto t = Var{0_sec};
    /* Then the 2nd degree equation: */
    auto distance = 0.2_mps2*t*t;// + 10_mps*t + 20_m;

    /* Now the velocity equation should be the first derivative: */
    auto velocity = Diff(distance, t);

    // /* And the acceleration equation is the second derivative: */
    auto acceleration = Diff(velocity, t);

    /* Let's print the formulas first: */
    cout << "distance = " << distance << endl;
    cout << "velocity = " << velocity << endl;
    cout << "acceleration = " << acceleration << endl;

    /* Now let's evaluate all of them at different values of t */
    for ( ; t < 3_sec ; t += 0.5_sec)
    {
        cout << "distance(" << $(t) << ") = " << $(distance) << endl;
        cout << "velocity(" << $(t) << ") = " << $(velocity) << endl;
        cout << "acceleration(" << $(t) << ") = " << $(acceleration) << endl;
    }

    return 0;
}
