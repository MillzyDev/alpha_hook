#pragma once

#include "il2cpp-api.h"

#include <string_view>
#include <functional>

#define CRASH_UNLESS(...) crash_unless(__VA_ARGS__, __PRETTY_FUNCTION__, __FILE__, __LINE__)

template<class T>
T crash_unless(T&& value, const char *func, const char *file, int line);

void safe_crash(const char *func, const char *file, int line);

namespace alpha_hook::il2cpp_utils {
    Il2CppClass *find_class(std::string name_space, std::string name);
    const MethodInfo *find_method(Il2CppClass *klass, std::string name, int arg_count);
    FieldInfo *find_field(Il2CppClass *klass, std::string name);
    const PropertyInfo *find_property(Il2CppClass *klass, std::string name);
}