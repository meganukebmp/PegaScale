#include <string>
#include <fstream>
#include <IndexController.h>
#include <UserAgent.h>
#include <ExploitScripts.h>

bool replaceAllInString(std::string &original, std::string tobereplaced, std::string replacement) {
    if(tobereplaced.empty())
        return false;
    size_t start_pos = 0;
    bool success = false;
    while((start_pos = original.find(tobereplaced, start_pos)) != std::string::npos) {
        original.replace(start_pos, tobereplaced.length(), replacement);
        start_pos += replacement.length();
        success = true;
    }
    return success;
}

void IndexController::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {

    // Match Nintendo useragent
    std::string useragent = req->getHeader("user-agent");
    switchfwversion_t version = getFWVersion(useragent);

    if (version.major > 6 && version.minor > 0 && version.patch > 0) {
        // resp->setBody("UNSUPPORTED");
        // callback(resp);
        // return;
    }

    HttpViewData data;
    data.insert("version", getFWVersionString(version));
    if (version.major == 4) {
        data.insert("warning", "The spinner will freeze on firmwares 4.0.0 - 4.1.0, you should wait approximately 20-45 seconds for the exploit to run.");
    }

    std::vector<exploitscript_t> items;
    for (int i=0;i<sizeof(explotscripts)/sizeof(exploitscript_t);i++) {
        int minver = explotscripts[i].minver.major * 100 + explotscripts[i].minver.minor * 10 + explotscripts[i].minver.patch;
        int maxver = explotscripts[i].maxver.major * 100 + explotscripts[i].maxver.minor * 10 + explotscripts[i].maxver.patch;
        int curver = version.major * 100 + version.minor * 10 + version.patch;
        if (minver <= curver && maxver >= curver) {
            items.push_back(explotscripts[i]);
        }
    }

    data.insert("items", items);

    // replaceAllInString(body, "$$$ITEMS", "<td><a href=\"#caffeine400\" onclick=\"window.scriptSelected();\"><img class=\"icon\" style=\"width:160px\" src=\"/caffeine.png\"/></a></td>");

    auto resp=HttpResponse::newHttpViewResponse("IndexView.csp",data);
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);
    callback(resp);
}