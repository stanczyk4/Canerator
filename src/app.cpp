#include "app.hpp"

#include <iostream>

#include "ImFrame.h"
#include "imgui.h"
#include "implot.h"

namespace app
{

    Canerator::Canerator()
    {
        std::cout << "Hi from C++, this is a demo how LuaCpp can be used"
                  << "\n";

        // The simples way is to use CompileStringAndRun method
        try
        {
            // lua.CompileStringAndRun("print('The fastest way to start using lua in a project')");
            lua_.CompileFile("main", "scripts/main.lua");
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << '\n';
        }
    }

    Canerator::~Canerator()
    {
    }

    void Canerator::Update()
    {
        // ImGui::ShowDemoWindow();
        // ImPlot::ShowDemoWindow();

        ImGui::Begin("Debug");
        ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Begin("Canerator");

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Edit"))
            {
                ImGui::EndMenu();
            }
            ImGui::EndMainMenuBar();
        }

        if (ImGui::Button("Execute Lua Script"))
        {
            lua_.Run("main");
        }

        if (ImGui::Button("File Explorer"))
        {
            ImFrame::OpenFileDialog({{"Image files", "png,jpg"}}, nullptr);
        }

        ImGui::End();
    }
}  // namespace app
