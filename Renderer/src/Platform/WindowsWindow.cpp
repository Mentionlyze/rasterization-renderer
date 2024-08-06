#include "Platform/WindowsWindow.hpp"
#include "Core/Math.hpp"
#include "Runtime/FrameBuffer.hpp"
#include "Runtime/Renderer.hpp"
#include <cstdint>

#define RASTERIZATION_ENTRY_NAME "Entry"
#define RASTERIZATION_CLASS_NAME "Class"

namespace Rasterization {
WindowsWindow::WindowsWindow(const std::string &title, const uint32_t width,
                             const uint32_t height)
    : m_Title{title}, m_Width{width}, m_Height{height}, m_Closed{true},
      m_Inited{false} {
  Init();

  DWORD style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
  RECT rect;
  rect.left = 0;
  rect.top = 0;
  rect.bottom = (long)height;
  rect.right = (long)width;
  AdjustWindowRect(&rect, style, false);

  m_Handle = CreateWindow(RASTERIZATION_CLASS_NAME, m_Title.c_str(), style,
                          CW_USEDEFAULT, 0, rect.right - rect.left,
                          rect.bottom - rect.top, nullptr, nullptr,
                          GetModuleHandle(nullptr), nullptr);
  ASSERT(m_Handle != nullptr);
  m_Closed = false;

  SetProp(m_Handle, RASTERIZATION_ENTRY_NAME, this);

  HDC windowDC = GetDC(m_Handle);
  m_MemoryDC = CreateCompatibleDC(windowDC);

  BITMAPINFOHEADER biHeader = {};
  HBITMAP newBitmap;
  HBITMAP oldBitmap;

  biHeader.biSize = sizeof(BITMAPINFOHEADER);
  biHeader.biWidth = (long)width;
  biHeader.biHeight = -(long)height;
  biHeader.biPlanes = 1;
  biHeader.biBitCount = 32;
  biHeader.biCompression = BI_RGB;

  newBitmap = CreateDIBSection(m_MemoryDC, (BITMAPINFO *)&biHeader,
                               DIB_RGB_COLORS, (void **)&m_Buffer, nullptr, 0);
  ASSERT(newBitmap != nullptr);
  constexpr uint32_t channelCount = 4;
  uint32_t size = m_Width * m_Height * channelCount * sizeof(u_char);
  memset(m_Buffer, 0, size);
  oldBitmap = (HBITMAP)SelectObject(m_MemoryDC, newBitmap);

  DeleteObject(oldBitmap);
  ReleaseDC(m_Handle, windowDC);
  Show();
}

WindowsWindow::~WindowsWindow() {
  ShowWindow(m_Handle, SW_HIDE);
  RemoveProp(m_Handle, RASTERIZATION_ENTRY_NAME);
  DeleteDC(m_MemoryDC);
  DestroyWindow(m_Handle);
}

void WindowsWindow::Init() {
  ASSERT(!m_Inited);
  Register();
  m_Inited = true;
}

void WindowsWindow::Terminate() {
  ASSERT(m_Inited);
  UnRegister();
  m_Inited = false;
}

void WindowsWindow::Show() {
  HDC windowDC = GetDC(m_Handle);
  BitBlt(windowDC, 0, 0, m_Width, m_Height, m_MemoryDC, 0, 0, SRCCOPY);
  ShowWindow(m_Handle, SW_SHOW);
  ReleaseDC(m_Handle, windowDC);
}

void WindowsWindow::Register() {
  ATOM class_atom;
  WNDCLASS window_class;
  window_class.style = CS_HREDRAW | CS_VREDRAW;
  window_class.cbClsExtra = 0;
  window_class.cbWndExtra = 0;
  window_class.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  window_class.hIcon = LoadCursor(nullptr, IDI_APPLICATION);
  window_class.hCursor = nullptr;
  window_class.hInstance = GetModuleHandle(nullptr);
  window_class.lpfnWndProc = WindowsWindow::WndProc;
  window_class.lpszMenuName = nullptr;
  window_class.lpszClassName = RASTERIZATION_CLASS_NAME;
  class_atom = RegisterClass(&window_class);
  ASSERT(class_atom != 0);
}

void WindowsWindow::UnRegister() {
  UnregisterClass(RASTERIZATION_CLASS_NAME, GetModuleHandleA(nullptr));
}

void WindowsWindow::OnUpdate() {
  auto frameBuffer = Renderer::GetFrameBuffer();
  DrawFrameBuffer(frameBuffer);
}

void WindowsWindow::DrawFrameBuffer(const Ref<FrameBuffer> &frameBuffer) {
  const uint32_t width = frameBuffer->GetWidth();
  const uint32_t height = frameBuffer->GetHeight();

  for (uint32_t i = 0; i < height; i++) {
    for (uint32_t j = 0; j < width; j++) {
      constexpr uint32_t channelCount = 4;
      constexpr uint32_t redChannel = 2;
      constexpr uint32_t greenChannel = 1;
      constexpr uint32_t bludChannel = 0;

      auto Color = frameBuffer->GetColor(j, i);
      auto pixelStart = (j + i * width) * channelCount;
      uint32_t r_Index = pixelStart + redChannel;
      uint32_t g_Index = pixelStart + greenChannel;
      uint32_t b_Index = pixelStart + bludChannel;

      m_Buffer[r_Index] = Float2UChar(Color.r);
      m_Buffer[g_Index] = Float2UChar(Color.g);
      m_Buffer[b_Index] = Float2UChar(Color.b);
    }
  }

  Show();
}

void WindowsWindow::PollInputEvents() {
  MSG message;
  while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
    TranslateMessage(&message);
    DispatchMessage(&message);
  }
}

LRESULT CALLBACK WindowsWindow::WndProc(const HWND hWnd, const UINT msgID,
                                        const WPARAM wParam,
                                        const LPARAM lParam) {
  auto window = (WindowsWindow *)GetProp(hWnd, RASTERIZATION_ENTRY_NAME);
  if (window == nullptr) {
    return DefWindowProc(hWnd, msgID, wParam, lParam);
  }
  switch (msgID) {
  case WM_DESTROY:
    window->m_Closed = true;
    return 0;
  }

  return DefWindowProc(hWnd, msgID, wParam, lParam);
}
} // namespace Rasterization