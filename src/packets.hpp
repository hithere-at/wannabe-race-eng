#ifndef _WRE_PACKETS_HPP_
#define _WRE_PACKETS_HPP_

#include <cstdint>

struct __attribute__((packed)) PacketHeader {
    uint16_t m_packetFormat;
    uint8_t m_gameMajorVersion;
    uint8_t m_gameMinorVersion;
    uint8_t m_packetVersion;
    uint8_t m_packetId;
    uint64_t m_sessionUID;
    float m_sessionTime;
    uint32_t m_frameIdentifier;
    uint8_t m_playerCarIndex;
    uint8_t m_secondaryPlayerCarIndex;

};

struct __attribute__((packed)) CarMotionData {
    float m_worldPositionX;
    float m_worldPositionY;
    float m_worldPositionZ;
    float m_worldVelocityX;
    float m_worldVelocityY;
    float m_worldVelocityZ;
    int16_t m_worldForwardDirX;
    int16_t m_worldForwardDirY;
    int16_t m_worldForwardDirZ;
    int16_t m_worldRightDirX;
    int16_t m_worldRightDirY;
    int16_t m_worldRightDirZ;
    float m_gForceLateral;
    float m_gForceLongitudinal;
    float m_gForceVertical;
    float m_yaw;
    float m_pitch;
    float m_roll;

};

struct __attribute__((packed)) PacketMotionData {
    PacketHeader m_header;
    CarMotionData m_carMotionData[22];
    float m_suspensionPosition[4];
    float m_suspensionVelocity[4];
    float m_suspensionAcceleration[4];
    float m_wheelSpeed[4];
    float m_wheelSlip[4];
    float m_localVelocityX;
    float m_localVelocityY;
    float m_localVelocityZ;
    float m_angularVelocityX;
    float m_angularVelocityY;
    float m_angularVelocityZ;
    float m_angularAccelerationX;
    float m_angularAccelerationY;
    float m_angularAccelerationZ;
    float m_frontWheelsAngle;

};

struct __attribute__((packed)) MarshalZone {
    float m_zoneStart;
    int8_t m_zoneFlag;

};

struct __attribute__((packed)) WeatherForecastSample {
    uint8_t m_sessionType;
    uint8_t m_timeOffset;
    uint8_t m_weather;
    int8_t m_trackTemperature;
    int8_t m_airTemperature;

};

struct __attribute__((packed)) PacketSessionData {
    PacketHeader m_header;
    uint8_t m_weather;
    int8_t m_trackTemperature;
    int8_t m_airTemperature;
    uint8_t m_totalLaps;
    uint16_t m_trackLength;
    uint8_t m_sessionType;
    int8_t m_trackId;
    uint8_t m_formula;
    uint16_t m_sessionTimeLeft;
    uint16_t m_sessionDuration;
    uint8_t m_pitSpeedLimit;
    uint8_t m_gamePaused;
    uint8_t m_isSpectating;
    uint8_t m_spectatorCarIndex;
    uint8_t m_sliProNativeSupport;
    uint8_t m_numMarshalZones;
    MarshalZone m_marshalZones[21];
    uint8_t m_safetyCarStatus;
    uint8_t m_networkGame;
    uint8_t m_numWeatherForecastSamples;
    WeatherForecastSample m_weatherForecastSamples[20];

};

struct __attribute__((packed)) LapData {
    float m_lastLapTime;
    float m_currentLapTime;
    uint16_t m_sector1TimeInMS;
    uint16_t m_sector2TimeInMS;
    float m_bestLapTime;
    uint8_t m_bestLapNum;
    uint16_t m_bestLapSector1TimeInMS;
    uint16_t m_bestLapSector2TimeInMS;
    uint16_t m_bestLapSector3TimeInMS;
    uint16_t m_bestOverallSector1TimeInMS;
    uint8_t m_bestOverallSector1LapNum;
    uint16_t m_bestOverallSector2TimeInMS;
    uint8_t m_bestOverallSector2LapNum;
    uint16_t m_bestOverallSector3TimeInMS;
    uint8_t m_bestOverallSector3LapNum;
    float m_lapDistance;
    float m_totalDistance;
    float m_safetyCarDelta;
    uint8_t m_carPosition;
    uint8_t m_currentLapNum;
    uint8_t m_pitStatus;
    uint8_t m_sector;
    uint8_t m_currentLapInvalid;
    uint8_t m_penalties;
    uint8_t m_gridPosition;
    uint8_t m_driverStatus;
    uint8_t m_resultStatus;

};

struct __attribute__((packed)) PacketLapData {
    PacketHeader m_header;
    LapData m_lapData[22];

};

union __attribute__((packed)) EventDataDetails {

    struct __attribute__((packed)) FastestLap {
        uint8_t	vehicleIdx;
        float	lapTime;

    };

    struct __attribute__((packed)) Retirement {
        uint8_t  vehicleIdx;

    };

    struct __attribute__((packed)) TeamMateInPits {
        uint8_t  vehicleIdx;

    };

    struct __attribute__((packed)) RaceWinner {
        uint8_t vehicleIdx;

    };

    struct __attribute__((packed)) Penalty {
        uint8_t penaltyType;
        uint8_t infringementType;
        uint8_t vehicleIdx;
        uint8_t otherVehicleIdx;
        uint8_t time;
        uint8_t lapNum;
        uint8_t placesGained;

    };

    struct __attribute__((packed)) SpeedTrap {
        uint8_t vehicleIdx;
        float speed;

    };

};

struct __attribute__((packed)) PacketEventData {
    PacketHeader m_header;
    uint8_t m_eventStringCode[4];
    EventDataDetails m_eventDetails;

};

struct __attribute__((__packed__)) ParticipantData {
    uint8_t m_aiControlled;
    uint8_t m_driverId;
    uint8_t m_teamId;
    uint8_t m_raceNumber;
    uint8_t m_nationality;
    char m_name[48];
    uint8_t m_yourTelemetry;
};

struct __attribute__((__packed__)) PacketParticipantsData {
    PacketHeader m_header;
    uint8_t m_numActiveCars;
    ParticipantData m_participants[22];
};

struct __attribute__((__packed__)) CarSetupData {
    uint8_t m_frontWing;
    uint8_t m_rearWing;
    uint8_t m_onThrottle;
    uint8_t m_offThrottle;
    float m_frontCamber;
    float m_rearCamber;
    float m_frontToe;
    float m_rearToe;
    uint8_t m_frontSuspension;
    uint8_t m_rearSuspension;
    uint8_t m_frontAntiRollBar;
    uint8_t m_rearAntiRollBar;
    uint8_t m_frontSuspensionHeight;
    uint8_t m_rearSuspensionHeight;
    uint8_t m_brakePressure;
    uint8_t m_brakeBias;
    float m_rearLeftTyrePressure;
    float m_rearRightTyrePressure;
    float m_frontLeftTyrePressure;
    float m_frontRightTyrePressure;
    uint8_t m_ballast;
    float m_fuelLoad;
};

struct __attribute__((__packed__)) PacketCarSetupData {
    PacketHeader m_header;
    CarSetupData m_carSetups[22];
};

struct __attribute__((__packed__)) CarTelemetryData {
    uint16_t m_speed;
    float m_throttle;
    float m_steer;
    float m_brake;
    uint8_t m_clutch;
    int8_t m_gear;
    uint16_t m_engineRPM;
    uint8_t m_drs;
    uint8_t m_revLightsPercent;
    uint16_t m_brakesTemperature[4];
    uint8_t m_tyresSurfaceTemperature[4];
    uint8_t m_tyresInnerTemperature[4];
    uint16_t m_engineTemperature;
    float m_tyresPressure[4];
    uint8_t m_surfaceType[4];
};

struct __attribute__((__packed__)) PacketCarTelemetryData {
    PacketHeader m_header;
    CarTelemetryData m_carTelemetryData[22];
    uint32_t m_buttonStatus;
    uint8_t m_mfdPanelIndex;
    uint8_t m_mfdPanelIndexSecondaryPlayer;
    int8_t m_suggestedGear;
};

struct __attribute__((__packed__)) CarStatusData {
    uint8_t m_tractionControl;
    uint8_t m_antiLockBrakes;
    uint8_t m_fuelMix;
    uint8_t m_frontBrakeBias;
    uint8_t m_pitLimiterStatus;
    float m_fuelInTank;
    float m_fuelCapacity;
    float m_fuelRemainingLaps;
    uint16_t m_maxRPM;
    uint16_t m_idleRPM;
    uint8_t m_maxGears;
    uint8_t m_drsAllowed;
    uint16_t m_drsActivationDistance;
    uint8_t m_tyresWear[4];
    uint8_t m_actualTyreCompound;
    uint8_t m_visualTyreCompound;
    uint8_t m_tyresAgeLaps;
    uint8_t m_tyresDamage[4];
    uint8_t m_frontLeftWingDamage;
    uint8_t m_frontRightWingDamage;
    uint8_t m_rearWingDamage;
    uint8_t m_drsFault;
    uint8_t m_engineDamage;
    uint8_t m_gearBoxDamage;
    int8_t m_vehicleFiaFlags;
    float m_ersStoreEnergy;
    uint8_t m_ersDeployMode;
    float m_ersHarvestedThisLapMGUK;
    float m_ersHarvestedThisLapMGUH;
    float m_ersDeployedThisLap;
};

struct __attribute__((__packed__)) PacketCarStatusData {
    PacketHeader m_header;
    CarStatusData m_carStatusData[22];
};

struct __attribute__((__packed__)) FinalClassificationData {
    uint8_t m_position;
    uint8_t m_numLaps;
    uint8_t m_gridPosition;
    uint8_t m_points;
    uint8_t m_numPitStops;
    uint8_t m_resultStatus;
    float m_bestLapTime;
    double m_totalRaceTime;
    uint8_t m_penaltiesTime;
    uint8_t m_numPenalties;
    uint8_t m_numTyreStints;
    uint8_t m_tyreStintsActual[8];
    uint8_t m_tyreStintsVisual[8];
};

struct __attribute__((__packed__)) PacketFinalClassificationData {
    PacketHeader m_header;
    uint8_t m_numCars;
    FinalClassificationData m_classificationData[22];
};

struct __attribute__((__packed__)) LobbyInfoData {
    uint8_t m_aiControlled;
    uint8_t m_teamId;
    uint8_t m_nationality;
    char m_name[48];
    uint8_t m_readyStatus;
};

struct __attribute__((__packed__)) PacketLobbyInfoData {
    PacketHeader m_header;
    uint8_t m_numPlayers;
    LobbyInfoData m_lobbyPlayers[22];
};

#endif
