#include <nspl.hpp>

using namespace NSPL;


int main() {
    if(!Application::Instance().Init({"Test"})) return -1;

    Application::Instance().Run();
    Application::Instance().Shutdown();
    return 0;
}