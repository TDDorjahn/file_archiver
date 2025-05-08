#include "semver.hpp"

extern constexpr std::string_view raw_version = "0.0.1"; //global version

static semver::version version; //global semantic versioning object