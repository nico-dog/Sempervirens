#include <GraphicsMgr/GraphicsMgr.hpp>
#include <GraphicsMgr/IGraphicsRenderer.hpp>

int main() {

  auto mgr = dog::graphics::mgr::GraphicsMgr{};

  if (!mgr.load("/home/nico/DawnOfGiants/Sempervirens/build/Graphics/libgraphicsogl.so")) return 1;

  auto renderer = mgr.createRenderer();
  if (!renderer) return 1;

  renderer->render();
  
  return 0;
}
