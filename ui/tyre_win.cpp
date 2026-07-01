#include <ncurses.h>

#include "windows.hpp"
#include "../spec/structs.hpp"
#include "../spec/maps.hpp"

static const int TYRE_LABEL_X_DRAW_POS = 2;
static const int RIGHT_TYRE_X_DRAW_POS = 27;

static const int TYRE_TYPE_Y_DRAW_POS = 1;
static const int TYRE_AGE_Y_DRAW_POS = 2;

static const int TYRE_FRONT_STATUS_Y_DRAW_POS = 4;
static const int TYRE_REAR_STATUS_Y_DRAW_POS = 8;

static const int BRAKE_FRONT_STATUS_Y_DRAW_POS = 5;
static const int BRAKE_REAR_STATUS_Y_DRAW_POS = 9;

static const int TYRE_WEAR_FRONT_Y_DRAW_POS = 6;
static const int TYRE_WEAR_REAR_Y_DRAW_POS = 10;

void TyreWindow::draw_tyre_status(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        TYRE_TYPE_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "Tyre : [ %s ]",
        TYRE_TYPE_VALUE[car.tyre_type]
    );

    mvwprintw(
        this->win,
        TYRE_AGE_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "Age  : [ %d laps ]",
        (int)car.tyre_age
    );

}

void TyreWindow::draw_tyre_and_brake_temp(const WRECarTelemetry &car) {

    // print front left tyre status
    mvwprintw(this->win,
        TYRE_FRONT_STATUS_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "FL: %d C (SUR: %d C)",
        (int)car.tyre_inner_temp[2],
        (int)car.tyre_surface_temp[2]
    );

    mvwprintw(
        this->win,
        BRAKE_FRONT_STATUS_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "    BRAKE: [ %d C ]",
        (int)car.brake_temp[2]);

    // print front right tyre status
    mvwprintw(this->win,
        TYRE_FRONT_STATUS_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "FR: %d C (SUR: %d C)",
        (int)car.tyre_inner_temp[3],
        (int)car.tyre_surface_temp[3]
    );

    mvwprintw(
        this->win,
        BRAKE_FRONT_STATUS_Y_DRAW_POS,
        RIGHT_TYRE_X_DRAW_POS,
        "    BRAKE: [ %d C ]",
        (int)car.brake_temp[3]
    );

    // print reat left tyre status
    mvwprintw(
        this->win,
        TYRE_REAR_STATUS_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "RL: %d C (SUR: %d C)",
        (int)car.tyre_inner_temp[0],
        (int)car.tyre_surface_temp[0]
    );

    mvwprintw(
        this->win,
        BRAKE_REAR_STATUS_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "    BRAKE: [ %d C ]",
        (int)car.brake_temp[0]);

    // print rear right tyre status
    mvwprintw(
        this->win,
        TYRE_REAR_STATUS_Y_DRAW_POS,
        RIGHT_TYRE_X_DRAW_POS,
        "RR: %d C (SUR: %d C)",
        (int)car.tyre_inner_temp[1],
        (int)car.tyre_surface_temp[1]
    );

    mvwprintw(
        this->win,
        BRAKE_REAR_STATUS_Y_DRAW_POS,
        RIGHT_TYRE_X_DRAW_POS,
        "    BRAKE: [ %d C ]",
        (int)car.brake_temp[1]
    );

}

void TyreWindow::draw_tyre_wear(const WRECarTelemetry &car) {

    mvwprintw(
        this->win,
        TYRE_WEAR_FRONT_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "    WEAR : [ %d%% ]",
        (int)car.tyres_wear[2]
    );

    mvwprintw(
        this->win,
        TYRE_WEAR_FRONT_Y_DRAW_POS,
        RIGHT_TYRE_X_DRAW_POS,
        "    WEAR : [ %d%% ]",
        (int)car.tyres_wear[3]
    );

    mvwprintw(
        this->win,
        TYRE_WEAR_REAR_Y_DRAW_POS,
        TYRE_LABEL_X_DRAW_POS,
        "    WEAR : [ %d%% ]",
        (int)car.tyres_wear[0]
    );

    mvwprintw(
        this->win,
        TYRE_WEAR_REAR_Y_DRAW_POS,
        RIGHT_TYRE_X_DRAW_POS,
        "    WEAR : [ %d%% ]",
        (int)car.tyres_wear[1]
    );

}

void TyreWindow::clear_win() {

    wmove(this->win, TYRE_TYPE_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, TYRE_AGE_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, TYRE_FRONT_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, BRAKE_FRONT_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, TYRE_WEAR_FRONT_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, TYRE_REAR_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, BRAKE_REAR_STATUS_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

    wmove(this->win, TYRE_WEAR_REAR_Y_DRAW_POS, 0);
    wclrtoeol(this->win);

}
