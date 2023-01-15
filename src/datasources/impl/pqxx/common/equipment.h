
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_EQUIPMENT_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_EQUIPMENT_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Equipment &e);
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_EQUIPMENT_H
