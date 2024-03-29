// Derived from this Gist by Richard Gale:
//     https://gist.github.com/RichardGale/6e2b74bc42b3005e08397236e4be0fd0

// ImGui BFFX binding
// In this binding, ImTextureID is used to store an OpenGL 'GLuint' texture
// identifier. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See
// main.cpp for an example of using this. If you use this binding you'll need to
// call 4 functions: ImGui_ImplXXXX_Init(), ImGui_ImplXXXX_NewFrame(),
// ImGui::Render() and ImGui_ImplXXXX_Shutdown(). If you are new to ImGui, see
// examples/README.txt and documentation at the top of imgui.cpp.
// https://github.com/ocornut/imgui

#include "ImGuiBgfxImpl.h"

#include <imgui.h>

#include <vector>

// BGFX/BX
#include "bgfx/bgfx.h"
#include "bx/math.h"
#include "bx/timer.h"

// Data
uint8_t ImGuiBgfxImpl::g_View = 255;
bgfx::TextureHandle ImGuiBgfxImpl::g_FontTexture = BGFX_INVALID_HANDLE;
bgfx::ProgramHandle ImGuiBgfxImpl::g_ShaderHandle = BGFX_INVALID_HANDLE;
bgfx::UniformHandle ImGuiBgfxImpl::g_AttribLocationTex = BGFX_INVALID_HANDLE;
bgfx::VertexLayout ImGuiBgfxImpl::g_VertexLayout;

std::pair<const bgfx::Memory*, const bgfx::Memory*> getOcornutImguiShader(
    bgfx::RendererType::Enum type) {
  const bgfx::Memory* fragmentMemory = nullptr;
  const bgfx::Memory* vertexMemory = nullptr;

  switch (type) {
    case bgfx::RendererType::OpenGLES: {
      const uint8_t fragment[] =
#include "builtin/FsEsslOcornutImgui.bin.h"
          ;
      const uint8_t vertex[] =
#include "builtin/VsEsslOcornutImgui.bin.h"
          ;
      fragmentMemory = bgfx::alloc(sizeof(fragment));
      vertexMemory = bgfx::alloc(sizeof(vertex));
      bx::memCopy(fragmentMemory->data, fragment, sizeof(fragment));
      bx::memCopy(vertexMemory->data, vertex, sizeof(vertex));
      return {vertexMemory, fragmentMemory};
    }
    case bgfx::RendererType::OpenGL: {
      const uint8_t fragment[] =
#include "builtin/FsGlslOcornutImgui.bin.h"
          ;
      const uint8_t vertex[] =
#include "builtin/VsGlslOcornutImgui.bin.h"
          ;
      fragmentMemory = bgfx::alloc(sizeof(fragment));
      vertexMemory = bgfx::alloc(sizeof(vertex));
      bx::memCopy(fragmentMemory->data, fragment, sizeof(fragment));
      bx::memCopy(vertexMemory->data, vertex, sizeof(vertex));
      return {vertexMemory, fragmentMemory};
    }
    case bgfx::RendererType::Vulkan: {
      const uint8_t fragment[] =
#include "builtin/FsSpirvOcornutImgui.bin.h"
          ;
      const uint8_t vertex[] =
#include "builtin/VsSpirvOcornutImgui.bin.h"
          ;
      fragmentMemory = bgfx::alloc(sizeof(fragment));
      vertexMemory = bgfx::alloc(sizeof(vertex));
      bx::memCopy(fragmentMemory->data, fragment, sizeof(fragment));
      bx::memCopy(vertexMemory->data, vertex, sizeof(vertex));
      return {vertexMemory, fragmentMemory};
    }
    default:
      return {};
  }
}

// This is the main rendering function that you have to implement and call after
// ImGui::Render(). Pass ImGui::GetDrawData() to this function.
// Note: If text or lines are blurry when integrating ImGui into your engine,
// in your Render function, try translating your projection matrix by
// (0.5f,0.5f) or (0.375f,0.375f)
void ImGuiBgfxImpl::renderDrawLists(ImDrawData* draw_data) {
  // Avoid rendering when minimized, scale coordinates for retina displays
  // (screen coordinates != framebuffer coordinates)
  ImGuiIO& io = ImGui::GetIO();
  int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
  int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
  if (fb_width == 0 || fb_height == 0) {
    return;
  }

  draw_data->ScaleClipRects(io.DisplayFramebufferScale);

  // Setup render state: alpha-blending enabled, no face culling,
  // no depth testing, scissor enabled
  uint64_t state = BGFX_STATE_WRITE_RGB | BGFX_STATE_WRITE_A | BGFX_STATE_MSAA |
                   BGFX_STATE_BLEND_FUNC(BGFX_STATE_BLEND_SRC_ALPHA,
                                         BGFX_STATE_BLEND_INV_SRC_ALPHA);

  const bgfx::Caps* caps = bgfx::getCaps();

  // Setup viewport, orthographic projection matrix
  float ortho[16];
  bx::mtxOrtho(ortho, 0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, 0.0f,
               1000.0f, 0.0f, caps->homogeneousDepth);
  bgfx::setViewTransform(g_View, NULL, ortho);
  bgfx::setViewRect(g_View, 0, 0, (uint16_t)fb_width, (uint16_t)fb_height);

  // Render command lists
  for (int n = 0; n < draw_data->CmdListsCount; n++) {
    const ImDrawList* cmd_list = draw_data->CmdLists[n];
    uint32_t idx_buffer_offset = 0;

    bgfx::TransientVertexBuffer tvb;
    bgfx::TransientIndexBuffer tib;

    uint32_t numVertices = (uint32_t)cmd_list->VtxBuffer.size();
    uint32_t numIndices = (uint32_t)cmd_list->IdxBuffer.size();

    if ((numVertices !=
         bgfx::getAvailTransientVertexBuffer(numVertices, g_VertexLayout)) ||
        (numIndices != bgfx::getAvailTransientIndexBuffer(numIndices))) {
      // not enough space in transient buffer, quit drawing the rest...
      break;
    }

    bgfx::allocTransientVertexBuffer(&tvb, numVertices, g_VertexLayout);
    bgfx::allocTransientIndexBuffer(&tib, numIndices);

    ImDrawVert* verts = (ImDrawVert*)tvb.data;
    memcpy(verts, cmd_list->VtxBuffer.begin(),
           numVertices * sizeof(ImDrawVert));

    ImDrawIdx* indices = (ImDrawIdx*)tib.data;
    memcpy(indices, cmd_list->IdxBuffer.begin(),
           numIndices * sizeof(ImDrawIdx));

    for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++) {
      const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];

      if (pcmd->UserCallback) {
        pcmd->UserCallback(cmd_list, pcmd);
      } else {
        const uint16_t xx = (uint16_t)bx::max(pcmd->ClipRect.x, 0.0f);
        const uint16_t yy = (uint16_t)bx::max(pcmd->ClipRect.y, 0.0f);
        bgfx::setScissor(xx, yy,
                         (uint16_t)bx::min(pcmd->ClipRect.z, 65535.0f) - xx,
                         (uint16_t)bx::min(pcmd->ClipRect.w, 65535.0f) - yy);

        bgfx::setState(state);
        bgfx::TextureHandle texture = {
            (uint16_t)((intptr_t)pcmd->TextureId & 0xffff)};
        bgfx::setTexture(0, g_AttribLocationTex, texture);
        bgfx::setVertexBuffer(0, &tvb, 0, numVertices);
        bgfx::setIndexBuffer(&tib, idx_buffer_offset, pcmd->ElemCount);
        bgfx::submit(g_View, g_ShaderHandle);
      }

      idx_buffer_offset += pcmd->ElemCount;
    }
  }
}

bool ImGuiBgfxImpl::createFontsTexture() {
  // Build texture atlas
  ImGuiIO& io = ImGui::GetIO();
  unsigned char* pixels;
  int width, height;
  io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

  // Upload texture to graphics system
  g_FontTexture = bgfx::createTexture2D((uint16_t)width, (uint16_t)height,
                                        false, 1, bgfx::TextureFormat::BGRA8, 0,
                                        bgfx::copy(pixels, width * height * 4));

  // Store our identifier
  io.Fonts->TexID = (void*)(intptr_t)g_FontTexture.idx;

  return true;
}

bool ImGuiBgfxImpl::createDeviceObjects() {
  bgfx::RendererType::Enum type = bgfx::getRendererType();
  auto shaderBinary = getOcornutImguiShader(type);

  bgfx::ShaderHandle vsOcornut = bgfx::createShader(shaderBinary.first);
  bgfx::setName(vsOcornut, "vs_ocornut_imgui");

  bgfx::ShaderHandle fsOcornut = bgfx::createShader(shaderBinary.second);
  bgfx::setName(fsOcornut, "fs_ocornut_imgui");

  //  g_ShaderHandle = bgfx::createProgram(
  //      bgfx::createEmbeddedShader(s_embeddedShaders, type,
  //      "vs_ocornut_imgui"), bgfx::createEmbeddedShader(s_embeddedShaders,
  //      type, "fs_ocornut_imgui"), true);
  g_ShaderHandle = bgfx::createProgram(vsOcornut, fsOcornut, true);

  g_VertexLayout.begin()
      .add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
      .add(bgfx::Attrib::Color0, 4, bgfx::AttribType::Uint8, true)
      .end();

  g_AttribLocationTex =
      bgfx::createUniform("g_AttribLocationTex", bgfx::UniformType::Sampler);

  ImGuiBgfxImpl::createFontsTexture();

  return true;
}

void ImGuiBgfxImpl::invalidateDeviceObjects() {
  bgfx::destroy(g_AttribLocationTex);
  bgfx::destroy(g_ShaderHandle);

  if (isValid(g_FontTexture)) {
    bgfx::destroy(g_FontTexture);
    ImGui::GetIO().Fonts->TexID = nullptr;
    g_FontTexture.idx = bgfx::kInvalidHandle;
  }
}

void ImGuiBgfxImpl::init(int view) { g_View = (uint8_t)(view & 0xff); }

void ImGuiBgfxImpl::shutdown() { ImGuiBgfxImpl::invalidateDeviceObjects(); }

void ImGuiBgfxImpl::newFrame() {
  if (!isValid(g_FontTexture)) {
    ImGuiBgfxImpl::createDeviceObjects();
  }
}
