#ifndef _WRE_CONSTANTS_HPP_
#define _WRE_CONSTANTS_HPP_

// define all the packet IDs
#define PID_MOTION_PACKET 0
#define PID_SESSION_PACKET 1
#define PID_LAP_DATA 2
#define PID_EVENT 3
#define PID_PARTICIPANTS 4
#define PID_CAR_SETUP 5
#define PID_CAR_TELEMETRY 6
#define PID_CAR_STATUS 7
#define PID_FINAL_CLASSIFICATION 8
#define PID_LOBBY_INFO 9

// define flags
#define MAR_NO_FLAG 0
#define MAR_GREEN_FLAG 1
#define MAR_BLUE_FLAG 2
#define MAR_YELLOW_FLAG 3
#define MAR_RED_FLAG 4

// define session type
#define SESSION_TYPE_UNKNOWN 0
#define SESSION_TYPE_FP1 1
#define SESSION_TYPE_FP2 2
#define SESSION_TYPE_FP3 3
#define SESSION_TYPE_SHORTFP 4
#define SESSION_TYPE_Q1 5
#define SESSION_TYPE_Q2 6
#define SESSION_TYPE_Q3 7
#define SESSION_TYPE_SHORTQ 8
#define SESSION_TYPE_OSQ 9
#define SESSION_TYPE_RACE 10
#define SESSION_TYPE_RACE_RESTART 11
#define SESSION_TYPE_TIME_TRIAL 12

// define weather type
#define WEATHER_CLEAR 0
#define WEATHER_LIGHT_CLOUD 1
#define WEATHER_OVERCAST 2
#define WEATHER_LIGHT_RAIN 3
#define WEATHER_HEAVY_RAIN 4
#define WEATHER_STORM 5

// define formula car type
#define FORMULA_1_MODERN 0
#define FORMULA_1_CLASSIC 1
#define FORMULA_2 2
#define FORMULA_1_GENERIC 3

// define SLI Pro? what the hell is this
#define SLI_PRO_INACTIVE 0
#define SLI_PRO_ACTIVE 1

// define safety car status
#define SC_VIRTUAL 0
#define SC_FULL 1

// define network status
#define NETWORK_OFFLINE 0
#define NETWORK_ONLINE 1

// define pit status
#define PIT_NONE 0
#define PIT_PITTING 1
#define PIT_IN_PIT_AREA 2

// define sector PIT_IN_PIT_AREA
#define SEC_SECTOR_1 0
#define SEC_SECTOR_2 1
#define SEC_SECTOR_3 2

// define lap validation
#define LAP_VALID 0
#define LAP_INVALID 1

// define driver status
#define DRV_IN_GARAGE 0
#define DRV_FLYING_LAP 1
#define DRV_IN_LAP 2
#define DRV_OUT_LAP 3
#define DRV_ON_TRACK 4

// define lap result
#define LAP_RESULT_INVALID 0
#define LAP_RESULT_INACTIVE 1
#define LAP_RESULT_ACTIVE 2
#define LAP_RESULT_FINISHED 3
#define LAP_RESULT_DISQUALIFIED 4
#define LAP_RESULT_NONE 5
#define LAP_RESULT_RETIRED 6

// define event codes
#define EVNT_SESSION_STARTED "SSTA"
#define EVNT_SESSION_ENDED "SEND"
#define EVNT_FASTEST_LAP "FTLP"
#define EVNT_RETIREMENT "RTMT"
#define EVNT_DRS_ENABLED "DRSE"
#define EVNT_DRS_DISABLED "DRSD"
#define EVNT_TEAMMATE_IN_PIT "TMPT"
#define EVNT_CHEQUERED_FLAG "CHQF"
#define EVNT_RACE_WINNER "RCWN"
#define EVNT_PENALTY_ISSUED "PENA"
#define EVNT_SPEED_TRAP "SPTP"

// define gear status (only for neutral and reverse)
#define CAR_GEAR_NEUTRAL 0
#define CAR_GEAR_REVERSE -1

// define car DRS status
#define CAR_DRS_DISABLED 0
#define CAR_DRS_ENABLED 1
#define CAR_DRS_UNKNOWN -1
#define CAR_DRS_NOT_ALLOWED 0
#define CAR_DRS_ALLOWED 1

// define tyre compound (visual)
#define TYRE_F1_SOFT 16
#define TYRE_F1_MEDIUM 17
#define TYRE_F1_HARD 18
#define TYRE_F1_INTER 7
#define TYRE_F1_WET 8
#define TYRE_F1C_DRY 9
#define TYRE_F1C_WET 10
#define TYRE_F2_SUPER_SOFT 11
#define TYRE_F2_SOFT 12
#define TYRE_F2_MEDIUM 13
#define TYRE_F2_HARD 14
#define TYRE_F2_WET 15

// define DRS fault
#define CAR_DRS_OK 0
#define CAR_DRS_FAULT 1

// define ERS deploy mode
#define ERS_DEPLOY_NONE 0
#define ERS_DEPLOY_MEDIUM 1
#define ERS_DEPLOY_OVERTAKE 2
#define ERS_DEPLOY_HOTLAP 3

// define fuel mix
#define FUEL_MIX_LEAN 0
#define FUEL_MIX_STANDARD 1
#define FUEL_MIX_RICH 2

// define pit limiter status
#define PIT_LIMITER_OFF 0
#define PIT_LIMITER_ON 1

#endif
