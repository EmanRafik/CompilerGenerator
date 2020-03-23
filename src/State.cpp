//
// Created by arabtech on 3/23/2020.
//
#include "State.h"
using namespace std;
State::State()
{
    //ctor
}

State::~State()
{
    //dtor
}

State* State::getInstance(){
    State* state_ptr = new State();
    return state_ptr;
}
