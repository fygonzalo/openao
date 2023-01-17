
#ifndef OPENAO_FRAMEWORK_TRANSPORT_CHECKSUM_H
#define OPENAO_FRAMEWORK_TRANSPORT_CHECKSUM_H

#include <cstdint>

namespace openao::framework::transport {

uint8_t checksum(const uint8_t *data, int size);

}

#endif// OPENAO_FRAMEWORK_TRANSPORT_CHECKSUM_H
