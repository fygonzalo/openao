
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Repositories::PQXX {
void deserialize(pqxx::row &r, Model::Attributes &a) {

  a.gender = r["gender"].as<int>();
  a.hair_style = r["hair_style"].as<int>();
  a.height = r["height"].as<int>();
  a.hair_color = r["hair_color"].as<int>();
  a.skin_color = r["skin_color"].as<int>();
}
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H
