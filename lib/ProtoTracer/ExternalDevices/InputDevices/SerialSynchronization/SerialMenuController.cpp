#include "SerialMenuController.h"

#include "../../../Examples/UserConfiguration.h"

#ifdef SERIALMENU

#ifdef NEOTRELLISMENU
#include "../NeoTrellisMenuHandler.h"
#elif defined MORSEBUTTON
#include "../SingleButtonMorseHandler.h"
#else
#include "../SingleButtonMenuHandler.h"
#endif

#include <string.h>

static const uint8_t kMenuCount = 13;

char SerialMenuController::buffer[bufferSize];
uint8_t SerialMenuController::bufferIndex = 0;

static const char* const paramNames[] = {
    "FACE", "BRIGHT", "ABRIGHT", "MIC", "MICLVL", "BOOP",
    "SPEC", "SIZE", "COLOR", "HUEF", "HUEB", "EFFECT", "FAN"
};

void SerialMenuController::Initialize(uint32_t baud) {
    Serial4.begin(baud);
}

void SerialMenuController::Update() {
    while (Serial4.available()) {
        char c = Serial4.read();

        if (c == '\n' || c == '\r') {
            if (bufferIndex > 0) {
                buffer[bufferIndex] = '\0';
                ProcessCommand(buffer);
                bufferIndex = 0;
            }
        } else if (bufferIndex < bufferSize - 1) {
            buffer[bufferIndex++] = c;
        }
    }
}

int8_t SerialMenuController::ParseParam(const char* name) {
    for (uint8_t i = 0; i < kMenuCount; i++) {
        if (strcasecmp(name, paramNames[i]) == 0) {
            return i;
        }
    }
    return -1;
}

const char* SerialMenuController::ParamName(uint8_t index) {
    if (index < kMenuCount) return paramNames[index];
    return "?";
}

void SerialMenuController::SendValue(uint8_t param) {
    Serial4.print(ParamName(param));
    Serial4.print('=');
    Serial4.println(MenuHandler<kMenuCount>::GetMenuValue(param));
}

void SerialMenuController::SendAll() {
    for (uint8_t i = 0; i < kMenuCount; i++) {
        SendValue(i);
    }
}

void SerialMenuController::ProcessCommand(const char* cmd) {
    char buf[32];
    strncpy(buf, cmd, sizeof(buf) - 1);
    buf[sizeof(buf) - 1] = '\0';

    char* token = strtok(buf, " ");
    if (!token) return;

    if (strcasecmp(token, "SET") == 0) {
        char* paramStr = strtok(nullptr, " ");
        char* valueStr = strtok(nullptr, " ");
        if (!paramStr || !valueStr) {
            Serial4.println("ERR USAGE: SET <PARAM> <VALUE>");
            return;
        }

        int8_t param = ParseParam(paramStr);
        if (param < 0) {
            Serial4.print("ERR UNKNOWN: ");
            Serial4.println(paramStr);
            return;
        }

        uint8_t value = (uint8_t)atoi(valueStr);
        MenuHandler<kMenuCount>::SetMenuValue(param, value);
        SendValue(param);

    }
    else if (strcasecmp(token, "GET") == 0) {
        char* paramStr = strtok(nullptr, " ");
        if (!paramStr) {
            Serial4.println("ERR USAGE: GET <PARAM|ALL>");
            return;
        }

        if (strcasecmp(paramStr, "ALL") == 0) {
            SendAll();
        } else {
            int8_t param = ParseParam(paramStr);
            if (param < 0) {
                Serial4.print("ERR UNKNOWN: ");
                Serial4.println(paramStr);
                return;
            }
            SendValue(param);
        }

    }
    else if (strcasecmp(token, "SAVE") == 0) {
        for (uint8_t i = 0; i < kMenuCount; i++) {
            MenuHandler<kMenuCount>::SetDefaultValue(i, MenuHandler<kMenuCount>::GetMenuValue(i));
        }
        Serial4.println("OK SAVED");

    }
    else {
        Serial4.print("ERR UNKNOWN CMD: ");
        Serial4.println(token);
    }
}

#endif // SERIALMENU
