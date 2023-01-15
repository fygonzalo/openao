
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_POSITION_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_POSITION_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Position &p);
}// namespace Repositories::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_POSITION_H
