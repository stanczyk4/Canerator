#include "app.hpp"

#include "ImFrame.h"
#include "imgui.h"
#include "implot.h"


namespace app
{

    Canerator::Canerator()
    {
    }

    Canerator::~Canerator()
    {
    }

    void Canerator::Update()
    {
        ImGui::Begin("Canerator");

        ImGui::Button("Test");

        // ImFrame::OpenFileDialog()

        ImGui::End();
    }
}  // namespace app
