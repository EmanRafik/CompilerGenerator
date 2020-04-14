//
// Created by DELL on 14-Apr-20.
//

#include <Parser/Production.h>

string Production::getFrom() {
    return from;
}

std::vector <Symbol> Production::getTo() {
    return to;
}
