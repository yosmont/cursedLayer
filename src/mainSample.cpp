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
    std::thread t{layeredCurses::LayeredScene::SceneLoop, &scene};
    quit.get_future().wait();
    scene.Exit();
    t.join();
    endwin();
}