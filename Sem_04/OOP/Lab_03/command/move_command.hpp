#ifndef MOVE_COMMAND_HPP
#define MOVE_COMMAND_HPP

#include "command.hpp"

class move_command : public command {
    public:
        move_command();
};

class move_UP : public move_command {

};

class move_DOWN : public move_command {

};

class move_LEFT : public move_command {

};

class move_RIGHT : public move_command {

};

#endif // MOVE_COMMAND_HPP
