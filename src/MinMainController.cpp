#include <string>
#include <fstream>
#include <MinMainController.h>
#include <UserAgent.h>

void MinMainController::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) {
    auto resp=HttpResponse::newHttpResponse();
    resp->setStatusCode(k200OK);
    resp->setContentTypeCode(CT_TEXT_JAVASCRIPT);

    // Match Nintendo useragent
    std::string useragent = req->getHeader("user-agent");
    switchfwversion_t version = getFWVersion(useragent);

    // Don't handle new versions
    if (version.major > 6 && version.minor > 0 && version.patch > 0) {
        resp->setBody("alert(\"UNSUPPORTED!\");");
        callback(resp);
        return;
    }

    // Handle 1.0.0-4.1.0 and 5.0.0-6.0.1
    std::string filename = "www/minmain_1.0.0-4.1.0.js";
    if (version.major >= 5) {
        filename = "www/minmain_5.0.0-6.0.1.js";
    }

    std::ostringstream buf;
    std::ifstream input(filename);
    buf << input.rdbuf();
    std::string body = buf.str();
    resp->setBody(body);
    callback(resp);
}