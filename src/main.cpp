#include "ImFrame.h"


#ifdef IMFRAME_WINDOWS
#include <SDKDDKVer.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include "app.hpp"

namespace app
{
    class MainApp : public ImFrame::ImApp
    {
      public:
        MainApp(GLFWwindow* window) :
            ImFrame::ImApp(window)
        {
        }
        virtual ~MainApp() {}
        void OnUpdate() override { app.Update(); }

      private:
        Canerator app;
    };
}  // namespace app

// ImFrame main function and app creation
IMFRAME_MAIN("Canerator", "Canerator", app::MainApp)
