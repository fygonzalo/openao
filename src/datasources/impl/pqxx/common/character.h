
#ifndef OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H
#define OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H

#include "model/character.h"
#include "datasources/impl/pqxx/common/attributes.h"
#include "datasources/impl/pqxx/common/misc.h"
#include "datasources/impl/pqxx/common/position.h"
#include "datasources/impl/pqxx/common/stats.h"
#include "datasources/impl/pqxx/common/equipment.h"

#include "pqxx/row"


namespace Datasources::PQXX {
void deserialize(pqxx::row &r, Model::Character &c);
}

#endif// OPENAO_REPOSITORIES_IMPL_PQXX_COMMON_CHARACTER_H
