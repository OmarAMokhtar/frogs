#include "frogs_expressions.h"

#include <regex>

namespace frogs
{

Integer ___numVars = 0;

Str conv2str(Real v)
{
    return std::regex_replace(std::to_string(v), std::regex{"(\\.|)0+$"}, "");
}

} // namespace frogs
