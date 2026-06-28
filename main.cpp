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

#define WRE_BUF_SIZE 2048
#define WRE_PORT 20777
#define WRE_ADDR "127.0.0.1"
#define BLOCK_CHAR '▉'

int main() {

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
    server_addr.sin_addr.s_addr = inet_addr(WRE_ADDR);
    server_addr.sin_port = htons(WRE_PORT);

    if (bind(sock, (const struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket :(\n";
        exit(EXIT_FAILURE);

    }

    std::cout << "Socket successfully created. Waiting for data\n";

    initscr();
    noecho();

    int width, height;
    getmaxyx(stdscr, height, width);

    // get the packet and check packet ID
    while(true) {

        socklen_t sock_len;
        int received = recvfrom(sock, buffer, WRE_BUF_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, &sock_len);

        PacketHeader *header = (PacketHeader*)buffer;
        int cursor_pos = 0;

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

            box(stdscr, 0, 0);

            // what the heck am i doing. all i know its that i need to draw a progress bar
            mvaddstr(1, 2, "Throttle : [");
            mvaddstr(2, 2, "Brake    : [");
            mvaddstr(3, 2, "RPM      : [");
            cursor_pos += 13;

            // assume 25 characters for decorations. should be enough
            int percentage_limit = width - (30 + cursor_pos);

            mvhline(1, cursor_pos + 1, '-', (int)((car_telemetry->m_throttle * 100) * percentage_limit) / 100);
            mvhline(2, cursor_pos + 1, '-', (int)((car_telemetry->m_brake * 100) * percentage_limit) / 100);
            mvhline(3, cursor_pos + 1, '-', (int)((car_telemetry->m_revLightsPercent) * percentage_limit) / 100);
            cursor_pos += percentage_limit;

            mvaddstr(1, cursor_pos + 1, "]");
            mvaddstr(2, cursor_pos + 1, "]");
            mvaddstr(3, cursor_pos + 1, "]");
            cursor_pos += 1;

            mvprintw(1, cursor_pos + 2, "%d / %d%%", (int)(car_telemetry->m_throttle * 100), 100);
            mvprintw(2, cursor_pos + 2, "%d / %d%%", (int)(car_telemetry->m_brake * 100), 100);
            mvprintw(3, cursor_pos + 2, "%d RPM", (int)car_telemetry->m_engineRPM);

        }

        usleep(6000);
        wnoutrefresh(stdscr);
        doupdate();

        // sleep for 2ms to not destroy computer :D
    }

    endwin();

    return 0;
}
