#include "alpha_hook.hpp"

#include <windows.h>
#include <string>

#include "il2cpp-api.h"
#include "il2cpp-class-internals.h"

void find_method_by_name_test() {
    Il2CppDomain *domain = il2cpp_domain_get();

    size_t assembly_count;
    const Il2CppAssembly **assemblies = il2cpp_domain_get_assemblies(domain, &assembly_count);

    for (size_t i = 0; i < assembly_count; i++) {
        const Il2CppAssembly *assembly = assemblies[i];
        const Il2CppImage *image = il2cpp_assembly_get_image(assembly);

        if (!image) {
            MessageBoxA(nullptr, "Assembly has no image", assembly->aname.name, MB_OK);
            continue;
        }

        Il2CppClass *klass = il2cpp_class_from_name(image, "", "ColorSetter");

        if (klass) {
            const MethodInfo *methodInfo = il2cpp_class_get_method_from_name(klass, "Start", 0);
            MessageBoxA(nullptr, "Found method at address", std::to_string(reinterpret_cast<intptr_t>(methodInfo->methodPointer)).c_str(), MB_OK);
        }
    }
}

void alpha_hook::init() {
    find_method_by_name_test();
}