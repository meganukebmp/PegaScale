#include <cstdio>
#include <string>
#include <regex>
#include <UserAgent.h>

std::string getNFVersion(std::string useragent) {
    std::regex sregex("NF\\/\\d+\\.\\d+\\.\\d+\\.\\d+\\.\\d+\\s");
    std::smatch matchresult;
    std::regex_match(useragent, matchresult, sregex);

    if (!std::regex_search(useragent,matchresult,sregex)) {
        return "";
    }

    return matchresult[0].str();
}

switchfwversion_t getFWVersion(std::string useragent) {
    std::string nfversion = getNFVersion(useragent);
    switchfwversion_t fwversion;

    if (nfversion == "NF/4.0.0.4.25 ") {
        return (switchfwversion_t) {1, 0, 0};
    } else if (nfversion == "NF/4.0.0.5.9 ") {
        return (switchfwversion_t) {2, 0, 0};
    } else if (nfversion == "NF/4.0.0.5.10 ") {
        return (switchfwversion_t) {2, 1, 0};
    } else if (nfversion == "NF/4.0.0.6.9 ") {
        return (switchfwversion_t) {3, 0, 0};
    } else if (nfversion == "NF/4.0.0.7.9 ") {
        return (switchfwversion_t) {4, 0, 0};
    } else if (nfversion == "NF/4.0.0.8.9 ") {
        return (switchfwversion_t) {5, 0, 0};
    } else if (nfversion == "NF/4.0.0.9.3 ") {
        return (switchfwversion_t) {5, 1, 0};
    } else if (nfversion == "NF/4.0.0.10.13 ") {
        return (switchfwversion_t) {6, 0, 0};
    } else {
        return (switchfwversion_t) {99, 99, 99};
    }
}

std::string getFWVersionString(switchfwversion_t fwversion) {
    char versionbuf[12];
    snprintf(versionbuf, sizeof(versionbuf), "%d.%d.%d", fwversion.major, fwversion.minor, fwversion.patch);
    std::string versionstring(versionbuf);
    return versionstring;
}