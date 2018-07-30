#include "main.h"
#include <string>
using namespace std;

string get_timestamp() {
  time_t t = time(0);
  tm* now = localtime(&t);
  string year = to_string((now->tm_year + 1900));
  string month = to_string((now->tm_mon + 1));
  string day = to_string(now->tm_mday);
  string hour = to_string(now->tm_hour);
  string min = to_string(now->tm_min);
  string sec = to_string(now->tm_sec);
  string c_time = year + "-" + month + "-" + day + " @ " + hour + ":" + min + ":" + sec;
  return c_time;
}