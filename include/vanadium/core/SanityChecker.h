#ifndef VANADIUM_SANITYCHECKER_H
#define VANADIUM_SANITYCHECKER_H

// Todo: think about removing this state.
static_assert(sizeof(size_t) == 8,
              "size_t is not 8 bytes! We need it to be 8 bytes to support "
              "string hashing.");

#endif  // VANADIUM_SANITYCHECKER_H
