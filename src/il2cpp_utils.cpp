#include <unistd.h>
#include <map>

#include "il2cpp_utils.hpp"
#include "main.hpp"

#include "il2cpp-class-internals.h"
#include "il2cpp-api.h"

template<class T>
T crash_unless(T &&value, const char *func, const char *file, int line) {
    if (!value)
        safe_crash(func, file, line);
    return value;
}

void safe_crash(const char *func, const char *file, int line) {
    get_logger().crit("CRASH_UNLESS FAILED");
    get_logger().crit("Aborting in {} at {}:{}", func, file, line);
    usleep(100000L);
    std::terminate();
}

Il2CppClass *alpha_hook::il2cpp_utils::find_class(std::string name_space, std::string name) {
    static std::map<std::pair<std::string, std::string>, Il2CppClass *> cache;

    std::pair<std::string, std::string> key = {name_space, name};
    if (cache.contains(key))
        return cache[key];

    static Il2CppDomain *domain = il2cpp_domain_get();
    size_t assembly_count;
    const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(domain, &assembly_count);

    for (size_t i = 0; i < assembly_count; i++) {
        const Il2CppAssembly *assembly = assemblies[i];
        const Il2CppImage *image = il2cpp_assembly_get_image(assembly);

        if (!image) {
            get_logger().info("Assembly {} has no image.", assembly->aname.name);
            continue;
        }

        Il2CppClass *klass = il2cpp_class_from_name(image, name_space.c_str(), name.c_str());

        if (klass) {
            cache.emplace(key, klass);
            return klass;
        }
    }

    get_logger().error("Unable to find class {}::{}", name_space, name);
    return nullptr;
}

const MethodInfo *alpha_hook::il2cpp_utils::find_method(Il2CppClass *klass, std::string name, int arg_count) {
    static std::map<std::pair<Il2CppClass *, std::pair<std::string, int>>, const MethodInfo *> cache;
    std::pair<Il2CppClass *, std::pair<std::string, int>> key = {klass, {name, arg_count}};

    if (cache.contains(key))
        return cache[key];

    const MethodInfo *method = il2cpp_class_get_method_from_name(klass, name.c_str(), arg_count);

    if (method) {
        cache.emplace(key, method);
        return method;
    }

    get_logger().error("Unable to find method {} in class {}::{}", name, klass->namespaze, klass->name);
    return nullptr;
}

FieldInfo *alpha_hook::il2cpp_utils::find_field(Il2CppClass *klass, std::string name) {
    static std::map<std::pair<Il2CppClass *, std::string>, FieldInfo *> cache;
    std::pair<Il2CppClass *, std::string> key = {klass, name};

    if (cache.contains(key))
        return cache[key];

    FieldInfo *field = il2cpp_class_get_field_from_name(klass, name.c_str());

    if (field) {
        cache.emplace(key, field);
        return field;
    }

    get_logger().error("Unable to find field {} in class {}::{}", name, klass->namespaze, klass->name);
    return nullptr;
}

const PropertyInfo *alpha_hook::il2cpp_utils::find_property(Il2CppClass *klass, std::string name) {
    static std::map<std::pair<Il2CppClass *, std::string>, const PropertyInfo *> cache;
    std::pair<Il2CppClass *, std::string> key = {klass, name};

    if (cache.contains(key))
        return cache[key];

    const PropertyInfo *property = il2cpp_class_get_property_from_name(klass, name.c_str());

    if (property) {
        cache.emplace(key, property);
        return property;
    }

    get_logger().error("Unable to find property {} in class {}::{}", name, klass->namespaze, klass->name);
    return nullptr;
}