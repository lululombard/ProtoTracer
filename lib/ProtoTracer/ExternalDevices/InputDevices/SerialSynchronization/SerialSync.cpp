#include "SerialSync.h"

SerialTransfer SerialSync::dataTransfer;
SerialSync::Data SerialSync::data;

void SerialSync::Initialize()
{
    Serial4.begin(230400);
    dataTransfer.begin(Serial4, false); // _debug = true
}

float SerialSync::GetRatio()
{
    return data.ratio;
}

uint8_t SerialSync::GetMode()
{
    return data.mode;
}

float SerialSync::GetMouthMove()
{
    return data.mouthMove;
}

void SerialSync::Read()
{
    if (dataTransfer.available())
    {
        uint16_t receiveSize = 0;
        receiveSize = dataTransfer.rxObj(data, receiveSize);
    }
}

void SerialSync::SetRatio(float ratio)
{
    data.ratio = ratio;
}

void SerialSync::SetMode(uint8_t mode)
{
    data.mode = mode;
}

void SerialSync::SetMouthMove(float ratio)
{
    data.mouthMove = ratio;
}

void SerialSync::Send()
{
    // Format data as a string with key-value pairs
    Serial4.printf("ratio:%.3f", data.ratio);
    Serial4.printf(",mode:%d", data.mode);
    Serial4.printf(",mouthMove:%.3f", data.mouthMove);
    Serial4.printf(",faceState:%d", data.faceState);
    Serial4.printf(",bright:%d", data.bright);
    Serial4.printf(",accentBright:%d", data.accentBright);
    Serial4.printf(",microphone:%d", data.microphone);
    Serial4.printf(",micLevel:%d", data.micLevel);
    Serial4.printf(",boopSensor:%d", data.boopSensor);
    Serial4.printf(",spectrumMirror:%d", data.spectrumMirror);
    Serial4.printf(",faceSize:%d", data.faceSize);
    Serial4.printf(",color:%d", data.color);
    Serial4.printf(",currentMenu:%d", data.currentMenu);
    Serial4.printf(",dead:%d", data.dead ? 1 : 0);
    Serial4.printf(",boop:%d", data.boop ? 1 : 0);
    Serial4.println(); // End with newline
}

void SerialSync::SetFaceState(uint8_t faceState)
{
    data.faceState = faceState;
}

uint8_t SerialSync::GetFaceState()
{
    return data.faceState;
}

void SerialSync::SetBrightness(uint8_t bright)
{
    data.bright = bright;
}

uint8_t SerialSync::GetBrightness()
{
    return data.bright;
}

void SerialSync::SetAccentBrightness(uint8_t accentBright)
{
    data.accentBright = accentBright;
}

uint8_t SerialSync::GetAccentBrightness()
{
    return data.accentBright;
}

void SerialSync::SetUseMicrophone(uint8_t microphone)
{
    data.microphone = microphone;
}

uint8_t SerialSync::UseMicrophone()
{
    return data.microphone;
}

void SerialSync::SetMicLevel(uint8_t micLevel)
{
    data.micLevel = micLevel;
}

uint8_t SerialSync::GetMicLevel()
{
    return data.micLevel;
}

void SerialSync::SetUseBoopSensor(uint8_t boopSensor)
{
    data.boopSensor = boopSensor;
}

uint8_t SerialSync::UseBoopSensor()
{
    return data.boopSensor;
}

void SerialSync::SetMirrorSpectrumAnalyzer(uint8_t spectrumMirror)
{
    data.spectrumMirror = spectrumMirror;
}

uint8_t SerialSync::MirrorSpectrumAnalyzer()
{
    return data.spectrumMirror;
}

void SerialSync::SetFaceSize(uint8_t faceSize)
{
    data.faceSize = faceSize;
}

uint8_t SerialSync::GetFaceSize()
{
    return data.faceSize;
}

void SerialSync::SetFaceColor(uint8_t color)
{
    data.color = color;
}

uint8_t SerialSync::GetFaceColor()
{
    return data.color;
}

void SerialSync::SetCurrentMenu(uint8_t currentMenu)
{
    data.currentMenu = currentMenu;
}

uint8_t SerialSync::GetCurrentMenu()
{
    return data.currentMenu;
}

void SerialSync::SetDead(bool dead)
{
    data.dead = dead;
}

bool SerialSync::GetDead()
{
    return data.dead;
}

void SerialSync::SetBoop(bool boop)
{
    data.boop = boop;
}

bool SerialSync::GetBoop()
{
    return data.boop;
}
