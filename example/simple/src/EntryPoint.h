#ifndef VANADIUM_ENTRYPOINT_H
#define VANADIUM_ENTRYPOINT_H

#include <Vanadium.h>

class EntryPoint : public vanadium::Application {
 private:
  void setupVfs();

 public:
  // DO NOT THROW HERE!!!
  EntryPoint() = default;

  // Application is not initialized here! DO NOT USE ANYTHING FROM
  // APPLICATION(Except program arguments)!!!
  void preInit() override;

  // Here application is fully initialized. You may load graphics resources.
  void postInit() override;
};

#endif  // VANADIUM_ENTRYPOINT_H
