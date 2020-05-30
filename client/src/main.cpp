#include <boost/date_time.hpp>

#include <actionManager.h>
#include <actionServer.h>

#include <GraphicsManager.h>
#include <struct_Config.h>

int main() {

    int game_duration = 60;

    actionServer action;
    actionManager user;

    Config configWindow;
    user.defineResolution(configWindow);

    GraphicsManager graph(configWindow, user);

    auto round_start = boost::posix_time::microsec_clock::universal_time();
    boost::posix_time::time_duration current_game_duration;

    std::vector<std::shared_ptr<ObjectInterface>> objects;

    while((graph.isOpen()) && ((current_game_duration.total_seconds() < game_duration))){
        if(!user.isGame){
            graph.displayMainMenu();

        } else{

            objects = action.getMessage();
            graph.object(objects);
            action.updatePosition(objects);

            auto curr_time = boost::posix_time::microsec_clock::universal_time();
            current_game_duration = curr_time - round_start;
        }

        graph.handleEvent(user, action);

        graph.display();

    }

    if(action.checkWinner(objects)) {
        graph.displayWin();
    }
    else
        graph.displayLose();

    graph.display();

    sleep(5);

    return 0;
}


