#pragma once

#pragma comment(lib, "C:/src/vcpkg/vcpkg/installed/x64-windows/lib/sqlite3.lib")

#include <sqlite3.h>

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>

#include "headers.h"

using namespace std;

int callback(void *data, int argc, char **argv, char **ColName);

class DB {
 private:
  sqlite3 *db;
  char *ErrMsg;
  int rc;
  const char *sql;
  string query;
  const char *filename;
  string m_data;

 public:
  DB();
  DB(const DB &) = delete;
  DB &operator=(const DB &) = delete;

  DB(DB &&other) noexcept {
    db = other.db;
    other.db = nullptr;
    ErrMsg = other.ErrMsg;
    other.ErrMsg = nullptr;
    rc = other.rc;
    other.rc = 0;
    sql = other.sql;
    other.sql = nullptr;
    query = other.query;
    other.query = nullptr;
    filename = other.filename;
    other.filename = nullptr;
    m_data = other.m_data;
    other.m_data = nullptr;
  }

  DB &operator=(DB &&rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }
    db = rhs.db;
    rhs.db = nullptr;
    ErrMsg = rhs.ErrMsg;
    rhs.ErrMsg = nullptr;
    rc = rhs.rc;
    rhs.rc = 0;
    sql = rhs.sql;
    rhs.sql = nullptr;
    query = rhs.query;
    rhs.query = nullptr;
    filename = rhs.filename;
    rhs.filename = nullptr;
    m_data = rhs.m_data;
    rhs.m_data = nullptr;

    return *this;
  }

  ~DB();

  void checkDBErr();
  void CreateMasterTable();
  void FillMasterTable();
  void ShowMasters();
  bool CheckReserve(Client client, string &name);
  void CreateClientTable();
  void InsertClientData(Client client, string &name);
  void CreateSignTable();
  void InsertSignData(Client client, string &name);
  std::string SelectMasterName(int master_id);
  void ShowSigns();
  void ShowClients();
  void ShowClientSign(Client client);
  void ShowSignCase(string car_num);
  void CancelSign(string id);
  void DeleteClient(string id);
};