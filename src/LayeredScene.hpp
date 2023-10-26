#include "ALayer.hpp"
#include <memory>
#include <ncurses.h>
#include <atomic>

namespace layeredCurses {
    class LayeredScene {
        public:
            LayeredScene(std::vector<std::shared_ptr<ALayer>> layer) : _layer{layer} {}
            void SceneLoop(void);
            void Exit(void) {_quit.store(true);}
        private:
            void MergeMap(void);
            void RefreshDisplay(void);
            std::vector<std::shared_ptr<ALayer>> _layer;
            std::vector<std::vector<char>> _lastMergedMap;
            std::atomic_bool _quit{false};
    };
}