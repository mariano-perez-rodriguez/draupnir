#ifndef DRAUPNIR_H__
#define DRAUPNIR_H__

#include <cstdint>

#include "Sponge.h"
#include "CrcSponge.h"
#include "CrcSpongeBuilder.h"
#include "Constants.h"

namespace Draupnir {

  // utility typedefs
  using CrcSponge64 = CrcSponge<std::uint64_t>;
  using CrcSponge32 = CrcSponge<std::uint32_t>;
  using CrcSponge16 = CrcSponge<std::uint16_t>;
  using CrcSponge8  = CrcSponge<std::uint8_t >;

  using CrcSponge64Builder = CrcSpongeBuilder<std::uint64_t>;
  using CrcSponge32Builder = CrcSpongeBuilder<std::uint32_t>;
  using CrcSponge16Builder = CrcSpongeBuilder<std::uint16_t>;
  using CrcSponge8Builder  = CrcSpongeBuilder<std::uint8_t >;

}

#endif /* DRAUPNIR_H__ */

