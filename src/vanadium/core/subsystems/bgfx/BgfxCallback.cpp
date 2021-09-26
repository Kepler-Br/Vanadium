#include "BgfxCallback.h"

#include "vanadium/core/Log.h"

namespace vanadium {

void BgfxCallback::fatal(const char *_filePath, uint16_t _line,
                         bgfx::Fatal::Enum _code, const char *_str) {
  VAN_ENGINE_CRITICAL(_str);
}

void BgfxCallback::traceVargs(const char *_filePath, uint16_t _line,
                              const char *_format, va_list _argList) {
  const int symbolsWrote =
      std::vsnprintf(this->_formattedLogMessage->data(),
                     this->_formattedLogMessage->size(), _format, _argList);
  const bool isNewLine =
      (*this->_formattedLogMessage)[symbolsWrote - 1] == '\n';
  const size_t usefulLen = isNewLine ? symbolsWrote - 1 : symbolsWrote;

  VAN_ENGINE_TRACE(std::string_view(_formattedLogMessage->data(), usefulLen));
}

void BgfxCallback::profilerBegin(const char *_name, uint32_t _abgr,
                                 const char *_filePath, uint16_t _line) {
  // noop.
}

void BgfxCallback::profilerBeginLiteral(const char *_name, uint32_t _abgr,
                                        const char *_filePath, uint16_t _line) {
  // noop.
}

void BgfxCallback::profilerEnd() {
  // noop.
}

uint32_t BgfxCallback::cacheReadSize(uint64_t _id) { return 0; }

bool BgfxCallback::cacheRead(uint64_t _id, void *_data, uint32_t _size) {
  return false;
}

void BgfxCallback::cacheWrite(uint64_t _id, const void *_data, uint32_t _size) {
  // noop.
}

void BgfxCallback::screenShot(const char *_filePath, uint32_t _width,
                              uint32_t _height, uint32_t _pitch,
                              const void *_data, uint32_t _size, bool _yflip) {
  // noop.
}

void BgfxCallback::captureBegin(uint32_t _width, uint32_t _height,
                                uint32_t _pitch,
                                bgfx::TextureFormat::Enum _format,
                                bool _yflip) {
  // noop.
}

void BgfxCallback::captureEnd() {
  // noop.
}

void BgfxCallback::captureFrame(const void *_data, uint32_t _size) {
  // noop.
}

}  // namespace vanadium
