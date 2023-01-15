
#include "datasources/impl/pqxx/common/attributes.h"

namespace Datasources::PQXX {
void deserialize(const pqxx::row &r, Model::Attributes &a) {

  a.gender = r["gender"].as<int>();
  a.hair_style = r["hair_style"].as<int>();
  a.height = r["height"].as<int>();
  a.hair_color = r["hair_color"].as<int>();
  a.skin_color = r["skin_color"].as<int>();
}
}// namespace Repositories::PQXX