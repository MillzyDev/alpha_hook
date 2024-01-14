#pragma once

#include "il2cpp_utils.hpp"
#include "il2cpp-api.h"
#include "codegen/il2cpp-codegen-metadata.h"
#include "dobby.h"

#define MAKE_HOOK_INSTANCE(hook_name, name_space, klass_name, method_name, arg_count, ret, ...)     \
typedef struct _hook_##hook_name {                                                                  \
    static const MethodInfo *get_method_info() {                                                    \
        Il2CppClass *klass = alpha_hook::il2cpp_utils::find_class(name_space, klass_name);          \
        return alpha_hook::il2cpp_utils::find_method(klass, method_name, arg_count);                \
    }                                                                                               \
    static ret (*hook_name)(__VA_ARGS__);                                                           \
    static ret hook(__VA_ARGS__);                                                                   \
} _hook_##hook_name;                                                                                \
ret _hook_##hook_name::hook(__VA_ARGS__)                                                            \


#define INSTALL_HOOK_INSTANCE(logger, hook_name)                        \
DobbyHook(_hook_##hook_name::get_method_info()->methodPointer,          \
          reinterpret_cast<void *>(_hook_##hook_name::hook),            \
          reinterpret_cast<void *>(_hook_##hook_name::hook_name))
