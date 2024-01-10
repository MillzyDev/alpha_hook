cmake_minimum_required(VERSION 3.25)
project(alpha_hook)

set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

set(CMAKE_SHARED_LIBRARY_PREFIX  "")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED 23)

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(SHARED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/shared)

if (NOT MSVC)
    add_compile_options(-frtti -fexceptions -Wreturn-type)
    add_compile_options(-O3)
    add_compile_options(-Wunknown-attributes)
endif ()

MACRO(RECURSE_FILES return_list filter)
    FILE(GLOB_RECURSE new_list ${filter})
    SET(file_list "")
    FOREACH(file_path ${new_list})
        SET(file_list ${file_list} ${file_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES file_list)
    SET(${return_list} ${file_list})
ENDMACRO()

file(READ game_path.txt GAME_PATH)
file(READ libil2cpp_path.txt LIBIL2CPP_PATH)

RECURSE_FILES(cpp_file_list ${SOURCE_DIR}/*.cpp)
RECURSE_FILES(c_file_list ${SOURCE_DIR}/*.c)

add_library(
        alpha_hook
        SHARED
        ${cpp_file_list}
        ${c_file_list}
)

target_include_directories(alpha_hook PRIVATE .)
target_include_directories(alpha_hook PRIVATE ${SOURCE_DIR})
#target_include_directories(alpha_hook PRIVATE ${INCLUDE_DIR})
target_include_directories(alpha_hook PUBLIC ${SHARED_DIR})

# IL2CPP headers
if (NOT MSVC)
    target_compile_definitions(alpha_hook PUBLIC
        -DIL2CPP_TARGET_CUSTOM=1
        -DIL2CPP_TARGET_WINDOWS_DESKTOP=1
        -DIL2CPP_TARGET_WINDOWS=1
        -DIL2CPP_PLATFORM_SUPPORTS_DEBUGGER_PRESENT=1
        -DIL2CPP_PLATFORM_SUPPORTS_SYSTEM_CERTIFICATES=1
        -DIL2CPP_PLATFORM_SUPPORTS_CPU_INFO=1
        -DNTDDI_VERSION=100728832
        -D_WIN32_WINNT=1537
        -DWINVER=1537
        -D_UNICODE=1
        -DUNICODE=1
        -DSTRICT=1
        )
endif()

target_include_directories(alpha_hook PUBLIC ${LIBIL2CPP_PATH})
target_link_libraries(alpha_hook PRIVATE ${GAME_PATH}/GameAssembly.dll)

add_subdirectory(Dobby)
target_link_libraries(alpha_hook PRIVATE dobby)

target_compile_definitions(alpha_hook PRIVATE -DALPHA_HOOK_EXPORT_SYMBOLS)