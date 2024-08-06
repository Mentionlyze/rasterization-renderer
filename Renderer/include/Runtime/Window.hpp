#pragma once

#include "Runtime/FrameBuffer.hpp"
#include <cstdint>
#include <string>
namespace Rasterization {

class Window {
public:
  virtual ~Window() = default;

  virtual void Init() = 0;

  virtual void Terminate() = 0;

  virtual void Show() = 0;

  virtual bool Closed() = 0;

  virtual void OnUpdate() = 0;

  virtual void DrawFrameBuffer(const Ref<FrameBuffer> &frameBuffer) = 0;

  virtual void PollInputEvents() = 0;

public:
  static Scope<Window> Create(const std::string &title, const uint32_t width,
                              const uint32_t height);
};

} // namespace Rasterization