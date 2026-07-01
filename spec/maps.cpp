#include "maps.hpp"

std::unordered_map<int8_t, char> GEAR_VALUE = {
    {-1, 'R'}, {0, 'N'}, {1, '1'}, {2, '2'}, {3, '3'},
    {4, '4'}, {5, '5'}, {6, '6'}, {7, '7'}, {8, '8'}
};

std::unordered_map<uint8_t, const char*> SESSION_TYPE_VALUE = {
    {0, "UNKNOWN"}, {1, "FP1"}, {2, "FP2"}, {3, "FP3"}, {4, "Short Practice"}, {5, "Q1"},
    {6, "Q2"}, {7, "Q3"}, {8, "Short Qualifying"}, {9, "One Shot Qualifying"}, {10, "RACE"}, {11, "RACE Restart"}, {12, "TIME TRIAL"}
};

std::unordered_map<uint8_t, const char *> WEATHER_VALUE = {
    {0, "Clear"}, {1, "Light Cloud"}, {2, "Overcast"},
    {3, "Light RAin"}, {4, "Heavy Rain"}, {5, "Storm"}
};

std::unordered_map<uint8_t, const char *> FORMULA_CAR_TYPE_VALUE = {
    {0, "Formula 1"}, {1, "Formula 1 Classic"},
    {2, "Formula 2"}, {3, "Formula 1 Generic"}
};

std::unordered_map<uint8_t, const char *> ERS_DEPLOY_VALUE = {
    {0, "NONE"}, {1, "MEDIUM"},
    {2, "OVERTAKE"}, {3, "HOTLAP"}
};

std::unordered_map<uint8_t, const char *> FUEL_MIX_VALUE = {
    {0, "Lean"}, {1, "Standard"}, {2, "Rich"}
};

std::unordered_map<uint8_t, const char *> TYRE_TYPE_VALUE = {
    {16, "SOFT"}, {17, "MEDIUM"}, {18, "HARD"}, {7, "INTERMEDIATE"},
    {8, "WET"}, {9, "DRY"}, {10, "WET"}, {23, "SUPER SOFT"},
    {24, "SOFT"}, {25, "MEDIUM"}, {14, "HARD"}, {15, "WET"}
};

std::unordered_map<uint8_t, const char *> FLAG_VALUE = {
    {0, "NONE"}, {1, "GREEN"}, {2, "BLUE"}, {3, "YELLOW"}, {4, "RED"}
};
