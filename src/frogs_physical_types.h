#ifndef _FROGS_PHYSICAL_TYPES_H
#define _FROGS_PHYSICAL_TYPES_H

#include "frogs_types_creator.h"
#include "frogs_types_fallback.h"

namespace frogs
{

/* All forward declarations */

DECL_FWD(Distance)
DECL_FWD(Area)
DECL_FWD(Volume)
DECL_FWD(Time)
DECL_FWD(Time2)
DECL_FWD(Velocity)
DECL_FWD(Acceleration)
DECL_FWD(Mass)
DECL_FWD(Force)
DECL_FWD(Angle)

/* All class definitions */

DECL_CLASS( Distance,
            meters,
            DECL_UNIT(Distance, _m,     toMeters,       1.0)
            DECL_UNIT(Distance, _cm,    toCentimeters,  1.0e-2)
            DECL_UNIT(Distance, _mm,    toMillimeters,  1.0e-3)
            DECL_UNIT(Distance, _um,    toMicrometers,  1.0e-6)
            DECL_UNIT(Distance, _nm,    toNanometers,   1.0e-9)
            DECL_UNIT(Distance, _km,    toKilometers,   1.0e+3)
            DECL_UNIT(Distance, _inch,  toInches,       0.0254)
            DECL_UNIT(Distance, _ft,    toFeet,         0.3048)
            DECL_UNIT(Distance, _miles, toMiles,        1609.344)
            DECL_CONV_DIV(Distance, Area, Distance)
            DECL_CONV_MUL(Distance, Velocity, Time)
            friend constexpr Distance Sqrt(Area a); )

DECL_CLASS( Area,
            m2,
            DECL_UNIT(Area, _km2, toKilometers2,  1.0e+6)
            DECL_UNIT(Area, _m2,  toMeters2,      1.0e+0)
            DECL_UNIT(Area, _cm2, toCentimeters2, 1.0e-4)
            DECL_UNIT(Area, _mm2, toMillimeters2, 1.0e-6)
            DECL_UNIT(Area, _um2, toMicrometers2, 1.0e-12)
            DECL_UNIT(Area, _nm2, toNanometers2,  1.0e-18)
            DECL_CONV_SQR(Area, Distance) )

DECL_CLASS( Volume,
            m3,
            DECL_UNIT(Volume, _km3, toKilometers3,  1.0e+9)
            DECL_UNIT(Volume, _m3,  toMeters3,      1.0e+0)
            DECL_UNIT(Volume, _cm3, toCentimeters3, 1.0e-8)
            DECL_UNIT(Volume, _mm3, toMillimeters3, 1.0e-9)
            DECL_UNIT(Volume, _um3, toMicrometers3, 1.0e-18)
            DECL_UNIT(Volume, _nm3, toNanometers3,  1.0e-27)
            DECL_CONV_MUL(Volume, Area, Distance) )

DECL_CLASS( Time,
            seconds,
            DECL_UNIT(Time, _hours,   toHours,         3600.0)
            DECL_UNIT(Time, _minutes, toMinutes,       60.0)
            DECL_UNIT(Time, _sec,     toSeconds,       1.0e+0)
            DECL_UNIT(Time, _msec,    toMilliseconds,  1.0e-3)
            DECL_UNIT(Time, _usec,    toMicroseconds,  1.0e-6)
            DECL_UNIT(Time, _nsec,    toNanoseconds,   1.0e-9) )

DECL_CLASS( Velocity,
            m/s,
            DECL_UNIT(Velocity, _kmph, toKilometersPerHour,  1.0/3.6)
            DECL_UNIT(Velocity, _mph,  toMilesPerHour,       0.44704)
            DECL_UNIT(Velocity, _mps,  toMetersPerSecond,    1.0e+0)
            DECL_CONV_DIV(Velocity, Distance, Time)
            DECL_CONV_MUL(Velocity, Acceleration, Time) )

DECL_CLASS( Acceleration,
            m/s2,
            DECL_UNIT(Acceleration, _mps2,  toMetersPerSecond2,      1.0e+0)
            DECL_UNIT(Acceleration, _mmps2, toMillimetersPerSecond2, 1.0e-3)
            DECL_UNIT(Acceleration, _umps2, toMicrometersPerSecond2, 1.0e-6)
            DECL_UNIT(Acceleration, _nmps2, toNanometersPerSecond2,  1.0e-9)
            DECL_CONV_DIV(Acceleration, Velocity, Time) )

DECL_CLASS( Mass,
            kg,
            DECL_UNIT(Mass, _kg, toKilograms,  1.0e+3)
            DECL_UNIT(Mass, _g,  toGrams,      1.0e+0)
            DECL_UNIT(Mass, _mg, toMilligrams, 1.0e-3)
            DECL_UNIT(Mass, _ug, toMicrograms, 1.0e-6)
            DECL_UNIT(Mass, _ng, toNanograms,  1.0e-9)
            DECL_UNIT(Mass, _lb, toPounds,     453.59)
            DECL_UNIT(Mass, _oz, toOunces,     28.350) )

DECL_CLASS( MassFlow,
            g/s,
            DECL_UNIT(MassFlow, _gps,  toGramsPerSecond,      1.0e+0)
            DECL_UNIT(MassFlow, _kgps, toKilogramsPerSecond,  1.0e+3)
            DECL_CONV_DIV(MassFlow, Mass, Time) )

DECL_CLASS( Momentum,
            g*m/s,
            DECL_UNIT(Momentum, _kgmps, toKilogramsMetersPerSecond, 1.0e+3)
            DECL_UNIT(Momentum, _gmps,  toGramsMetersPerSecond,     1.0)
            DECL_CONV_MUL(Momentum, Mass, Velocity)
            DECL_CONV_AB_DIV_C(Momentum, Mass, Distance, Time)
            DECL_CONV_MUL(Momentum, MassFlow, Distance)
            DECL_CONV_MUL(Momentum, Force, Time) )

DECL_CLASS( Force,
            N,
            DECL_UNIT(Force, _N, toNewtons, 1.0e+0)
            DECL_CONV_MUL(Force, Mass, Acceleration)
            DECL_CONV_DIV(Force, Momentum, Time) )

DECL_CLASS( Energy,
            J,
            DECL_UNIT(Energy, _J,    toJoules,       1.0e+0)
            DECL_UNIT(Energy, _kJ,   toKilojoules,   1.0e+3)
            DECL_UNIT(Energy, _MJ,   toMegajoules,   1.0e+6)
            DECL_UNIT(Energy, _GJ,   toGigajoules,   1.0e+9)
            DECL_UNIT(Energy, _mJ,   toMillijoules,  1.0e-3)
            DECL_UNIT(Energy, _uJ,   toMicrojoules,  1.0e-6)
            DECL_UNIT(Energy, _nJ,   toNanojoules,   1.0e-9)
            DECL_UNIT(Energy, _kWh,  toKilowattHour, 3.6e+6)
            DECL_UNIT(Energy, _cal,  toCalories,     4.184e+0)
            DECL_UNIT(Energy, _kcal, toKilocalories, 4.184e+3) )

DECL_CLASS( Power,
            W,
            DECL_UNIT(Power, _GW,  toGigaWatts,  1.0e+9)
            DECL_UNIT(Power, _MW,  toMegaWatts,  1.0e+6)
            DECL_UNIT(Power, _kW,  toKiloWatts,  1.0e+3)
            DECL_UNIT(Power, _W,   toWatts,      1.0e+0)
            DECL_UNIT(Power, _mW,  toMilliWatts, 1.0e-3)
            DECL_UNIT(Power, _uW,  toMicroWatts, 1.0e-6)
            DECL_CONV_DIV(Power, Energy, Time)
            DECL_CONV_DIV(Power, Force, Time) )

/* All implementations */

IMPL_UNIT(Distance, _m)
IMPL_UNIT(Distance, _cm)
IMPL_UNIT(Distance, _mm)
IMPL_UNIT(Distance, _um)
IMPL_UNIT(Distance, _nm)
IMPL_UNIT(Distance, _km)
IMPL_UNIT(Distance, _inch)
IMPL_UNIT(Distance, _ft)
IMPL_UNIT(Distance, _miles)
IMPL_CONV_DIV(Distance, Area, toMeters2, Distance, toMeters)
IMPL_CONV_MUL(Distance, Velocity, toMetersPerSecond, Time, toSeconds)

IMPL_UNIT(Time, _hours)
IMPL_UNIT(Time, _minutes)
IMPL_UNIT(Time, _sec)
IMPL_UNIT(Time, _msec)
IMPL_UNIT(Time, _usec)
IMPL_UNIT(Time, _nsec)

IMPL_UNIT(Velocity, _kmph)
IMPL_UNIT(Velocity, _mph)
IMPL_UNIT(Velocity, _mps)
IMPL_CONV_DIV(Velocity, Distance, toMeters, Time, toSeconds)
IMPL_CONV_MUL(Velocity, Acceleration, toMetersPerSecond2, Time, toSeconds)

IMPL_UNIT(Acceleration, _mps2)
IMPL_UNIT(Acceleration, _mmps2)
IMPL_UNIT(Acceleration, _umps2)
IMPL_UNIT(Acceleration, _nmps2)
IMPL_CONV_DIV(Acceleration, Velocity, toMetersPerSecond, Time, toSeconds)

IMPL_UNIT(Mass, _kg)
IMPL_UNIT(Mass, _g)
IMPL_UNIT(Mass, _mg)
IMPL_UNIT(Mass, _ug)
IMPL_UNIT(Mass, _ng)
IMPL_UNIT(Mass, _lb)
IMPL_UNIT(Mass, _oz)

IMPL_UNIT(Area, _km2)
IMPL_UNIT(Area, _m2)
IMPL_UNIT(Area, _cm2)
IMPL_UNIT(Area, _mm2)
IMPL_UNIT(Area, _um2)
IMPL_UNIT(Area, _nm2)
IMPL_CONV_SQR(Area, Distance, toMeters)

IMPL_UNIT(Volume, _km3)
IMPL_UNIT(Volume, _m3)
IMPL_UNIT(Volume, _cm3)
IMPL_UNIT(Volume, _mm3)
IMPL_UNIT(Volume, _um3)
IMPL_UNIT(Volume, _nm3)
IMPL_CONV_MUL(Volume, Area, toMeters2, Distance, toMeters)

IMPL_UNIT(MassFlow, _kgps)
IMPL_UNIT(MassFlow, _gps)
IMPL_CONV_DIV(MassFlow, Mass, toGrams, Time, toSeconds)

IMPL_UNIT(Momentum, _kgmps)
IMPL_CONV_MUL(Momentum, Mass, toGrams, Velocity, toMetersPerSecond)
IMPL_CONV_MUL(Momentum, MassFlow, toGramsPerSecond, Distance, toMeters)
IMPL_CONV_MUL(Momentum, Force, toNewtons, Distance, toMeters)
IMPL_CONV_AB_DIV_C(Momentum, Mass, toGrams, Distance, toMeters, Time, toSeconds)

IMPL_UNIT(Force, _N)
IMPL_CONV_MUL(Force, Mass, toGrams, Acceleration, toMetersPerSecond2)
IMPL_CONV_DIV(Force, Momentum, toGramsMetersPerSecond, Time, toSeconds)

IMPL_UNIT(Energy, _J)
IMPL_UNIT(Energy, _kJ)
IMPL_UNIT(Energy, _MJ)
IMPL_UNIT(Energy, _GJ)
IMPL_UNIT(Energy, _mJ)
IMPL_UNIT(Energy, _uJ)
IMPL_UNIT(Energy, _nJ)
IMPL_UNIT(Energy, _kWh)
IMPL_UNIT(Energy, _cal)
IMPL_UNIT(Energy, _kcal)

constexpr Distance Sqrt(Area a) { return {sqrt(a.toMeters2())}; }

} // namespace frogs

#endif // _FROGS_PHYSICAL_TYPES_H
