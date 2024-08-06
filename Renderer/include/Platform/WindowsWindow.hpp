#pragma once

#include "Runtime/Window.hpp"
#include <windows.h>

namespace Rasterization {
class WindowsWindow : public Window {
public:
  WindowsWindow(const std::string &title, const uint32_t width,
                const uint32_t height);
  virtual ~WindowsWindow();

  virtual void Init() override;

  virtual void Terminate() override;

  virtual void Show() override;

  virtual bool Closed() override { return m_Closed; }

  virtual void OnUpdate() override;

  virtual void DrawFrameBuffer(const Ref<FrameBuffer> &frameBuffer) override;

  virtual void PollInputEvents() override;

private:
  void Register();
  void UnRegister();

  static LRESULT CALLBACK WndProc(const HWND hWnd, const UINT msgID,
                                  const WPARAM wParam, const LPARAM lParam);

private:
  bool m_Closed;
  std::string m_Title;
  uint32_t m_Width, m_Height;

  HWND m_Handle;
  HDC m_MemoryDC;

  u_char *m_Buffer;

  bool m_Inited;
};
} // namespace Rasterization