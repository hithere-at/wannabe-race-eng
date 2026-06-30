#include <iostream>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ncurses.h>

#include "src/constants.hpp"
#include "src/packets.hpp"
#include "src/maps.hpp"
#include "src/structs.hpp"

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

    short WRE_PORT;

    // parse argument
    if (argc >= 2) {
        WRE_PORT = parse_int(argv[1]);

    }

    // initialize a UDP socket. how?
    int sock;
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

    std::cout << "Socket successfully created. Waiting for data\n";

    initscr();
    noecho();
    curs_set(0);

    struct WindowInfo main {
        .win = stdscr,
        .width = getmaxx(stdscr),
        .height = getmaxy(stdscr)
    };

    struct WindowInfo meter {
      .win = derwin(stdscr, 7, main.width - 4, 1, 2),
      .width = main.width - 4,
      .height = 7
    };

    struct WindowInfo status {
        .win = derwin(stdscr, 11, 33, main.height - 12, main.width - 35),
        .width = 33,
        .height = 11
    };

    struct WindowInfo tyre {
        .win = derwin(stdscr, 12, 52, main.height - 13, 2),
        .width = 52,
        .height = 12,
    };

    touchwin(stdscr);

    box(stdscr, 0, 0);
    wrefresh(stdscr);

    // get the packet and check packet ID
    while(true) {

        socklen_t sock_len = sizeof(server_addr);
        int received = recvfrom(sock, buffer, WRE_BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &sock_len);

        PacketHeader *header = (PacketHeader*)buffer;

        // then just read the data based on the packet id
        if (header->m_packetId == PID_CAR_TELEMETRY) {

            PacketCarTelemetryData *car_packets = (PacketCarTelemetryData*)buffer;
            CarTelemetryData *car_telemetry = &car_packets->m_carTelemetryData[header->m_playerCarIndex];

            // clear the meter window
            wmove(meter.win, 1, 0);
            wclrtoeol(meter.win);

            wmove(meter.win, 2, 0);
            wclrtoeol(meter.win);

            wmove(meter.win, 3, 0);
            wclrtoeol(meter.win);

            wmove(meter.win, 5, 0);
            wclrtoeol(meter.win);

            // clear the status window
            wmove(status.win, 1, 0);
            wclrtoeol(status.win);

            wmove(status.win, 2, 0);
            wclrtoeol(status.win);

            // clear the tyre window
            wmove(tyre.win, 4, 0);
            wclrtoeol(status.win);

            wmove(tyre.win, 5, 0);
            wclrtoeol(status.win);

            wmove(tyre.win, 8, 0);
            wclrtoeol(status.win);

            wmove(tyre.win, 9, 0);
            wclrtoeol(status.win);

            // draw the meters
            mvwaddstr(meter.win, 1, 2, "Throttle : [");
            mvwaddstr(meter.win, 2, 2, "Brake    : [");
            mvwaddstr(meter.win, 3, 2, "RPM      : [");
            mvwaddstr(meter.win, 5, 2, "Speed    : [");

            // assume 21 characters for meter values. it should be enough
            int percentage_limit = meter.width - (21 + 14);

            mvwhline(meter.win, 1, 14, '=', (int)((car_telemetry->m_throttle * 100) * percentage_limit) / 100);
            mvwhline(meter.win, 2, 14, '=', (int)((car_telemetry->m_brake * 100) * percentage_limit) / 100);
            mvwhline(meter.win, 3, 14, '=', (int)((car_telemetry->m_revLightsPercent) * percentage_limit) / 100);
            mvwhline(meter.win, 5, 14, '=', (int)((car_telemetry->m_speed) * percentage_limit) / 380);

            mvwprintw(meter.win, 1, 14 + percentage_limit, "] %d / 100%%", (int)(car_telemetry->m_throttle * 100));
            mvwprintw(meter.win, 2, 14 + percentage_limit, "] %d / 100%%", (int)(car_telemetry->m_brake * 100));
            mvwprintw(meter.win, 3, 14 + percentage_limit, "] %d", (int)car_telemetry->m_engineRPM);
            mvwprintw(meter.win, 5, 14 + percentage_limit, "] %d / 380 kph", (int)car_telemetry->m_speed);

            // draw car DRS status
            mvwprintw(status.win, 1, 2, "DRS          : [ %s", (car_telemetry->m_drs == CAR_DRS_ENABLED) ? "ON" : "OFF");

            // draw gear status
            mvwprintw(status.win, 2, 2, "Gear         : [ %c (%d) ]", GEAR_VALUE[car_telemetry->m_gear], (int)car_packets->m_suggestedGear);

            // print rear left tyre status
            mvwprintw(tyre.win, 8, 2, "RL: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[0], (int)car_telemetry->m_tyresSurfaceTemperature[0]);
            mvwprintw(tyre.win, 9, 2, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[0]);

            // print rear right tyre status
            mvwprintw(tyre.win, 8, 27, "RR: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[1], (int)car_telemetry->m_tyresSurfaceTemperature[1]);
            mvwprintw(tyre.win, 9, 27, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[1]);

            // print front left tyre status
            mvwprintw(tyre.win, 4, 2, "FL: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[2], (int)car_telemetry->m_tyresSurfaceTemperature[2]);
            mvwprintw(tyre.win, 5, 2, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[2]);

            // print front right tyre status
            mvwprintw(tyre.win, 4, 27, "FR: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[3], (int)car_telemetry->m_tyresSurfaceTemperature[3]);
            mvwprintw(tyre.win, 5, 27, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[3]);

        } else if (header->m_packetId == PID_CAR_STATUS) {

            PacketCarStatusData *car_status_packet = (PacketCarStatusData*)buffer;
            CarStatusData *car_status = &car_status_packet->m_carStatusData[header->m_playerCarIndex];

            // clear the status window
            wmove(status.win, 4, 0);
            wclrtoeol(status.win);

            wmove(status.win, 5, 0);
            wclrtoeol(status.win);

            wmove(status.win, 6, 0);
            wclrtoeol(status.win);

            wmove(status.win, 8, 0);
            wclrtoeol(status.win);

            wmove(status.win, 9, 0);
            wclrtoeol(status.win);

            // clear the tyre window
            wmove(tyre.win, 1, 0);
            wclrtoeol(tyre.win);

            wmove(tyre.win, 2, 0);
            wclrtoeol(tyre.win);

            wmove(tyre.win, 6, 0);
            wclrtoeol(tyre.win);

            wmove(tyre.win, 10, 0);
            wclrtoeol(tyre.win);

            // in theory. the cursor position should be at around (14 + (width - 21 + 14) + 2 + 6)
            // meter label + meter length + meter bracket + digits of engine rpm

            // draw the max engine rpm in the meter
            mvwprintw(meter.win, 3, 14 + (meter.width - (21 + 14)) + 2 + 6, "/ %d RPM", car_status->m_maxRPM);

            // draw DRS activation distance
            mvwprintw(status.win, 1, 22, " (%dm) ]", car_status->m_drsActivationDistance);

            // draw ERS mode and fuel status
            mvwprintw(status.win, 4, 2, "ERS Deployed : [ %d%% ]", (int)((car_status->m_ersDeployedThisLap / 4000000) * 100));
            mvwprintw(status.win, 5, 2, "ERS Energy   : [ %d%% ]", (int)((car_status->m_ersStoreEnergy / 4000000) * 100));
            mvwprintw(status.win, 6, 2, "ERS Mode     : [ %s ]", ERS_DEPLOY_VALUE[car_status->m_ersDeployMode]);

            mvwprintw(status.win, 8, 2, "Fuel         : [ %.2f ]", car_status->m_fuelRemainingLaps);
            mvwprintw(status.win, 9, 2, "Fuel Mix     : [ %s ]", FUEL_MIX_VALUE[car_status->m_fuelMix]);

            // print tyre status
            mvwprintw(tyre.win, 1, 2, "Tyre : [ %s ]", TYRE_TYPE_VALUE[car_status->m_visualTyreCompound]);
            mvwprintw(tyre.win, 2, 2, "Age  : [ %d laps ]", (int)car_status->m_tyresAgeLaps);
            mvwprintw(tyre.win, 10, 2, "    WEAR : [ %d%% ]", (int)car_status->m_tyresWear[0]);
            mvwprintw(tyre.win, 10, 27, "    WEAR : [ %d%% ]", (int)car_status->m_tyresWear[1]);
            mvwprintw(tyre.win, 6, 2, "    WEAR : [ %d%% ]", (int)car_status->m_tyresWear[2]);
            mvwprintw(tyre.win, 6, 27, "    WEAR : [ %d%% ]", (int)car_status->m_tyresWear[3]);

        }

        box(meter.win, 0, 0);
        box(status.win, 0, 0);
        box(tyre.win, 0, 0);

        // sleep for 10ms to not destroy computer :D
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
