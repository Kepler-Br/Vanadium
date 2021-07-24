#ifndef VANADIUM_LOGGINGSUBSYSTEM_H
#define VANADIUM_LOGGINGSUBSYSTEM_H

#include "core/Log.h"
#include "core/interfaces/Subsystem.h"

namespace vanadium {

class LoggingSubsystem : public Subsystem {
 protected:
  spdlog::level::level_enum _level;
  bool _writeFile;
  std::string _filename;

 public:
  explicit LoggingSubsystem(
      spdlog::level::level_enum level = spdlog::level::level_enum::trace,
      bool writeFile = true, std::string filename = "Log.txt");

  void init() override;
  void shutdown() override;
};

}  // namespace vanadium

#endif  // VANADIUM_LOGGINGSUBSYSTEM_H
