#include "ALayer.hpp"
#include <memory>
#include <ncurses.h>
#include <atomic>
#include <thread>

namespace layeredCurses {
    class LayeredScene {
        public:
            LayeredScene(std::vector<std::shared_ptr<ALayer>> layer) : _layer{layer}, _sceneLoop{&layeredCurses::LayeredScene::SceneLoop, this} {}
            void Exit(void) {_quit.store(true);_sceneLoop.join();}
        private:
            void SceneLoop(void);
            void MergeMap(void);
            void RefreshDisplay(void);
            std::vector<std::shared_ptr<ALayer>> _layer;
            std::vector<std::vector<char>> _lastMergedMap;
            std::atomic_bool _quit{false};
            std::thread _sceneLoop;
    };
}