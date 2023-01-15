
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Stats &s);
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_STATS_H
