#include <GraphicsMgr/GraphicsMgr.hpp>
#include <GraphicsMgr/IGraphicsRenderer.hpp>

int main() {

  auto mgr = dog::graphics::mgr::GraphicsMgr{};

  mgr.load();
  mgr.createRenderer();
  
  auto renderer = mgr.renderer();
  renderer->render();
  
  return 0;
}
