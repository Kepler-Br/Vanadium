#pragma once

#include <spdlog/common.h>

#include "vanadium/core/types/LogLevel.h"

namespace vanadium {

spdlog::level::level_enum toSpdLogLevel(LogLevel logLevel);

LogLevel fromSpdLogLevel(spdlog::level::level_enum logLevel);

}  // namespace vanadium
