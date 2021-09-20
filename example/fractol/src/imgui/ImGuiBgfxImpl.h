#pragma once

#include <bgfx/bgfx.h>

class ImGuiBgfxImpl {
 private:
  static uint8_t g_View;
  static bgfx::TextureHandle g_FontTexture;
  static bgfx::ProgramHandle g_ShaderHandle;
  static bgfx::UniformHandle g_AttribLocationTex;
  static bgfx::VertexLayout g_VertexLayout;

  static bool createFontsTexture();

 public:
  static void init(int view);
  static void shutdown();
  static void newFrame();
  static void renderDrawLists(struct ImDrawData* draw_data);

  // Use if you want to reset your rendering device without losing ImGui state.
  static void invalidateDeviceObjects();
  static bool createDeviceObjects();
};
