#include "frogs.h"

using namespace std;
using namespace frogs;

int32_t main()
{
    cout << "*****************************************************" << endl;
    cout << "* This example shows how to use physical quantities *" << endl;
    cout << "*****************************************************" << endl;
    cout << endl;

    /* Declaring a distance variable and a time variable. */
    auto d = 20_km;
    auto t = 30_minutes;

    cout << "Declared distance and time variables:" << endl;
    cout << "d = " << d << endl;
    cout << "t = " << d << endl;

    /* Now if we divide the distance by the time, we should get a velocity */
    auto v = d/t;

    cout << "Dividing distance by time should give a velocity:" << endl;
    cout << "v = " << v << endl;

    cout << "Converting them to different units:" << endl;
    cout << "t in minutes = " << $(t).toMinutes() << endl;
    cout << "t in seconds = " << $(t).toSeconds() << endl;
    cout << "t in milliseconds = " << $(t).toMilliseconds() << endl;
    cout << "d in meters = " << $(d).toMeters() << endl;
    cout << "d in inches = " << $(d).toInches() << endl;
    cout << "d in miles = " << $(d).toMiles() << endl;
    cout << "v in kmph = " << $(v).toKilometersPerHour() << endl;
    cout << "v in mps = " << $(v).toMetersPerSecond() << endl;
    cout << "v in mph = " << $(v).toMilesPerHour() << endl;

    return 0;
}
