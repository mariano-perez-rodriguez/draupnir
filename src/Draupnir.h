#ifndef DRAUPNIR_H__
#define DRAUPNIR_H__

#include <cstdint>

#include "Sponge.h"
#include "CrcSponge.h"
#include "CrcSpongeBuilder.h"
#include "Constants.h"

namespace Draupnir {

  // explicit instantiations
  template class CrcSponge<std::uint64_t>;
  template class CrcSponge<std::uint32_t>;
  template class CrcSponge<std::uint16_t>;
  template class CrcSponge<std::uint8_t>;

  template class CrcSpongeBuilder<std::uint64_t>;
  template class CrcSpongeBuilder<std::uint32_t>;
  template class CrcSpongeBuilder<std::uint16_t>;
  template class CrcSpongeBuilder<std::uint8_t>;


  // utility typedefs
  typedef CrcSponge<std::uint64_t> CrcSponge64;
  typedef CrcSponge<std::uint32_t> CrcSponge32;
  typedef CrcSponge<std::uint16_t> CrcSponge16;
  typedef CrcSponge<std::uint8_t> CrcSponge8;

  typedef CrcSpongeBuilder<std::uint64_t> CrcSponge64Builder;
  typedef CrcSpongeBuilder<std::uint32_t> CrcSponge32Builder;
  typedef CrcSpongeBuilder<std::uint16_t> CrcSponge16Builder;
  typedef CrcSpongeBuilder<std::uint8_t> CrcSponge8Builder;

}

#endif /* DRAUPNIR_H__ */

