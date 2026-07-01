#include <ncurses.h>

#include "windows.hpp"

// draw offsets value definitions
static const int METER_BAR_X_DRAW_POS = 14;
static const int BAR_LABEL_X_DRAW_POS = 2;

static const int THROTTLE_BAR_Y_DRAW_POS = 1;
static const int BRAKE_BAR_Y_DRAW_POS = 2;
static const int RPM_BAR_Y_DRAW_POS = 3;
static const int SPEED_BAR_Y_DRAW_POS = 5;

void MeterWindow::draw_throttle(const WRECarTelemetry &car) {

    // draw the label
    mvwaddstr(
        this->win,
        THROTTLE_BAR_Y_DRAW_POS,
        BAR_LABEL_X_DRAW_POS,
        "Throttle : ["
    );

    // draw the meter bar
    mvwhline(
        this->win,
        THROTTLE_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS,
        '=',
        (int)((car.throttle * 100) * percentage_limit) / 100
    );

    // draw the numbers
    mvwprintw(
        this->win,
        THROTTLE_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS + this->percentage_limit,
        "] %d / 100%%", (int)(car.throttle * 100)
    );

}

void MeterWindow::draw_brake(const WRECarTelemetry &car) {

    // draw the label
    mvwaddstr(
        this->win,
        BRAKE_BAR_Y_DRAW_POS,
        BAR_LABEL_X_DRAW_POS,
        "Brake    : ["
    );

    // draw the meter bar
    mvwhline(
        this->win,
        BRAKE_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS,
        '=',
        (int)((car.brake * 100) * percentage_limit) / 100
    );

    // draw the numbers
    mvwprintw(
        this->win,
        BRAKE_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS + this->percentage_limit,
        "] %d / 100%%",
        (int)(car.brake * 100)
    );

}

void MeterWindow::draw_rpm_meter(const WRECarTelemetry &car) {

    // draw the label
    mvwaddstr(
        this->win,
        RPM_BAR_Y_DRAW_POS,
        BAR_LABEL_X_DRAW_POS,
        "RPM      : ["
    );

    // draw the meter bar
    mvwhline(
        this->win,
        RPM_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS,
        '=',
        (int)((car.rev_percent) * percentage_limit) / 100
    );

    // draw the numbers
    mvwprintw(
        this->win,
        RPM_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS + this->percentage_limit,
        "] %d",
        (int)car.engine_rpm
    );

}

void MeterWindow::draw_max_rpm(const WRECarTelemetry &car) {

    // in theory. the cursor position should be at around (14 + (width - 21 + 14) + 2 + 6)
    // meter label + meter length + meter bracket + digits of engine rpm

    // draw the max engine rpm in the meter
    mvwprintw(
        this->win,
        RPM_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS + this->percentage_limit + 2 + 6,
        "/ %5d RPM", car.max_rpm
    );

}

void MeterWindow::draw_speed(const WRECarTelemetry &car) {

    // draw the label
    mvwaddstr(
        this->win,
        SPEED_BAR_Y_DRAW_POS,
        BAR_LABEL_X_DRAW_POS,
        "Speed    : [");

    // draw the meter bar
    mvwhline(
        this->win,
        SPEED_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS,
        '=',
        (int)((car.speed) * percentage_limit) / 380
    );

    // draw the numbers
    mvwprintw(
        this->win,
        SPEED_BAR_Y_DRAW_POS,
        METER_BAR_X_DRAW_POS + this->percentage_limit,
        "] %d / 380 kph",
        (int)car.speed
    );

}

void MeterWindow::clear_win() {

    wmove(this->win, THROTTLE_BAR_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, BRAKE_BAR_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, RPM_BAR_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, SPEED_BAR_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

}
