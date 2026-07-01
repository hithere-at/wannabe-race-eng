#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ncurses.h>

#include "spec/constants.hpp"
#include "spec/packets.hpp"
#include "spec/structs.hpp"
#include "ui/windows.hpp"

#define WRE_BUF_SIZE 2048

int parse_int(const char *to_parse) {

    char *endptr;
    const long temp = std::strtol(to_parse, &endptr, 10);

    if (endptr == to_parse) {
        std::cerr << "Switch argument " << to_parse << " is not a valid number\n";
        std::exit(EXIT_FAILURE);
    }

    if ((temp < 0) || (temp > 65535)) {
        std::cerr << "Value " << to_parse << " is out of range. Valid range is a value between 1 to 65535\n";
        std::exit(EXIT_FAILURE);

    } else {
        return temp;

    }

}

int main(int argc, char *argv[]) {

    // initialize a UDP socket. how?
    int sock;
    short WRE_PORT = (argc >= 2) ? parse_int(argv[1]) : 20777;
    char buffer[WRE_BUF_SIZE];
    struct sockaddr_in server_addr;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        std::cerr << "Failed to create socket :(\n";
        exit(EXIT_FAILURE);

    }

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(WRE_PORT);

    if (bind(sock, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket :(\n";
        exit(EXIT_FAILURE);

    }

    struct WRECarTelemetry tele;

    initscr();
    noecho();
    curs_set(0);

    MainWindow base(
        stdscr,
        getmaxy(stdscr),
        getmaxx(stdscr)

    );

    MeterWindow meter(
        derwin(stdscr, 7, base.width - 4, 1, 2),
        7,
        base.width - 4
    );

    StatusWindow status(
        derwin(stdscr, 11, 33, base.height - 12, base.width - 35),
        11,
        33
    );

    TyreWindow tyre(
        derwin(stdscr, 12, 52, base.height - 13, 2),
        12,
        52
    );

    touchwin(base.win);

    box(base.win, 0, 0);
    wrefresh(base.win);

    // get the packet and check packet ID
    while(true) {

        socklen_t sock_len = sizeof(server_addr);
        int received = recvfrom(sock, buffer, WRE_BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &sock_len);

        PacketHeader *header = (PacketHeader*)buffer;

        // then just read the data based on the packet id
        if (header->m_packetId == PID_CAR_TELEMETRY) {

            PacketCarTelemetryData *car_packets = (PacketCarTelemetryData*)buffer;
            CarTelemetryData *car_telemetry = &car_packets->m_carTelemetryData[header->m_playerCarIndex];

            tele.throttle = car_telemetry->m_throttle;
            tele.brake = car_telemetry->m_brake;
            tele.engine_rpm = car_telemetry->m_engineRPM;
            tele.speed = car_telemetry->m_speed;
            tele.rev_percent = car_telemetry->m_revLightsPercent;

            tele.drs = car_telemetry->m_drs;
            tele.gear = car_telemetry->m_gear;
            tele.suggested_gear = car_packets->m_suggestedGear;

            memcpy(tele.tyre_inner_temp, car_telemetry->m_tyresInnerTemperature, sizeof(tele.tyre_inner_temp));
            memcpy(tele.tyre_surface_temp, car_telemetry->m_tyresSurfaceTemperature, sizeof(tele.tyre_surface_temp));
            memcpy(tele.brake_temp, car_telemetry->m_brakesTemperature, sizeof(tele.brake_temp));

        } else if (header->m_packetId == PID_CAR_STATUS) {

            PacketCarStatusData *car_status_packet = (PacketCarStatusData*)buffer;
            CarStatusData *car_status = &car_status_packet->m_carStatusData[header->m_playerCarIndex];

            tele.max_rpm = car_status->m_maxRPM;
            tele.drs_distance = car_status->m_drsActivationDistance;

            tele.ers_deployed = car_status->m_ersDeployedThisLap;
            tele.ers_energy = car_status->m_ersStoreEnergy;
            tele.ers_mode = car_status->m_ersDeployMode;

            tele.fuel_remaining = car_status->m_fuelRemainingLaps;
            tele.fuel_mix = car_status->m_fuelMix;

            tele.tyre_type = car_status->m_visualTyreCompound;
            tele.tyre_age = car_status->m_tyresAgeLaps;

            memcpy(tele.tyres_wear, car_status->m_tyresWear, sizeof(tele.tyres_wear));

        }

        meter.clear_win();
        status.clear_win();
        tyre.clear_win();

        // draw the meters
        meter.draw_throttle(tele);
        meter.draw_brake(tele);
        meter.draw_rpm_meter(tele);
        meter.draw_max_rpm(tele);
        meter.draw_speed(tele);

        // draw the status
        status.draw_drs_status(tele);
        status.draw_drs_distance(tele);
        status.draw_gear(tele);

        status.draw_ers(tele);

        status.draw_fuel(tele);

        // draw tyre status
        tyre.draw_tyre_status(tele);
        tyre.draw_tyre_and_brake_temp(tele);
        tyre.draw_tyre_wear(tele);

        // draw the box for the windows
        box(meter.win, 0, 0);
        box(status.win, 0, 0);
        box(tyre.win, 0, 0);

        // sleep for 5ms to not destroy computer :D
        usleep(5000);

        wnoutrefresh(meter.win);
        wnoutrefresh(status.win);
        wnoutrefresh(tyre.win);
        doupdate();

    }

    endwin();
    close(sock);

    return 0;
}
