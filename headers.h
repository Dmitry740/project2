#pragma once

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0601
#endif

#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Client {
  string name;
  string car_number;
  string date;
  string time;
  string phone;
  int master_id;
  string master_name;
};

enum class State {
  Init,
  Sign,
  ShowSign,
  CancelSign,
};

void StartProg();
void ShowAvailable(State state);
void InitCase(State state);