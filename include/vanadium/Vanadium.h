#ifndef VANADIUM_VANADIUM_H
#define VANADIUM_VANADIUM_H

#include <yaml-cpp/yaml.h>

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "vanadium/Version.h"
#include "vanadium/core/Animation.h"
#include "vanadium/core/Application.h"
#include "vanadium/core/Assert.h"
#include "vanadium/core/Dialogs.h"
#include "vanadium/core/EventProvider.h"
#include "vanadium/core/Exceptions.h"
#include "vanadium/core/IO.h"
#include "vanadium/core/KeyCodes.h"
#include "vanadium/core/Log.h"
#include "vanadium/core/Math.h"
#include "vanadium/core/SanityChecker.h"
#include "vanadium/core/State.h"
#include "vanadium/core/StateStack.h"
#include "vanadium/core/Stopwatch.h"
#include "vanadium/core/Timer.h"
#include "vanadium/core/Tools.h"
#include "vanadium/core/Types.h"
#include "vanadium/core/Window.h"
#include "vanadium/event/EventDispatcher.h"
#include "vanadium/event/KeyEvent.h"
#include "vanadium/event/MouseEvent.h"
#include "vanadium/event/WindowEvent.h"
#include "vanadium/render/Framebuffer.h"
#include "vanadium/render/IndexBuffer.h"
#include "vanadium/render/Postprocessing.h"
#include "vanadium/render/RenderApi.h"
#include "vanadium/render/Shader.h"
#include "vanadium/render/Texture.h"
#include "vanadium/render/VertexArray.h"
#include "vanadium/render/VertexBuffer.h"
#include "vanadium/scene/Camera.h"
#include "vanadium/scene/Mesh.h"
#include "vanadium/scene/PositionCamera.h"
#include "vanadium/submodules/svg/Parser.h"
#include "vanadium/submodules/svg/Path.h"
#include "vanadium/submodules/svg/Rasterizer.h"
#include "vanadium/vfs/Entry.h"
#include "vanadium/vfs/Exceptions.h"
#include "vanadium/vfs/FileStream.h"
#include "vanadium/vfs/Vfs.h"

#endif  // VANADIUM_VANADIUM_H
