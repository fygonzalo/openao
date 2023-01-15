
#include "datasources/impl/pqxx/common/position.h"

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Position &p) {
  p.x = r["position_x"].as<int>();
  p.y = r["position_y"].as<int>();
  p.orientation = r["orientation"].as<int>();
}
}// namespace Datasources::PQXX