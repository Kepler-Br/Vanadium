#ifndef VANADIUM_VANADIUM_H
#define VANADIUM_VANADIUM_H

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>

#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <yaml-cpp/yaml.h>

#include "core/EventProvider.h"
#include "core/SanityChecker.h"
#include "core/Application.h"
#include "core/Exceptions.h"
#include "core/StateStack.h"
#include "core/Animation.h"
#include "core/Stopwatch.h"
#include "core/KeyCodes.h"
#include "core/Dialogs.h"
#include "core/Window.h"
#include "core/Assert.h"
#include "core/Timer.h"
#include "core/State.h"
#include "core/Types.h"
#include "core/Log.h"
#include "core/IO.h"

#include "../../vfs/Vfs.h"
#include "../../vfs/FileStream.h"
#include "../../vfs/Exceptions.h"
#include "../../vfs/Entry.h"

#include "event/EventDispatcher.h"
#include "event/KeyEvent.h"
#include "event/MouseEvent.h"
#include "event/WindowEvent.h"

#include "render/VertexBuffer.h"
#include "render/IndexBuffer.h"
#include "render/VertexArray.h"
#include "render/Framebuffer.h"
#include "render/RenderApi.h"
#include "render/Texture.h"
#include "render/Shader.h"

#endif //VANADIUM_VANADIUM_H
