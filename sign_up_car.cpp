#include "db.h"
#include "headers.h"

DB db;
Client client;
char *p;

State InitCase() {
  int menu{0};
  cout << "---For sign to the service - enter '1'---" << endl;
  cout << "---Check your sign - enter '2'---" << endl;
  cout << "---Cancel your sign - enter '3'---" << endl;
  cin >> menu;
  while (menu <= 0 || menu > 3) {
    cout << "Error: unvalid data. try agin" << endl;
    cout << "---For exit to main menu - enter '0'---" << endl;
    cin >> menu;
  }

  if (menu == 1) {
    return State::Sign;
  } else if (menu == 2) {
    return State::ShowSign;
  } else if (menu == 3) {
    return State::CancelSign;
  } else {
    return State::Init;
  }
}

State SignCase() {
  cout << "Choose master_id fo sign" << endl;
  db.ShowMasters();

  cin >> client.master_id;
  while (client.master_id < 1 || client.master_id > 4) {
    cout << "Error: wrong master_id. Please try again";
    cin >> client.master_id;
  }

  cout << "Enter car plate number" << endl;
  cin >> client.car_number;

  cout << "Enter Car-owner name" << endl;
  cin >> client.name;

  cout << "Enter your phone number" << endl;
  cin >> client.phone;
  while (!(client.phone.size() == 11 && strtol(client.phone.c_str(), &p, 11))) {
    cout << "Error: wrong format of phone number. Please try again";
    cin >> client.phone;
  }

  cout << "Enter date of your visit (in format 01.01.2021)" << endl;
  cin >> client.date;

  cout << "Enter the time of your visit (in format 11 - only hour)" << endl;
  cin >> client.time;

  auto name = db.SelectMasterName(client.master_id);

  while (db.CheckReserve(client, name) == false) {
    cout << "Enter date of your visit (in format 01.01.2021)" << endl;
    cin >> client.date;

    cout << "Enter the time of your visit (in format 11 - only hour)" << endl;
    cin >> client.time;
  }

  db.InsertClientData(client, name);
  db.InsertSignData(client, name);

  cout << "Thank you for fo your choose of our company! Your sign is approved:"
       << endl;
  db.ShowClientSign(client);

  return State::Init;
}

State ShowCase() {
  string car_num;
  cout << "Enter your car number to check sign" << endl;
  cin >> car_num;

  db.ShowSignCase(car_num);

  return State::Init;
}

State CancelCase() {
  string id;
  cout << "Enter your sign ID" << endl;
  cin >> id;

  db.CancelSign(id);

  cout << "Your sign is canceled" << endl;

  return State::Init;
}

void StartProg() {
  State state = State::Init;
  for (;;) {
    switch (state) {
      case State::Init:
        state = InitCase();
        break;
      case State::Sign:
        state = SignCase();
        break;
      case State::ShowSign:
        state = ShowCase();
        break;
      case State::CancelSign:
        state = CancelCase();
        break;
      default:
        state = InitCase();
        break;
    }
  }
}