#ifndef _WRE_MAPS_HPP_
#define _WRE_MAPS_HPP_

#include <cstdint>
#include <unordered_map>

extern std::unordered_map<int8_t, char> GEAR_VALUE;
extern std::unordered_map<uint8_t, const char*> SESSION_TYPE_VALUE;
extern std::unordered_map<uint8_t, const char*> FORMULA_CAR_TYPE_VALUE;
extern std::unordered_map<uint8_t, const char*> ERS_DEPLOY_VALUE;
extern std::unordered_map<uint8_t, const char*> FUEL_MIX_VALUE;
extern std::unordered_map<uint8_t, const char*> TYRE_TYPE_VALUE;
extern std::unordered_map<uint8_t, const char*> FLAG_VALUE;

#endif
