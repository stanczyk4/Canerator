cmake_minimum_required(VERSION 3.26)

# Source files
set(LUA_SOURCE_FILES
    Lua.hpp
    LuaCpp.hpp
    LuaVersion.cpp LuaVersion.hpp
    Engine/LuaState.cpp Engine/LuaState.hpp
    Engine/LuaType.cpp Engine/LuaType.hpp
    Engine/LuaTNil.cpp Engine/LuaTNil.hpp
    Engine/LuaTString.cpp Engine/LuaTString.hpp
    Engine/LuaTNumber.cpp Engine/LuaTNumber.hpp
    Engine/LuaTBoolean.cpp Engine/LuaTBoolean.hpp
    Engine/LuaTTable.cpp Engine/LuaTTable.hpp
    Engine/LuaTUserData.cpp Engine/LuaTUserData.hpp
    Registry/LuaRegistry.cpp Registry/LuaRegistry.hpp
    Registry/LuaCodeSnippet.cpp Registry/LuaCodeSnippet.hpp
    Registry/LuaCompiler.cpp Registry/LuaCompiler.hpp
    Registry/LuaCFunction.cpp Registry/LuaCFunction.hpp
    Registry/LuaLibrary.cpp Registry/LuaLibrary.hpp
    LuaContext.cpp LuaContext.hpp
    LuaMetaObject.cpp LuaMetaObject.hpp
)

add_library(luacpp STATIC ${LUA_SOURCE_FILES})
target_link_libraries(luacpp ${CMAKE_CURRENT_LIST_DIR}/lua/lua54.lib)
target_include_directories(luacpp PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(luacpp PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lua/include)
