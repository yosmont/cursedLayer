#include "LayeredScene.hpp"
#include <ctime>

void layeredCurses::LayeredScene::SceneLoop(void)
{
    RefreshDisplay();
    clock_t prevFrame{std::clock()};
    while (!_quit.load()) {
        clock_t currentFrame{std::clock()};
        float deltaTime{((float)currentFrame - (float)prevFrame) / (float)CLOCKS_PER_SEC};
        bool updated{false};
        for (auto elem : _layer)
            if (elem->Update(deltaTime))
                updated = true;
        if (updated)
            RefreshDisplay();
        prevFrame = currentFrame;
    }
}

void layeredCurses::LayeredScene::MergeMap(void)
{
    _lastMergedMap = _layer[0]->GetMap();
    for (int i{0}; LINES > i; ++i)
        for (int j{0}; COLS > j; ++j)
            for (size_t k{1}; _layer.size() > k; ++k)
                if (_layer[k]->GetMap()[i][j] != -1)
                    _lastMergedMap[i][j] = _layer[k]->GetMap()[i][j];
}

void layeredCurses::LayeredScene::RefreshDisplay(void)
{
    MergeMap();
    clear();
    for (int i{0}; LINES > i; ++i)
        for (int j{0}; COLS > j; ++j)
            if (_lastMergedMap[i][j] != -1)
                mvaddch(i, j, _lastMergedMap[i][j]);
    refresh();
}