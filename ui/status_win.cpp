#include <ncurses.h>

#include "windows.hpp"
#include "../spec/constants.hpp"
#include "../spec/maps.hpp"

// TODO: change the value for each game
// this is temporary
static const int ERS_CAPACITY = 4000000;

// draw offsets value definitions
static const int STATUS_LABEL_X_DRAW_POS = 2;

static const int DRS_STATUS_Y_DRAW_POS = 1;
static const int DRS_DISTANCE_X_DRAW_POS = 22;

static const int GEAR_STATUS_Y_DRAW_POS = 2;

static const int ERS_DEPLOY_STATUS_Y_DRAW_POS = 4;
static const int ERS_ENERGY_STATUS_Y_DRAW_POS = 5;
static const int ERS_MODE_STATUS_Y_DRAW_POS = 6;

static const int FUEL_CAP_STATUS_Y_DRAW_POS = 8;
static const int FUEL_MIX_STATUS_Y_DRAW_POS = 9;

void StatusWindow::draw_drs_status(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        DRS_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "DRS          : [ %s",
        (car.drs == CAR_DRS_ENABLED) ? "ON" : "OFF"
    );

}

void StatusWindow::draw_drs_distance(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        DRS_STATUS_Y_DRAW_POS,
        DRS_DISTANCE_X_DRAW_POS,
        " (%dm) ]",
        car.drs_distance
    );

}

void StatusWindow::draw_gear(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        GEAR_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "Gear         : [ %c (%d) ]",
        GEAR_VALUE[car.gear], (int)car.suggested_gear
    );

}

void StatusWindow::draw_ers(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        ERS_DEPLOY_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "ERS Deployed : [ %d%% ]",
        (int)((car.ers_deployed / ERS_CAPACITY) * 100)
    );

    mvwprintw(
        this->win,
        ERS_ENERGY_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "ERS Energy   : [ %d%% ]",
        (int)((car.ers_energy / ERS_CAPACITY) * 100)
    );

    mvwprintw(
        this->win,
        ERS_MODE_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "ERS Mode     : [ %s ]",
        ERS_DEPLOY_VALUE[car.ers_mode]
    );

}

void StatusWindow::draw_fuel(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        FUEL_CAP_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "Fuel         : [ %.2f ]",
        car.fuel_remaining
    );

    mvwprintw(
        this->win,
        FUEL_MIX_STATUS_Y_DRAW_POS,
        STATUS_LABEL_X_DRAW_POS,
        "Fuel Mix     : [ %s ]",
        FUEL_MIX_VALUE[car.fuel_mix]
    );

}

void StatusWindow::clear_win() {

    wmove(this->win, DRS_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, GEAR_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, ERS_DEPLOY_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, ERS_ENERGY_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, ERS_MODE_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, FUEL_CAP_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, FUEL_MIX_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

}
