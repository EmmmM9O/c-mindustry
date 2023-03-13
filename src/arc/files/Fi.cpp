#pragma once
#include "./Fi.hpp"
using namespace boost;

arc::files::File::File(std::string pa) { path = filesystem::path(pa); }
std::string arc::files::File::getPath() { return path.string(); }
std::string arc::files::File::getName() { return path.string(); }
arc::files::Fi::Fi(std::string p, FileType t) : file(p) { type = t; }
arc::files::Fi::Fi(std::string p) : file(p) { type = FileType::absolute; }
std::string arc::files::Fi::path() { return file.getPath(); }
std::string arc::files::Fi::name() { return file.getName(); }