#ifndef _WRE_UI_METER_HPP_
#define _WRE_UI_METER_HPP_

#include <ncurses.h>

#include "../spec/structs.hpp"

class CursesWindow {

    public:

        WINDOW *win;
        int height;
        int width;

        CursesWindow(WINDOW *wi, int h, int w) : win(wi), height(h), width(w) {}

        virtual void clear_win() = 0;

};

class MainWindow final : public CursesWindow {

    public:

        MainWindow(WINDOW *wi, int h, int w) : CursesWindow(wi, h, w) {}

        void clear_win() override;

};

class MeterWindow final : public CursesWindow {

    private:
        int percentage_limit;

    public:

        MeterWindow(WINDOW *wi, int h, int w) : CursesWindow(wi, h, w), percentage_limit(getmaxx(wi) - (21 + 14)) {}

        void draw_throttle(const WRECarTelemetry &car);
        void draw_brake(const WRECarTelemetry &car);

        void draw_rpm_meter(const WRECarTelemetry &car);
        void draw_max_rpm(const WRECarTelemetry &car);

        void draw_speed(const WRECarTelemetry &car);

        void clear_win() override;

};

class StatusWindow final : public CursesWindow {

    public:

        StatusWindow(WINDOW *wi, int h, int w) : CursesWindow(wi, h, w) {}

        void draw_drs_status(const WRECarTelemetry &car);
        void draw_drs_distance(const WRECarTelemetry &car);

        void draw_gear(const WRECarTelemetry &car);
        void draw_ers(const WRECarTelemetry &car);
        void draw_fuel(const WRECarTelemetry &car);

        void clear_win() override;

};

class TyreWindow final : public CursesWindow {

    public:

        TyreWindow(WINDOW *wi, int h, int w) : CursesWindow(wi, h, w) {}

        void draw_tyre_status(const WRECarTelemetry &car);
        void draw_tyre_and_brake_temp(const WRECarTelemetry &car);
        void draw_tyre_wear(const WRECarTelemetry &car);

        void clear_win() override;

};

#endif
