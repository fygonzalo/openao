
#include "datasources/impl/pqxx/common/misc.h"

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Misc &m) {

  m.month = r["birthday_month"].as<int>();
  m.day = r["birthday_day"].as<int>();
  m.blood = r["blood"].as<int>();
  m.place = r["place"].as<int>();
  m.job = r["job"].as<int>();
  m.face = r["face"].as<int>();
  m.personality = r["personality"].as<int>();
}
}// namespace Repositories::PQXX