#include "frogs.h"

using namespace std;
using namespace frogs;

int32_t main()
{
    cout << "**********************************************************" << endl;
    cout << "* This example shows how to use mathematical expressions *" << endl;
    cout << "**********************************************************" << endl;
    cout << endl;

    /* Declaring distance and time variables but as a Var. They're not just C++
     * variables, but also a FROGS variables and any changes in them will actively
     * reflect in any expression it's used in. We could give them names or let the
     * library give them default names. It's more debuggable if we give them names.
     */
    auto x = Var{2000_m, "x"};
    auto y = Var{2000_m, "y"};
    auto t = Var{20_minutes, "t"};

    /* Let's print the values of these variables. Since they're active FROGS variables
     * whose values are being tracked and not just C++ variables, we should use the 
     * dollar sign with them so that we get the actual value and not the container.
     */
    cout << "x = " << $(x) << endl;
    cout << "y = " << $(y) << endl;
    cout << "t = " << $(t) << endl;

    /* Now the velocity will be calculated from all these variables. We could 
     * split it into several expressions just to make it easier:
     */
    auto distance = Sqrt(x*x + y*y);
    auto velocity = distance / t;
    auto angle = ATan2(y, x);
    auto velocity_x = Cos(angle) * distance;
    auto velocity_y = Sin(angle) * distance;

    /* Now let's see their values. Since it's an expression and not just a
     * variable, we need to evaluate it at this particular moment.
     * Which is done using the dollar sign:
     */
    cout << "Velocity now = " << $(velocity) << endl;
    cout << "Angle now = " << $(angle) << endl;
    cout << "Velocity (x,y) = " << $(velocity_x) << ", " << $(velocity_y) << endl;

    /* Now let's change the variables to see what happens */
    x += 250_m;
    y -= 60_m;
    t *= 1.5;
    cout << "After that change:" << endl;
    cout << "Velocity now = " << $(velocity) << endl;
    cout << "Angle now = " << $(angle) << endl;
    cout << "Velocity (x,y) = " << $(velocity_x) << ", " << $(velocity_y) << endl;

    /* We could also view the expressions themselves and see what they're made of.
     * This is done by printing it without the dollar sign.
     */
    cout << "Velocity expression = " << velocity << endl;
    cout << "Angle expression = " << angle << endl;
    cout << "Velocity_x = " << velocity_x << endl;
    cout << "Velocity_y = " << velocity_y << endl;

    return 0;
}
