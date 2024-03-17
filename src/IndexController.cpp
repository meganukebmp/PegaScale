#include <string>
#include <fstream>
#include <IndexController.h>
#include <UserAgent.h>

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
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_HTML);

    // Match Nintendo useragent
    std::string useragent = req->getHeader("user-agent");
    switchfwversion_t version = getFWVersion(useragent);

    if (version.major > 6 && version.minor > 0 && version.patch > 0) {
        resp->setBody("UNSUPPORTED");
        callback(resp);
        return;
    }

    std::ostringstream buf;
    std::ifstream input("www/index.html");
    buf << input.rdbuf();

    std::string body = buf.str();
    replaceAllInString(body, "$$$VERSION", getFWVersionString(version));
    if (version.major >= 5) {
        replaceAllInString(body, "$$$WARNING", "");
    }
    else {
        replaceAllInString(body, "$$$WARNING", "<td><p style=\"font-size:15px;\"><b>The spinner will freeze on firmwares 4.0.0 - 4.1.0, you should wait approximately 20-45 seconds for the exploit to run.</b></p></td>");
    }

    replaceAllInString(body, "$$$ITEMS", "<td><a href=\"#caffeine400\" onclick=\"window.scriptSelected();\"><img class=\"icon\" style=\"width:160px\" src=\"/caffeine.png\"/></a></td>");

    resp->setBody(body);
    callback(resp);
}