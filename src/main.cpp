#include "main.hpp"

alpha1::logger &get_logger() {
    static auto logger = alpha1::logger({"alpha_hook", "0.1.0"});
    return logger;
}