// LGFX_JD9165.hpp - JD9165 DSI Panel Driver for LovyanGFX
#pragma once

#define LGFX_USE_V1
#include "Panel_JD9165.hpp"
#include <LovyanGFX.hpp>

class LGFX_JD9165 : public lgfx::LGFX_Device {
  public:
    lgfx::Bus_DSI _bus_dsi;
    lgfx::Panel_JD9165 _panel_instance;

    LGFX_JD9165(void) {
        // DSI bus configuration
        {
            auto cfg = _bus_dsi.config();
            cfg.bus_id = 0;
            cfg.lane_num = 2;
            cfg.lane_mbps = 750;
            cfg.ldo_chan_id = 3;
            cfg.ldo_voltage_mv = 2500;
            cfg.lcd_cmd_bits = 8;
            cfg.lcd_param_bits = 8;
            _bus_dsi.config(cfg);
        }

        // Link panel to bus
        _panel_instance.setBus(&_bus_dsi);

        // Set panel to LGFX device
        setPanel(&_panel_instance);
    }

    /**
     * @brief Initialize the display.
     * @param rst_pin Reset pin number. If -1, no hardware reset is performed.
     */
    bool begin(int rst_pin = -1) {
        // Hardware Reset if pin is specified
        if(rst_pin >= 0) {
            ::pinMode(rst_pin, OUTPUT);
            ::digitalWrite(rst_pin, LOW);
            delay(100);
            ::digitalWrite(rst_pin, HIGH);
            delay(200);
        }

        // Initialize panel
        if(!init()) {
            return false;
        }

        // LovyanGFX basic settings
        setRotation(0);
        setColorDepth(16);

        return true;
    }
};
