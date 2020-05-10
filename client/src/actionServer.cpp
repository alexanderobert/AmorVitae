#include <actionServer.h>

void actionServer::sendActionMove(Direction direction){ // МАРК Я ЗАКОМЕНТИЛ ЧТОБЫ ВСЕ СКОМПИЛИЛОСЬ,
    /*ССделай для Ивентов и обьектов конструкторы по умолчанию(Можешь посмотреть у меня)
     * или сделай нормальные конструкторы и юзай их
     * */
/*

    MoveInterface event();
    event.type = move;
    event.direction = direction;
    event.sight = mySight;
*/


    //std::cout<<event.sight.to.x<<"\n";
    //std::cout<<event.sight.to.y<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::sendActionBlink(){

/*
    Blink event;
    event.type = blink;
    event.sight = mySight;

*/
    //std::cout<<"Блинк"<<"\n";

    // Send_action(event); from NetClient
}

void actionServer::updatePosition(){

    myPosition.x = 500;
    myPosition.y = 500;
}

void actionServer::updateSight(int x, int y){

/*
    Point mouse;
    mouse.x = x;
    mouse.y = y;

    myPosition.x = 500;
    myPosition.y = 500;

    mySight.from = myPosition;
    mySight.to = mouse;
*/
}


std::shared_ptr<ObjectInterface> actionServer::getMessage(){

    // return Get_servet_action(); from NetClient

/*
    ObjectInterface object;
    object.type = STATIC_OBJECT;
*/
    return std::shared_ptr<ObjectInterface>();

}