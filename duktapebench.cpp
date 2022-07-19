#include "duktape.h"
#include <iostream>

duk_ret_t native_add(duk_context *ctx)
{
    int num1 = duk_to_int(ctx, 0);
    int num2 = duk_to_int(ctx, 1);
    duk_push_int(ctx, num1 + num2);
    return 1;
}
duk_ret_t native_print(duk_context *ctx)
{
    std::cout << duk_to_string(ctx, 0) << std::endl;
    return 0;
}

duk_context *ctx = duk_create_heap_default();
int main()
{
    // const char *fib = "function fib(n) { if(n <= 1) {return n} return native_add(fib(native_add(n, -1)), fib(native_add(n, -2)));} native_print(fib(20));";
    // const char *fib = "function fib(n) { if(n <= 1) {return n} return native_add(fib(n - 1), fib(n - 2));} native_print(fib(20));";
    const char *sort = "var items = [5,3,7,6,2,9]; items.sort(); native_print(items[0]);";

    duk_push_global_object(ctx);
    duk_idx_t obj_id = duk_get_top_index(ctx);
    duk_push_c_function(ctx, native_add, 2);
    duk_put_prop_string(ctx, obj_id, "native_add");
    duk_push_c_function(ctx, native_print, 1);
    duk_put_prop_string(ctx, obj_id, "native_print");

    duk_peval_string_noresult(ctx, sort);
}