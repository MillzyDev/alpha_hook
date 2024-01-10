#pragma once

#ifdef ALPHA_HOOK_EXPORT_SYMBOLS
#define IMPORT_EXPORT __declspec(dllexport)
#else
#define IMPORT_EXPORT __declspec(dllimport)
#endif

namespace alpha_hook {
    IMPORT_EXPORT void init();
}

#undef IMPORT_EXPORT