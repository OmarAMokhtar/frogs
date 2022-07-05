#include <string>
#include <iostream>

#include "frogs.h"

using namespace std;
using namespace frogs;

int main()
{
    // Using the physical units
    auto d = 20_km;
    auto t = 30_minutes;
    auto v = d/t;
    
    // Now v is distance / time so it's velocity. Let's see what will be printed.
    cout << v << endl;
    
    // You can also get that speed in different units. This just returns a double.
    cout << "in miles per hour " << v.toMilesPerHour() << endl;
    cout << "in km per hour " << v.toKilometersPerHour() << endl;

    // Since v is a velocity, it should be ok to compare it against other velocities.
    if (v > 39.9_kmph && v < 40.1_kmph)
        cout << "Yes it's almost " << 40_kmph << endl;
    else
        cout << "Wrong expected velocity" << endl;

    // But it shouldn't be ok to compare it against other units.
    // The following part should not compile.
#if 0
    if (v > 50_kg)
        cout << "We just compared mass to velocity" << endl;
#endif

    // So v is d/t but only the value of d and t at that time.
    // If d or t changed their values, v will not be affected.
    // But here's how to do that. Just declare them as a Var:

    auto my_dist_1 = Var{10_m};
    auto my_time_1 = Var{1000_msec};

    auto my_dist_2 = Var{90_m};
    auto my_time_2 = Var{1500_msec};

    auto speed = (my_dist_2 - my_dist_1) / (my_time_2 - my_time_1);

    // Now of course the speed is 160 meters per second. Let's
    // evaluate that expression and see. Since speed now is an
    // expression and not just a value, use the dollar sign:
    cout << "First speed: " << $(speed) << endl;

    // So what happens if we change any of these variables?
    my_dist_2 += 500_cm;
    cout << "Second speed: " << $(speed) << endl;

    return 0;
}
