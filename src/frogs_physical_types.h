#ifndef _FROGS_PHYSICAL_TYPES_H
#define _FROGS_PHYSICAL_TYPES_H

#include "frogs_types_creator.h"
#include "frogs_types_fallback.h"
#include "frogs_constants.h"

namespace frogs
{

/* All forward declarations */

DECL_FWD(Distance)
DECL_FWD(Time)
DECL_FWD(Velocity)
DECL_FWD(Acceleration)
DECL_FWD(Mass)
DECL_FWD(MassFlow)
DECL_FWD(Momentum)
DECL_FWD(Force)
DECL_FWD(Power)
DECL_FWD(Angle)

/* All class definitions */

DECL_CLASS( Distance,
            meters,
            DECL_UNIT(Distance<1>, _m,     toMeters,       1.0)
            DECL_UNIT(Distance<1>, _cm,    toCentimeters,  1.0e-2)
            DECL_UNIT(Distance<1>, _mm,    toMillimeters,  1.0e-3)
            DECL_UNIT(Distance<1>, _um,    toMicrometers,  1.0e-6)
            DECL_UNIT(Distance<1>, _nm,    toNanometers,   1.0e-9)
            DECL_UNIT(Distance<1>, _km,    toKilometers,   1.0e+3)
            DECL_UNIT(Distance<1>, _inch,  toInches,       0.0254)
            DECL_UNIT(Distance<1>, _ft,    toFeet,         0.3048)
            DECL_UNIT(Distance<1>, _miles, toMiles,        1609.344)
            DECL_CONV_MUL(Distance<1>, Velocity<1>, Time<1>) )

DECL_CLASS( Angle,
            rad,
            DECL_UNIT(Angle<1>, _rad, toRadians, 1.0)
            DECL_UNIT(Angle<1>, _deg, toDegrees, PI/180.0)
            friend constexpr Real Cos(Angle<1> v);
            friend constexpr Real Sin(Angle<1> v);
            friend constexpr Real Tan(Angle<1> v);
            friend constexpr Angle<1> ACos(Real v);
            friend constexpr Angle<1> ASin(Real v);
            friend constexpr Angle<1> ATan(Real v);
            friend constexpr Angle<1> ATan2(Real a, Real b);
            friend constexpr Angle<1> ATan2(Distance<1> a, Distance<1> b); )

DECL_CLASS( Time,
            seconds,
            DECL_UNIT(Time<1>, _hours,   toHours,         3600.0)
            DECL_UNIT(Time<1>, _minutes, toMinutes,       60.0)
            DECL_UNIT(Time<1>, _sec,     toSeconds,       1.0e+0)
            DECL_UNIT(Time<1>, _msec,    toMilliseconds,  1.0e-3)
            DECL_UNIT(Time<1>, _usec,    toMicroseconds,  1.0e-6)
            DECL_UNIT(Time<1>, _nsec,    toNanoseconds,   1.0e-9) )

DECL_CLASS( Velocity,
            m/s,
            DECL_UNIT(Velocity<1>, _kmph, toKilometersPerHour,  1.0/3.6)
            DECL_UNIT(Velocity<1>, _mph,  toMilesPerHour,       0.44704)
            DECL_UNIT(Velocity<1>, _mps,  toMetersPerSecond,    1.0e+0)
            DECL_CONV_DIV(Velocity<1>, Distance<1>, Time<1>)
            DECL_CONV_MUL(Velocity<1>, Acceleration<1>, Time<1>) )

DECL_CLASS( Acceleration,
            m/s2,
            DECL_UNIT(Acceleration<1>, _mps2,  toMetersPerSecond2,      1.0e+0)
            DECL_UNIT(Acceleration<1>, _mmps2, toMillimetersPerSecond2, 1.0e-3)
            DECL_UNIT(Acceleration<1>, _umps2, toMicrometersPerSecond2, 1.0e-6)
            DECL_UNIT(Acceleration<1>, _nmps2, toNanometersPerSecond2,  1.0e-9)
            DECL_CONV_DIV(Acceleration<1>, Velocity<1>, Time<1>)
            DECL_CONV_DIV(Acceleration<1>, Distance<1>, Time<2>)
            DECL_CONV_MUL(Acceleration<1>, Distance<1>, Time<-2>) )

DECL_CLASS( Mass,
            kg,
            DECL_UNIT(Mass<1>, _kg, toKilograms,  1.0e+3)
            DECL_UNIT(Mass<1>, _g,  toGrams,      1.0e+0)
            DECL_UNIT(Mass<1>, _mg, toMilligrams, 1.0e-3)
            DECL_UNIT(Mass<1>, _ug, toMicrograms, 1.0e-6)
            DECL_UNIT(Mass<1>, _ng, toNanograms,  1.0e-9)
            DECL_UNIT(Mass<1>, _lb, toPounds,     453.59)
            DECL_UNIT(Mass<1>, _oz, toOunces,     28.350) )

DECL_CLASS( MassFlow,
            g/s,
            DECL_UNIT(MassFlow<1>, _gps,  toGramsPerSecond,      1.0e+0)
            DECL_UNIT(MassFlow<1>, _kgps, toKilogramsPerSecond,  1.0e+3)
            DECL_CONV_DIV(MassFlow<1>, Mass<1>, Time<1>) )

DECL_CLASS( Momentum,
            g*m/s,
            DECL_UNIT(Momentum<1>, _kgmps, toKilogramsMetersPerSecond, 1.0e+3)
            DECL_UNIT(Momentum<1>, _gmps,  toGramsMetersPerSecond,     1.0)
            DECL_CONV_MUL(Momentum<1>, Mass<1>, Velocity<1>)
            DECL_CONV_AB_DIV_C(Momentum<1>, Mass<1>, Distance<1>, Time<1>)
            DECL_CONV_MUL(Momentum<1>, MassFlow<1>, Distance<1>)
            DECL_CONV_MUL(Momentum<1>, Force<1>, Time<1>) )

DECL_CLASS( Force,
            N,
            DECL_UNIT(Force<1>, _N, toNewtons, 1.0e+0)
            DECL_CONV_MUL(Force<1>, Mass<1>, Acceleration<1>)
            DECL_CONV_DIV(Force<1>, Momentum<1>, Time<1>) )

DECL_CLASS( Energy,
            J,
            DECL_UNIT(Energy<1>, _J,    toJoules,       1.0e+0)
            DECL_UNIT(Energy<1>, _kJ,   toKilojoules,   1.0e+3)
            DECL_UNIT(Energy<1>, _MJ,   toMegajoules,   1.0e+6)
            DECL_UNIT(Energy<1>, _GJ,   toGigajoules,   1.0e+9)
            DECL_UNIT(Energy<1>, _mJ,   toMillijoules,  1.0e-3)
            DECL_UNIT(Energy<1>, _uJ,   toMicrojoules,  1.0e-6)
            DECL_UNIT(Energy<1>, _nJ,   toNanojoules,   1.0e-9)
            DECL_UNIT(Energy<1>, _kWh,  toKilowattHour, 3.6e+6)
            DECL_UNIT(Energy<1>, _cal,  toCalories,     4.184e+0)
            DECL_UNIT(Energy<1>, _kcal, toKilocalories, 4.184e+3) )

DECL_CLASS( Power,
            W,
            DECL_UNIT(Power<1>, _GW,  toGigaWatts,  1.0e+9)
            DECL_UNIT(Power<1>, _MW,  toMegaWatts,  1.0e+6)
            DECL_UNIT(Power<1>, _kW,  toKiloWatts,  1.0e+3)
            DECL_UNIT(Power<1>, _W,   toWatts,      1.0e+0)
            DECL_UNIT(Power<1>, _mW,  toMilliWatts, 1.0e-3)
            DECL_UNIT(Power<1>, _uW,  toMicroWatts, 1.0e-6)
            DECL_CONV_DIV(Power<1>, Energy<1>, Time<1>)
            DECL_CONV_AB_DIV_C(Power<1>, Force<1>, Distance<1>, Time<1>) )

/* All implementations */

IMPL_CLASS(Distance)
IMPL_UNIT(Distance<1>, _m)
IMPL_UNIT(Distance<1>, _cm)
IMPL_UNIT(Distance<1>, _mm)
IMPL_UNIT(Distance<1>, _um)
IMPL_UNIT(Distance<1>, _nm)
IMPL_UNIT(Distance<1>, _km)
IMPL_UNIT(Distance<1>, _inch)
IMPL_UNIT(Distance<1>, _ft)
IMPL_UNIT(Distance<1>, _miles)
IMPL_CONV_MUL(Distance<1>, Velocity<1>, toMetersPerSecond, Time<1>, toSeconds)

IMPL_CLASS(Angle)
IMPL_UNIT(Angle<1>, _rad)
IMPL_UNIT(Angle<1>, _deg)
constexpr Real Cos(Angle<1> v) { return cos(v.m_value); }
constexpr Real Sin(Angle<1> v) { return sin(v.m_value); }
constexpr Real Tan(Angle<1> v) { return tan(v.m_value); }
constexpr Angle<1> ACos(Real v) { return {acos(v)}; }
constexpr Angle<1> ASin(Real v) { return {asin(v)}; }
constexpr Angle<1> ATan(Real v) { return {atan(v)}; }
constexpr Angle<1> ATan2(Real a, Real b) { return {atan2(a,b)}; }
constexpr Angle<1> ATan2(Distance<1> a, Distance<1> b)
{ return {atan2(a.toMeters(), b.toMeters())}; }

IMPL_CLASS(Time)
IMPL_UNIT(Time<1>, _hours)
IMPL_UNIT(Time<1>, _minutes)
IMPL_UNIT(Time<1>, _sec)
IMPL_UNIT(Time<1>, _msec)
IMPL_UNIT(Time<1>, _usec)
IMPL_UNIT(Time<1>, _nsec)

IMPL_CLASS(Velocity)
IMPL_UNIT(Velocity<1>, _kmph)
IMPL_UNIT(Velocity<1>, _mph)
IMPL_UNIT(Velocity<1>, _mps)
IMPL_CONV_DIV(Velocity<1>, Distance<1>, toMeters, Time<1>, toSeconds)
IMPL_CONV_MUL(Velocity<1>, Acceleration<1>, toMetersPerSecond2, Time<1>, toSeconds)

IMPL_CLASS(Acceleration)
IMPL_UNIT(Acceleration<1>, _mps2)
IMPL_UNIT(Acceleration<1>, _mmps2)
IMPL_UNIT(Acceleration<1>, _umps2)
IMPL_UNIT(Acceleration<1>, _nmps2)
IMPL_CONV_DIV(Acceleration<1>, Velocity<1>, toMetersPerSecond, Time<1>, toSeconds)
IMPL_CONV_DIV(Acceleration<1>, Distance<1>, toMeters, Time<2>, toSeconds)
IMPL_CONV_MUL(Acceleration<1>, Distance<1>, toMeters, Time<-2>, toSeconds)

IMPL_CLASS(Mass)
IMPL_UNIT(Mass<1>, _kg)
IMPL_UNIT(Mass<1>, _g)
IMPL_UNIT(Mass<1>, _mg)
IMPL_UNIT(Mass<1>, _ug)
IMPL_UNIT(Mass<1>, _ng)
IMPL_UNIT(Mass<1>, _lb)
IMPL_UNIT(Mass<1>, _oz)

IMPL_CLASS(MassFlow)
IMPL_UNIT(MassFlow<1>, _kgps)
IMPL_UNIT(MassFlow<1>, _gps)
IMPL_CONV_DIV(MassFlow<1>, Mass<1>, toGrams, Time<1>, toSeconds)

IMPL_CLASS(Momentum)
IMPL_UNIT(Momentum<1>, _kgmps)
IMPL_CONV_MUL(Momentum<1>, Mass<1>, toGrams, Velocity<1>, toMetersPerSecond)
IMPL_CONV_MUL(Momentum<1>, MassFlow<1>, toGramsPerSecond, Distance<1>, toMeters)
IMPL_CONV_MUL(Momentum<1>, Force<1>, toNewtons, Distance<1>, toMeters)
IMPL_CONV_AB_DIV_C(Momentum<1>, Mass<1>, toGrams, Distance<1>, toMeters, Time<1>, toSeconds)

IMPL_CLASS(Force)
IMPL_UNIT(Force<1>, _N)
IMPL_CONV_MUL(Force<1>, Mass<1>, toGrams, Acceleration<1>, toMetersPerSecond2)
IMPL_CONV_DIV(Force<1>, Momentum<1>, toGramsMetersPerSecond, Time<1>, toSeconds)

IMPL_CLASS(Energy)
IMPL_UNIT(Energy<1>, _J)
IMPL_UNIT(Energy<1>, _kJ)
IMPL_UNIT(Energy<1>, _MJ)
IMPL_UNIT(Energy<1>, _GJ)
IMPL_UNIT(Energy<1>, _mJ)
IMPL_UNIT(Energy<1>, _uJ)
IMPL_UNIT(Energy<1>, _nJ)
IMPL_UNIT(Energy<1>, _kWh)
IMPL_UNIT(Energy<1>, _cal)
IMPL_UNIT(Energy<1>, _kcal)

IMPL_CLASS(Power)
IMPL_UNIT(Power<1>, _GW)
IMPL_UNIT(Power<1>, _MW)
IMPL_UNIT(Power<1>, _kW)
IMPL_UNIT(Power<1>, _W)
IMPL_UNIT(Power<1>, _mW)
IMPL_UNIT(Power<1>, _uW)
IMPL_CONV_DIV(Power<1>, Energy<1>, toJoules, Time<1>, toSeconds)
IMPL_CONV_AB_DIV_C(Power<1>, Force<1>, toNewtons, Distance<1>, toMeters, Time<1>, toSeconds)

} // namespace frogs

#endif // _FROGS_PHYSICAL_TYPES_H
