#include <string>
#include <iostream>

#include "frogs.h"

using namespace std;
using namespace frogs;

int main()
{
    auto my_dist_1 = Var{10_m};
    auto my_time_1 = Var{1000_msec};

    auto my_dist_2 = Var{100_m};
    auto my_time_2 = Var{2_minutes};

    auto speed_diff = my_dist_1 / my_time_1 - my_dist_2 / my_time_2;

    cout << $(speed_diff) << endl;

    my_dist_1 += 20_m;
    cout << $(speed_diff) << endl;

    my_time_1 += 1_sec;
    cout << $(speed_diff) << endl;

    return 0;
}
