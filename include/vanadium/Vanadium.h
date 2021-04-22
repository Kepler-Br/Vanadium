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

#include "Version.h"
#include "core/Animation.h"
#include "core/Application.h"
#include "core/Assert.h"
#include "core/Dialogs.h"
#include "core/EventProvider.h"
#include "core/Exceptions.h"
#include "core/IO.h"
#include "core/KeyCodes.h"
#include "core/Log.h"
#include "core/Math.h"
#include "core/SanityChecker.h"
#include "core/State.h"
#include "core/StateStack.h"
#include "core/Stopwatch.h"
#include "core/Timer.h"
#include "core/Tools.h"
#include "core/Types.h"
#include "core/Window.h"
#include "event/EventDispatcher.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"
#include "render/Framebuffer.h"
#include "render/IndexBuffer.h"
#include "render/Postprocessing.h"
#include "render/RenderApi.h"
#include "render/Shader.h"
#include "render/Texture.h"
#include "render/VertexArray.h"
#include "render/VertexBuffer.h"
#include "scene/Camera.h"
#include "scene/Mesh.h"
#include "scene/PositionCamera.h"
#include "submodules/svg/Parser.h"
#include "submodules/svg/Path.h"
#include "submodules/svg/Rasterizer.h"
#include "vfs/Entry.h"
#include "vfs/Exceptions.h"
#include "vfs/FileStream.h"
#include "vfs/Vfs.h"

#endif  // VANADIUM_VANADIUM_H
