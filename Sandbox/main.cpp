#include "Runtime/Application.hpp"
#include "Triangle.hpp"

#define VIEWPORT_TITLE "Rasterization"
#define VIEWPORT_WIDTH 1280
#define VIEWPORT_HEIGHT 900

int main() {
  auto app = new Rasterization::Application(VIEWPORT_TITLE, VIEWPORT_WIDTH,
                                            VIEWPORT_HEIGHT);

  app->PushLayer(new Triangle());

  app->Run();
  return 0;
}