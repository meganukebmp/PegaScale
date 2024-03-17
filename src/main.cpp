#include <cstdio>
#include <drogon/HttpAppFramework.h>

int main(int argc, char const *argv[])
{
    printf("Dragons!\n");
    //Set HTTP listener address and port
    drogon::app().addListener("0.0.0.0",80);
    drogon::app().setFileTypes({"html","js","png","jpg","jpeg","gif","bmp","nro","bin"});
    drogon::app().setDocumentRoot("www");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}