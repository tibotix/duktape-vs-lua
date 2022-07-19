extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include <iostream>

int native_add(lua_State *l)
{
    int num1 = lua_tonumber(l, 1);
    int num2 = lua_tonumber(l, 2);
    lua_pushnumber(l, num1 + num2);
    return 1;
}
int native_print(lua_State *l)
{
    std::cout << lua_tostring(l, 1) << std::endl;
    return 0;
}

int main()
{
    // const char *fib = "function fib(n) if n <= 1 then return n end return fib(native_add(n, -1)) + fib(native_add(n, -2)) end native_print(fib(10))";
    // const char *fib = "function fib(n) if n <= 1 then return n end return fib(n-1) + fib(n-2) end native_print(fib(20))";
    const char *sort = "a = {5,3,7,6,2,9} \n table.sort(a) \n native_print(a[1])";

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_register(L, "native_add", native_add);
    lua_register(L, "native_print", native_print);

    int r = luaL_dostring(L, sort);
    if (r != LUA_OK)
    {
        std::cout << lua_tostring(L, -1) << std::endl;
    }

    lua_close(L);
}