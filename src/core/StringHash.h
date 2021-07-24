#ifndef VANADIUM_STRINGHASH_H
#define VANADIUM_STRINGHASH_H

namespace vanadium {

// Thank you, https://stackoverflow.com/a/48896410/11498103
template <typename T>
constexpr size_t hashString(const T& stdstr) {
  // For this example, I'm requiring size_t to be 64-bit, but you could
  // easily change the offset and prime used to the appropriate ones
  // based on sizeof(size_t).
  static_assert(sizeof(size_t) == 8, "size_t is not 8 bytes!");
  // FNV-1a 64 bit algorithm
  size_t result = 0xcbf29ce484222325;  // FNV offset basis
  for (char c : stdstr) {
    result ^= c;
    result *= 1099511628211;  // FNV prime
  }
  return result;
}

constexpr size_t operator"" _hash(char const* s, size_t count) {
  static_assert(sizeof(size_t) == 8, "size_t is not 8 bytes!");
  // FNV-1a 64 bit algorithm
  size_t result = 0xcbf29ce484222325;  // FNV offset basis
  for (size_t i = 0; i < count; i++) {
    result ^= s[i];
    result *= 1099511628211;  // FNV prime
  }

  return result;
}

}  // namespace vanadium

#endif  // VANADIUM_STRINGHASH_H
