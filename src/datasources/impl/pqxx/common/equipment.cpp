
#include "datasources/impl/pqxx/common/equipment.h"

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Equipment &e) {
  e.head = r["head"].as<int>();
  e.body = r["body"].as<int>();
  e.main_hand = r["main_hand"].as<int>();
  e.off_hand = r["off_hand"].as<int>();
  e.hand = r["hand"].as<int>();
  e.feet = r["feet"].as<int>();
  e.back = r["back"].as<int>();
  e.ride = r["ride"].as<int>();
}
}// namespace Datasources::PQXX