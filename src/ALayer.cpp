#include "ALayer.hpp"

bool layeredCurses::ALayer::CheckTimer(float deltaTime)
{
    _timer += deltaTime;
    if (_timerMax <= _timer) {
        _timer = 0;
        return true;
    }
    return false;
}

void layeredCurses::ALayer::DrawOnMap(std::vector<std::vector<char>> miniMap, int startY, int startX)
{
    for (size_t i{0}; miniMap.size() > i; ++i) {
        if ((size_t)LINES <= (i + startY))
            break;
        for (size_t j{0}; miniMap[i].size() > j; ++j) {
            if ((size_t)COLS <= (j + startX))
                break;
            if (miniMap[i][j] != -1)
                _map[i + startY][j + startX] = miniMap[i][j];
        }
    }
}

void layeredCurses::ALayer::ResetMap(void)
{
    _map.clear();
    for (int i{0}; LINES > i; ++i) {
        std::vector<char> tmp;
        for (int j{0}; COLS > j; ++j)
            tmp.push_back((char)-1);
        _map.push_back(tmp);
    }
}