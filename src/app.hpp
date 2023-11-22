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

      private:
        LuaContext lua_;
    };
}  // namespace app
