
#ifndef OPENAO_GENERIC_H
#define OPENAO_GENERIC_H

#include <array>
#include <cstdint>

namespace Model {

typedef uint8_t Month;
typedef uint8_t Day;
typedef uint8_t Blood;
typedef uint32_t HP;
typedef uint32_t MP;

typedef uint32_t Skill;
typedef std::array<Skill, 9> Skills;
}// namespace Model

#endif// OPENAO_GENERIC_H
