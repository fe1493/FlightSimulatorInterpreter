//
// Created by yonatan on 26/12/2019.
//

#include "InputSymbolTable.h"
#include "Var.h"

/*
 * hold all the value that we get from the simulator
 */
InputSymbolTable::InputSymbolTable()
{
    this->inputMap->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt", new Var()});
    this->inputMap->insert({"/sim/time/warp", new Var()});
    this->inputMap->insert({"/controls/switches/magnetos", new Var()});
    this->inputMap->insert({"/instrumentation/heading-indicator/offset-deg", new Var()});
    this->inputMap->insert({"/instrumentation/altimeter/indicated-altitude-ft", new Var()});
    this->inputMap->insert({"/instrumentation/altimeter/pressure-alt-ft", new Var()});
    this->inputMap->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg", new Var()});
    this->inputMap->insert({"/instrumentation/attitude-indicator/indicated-roll-deg", new Var()});
    this->inputMap->insert({"/instrumentation/attitude-indicator/internal-pitch-deg", new Var()});
    this->inputMap->insert({"/instrumentation/attitude-indicator/internal-roll-deg", new Var()});
    this->inputMap->insert({"/instrumentation/encoder/indicated-altitude-ft", new Var()});
    this->inputMap->insert({"/instrumentation/encoder/pressure-alt-ft", new Var()});
    this->inputMap->insert({"/instrumentation/gps/indicated-altitude-ft", new Var()});
    this->inputMap->insert({"/instrumentation/gps/indicated-ground-speed-kt", new Var()});
    this->inputMap->insert({"/instrumentation/gps/indicated-vertical-speed", new Var()});
    this->inputMap->insert({"/instrumentation/heading-indicator/indicated-heading-deg", new Var()});
    this->inputMap->insert({"/instrumentation/magnetic-compass/indicated-heading-deg", new Var()});
    this->inputMap->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid", new Var()});
    this->inputMap->insert({"/instrumentation/turn-indicator/indicated-turn-rate", new Var()});
    this->inputMap->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm", new Var()});
    this->inputMap->insert({"/controls/flight/aileron", new Var()});
    this->inputMap->insert({"/controls/flight/elevator", new Var()});
    this->inputMap->insert({"/controls/flight/rudder", new Var()});
    this->inputMap->insert({"/controls/flight/flaps", new Var()});
    this->inputMap->insert({"/controls/engines/engine/throttle", new Var()});
    this->inputMap->insert({"/controls/engines/current-engine/throttle", new Var()});
    this->inputMap->insert({"/controls/switches/master-avionics", new Var()});
    this->inputMap->insert({"/controls/switches/starter", new Var()});
    this->inputMap->insert({"/engines/active-engine/auto-start", new Var()});
    this->inputMap->insert({"/controls/flight/speedbrake", new Var()});
    this->inputMap->insert({"/sim/model/c172p/brake-parking", new Var()});
    this->inputMap->insert({"/controls/engines/engine/primer", new Var()});
    this->inputMap->insert({"/controls/engines/current-engine/mixture", new Var()});
    this->inputMap->insert({"/controls/switches/master-bat", new Var()});
    this->inputMap->insert({"/controls/switches/master-alt", new Var()});
    this->inputMap->insert({"/engines/engine/rpm", new Var()});
    this->inputMap->insert({"/controls/gear/brake-right", new Var()});
}
