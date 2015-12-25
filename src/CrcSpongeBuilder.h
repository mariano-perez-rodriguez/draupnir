#ifndef DRAUPNIR_CRC_SPONGE_BUILDER_H__
#define DRAUPNIR_CRC_SPONGE_BUILDER_H__

#include <cstdint>
#include <array>

#include "CrcSponge.h"

namespace Draupnir {

  /**
   * Convenience class to implement named parameter constructors for CrcSponge
   *
   */
  template <typename T>
  class CrcSpongeBuilder {
    public:
      /**
       * Default constructor
       *
       */
      CrcSpongeBuilder() noexcept;

      /**
       * Copy constructor - defaulted
       *
       * @param other  CrcSpongeBuilder to copy from
       */
      CrcSpongeBuilder(CrcSpongeBuilder const &other) noexcept = default;

      /**
       * Move constructor - defaulted
       *
       * @param other  CrcSpongeBuilder to move from
       */
      CrcSpongeBuilder(CrcSpongeBuilder &&other) noexcept = default;

      /**
       * Assignment operator - defaulted
       *
       * @param other  CrcSpongeBuilder to assign
       * @return the newly assigned CrcSpongeBuilder
       */
      CrcSpongeBuilder &operator=(CrcSpongeBuilder const &other) noexcept = default;

      /**
       * Move-assignment operator - defaulted
       *
       * @param other  CrcSpongeBuilder to move-assign
       * @return the newly move-assigned CrcSpongeBuilder
       */
      CrcSpongeBuilder &operator=(CrcSpongeBuilder &&other) noexcept = default;

      /**
       * Virtual destructor - defaulted
       *
       */
      virtual ~CrcSpongeBuilder() noexcept = default;

      /**
       * Conversion to a CrcSponge
       *
       */
      operator CrcSponge<T>() const noexcept;

      /**
       * Set the generator to use
       *
       * @param __generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &generator(T const &__generator) noexcept;

      /**
       * Set the initial value to use
       *
       * @param __initialValue  Initial value to adopt for the running crc
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &initialValue(T const &__initialValue) noexcept;

      /**
       * Set the xor value to use
       *
       * @param __xorValue  Value to xor with the running crc to generate a partial output
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &xorValue(T const &__xorValue) noexcept;

      /**
       * Set the number of soaking rounds to use
       *
       * @param __soakingRounds  Number of transformation rounds to apply after soaking each block
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &soakingRounds(std::size_t __soakingRounds) noexcept;

      /**
       * Set the number of squeezing rounds to use
       *
       * @param __squeezingRounds  Number of transformation rounds to apply after squeezing each block
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &squeezingRounds(std::size_t __squeezingRounds) noexcept;

      /**
       * Set the initial state to use
       *
       * @param __initialState  Initial state to adopt
       * @return the current CrcSpongeBuilder
       */
      CrcSpongeBuilder &initialState(std::array<T, CrcSponge<T>::bitSize> const &__initialState) noexcept;

      /**
       * Explicitly build the specified CrcSponge
       *
       * @return the CrcSponge object built
       */
      CrcSponge<T> build() const noexcept;

      /**
       * Default number of soaking rounds (8)
       *
       */
      static const std::size_t defaultSoakingRounds;

      /**
       * Default number of squeezing rounds (1)
       *
       */
      static const std::size_t defaultSqueezingRounds;

      /**
       * Default initial state (pi)
       *
       */
      static const std::array<T, CrcSponge<T>::bitSize> defaultInitialState;

      /**
       * Default generator:
       *
       *   - 0x42f0e1eba9ea3693 for 64 bits
       *   - 0x04c11db7         for 32 bits
       *   - 0x1021             for 16 bits
       *   - 0x9b               for  8 bits
       *
       */
      static const T defaultGenerator;

      /**
       * Default initial value (all-1s)
       *
       */
      static const T defaultInitialValue;

      /**
       * Default xoring value (all-1s)
       *
       */
      static const T defaultXorValue;

    protected:
      /**
       * Number of transformation rounds to apply after soaking each block
       *
       */
      std::size_t _soakingRounds;

      /**
       * Number of transformation rounds to apply after squeezing each block
       *
       */
      std::size_t _squeezingRounds;

      /**
       * Initial state to adopt
       *
       */
      std::array<T, CrcSponge<T>::bitSize> _initialState;

      /**
       * Generator polynomial to use - given in non-reversed form with its
       * most significant bit omitted
       *
       */
      T _generator;

      /**
       * Initial value to adopt for the running crc
       *
       */
      T _initialValue;

      /**
       * Value to xor with the running crc to generate a partial output
       *
       */
      T _xorValue;
  };

}

#include "CrcSpongeBuilder.hpp"

#endif /* DRAUPNIR_CRC_SPONGE_BUILDER_H__ */

