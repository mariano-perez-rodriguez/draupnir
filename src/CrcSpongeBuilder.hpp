#ifndef CRC_SPONGE_BUILDER_HPP__
#define CRC_SPONGE_BUILDER_HPP__

#include "CrcSpongeBuilder.h"
#include "Constants.h"

namespace {

  /**
   * Function to copy an std::array from a legacy array
   *
   * @param src  Legacy (C-style) array to use as source data
   * @return the copied array
   */
  template <typename T, std::size_t N>
  std::array<T, N> copy(T const *src) noexcept {
    std::array<T, N> result;
    for (std::size_t i = 0; i < N; i++) {
      result[i] = src[i];
    }
    return result;
  }

}


namespace Draupnir {

  /**
   * CrcSpongeBuilder default constructor
   *
   */
  template <typename T>
  CrcSpongeBuilder<T>::CrcSpongeBuilder() noexcept
    :
  _soakingRounds {defaultSoakingRounds},
  _squeezingRounds {defaultSqueezingRounds},
  _initialState {CrcSponge<T>::bitSize},
  _generator {defaultGenerator},
  _initialValue {defaultInitialValue},
  _xorValue {defaultXorValue}
  {
    _initialState = defaultInitialState;
  }

  /**
   * CrcSpongeBuilder conversion to a CrcSponge
   *
   */
  template <typename T>
  CrcSpongeBuilder<T>::operator CrcSponge<T>() const noexcept {
    return build();
  }

  /**
   * Set the generator to use
   *
   * @param __generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::generator(T __generator) noexcept {
    _generator = __generator;
    return *this;
  }

  /**
   * Set the initial value to use
   *
   * @param __initialValue  Initial value to adopt for the running crc
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::initialValue(T __initialValue) noexcept {
    _initialValue = __initialValue;
    return *this;
  }

  /**
   * Set the xor value to use
   *
   * @param __xorValue  Value to xor with the running crc to generate a partial output
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::xorValue(T __xorValue) noexcept {
    _xorValue = __xorValue;
    return *this;
  }

  /**
   * Set the number of soaking rounds to use
   *
   * @param __soakingRounds  Number of transformation rounds to apply after soaking each block
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::soakingRounds(std::size_t __soakingRounds) noexcept {
    _soakingRounds = __soakingRounds;
    return *this;
  }

  /**
   * Set the number of squeezing rounds to use
   *
   * @param __squeezingRounds  Number of transformation rounds to apply after squeezing each block
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::squeezingRounds(std::size_t __squeezingRounds) noexcept {
    _squeezingRounds = __squeezingRounds;
    return *this;
  }

  /**
   * Set the initial state to use
   *
   * @param __initialState  Initial state to adopt
   * @return the current CrcSpongeBuilder
   */
  template <typename T>
  CrcSpongeBuilder<T> &CrcSpongeBuilder<T>::initialState(std::array<T, CrcSponge<T>::bitSize> const __initialState) noexcept {
    _initialState = __initialState;
    return *this;
  }

  /**
   * Explicitly build the specified CrcSponge
   *
   * @return the CrcSponge object built
   */
  template <typename T>
  CrcSponge<T> CrcSpongeBuilder<T>::build() const noexcept {
    return CrcSponge<T>(_generator, _initialValue, _xorValue, _initialState, _soakingRounds, _squeezingRounds);
  }


  /**
   * Default number of soaking rounds (8)
   *
   */
  template <typename T>
  const std::size_t CrcSpongeBuilder<T>::defaultSoakingRounds = 8;

  /**
   * Default number of squeezing rounds (1)
   *
   */
  template <typename T>
  const std::size_t CrcSpongeBuilder<T>::defaultSqueezingRounds = 1;

  /**
   * Default initial state (pi)
   *
   */
  template <typename T>
  const std::array<T, CrcSponge<T>::bitSize> CrcSpongeBuilder<T>::defaultInitialState = copy<T, CrcSponge<T>::bitSize>(reinterpret_cast<T const *>(pi.data()));

  /**
   * Default generator for 64 bits
   *
   */
  template <>
  const std::uint64_t CrcSpongeBuilder<std::uint64_t>::defaultGenerator = 0x42f0e1eba9ea3693ul;

  /**
   * Default generator for 32 bits
   *
   */
  template <>
  const std::uint32_t CrcSpongeBuilder<std::uint32_t>::defaultGenerator = 0x04c11db7u;

  /**
   * Default generator for 16 bits
   *
   */
  template <>
  const std::uint16_t CrcSpongeBuilder<std::uint16_t>::defaultGenerator = 0x1021u;

  /**
   * Default generator for 8 bits
   *
   */
  template <>
  const std::uint8_t CrcSpongeBuilder<std::uint8_t>::defaultGenerator = 0x9bu;

  /**
   * Default initial value (all-1s)
   *
   */
  template <typename T>
  const T CrcSpongeBuilder<T>::defaultInitialValue = static_cast<T>(~static_cast<T>(0));

  /**
   * Default xoring value (all-1s)
   *
   */
  template <typename T>
  const T CrcSpongeBuilder<T>::defaultXorValue = static_cast<T>(~static_cast<T>(0));

}


#endif /* CRC_SPONGE_BUILDER_HPP__ */

