
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H

#include "model/character.h"
#include <pqxx/pqxx>

namespace Datasources::PQXX {
void deserialize(const pqxx::row &r, Model::Attributes &a);
}// namespace Datasources::PQXX

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_ATTRIBUTES_H
