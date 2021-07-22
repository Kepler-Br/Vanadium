#include "EntryPoint.h"

void EntryPoint::setupVfs() {
  // Here one should open folders for VFS.
}
void EntryPoint::preInit() {
  this->setupVfs();
}
void EntryPoint::postInit() { }
