#pragma once
#include "./ArcNet.hpp"

void arc::net::ArcNet::handleError(std::exception err) { errorHandler(err); }
std::function<void(std::exception)> arc::net::ArcNet::errorHandler =
    [](std::exception err) -> void {

};