
#ifndef OPENAO_MESSAGES_RESPONSES_COMMON_BRANCHES_H
#define OPENAO_MESSAGES_RESPONSES_COMMON_BRANCHES_H

#include "model/branches.h"
#include "utils/binarybuffer.h"

namespace Login::Messages::Responses {
void serialize(BinaryBuffer &buffer, Model::Branches &bb) {
  buffer.write((uint32_t) bb.statuses.size());
  buffer.set(0, 51);
  for (auto &v: bb.statuses) { buffer.write(v); }
}
}// namespace Login::Messages::Responses

#endif// OPENAO_MESSAGES_RESPONSES_COMMON_BRANCHES_H
