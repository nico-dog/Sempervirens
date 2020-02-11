#include <RendererMgr/RendererMgr.hpp>
#include <RendererMgr/IRenderer.hpp>
#include <Logging/Logger.hpp>

int main() {

  
  auto rendererMgr = sempervirens::renderer::mgr::RendererMgr{};
  if (!rendererMgr.load("/home/nico/DawnOfGiants/Sempervirens/build/Renderer/liboglrenderer.so")) return 1;
  rendererMgr.release();
  
  return 0;
}
