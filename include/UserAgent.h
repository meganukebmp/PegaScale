#pragma once

typedef struct switchfwversion_t {
    int major;
    int minor;
    int patch;
} switchfwversion_t;

std::string getNFVersion(std::string useragent);
switchfwversion_t getFWVersion(std::string useragent);
std::string getFWVersionString(switchfwversion_t fwversion);