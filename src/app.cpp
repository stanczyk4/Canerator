#include "app.hpp"

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

        ImGui::End();
    }
}  // namespace app
