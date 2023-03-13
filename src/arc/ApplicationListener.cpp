#pragma once

#include "./ApplicationListener.hpp"
#include "./files/Fi.cpp"
void arc::ApplicationListener::dispose() {}
void arc::ApplicationListener::exit() {}
void arc::ApplicationListener::fileDropped(arc::files::Fi file) {}
void arc::ApplicationListener::resize(int w, int h) {}
void arc::ApplicationListener::pause() {}
void arc::ApplicationListener::init() {}
void arc::ApplicationListener::update() {}
void arc::ApplicationListener::resume() {}
