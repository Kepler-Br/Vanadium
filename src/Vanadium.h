#ifndef VANADIUM_VANADIUM_H
#define VANADIUM_VANADIUM_H

#include <bgfx/bgfx.h>
#include <bx/bx.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <yaml-cpp/yaml.h>

#include <boost/di.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/Animation.h"
#include "core/Assert.h"
#include "core/Dialogs.h"
#include "core/EventProvider.h"
#include "core/Exceptions.h"
#include "core/IO.h"
#include "core/KeyCodes.h"
#include "core/Log.h"
#include "core/Stopwatch.h"
#include "core/Timer.h"
#include "core/Tools.h"
#include "core/Types.h"
#include "core/Version.h"
#include "core/Window.h"
#include "core/application/Application.h"
#include "core/application/State.h"
#include "core/application/StateStack.h"
#include "core/math/Math.h"
#include "event/EventDispatcher.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"
#include "graphics/ShaderFactory.h"
#include "scene/Camera.h"
#include "scene/Mesh.h"
#include "scene/PositionCamera.h"
#include "submodules/svg/Parser.h"
#include "submodules/svg/Path.h"
#include "submodules/svg/Rasterizer.h"
#include "vfs/FileStream.h"
#include "vfs/Vfs.h"

#endif  // VANADIUM_VANADIUM_H
