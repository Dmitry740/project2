#include "db.h"

stringstream ss;
stringstream qq;

int callback(void *data, int argc, char **argv, char **ColName) {
  for (int i = 0; i < argc; ++i) {
    ss << ColName[i];
    ss << ": ";
    ss << argv[i];
    qq << argv[i];
    ss << "\n";
  }
  ss << "\n";
  return 0;
}

DB::DB()
    : filename{
          "C:/Users/Dmitry/Desktop/CPP_home_work/HW_proff/Project_2"
          "sign_upDB.db"} {
  rc = sqlite3_open_v2(
      "sign_upDB.db", &db,
      SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_FULLMUTEX, NULL);
  checkDBErr();
}

DB::~DB() { sqlite3_close(db); }

void DB::checkDBErr() {
  if (rc != SQLITE_OK) {
    cout << "DB Error: " << sqlite3_errmsg(db) << endl;
    sqlite3_close(db);
  }
}

void DB::CreateMasterTable() {
  sql =
      "CREATE TABLE MASTER (ID INTEGER PRIMARY KEY AUTOINCREMENT, MASTER_NAME "
      "TEXT NOT NULL);";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::FillMasterTable() {
  sql =
      "INSERT INTO MASTER (MASTER_NAME) "
      "VALUES('Berezovskiy');INSERT INTO MASTER (MASTER_NAME) "
      "VALUES('Fetisov');INSERT INTO MASTER (MASTER_NAME) "
      "VALUES('Marchenko');INSERT INTO MASTER (MASTER_NAME) "
      "VALUES('Rudametkin');";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ShowMasters() {
  sql = "SELECT *FROM MASTER";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;
  checkDBErr();
}

string DB::SelectMasterName(int master_id) {
  query = "SELECT MASTER_NAME FROM MASTER WHERE ID = '" +
          std::to_string(master_id) + "'";
  qq.str("");
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  checkDBErr();
  std::cout << qq.str() << std::endl;
  return qq.str();
}

bool DB::CheckReserve(Client client, string &name) {
  query = "SELECT DATE, TIME FROM SIGN WHERE MASTER_NAME = '" + name +
          "' AND DATE "
          "= '" +
          client.date + "' AND TIME = '" + client.time + "'";
  qq.str("");
  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  if (qq.str() == client.date + client.time) {
    cout << "Error: time is anavailiable. choose another please" << endl;
    ;
    return false;
  }
  return true;
}

void DB::CreateSignTable() {
  sql =
      "CREATE TABLE SIGN (ID INTEGER PRIMARY KEY AUTOINCREMENT, DATE TEXT "
      "NOT "
      "NULL, TIME TEXT NOT NULL, MASTER_NAME TEXT NOT NULL, CAR_NUMBER TEXT "
      "NOT NULL);";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::InsertSignData(Client client, string &name) {
  cout << client.master_name << endl;
  query = "INSERT INTO SIGN (DATE, TIME, MASTER_NAME, CAR_NUMBER) VALUES( '" +
          client.date + "', '" + client.time + "', '" + name + "', '" +
          client.car_number + "');";

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ShowSigns() {
  sql = "SELECT *FROM SIGN";
  ss.str("");

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;
  checkDBErr();
}

void DB::ShowClientSign(Client client) {
  query = "SELECT FROM SIGN WHERE DATE = '" + client.date +
          "' AND CAR_NUMBER = '" + client.car_number + "'";
  ss.str("");

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;
  checkDBErr();
}

void DB::CancelSign(string id) {
  query = "SELECT CAR_NUMBER FROM SIGN WHERE ID = '" + id + "'";
  qq.str("");

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  auto car_num = qq.str();

  query = "DELETE FROM CLIENT WHERE CAR_NUMBER = '" + car_num + "'";
  qq.str("");

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  query = "DELETE FROM SIGN WHERE ID = '" + id + "'";
  ss.str("");

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ShowSignCase(string car_num) {
  query = "SELECT *FROM SIGN WHERE CAR_NUMBER = '" + car_num + "'";
  ss.str("");

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;
  checkDBErr();
}

void DB::CreateClientTable() {
  sql =
      "CREATE TABLE CLIENT (ID INTEGER PRIMARY KEY AUTOINCREMENT, NAME "
      "TEXT NOT NULL, CAR_NUMBER TEXT NOT NULL, PHONE TEXT NOT NULL,"
      "MASTER_NAME TEXT NOT NULL)";

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::InsertClientData(Client client, string &name) {
  query =
      "INSERT INTO CLIENT (NAME, CAR_NUMBER, PHONE, MASTER_NAME) VALUES( '" +
      client.name + "', '" + client.car_number + "', '" + client.phone +
      "', '" + name + "');";

  sql = query.c_str();
  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);

  checkDBErr();
}

void DB::ShowClients() {
  sql = "SELECT *FROM CLIENT";
  ss.str("");

  rc = sqlite3_exec(db, sql, callback, 0, &ErrMsg);
  cout << ss.str() << endl;
  checkDBErr();
}
