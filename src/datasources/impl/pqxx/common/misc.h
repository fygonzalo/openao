
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_MISC_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_MISC_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Misc &m);
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H
