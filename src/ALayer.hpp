#pragma once
#ifndef ALAYER_HPP_
#define ALAYER_HPP_

#include <vector>
#include <ncurses.h>

namespace layeredCurses {
    class ALayer {
        public:
            //update layer map, return true if a update as been done (use to check if the display need to be refresh)
            virtual bool Update(float deltaTime) = 0;
            /*GetMap : get the array of the map, ex:
                [-1, -1, -1,  0]
                [-1, -1,  0,  0]
                [-1,  0,  0,  0]
                [-1, -1,  0,  0]
                [-1, -1, -1,  0]
                with -1: alpha, everything else: char code (0 being space)
            */
            virtual std::vector<std::vector<char>> &GetMap(void) {return _map;};
            //init timer max
            ALayer(float timerMax) : _timerMax{timerMax} {ResetMap();}
            virtual ~ALayer(void) {}
        protected:
            //update timer and check if its bigger than timer max
            virtual bool CheckTimer(float deltaTime);
            //DrawOnMap: put a mini map on the map
            virtual void DrawOnMap(std::vector<std::vector<char>> miniMap, int startY, int startX);
            //ResetMap: replace the map with a full -1 one (only alpha)
            virtual void ResetMap(void);
            std::vector<std::vector<char>> _map{};
            float _timer{0};
            const float _timerMax;
    };
}

#endif /* ALAYER_HPP_ */