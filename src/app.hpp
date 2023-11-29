#pragma once

#include "LuaCpp.hpp"

using namespace LuaCpp;
using namespace LuaCpp::Registry;
using namespace LuaCpp::Engine;

namespace app
{
    class Canerator
    {
      public:
        Canerator();
        ~Canerator();

        void Update();

        void UpdateMouseButton(int button, int action, int mods);
        void UpdateMousePosition(double x, double y);

      private:
        LuaContext lua_;
    };
}  // namespace app
