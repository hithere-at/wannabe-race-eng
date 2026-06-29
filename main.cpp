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

// argv[1] is the address
// argv[2] is the port
int main(int argc, char *argv[]) {

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
    server_addr.sin_port = htons(parse_int(argv[2]));

    if (bind(sock, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket :(\n";
        exit(EXIT_FAILURE);

    }

    std::cout << "Socket successfully created. Waiting for data\n";

    initscr();
    noecho();
    curs_set(0);

    int width, height;
    getmaxyx(stdscr, height, width);

    // get the packet and check packet ID
    while(true) {

        socklen_t sock_len = sizeof(server_addr);
        int received = recvfrom(sock, buffer, WRE_BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &sock_len);

        PacketHeader *header = (PacketHeader*)buffer;
        int cursor_x_pos = 0;

        // then just read the data based on the packet id
        if (header->m_packetId == PID_CAR_TELEMETRY) {

            PacketCarTelemetryData *car_packets = (PacketCarTelemetryData*)buffer;
            CarTelemetryData *car_telemetry = &car_packets->m_carTelemetryData[header->m_playerCarIndex];

            move(1, 0);
            clrtoeol();

            move(2, 0);
            clrtoeol();

            move(3, 0);
            clrtoeol();

            move(5, 0);
            clrtoeol();

            move(7, 0);
            clrtoeol();

            move(8, 0);
            clrtoeol();

            move(height - 5, 0);
            clrtoeol();

            move(height - 4, 0);
            clrtoeol();

            move(height - 2, 0);
            clrtoeol();

            move(height - 3, 0);
            clrtoeol();

            // draw the meters
            mvaddstr(1, 2, "Throttle : [");
            mvaddstr(2, 2, "Brake    : [");
            mvaddstr(3, 2, "RPM      : [");
            mvaddstr(5, 2, "Speed    : [");
            cursor_x_pos += 14;

            // assume 25 characters for decorations. should be enough
            int percentage_limit = width - (21 + cursor_x_pos);

            mvhline(1, cursor_x_pos, '=', (int)((car_telemetry->m_throttle * 100) * percentage_limit) / 100);
            mvhline(2, cursor_x_pos, '=', (int)((car_telemetry->m_brake * 100) * percentage_limit) / 100);
            mvhline(3, cursor_x_pos, '=', (int)((car_telemetry->m_revLightsPercent) * percentage_limit) / 100);
            mvhline(5, cursor_x_pos, '=', (int)((car_telemetry->m_speed) * percentage_limit) / 380);
            cursor_x_pos += percentage_limit;

            mvaddstr(1, cursor_x_pos, "]");
            mvaddstr(2, cursor_x_pos, "]");
            mvaddstr(3, cursor_x_pos, "]");
            mvaddstr(5, cursor_x_pos, "]");
            cursor_x_pos += 2;

            mvprintw(1, cursor_x_pos, "%d / 100%%", (int)(car_telemetry->m_throttle * 100));
            mvprintw(2, cursor_x_pos, "%d / 100%%", (int)(car_telemetry->m_brake * 100));
            mvprintw(3, cursor_x_pos, "%d", (int)car_telemetry->m_engineRPM);
            mvprintw(5, cursor_x_pos, "%d / 380 kph", (int)car_telemetry->m_speed);
            cursor_x_pos = 0;

            // draw car DRS status
            mvprintw(7, width - 55, "DRS                 : [ %s ]", (car_telemetry->m_drs == CAR_DRS_ENABLED) ? "ON" : "OFF");
            cursor_x_pos += width - 55;

            // draw gear status
            mvprintw(7, cursor_x_pos + 31, "Gear           : [ %c ]", GEAR_VALUE[car_telemetry->m_gear]);
            mvprintw(8, cursor_x_pos + 31, "Suggested Gear : [ %d ]", (int)car_packets->m_suggestedGear);
            cursor_x_pos = 0;

            // print rear left tyre status
            mvprintw(height - 3, 2, "RL: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[0], (int)car_telemetry->m_tyresSurfaceTemperature[0]);
            mvprintw(height - 2, 2, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[0]);

            // print rear right tyre status
            mvprintw(height - 3, 27, "RR: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[1], (int)car_telemetry->m_tyresSurfaceTemperature[1]);
            mvprintw(height - 2, 27, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[1]);

            // print front left tyre status
            mvprintw(height - 6, 2, "FL: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[2], (int)car_telemetry->m_tyresSurfaceTemperature[2]);
            mvprintw(height - 5, 2, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[2]);

            // print front right tyre status
            mvprintw(height - 6, 27, "FR: %d C (SUR: %d C)", (int)car_telemetry->m_tyresInnerTemperature[3], (int)car_telemetry->m_tyresSurfaceTemperature[3]);
            mvprintw(height - 5, 27, "    BRAKE: [ %d C ]", (int)car_telemetry->m_brakesTemperature[3]);

        } else if (header->m_packetId == PID_CAR_STATUS) {

            PacketCarStatusData *car_status_packet = (PacketCarStatusData*)buffer;
            CarStatusData *car_status = &car_status_packet->m_carStatusData[header->m_playerCarIndex];

            move(height - 8, 0);
            clrtoeol();

            // in theory. the cursor position should be at around (14 + (width - 21 + 14) + 2 + 6)
            // meter label + meter length + meter bracket + digits of engine rpm

            // draw the max engine rpm in the meter and DRS activation distance
            mvprintw(3, 14 + (width - (21 + 14)) + 2 + 6, "/ %d RPM", car_status->m_maxRPM);
            mvprintw(8, width - 55, "Activation Distance : [ %dm ]", car_status->m_drsActivationDistance);

            // draw ERS mode and fuel status
            mvprintw(height - 5, width - 25, "ERS Mode : [ %s ]", ERS_DEPLOY_VALUE[car_status->m_ersDeployMode]);

            mvprintw(height - 3, width - 25, "Fuel     : [ %.2f ]", car_status->m_fuelRemainingLaps);
            mvprintw(height - 2, width - 25, "Fuel Mix : [ %s ]", FUEL_MIX_VALUE[car_status->m_fuelMix]);

            // print tyre type
            mvprintw(height - 8, 2, "Tyre : [ %s ]", TYRE_TYPE_VALUE[car_status->m_visualTyreCompound]);

        }

        box(stdscr, 0, 0);

        // sleep for 10ms to not destroy computer :D
        usleep(5000);
        wnoutrefresh(stdscr);
        doupdate();

    }

    endwin();
    close(sock);

    return 0;
}
