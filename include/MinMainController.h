#pragma once
#include <drogon/HttpSimpleController.h>
using namespace drogon;
class MinMainController:public drogon::HttpSimpleController<MinMainController> {
    public:
        virtual void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)override;

        PATH_LIST_BEGIN
        PATH_ADD("/minmain.js",Get);
        PATH_LIST_END
};