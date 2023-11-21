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

        // Update tick
        void OnUpdate() override { app.Update(); }

        // Input events
        void OnKeyEvent([[maybe_unused]] int key,
                        [[maybe_unused]] int scancode,
                        [[maybe_unused]] int action,
                        [[maybe_unused]] int mods) override
        {
        }
        void OnKeyPress([[maybe_unused]] int key, [[maybe_unused]] int mods) override {}
        void OnMouseButtonEvent([[maybe_unused]] int button,
                                [[maybe_unused]] int action,
                                [[maybe_unused]] int mods) override
        {
        }
        void OnCursorPosition([[maybe_unused]] double x, [[maybe_unused]] double y) override {}

        // Window messages
        void OnWindowPositionChange([[maybe_unused]] int x, [[maybe_unused]] int y) override {}
        void OnWindowSizeChange([[maybe_unused]] int width, [[maybe_unused]] int height) override {}
        void OnWindowMaximize([[maybe_unused]] bool maximized) override {}

      private:
        Canerator app;
    };
}  // namespace app

// ImFrame main function and app creation
IMFRAME_MAIN("Canerator", "Canerator", app::MainApp)
