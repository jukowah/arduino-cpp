#include <tuple>
#include "libtcod.hpp"

class actor {
private:
    int pos_x;
    int pos_y;
    char repr;

    TCODColor background;
    TCODColor foreground;
public: 
    actor(char representation, int position_x, int position_y) {
        this->repr  = representation;
        this->pos_x = position_x;
        this->pos_y = position_y;
    };

    char get_representation() { return this->repr;  };
    int  get_position_x()     { return this->pos_x; };
    int  get_position_y()     { return this->pos_y; };
    
    void set_position_xy(int new_x, int new_y) { this->pos_x = new_x; this->pos_y = new_y; };

    void render(int x, int y) {
        TCODConsole::root->setChar(this->pos_x, this->pos_y, this->repr);
        TCODConsole::root->setCharForeground(this->pos_x, this->pos_y, this->background);
        TCODConsole::root->setCharBackground(this->pos_x, this->pos_y, this->foreground);
    };
};

class multi_actor {
private:
    actor *actors;
    actor controller;
public:
    
};