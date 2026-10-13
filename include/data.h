#pragma once
#include "common.h"
#include <array>
#include <filesystem>

namespace lab::data
{
    extern const std::array<std::size_t, 3> sizes;
    extern const std::array<std::string, 3> cases;
    std::filesystem::path path(const std::filesystem::path &directory,
                               std::size_t n, const std::string &scenario);
    void generate(const std::filesystem::path &directory);
    Numbers load(const std::filesystem::path &path);
}
