#define _CRT_SECURE_NO_WARNINGS

#include "logger.hpp"

#include <cstdio>
#include <optional>

#include "fmt/color.h"

LogLevel::LogLevel(Level level) : level_(level) {}

LogLevel::operator LogLevel::Level() const { return level_; }

const std::string LogLevel::to_string() const {
    switch (level_) {
    case Level::Info:
        return "INFO";
    case Level::Debug:
        return "DEBUG";
    case Level::Warn:
        return "WARN";
    case Level::Error:
        return "ERROR";
    case Level::Fatal:
        return "FATAL";
    default:
        // dummy line because msvc is chronically stupid
        return "";
    }
}

fmt::color LogLevel::to_colour() const {
    switch (level_) {
    case Level::Info:
        return fmt::color::gray;
    case Level::Debug:
        return fmt::color::green;
    case Level::Warn:
        return fmt::color::yellow;
    case Level::Error:
        return fmt::color::orange;
    case Level::Fatal:
        return fmt::color::dark_red;
    default:
        // another dummy line
        return fmt::color::alice_blue;
    }
}

void Logger::set_log(const std::string &log_file_path) {
    if (file_.has_value()) {
        std::fclose(file_.value());
    }
    file_ = std::fopen(log_file_path.c_str(), "a");
}
