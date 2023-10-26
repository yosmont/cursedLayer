# cursedLayer
a C++ ncurses engine for doing animation with layer

## Usage
### Layer
The idea is make layer inherited from ALayer, each layer have an Update method where it can manage his `std::vector<std::vector<char>>` where -1 is transparent
``` c++
bool SampleLayer::Update(float deltaTime)
    if (CheckTimer(deltaTime)) { // check if enough time has passed since the last update
        // do your thing here
        return true; // only return true if something change on the map
    }
    return false; // return false if nothing is change on the map
```

### LayeredScene
once your layer ready, the layered scene will take them and use it to display your animation
``` c++
#include <ncurses.h>
#include <random>
#include <ctime>
#include <signal.h>
#include <future>
#include <thread>
#include "LayeredScene.hpp"

std::promise<void> quit{};

void sighandler(int sig)
{
    (void)sig;
    quit.set_value();
}

int main(int ac, char **av, char **env)
{
    std::srand(std::time(nullptr));
    initscr();
    layeredCurses::LayeredScene scene{std::vector<std::shared_ptr<layeredCurses::ALayer>>{
        // Add layer here
    }};
    quit.get_future().wait();
    scene.Exit();
    endwin();
}
```