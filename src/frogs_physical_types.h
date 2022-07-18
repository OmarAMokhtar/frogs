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
            DECL_UNIT(DistanceT<1>, _m,      toMeters,       1.0)
            DECL_UNIT(DistanceT<1>, _cm,     toCentimeters,  1.0e-2)
            DECL_UNIT(DistanceT<1>, _mm,     toMillimeters,  1.0e-3)
            DECL_UNIT(DistanceT<1>, _um,     toMicrometers,  1.0e-6)
            DECL_UNIT(DistanceT<1>, _nm,     toNanometers,   1.0e-9)
            DECL_UNIT(DistanceT<1>, _km,     toKilometers,   1.0e+3)
            DECL_UNIT(DistanceT<1>, _inch,   toInches,       0.0254)
            DECL_UNIT(DistanceT<1>, _ft,     toFeet,         0.3048)
            DECL_UNIT(DistanceT<1>, _miles,  toMiles,        1609.344)
            DECL_UNIT(DistanceT<1>, _yd,     toYards,        0.914444)
            DECL_UNIT(DistanceT<2>, _m2,     toMeters2,      convFrom_m*convFrom_m)
            DECL_UNIT(DistanceT<2>, _cm2,    toCentimeters2, convFrom_cm*convFrom_cm)
            DECL_UNIT(DistanceT<2>, _mm2,    toMillimeters2, convFrom_mm*convFrom_mm)
            DECL_UNIT(DistanceT<2>, _um2,    toMicrometers2, convFrom_um*convFrom_um)
            DECL_UNIT(DistanceT<2>, _nm2,    toNanometers2,  convFrom_nm*convFrom_nm)
            DECL_UNIT(DistanceT<2>, _km2,    toKilometers2,  convFrom_km*convFrom_km)
            DECL_UNIT(DistanceT<2>, _inch2,  toInches2,      convFrom_inch*convFrom_inch)
            DECL_UNIT(DistanceT<2>, _ft2,    toFeet2,        convFrom_ft*convFrom_ft)
            DECL_UNIT(DistanceT<2>, _miles2, toMiles2,       convFrom_miles*convFrom_miles)
            DECL_UNIT(DistanceT<2>, _yd2,    toYards2,       convFrom_yd*convFrom_yd)
            DECL_UNIT(DistanceT<2>, _acre,   toAcres,        4047)
            DECL_UNIT(DistanceT<3>, _m3,     toMeters3,      convFrom_m2*convFrom_m)
            DECL_UNIT(DistanceT<3>, _cm3,    toCentimeters3, convFrom_cm2*convFrom_cm)
            DECL_UNIT(DistanceT<3>, _mm3,    toMillimeters3, convFrom_mm2*convFrom_mm)
            DECL_UNIT(DistanceT<3>, _um3,    toMicrometers3, convFrom_um2*convFrom_um)
            DECL_UNIT(DistanceT<3>, _nm3,    toNanometers3,  convFrom_nm2*convFrom_nm)
            DECL_UNIT(DistanceT<3>, _km3,    toKilometers3,  convFrom_km2*convFrom_km)
            DECL_UNIT(DistanceT<3>, _inch3,  toInches3,      convFrom_inch2*convFrom_inch)
            DECL_UNIT(DistanceT<3>, _ft3,    toFeet3,        convFrom_ft2*convFrom_ft)
            DECL_UNIT(DistanceT<3>, _miles3, toMiles3,       convFrom_miles2*convFrom_miles)
            DECL_UNIT(DistanceT<3>, _yd3,    toYards3,       convFrom_yd2*convFrom_yd)
            DECL_UNIT(DistanceT<3>, _l,      toLiters,       1e-3)
            DECL_UNIT(DistanceT<3>, _ml,     toMilliliters,  1e-6)
            DECL_UNIT(DistanceT<3>, _gal,    toGallons,      3.78541e-3)
            DECL_CONV_MUL(DistanceT<1>, VelocityT<1>, TimeT<1>) )

DECL_CLASS( Angle,
            rad,
            DECL_UNIT(AngleT<1>, _rad, toRadians, 1.0)
            DECL_UNIT(AngleT<1>, _deg, toDegrees, PI/180.0)
            friend constexpr Real Cos(AngleT<1> v);
            friend constexpr Real Sin(AngleT<1> v);
            friend constexpr Real Tan(AngleT<1> v);
            friend constexpr AngleT<1> ACos(Real v);
            friend constexpr AngleT<1> ASin(Real v);
            friend constexpr AngleT<1> ATan(Real v);
            friend constexpr AngleT<1> ATan2(Real a, Real b);
            friend constexpr AngleT<1> ATan2(DistanceT<1> a, DistanceT<1> b); )

DECL_CLASS( Time,
            seconds,
            DECL_UNIT(TimeT<1>, _hours,   toHours,         3600.0)
            DECL_UNIT(TimeT<1>, _minutes, toMinutes,       60.0)
            DECL_UNIT(TimeT<1>, _sec,     toSeconds,       1.0e+0)
            DECL_UNIT(TimeT<1>, _msec,    toMilliseconds,  1.0e-3)
            DECL_UNIT(TimeT<1>, _usec,    toMicroseconds,  1.0e-6)
            DECL_UNIT(TimeT<1>, _nsec,    toNanoseconds,   1.0e-9)
            DECL_UNIT(TimeT<2>, _sec2,    toSeconds2,      1.0e+0)
            DECL_UNIT(TimeT<-1>, _Hz,     toHertz,         1.0e+0)
            DECL_UNIT(TimeT<-2>, _Hz2,    toHertz2,         1.0e+0) )

DECL_CLASS( Velocity,
            m/s,
            DECL_UNIT(VelocityT<1>, _kmph, toKilometersPerHour,  1.0/3.6)
            DECL_UNIT(VelocityT<1>, _mph,  toMilesPerHour,       0.44704)
            DECL_UNIT(VelocityT<1>, _mps,  toMetersPerSecond,    1.0e+0)
            DECL_CONV_DIV(VelocityT<1>, DistanceT<1>, TimeT<1>)
            DECL_CONV_MUL(VelocityT<1>, AccelerationT<1>, TimeT<1>) )

DECL_CLASS( Acceleration,
            m/s2,
            DECL_UNIT(AccelerationT<1>, _mps2,  toMetersPerSecond2,      1.0e+0)
            DECL_UNIT(AccelerationT<1>, _mmps2, toMillimetersPerSecond2, 1.0e-3)
            DECL_UNIT(AccelerationT<1>, _umps2, toMicrometersPerSecond2, 1.0e-6)
            DECL_UNIT(AccelerationT<1>, _nmps2, toNanometersPerSecond2,  1.0e-9)
            DECL_CONV_DIV(AccelerationT<1>, VelocityT<1>, TimeT<1>)
            DECL_CONV_DIV(AccelerationT<1>, DistanceT<1>, TimeT<2>)
            DECL_CONV_MUL(AccelerationT<1>, DistanceT<1>, TimeT<-2>) )

DECL_CLASS( Mass,
            kg,
            DECL_UNIT(MassT<1>, _kg, toKilograms,  1.0e+3)
            DECL_UNIT(MassT<1>, _g,  toGrams,      1.0e+0)
            DECL_UNIT(MassT<1>, _mg, toMilligrams, 1.0e-3)
            DECL_UNIT(MassT<1>, _ug, toMicrograms, 1.0e-6)
            DECL_UNIT(MassT<1>, _ng, toNanograms,  1.0e-9)
            DECL_UNIT(MassT<1>, _lb, toPounds,     453.59)
            DECL_UNIT(MassT<1>, _oz, toOunces,     28.350) )

DECL_CLASS( MassFlow,
            g/s,
            DECL_UNIT(MassFlowT<1>, _gps,  toGramsPerSecond,      1.0e+0)
            DECL_UNIT(MassFlowT<1>, _kgps, toKilogramsPerSecond,  1.0e+3)
            DECL_CONV_DIV(MassFlowT<1>, MassT<1>, TimeT<1>) )

DECL_CLASS( Momentum,
            g*m/s,
            DECL_UNIT(MomentumT<1>, _kgmps, toKilogramsMetersPerSecond, 1.0e+3)
            DECL_UNIT(MomentumT<1>, _gmps,  toGramsMetersPerSecond,     1.0)
            DECL_CONV_MUL(MomentumT<1>, MassT<1>, VelocityT<1>)
            DECL_CONV_AB_DIV_C(MomentumT<1>, MassT<1>, DistanceT<1>, TimeT<1>)
            DECL_CONV_MUL(MomentumT<1>, MassFlowT<1>, DistanceT<1>)
            DECL_CONV_MUL(MomentumT<1>, ForceT<1>, TimeT<1>) )

DECL_CLASS( Force,
            N,
            DECL_UNIT(ForceT<1>, _N, toNewtons, 1.0e+0)
            DECL_CONV_MUL(ForceT<1>, MassT<1>, AccelerationT<1>)
            DECL_CONV_DIV(ForceT<1>, MomentumT<1>, TimeT<1>) )

DECL_CLASS( Energy,
            J,
            DECL_UNIT(EnergyT<1>, _J,    toJoules,       1.0e+0)
            DECL_UNIT(EnergyT<1>, _kJ,   toKilojoules,   1.0e+3)
            DECL_UNIT(EnergyT<1>, _MJ,   toMegajoules,   1.0e+6)
            DECL_UNIT(EnergyT<1>, _GJ,   toGigajoules,   1.0e+9)
            DECL_UNIT(EnergyT<1>, _mJ,   toMillijoules,  1.0e-3)
            DECL_UNIT(EnergyT<1>, _uJ,   toMicrojoules,  1.0e-6)
            DECL_UNIT(EnergyT<1>, _nJ,   toNanojoules,   1.0e-9)
            DECL_UNIT(EnergyT<1>, _kWh,  toKilowattHour, 3.6e+6)
            DECL_UNIT(EnergyT<1>, _cal,  toCalories,     4.184e+0)
            DECL_UNIT(EnergyT<1>, _kcal, toKilocalories, 4.184e+3) )

DECL_CLASS( Power,
            W,
            DECL_UNIT(PowerT<1>, _GW,  toGigaWatts,  1.0e+9)
            DECL_UNIT(PowerT<1>, _MW,  toMegaWatts,  1.0e+6)
            DECL_UNIT(PowerT<1>, _kW,  toKiloWatts,  1.0e+3)
            DECL_UNIT(PowerT<1>, _W,   toWatts,      1.0e+0)
            DECL_UNIT(PowerT<1>, _mW,  toMilliWatts, 1.0e-3)
            DECL_UNIT(PowerT<1>, _uW,  toMicroWatts, 1.0e-6)
            DECL_CONV_DIV(PowerT<1>, EnergyT<1>, TimeT<1>)
            DECL_CONV_AB_DIV_C(PowerT<1>, ForceT<1>, DistanceT<1>, TimeT<1>) )

/* All implementations */

IMPL_CLASS(Distance)
IMPL_UNIT(DistanceT<1>, _m)
IMPL_UNIT(DistanceT<1>, _cm)
IMPL_UNIT(DistanceT<1>, _mm)
IMPL_UNIT(DistanceT<1>, _um)
IMPL_UNIT(DistanceT<1>, _nm)
IMPL_UNIT(DistanceT<1>, _km)
IMPL_UNIT(DistanceT<1>, _inch)
IMPL_UNIT(DistanceT<1>, _ft)
IMPL_UNIT(DistanceT<1>, _miles)
IMPL_UNIT(DistanceT<1>, _yd)
IMPL_UNIT(DistanceT<2>, _m2)
IMPL_UNIT(DistanceT<2>, _cm2)
IMPL_UNIT(DistanceT<2>, _mm2)
IMPL_UNIT(DistanceT<2>, _um2)
IMPL_UNIT(DistanceT<2>, _nm2)
IMPL_UNIT(DistanceT<2>, _km2)
IMPL_UNIT(DistanceT<2>, _inch2)
IMPL_UNIT(DistanceT<2>, _ft2)
IMPL_UNIT(DistanceT<2>, _miles2)
IMPL_UNIT(DistanceT<2>, _yd2)
IMPL_UNIT(DistanceT<2>, _acre)
IMPL_UNIT(DistanceT<3>, _m3)
IMPL_UNIT(DistanceT<3>, _cm3)
IMPL_UNIT(DistanceT<3>, _mm3)
IMPL_UNIT(DistanceT<3>, _um3)
IMPL_UNIT(DistanceT<3>, _nm3)
IMPL_UNIT(DistanceT<3>, _km3)
IMPL_UNIT(DistanceT<3>, _inch3)
IMPL_UNIT(DistanceT<3>, _ft3)
IMPL_UNIT(DistanceT<3>, _miles3)
IMPL_UNIT(DistanceT<3>, _yd3)
IMPL_UNIT(DistanceT<3>, _l)
IMPL_UNIT(DistanceT<3>, _ml)
IMPL_UNIT(DistanceT<3>, _gal)
IMPL_CONV_MUL(DistanceT<1>, VelocityT<1>, toMetersPerSecond, TimeT<1>, toSeconds)

IMPL_CLASS(Angle)
IMPL_UNIT(AngleT<1>, _rad)
IMPL_UNIT(AngleT<1>, _deg)
constexpr Real Cos(AngleT<1> v) { return cos(v.m_value); }
constexpr Real Sin(AngleT<1> v) { return sin(v.m_value); }
constexpr Real Tan(AngleT<1> v) { return tan(v.m_value); }
constexpr AngleT<1> ACos(Real v) { return {acos(v)}; }
constexpr AngleT<1> ASin(Real v) { return {asin(v)}; }
constexpr AngleT<1> ATan(Real v) { return {atan(v)}; }
constexpr AngleT<1> ATan2(Real a, Real b) { return {atan2(a,b)}; }
constexpr AngleT<1> ATan2(DistanceT<1> a, DistanceT<1> b)
{ return {atan2(a.toMeters(), b.toMeters())}; }

IMPL_CLASS(Time)
IMPL_UNIT(TimeT<1>, _hours)
IMPL_UNIT(TimeT<1>, _minutes)
IMPL_UNIT(TimeT<1>, _sec)
IMPL_UNIT(TimeT<1>, _msec)
IMPL_UNIT(TimeT<1>, _usec)
IMPL_UNIT(TimeT<1>, _nsec)
IMPL_UNIT(TimeT<2>, _sec2)
IMPL_UNIT(TimeT<-1>, _Hz)
IMPL_UNIT(TimeT<-2>, _Hz2)

IMPL_CLASS(Velocity)
IMPL_UNIT(VelocityT<1>, _kmph)
IMPL_UNIT(VelocityT<1>, _mph)
IMPL_UNIT(VelocityT<1>, _mps)
IMPL_CONV_DIV(VelocityT<1>, DistanceT<1>, toMeters, TimeT<1>, toSeconds)
IMPL_CONV_MUL(VelocityT<1>, AccelerationT<1>, toMetersPerSecond2, TimeT<1>, toSeconds)

IMPL_CLASS(Acceleration)
IMPL_UNIT(AccelerationT<1>, _mps2)
IMPL_UNIT(AccelerationT<1>, _mmps2)
IMPL_UNIT(AccelerationT<1>, _umps2)
IMPL_UNIT(AccelerationT<1>, _nmps2)
IMPL_CONV_DIV(AccelerationT<1>, VelocityT<1>, toMetersPerSecond, TimeT<1>, toSeconds)
IMPL_CONV_DIV(AccelerationT<1>, DistanceT<1>, toMeters, TimeT<2>, toSeconds2)
IMPL_CONV_MUL(AccelerationT<1>, DistanceT<1>, toMeters, TimeT<-2>, toHertz2)

IMPL_CLASS(Mass)
IMPL_UNIT(MassT<1>, _kg)
IMPL_UNIT(MassT<1>, _g)
IMPL_UNIT(MassT<1>, _mg)
IMPL_UNIT(MassT<1>, _ug)
IMPL_UNIT(MassT<1>, _ng)
IMPL_UNIT(MassT<1>, _lb)
IMPL_UNIT(MassT<1>, _oz)

IMPL_CLASS(MassFlow)
IMPL_UNIT(MassFlowT<1>, _kgps)
IMPL_UNIT(MassFlowT<1>, _gps)
IMPL_CONV_DIV(MassFlowT<1>, MassT<1>, toGrams, TimeT<1>, toSeconds)

IMPL_CLASS(Momentum)
IMPL_UNIT(MomentumT<1>, _kgmps)
IMPL_CONV_MUL(MomentumT<1>, MassT<1>, toGrams, VelocityT<1>, toMetersPerSecond)
IMPL_CONV_MUL(MomentumT<1>, MassFlowT<1>, toGramsPerSecond, DistanceT<1>, toMeters)
IMPL_CONV_MUL(MomentumT<1>, ForceT<1>, toNewtons, DistanceT<1>, toMeters)
IMPL_CONV_AB_DIV_C(MomentumT<1>, MassT<1>, toGrams, DistanceT<1>, toMeters, TimeT<1>, toSeconds)

IMPL_CLASS(Force)
IMPL_UNIT(ForceT<1>, _N)
IMPL_CONV_MUL(ForceT<1>, MassT<1>, toGrams, AccelerationT<1>, toMetersPerSecond2)
IMPL_CONV_DIV(ForceT<1>, MomentumT<1>, toGramsMetersPerSecond, TimeT<1>, toSeconds)

IMPL_CLASS(Energy)
IMPL_UNIT(EnergyT<1>, _J)
IMPL_UNIT(EnergyT<1>, _kJ)
IMPL_UNIT(EnergyT<1>, _MJ)
IMPL_UNIT(EnergyT<1>, _GJ)
IMPL_UNIT(EnergyT<1>, _mJ)
IMPL_UNIT(EnergyT<1>, _uJ)
IMPL_UNIT(EnergyT<1>, _nJ)
IMPL_UNIT(EnergyT<1>, _kWh)
IMPL_UNIT(EnergyT<1>, _cal)
IMPL_UNIT(EnergyT<1>, _kcal)

IMPL_CLASS(Power)
IMPL_UNIT(PowerT<1>, _GW)
IMPL_UNIT(PowerT<1>, _MW)
IMPL_UNIT(PowerT<1>, _kW)
IMPL_UNIT(PowerT<1>, _W)
IMPL_UNIT(PowerT<1>, _mW)
IMPL_UNIT(PowerT<1>, _uW)
IMPL_CONV_DIV(PowerT<1>, EnergyT<1>, toJoules, TimeT<1>, toSeconds)
IMPL_CONV_AB_DIV_C(PowerT<1>, ForceT<1>, toNewtons, DistanceT<1>, toMeters, TimeT<1>, toSeconds)

using Distance = DistanceT<1>;
using Area = DistanceT<2>;
using Volume = DistanceT<3>;
using Time = TimeT<1>;
using Power = PowerT<1>;
using Energy = EnergyT<1>;
using Mass = MassT<1>;
using MassFlow = MassFlowT<1>;
using Force = ForceT<1>;
using Velocity = VelocityT<1>;
using Acceleration = AccelerationT<1>;
using Angle = AngleT<1>;

} // namespace frogs

#endif // _FROGS_PHYSICAL_TYPES_H
