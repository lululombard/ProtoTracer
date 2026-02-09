/**
 * @file SerialMenuController.h
 * @brief Provides serial control of Menu parameters via a text-based protocol.
 *
 * Allows an external device (e.g., ESP32) connected on Serial4 to read and write
 * menu parameter values using simple newline-terminated text commands.
 *
 * Protocol:
 *   SET <PARAM> <VALUE>\n   - Set a parameter (0-9)
 *   GET <PARAM>\n           - Query a parameter, responds: <PARAM>=<VALUE>\n
 *   GET ALL\n               - Query all parameters
 *   SAVE\n                  - Persist current values to EEPROM
 *
 * Parameter names:
 *   FACE, BRIGHT, ABRIGHT, MIC, MICLVL, BOOP, SPEC, SIZE, COLOR, HUEF, HUEB, EFFECT, FAN
 */

#pragma once

#include <Arduino.h>

class SerialMenuController {
private:
    static const uint8_t bufferSize = 32;
    static char buffer[bufferSize];
    static uint8_t bufferIndex;

    static void ProcessCommand(const char* cmd);
    static int8_t ParseParam(const char* name);
    static const char* ParamName(uint8_t index);
    static void SendValue(uint8_t param);
    static void SendAll();

public:
    static void Initialize(uint32_t baud = 921600);
    static void Update();
};
