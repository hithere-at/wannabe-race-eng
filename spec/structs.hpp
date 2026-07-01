/*
 * one might say this structs is useless well uhmm we need to display every data that the telemetry sends
 * problem is, some of the data is scatered across diferrent packet type.
 * so we need a struct that holds all the data sent by all the different packets. kind of like intermedia struct
 * this improves the drawing logic because it doesnt depend on packet IDs
 * the struct also has default values when its first initialized. so thats pretty good
 * this might very slightly increase memory usage but meh stack memory is a lot for now
 */


#ifndef _WRE_STRUCTS_HPP_
#define _WRE_STRUCTS_HPP_

#include <cstdint>

struct WRECarTelemetry {

    // data's sent by CarTelemetryData
    float throttle = 0;
    float brake = 0;
    uint16_t speed = 0;
    uint16_t engine_rpm = 0;

    uint8_t rev_percent = 0;
    uint8_t drs = 0;
    int8_t gear = 0;
    int8_t suggested_gear = 0;

    uint8_t tyre_inner_temp[4] = {0};
    uint8_t tyre_surface_temp[4] = {0};
    uint16_t brake_temp[4] = {0};

    uint16_t max_rpm = 0;
    uint16_t drs_distance = 0;
    uint8_t ers_mode = 0;
    uint8_t fuel_mix = 0;

    float ers_deployed = 0;
    float ers_energy = 0;
    float fuel_remaining = 0;
    uint8_t tyre_type = 0;
    uint8_t tyre_age = 0;
    uint8_t tyres_wear[4] = {0};

};

#endif
