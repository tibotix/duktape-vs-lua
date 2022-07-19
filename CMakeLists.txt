cmake_minimum_required(VERSION 3.10)

project(DuktapeVSLua)


add_executable(duktapebench duktapebench.cpp duktape/include/duktape.c)
target_include_directories(duktapebench PUBLIC duktape/include)


add_executable(luabench luabench.cpp)
target_include_directories(luabench PUBLIC lua/lua-5.4.4/src)
target_link_directories(luabench PUBLIC lua/lua-5.4.4/src)
target_link_libraries(luabench PUBLIC liblua.a)
