#pragma once
#ifndef global_
#define global_
#include<iostream>
#include <unordered_map>

#include "vertex.h"
using namespace std;

extern const double PI;
extern const double err;

extern unordered_map<Vertex*, bool> visited;

#endif