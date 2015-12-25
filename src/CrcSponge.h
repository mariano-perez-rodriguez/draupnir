#ifndef DRAUPNIR_CRC_SPONGE_H__
#define DRAUPNIR_CRC_SPONGE_H__

#include <cstdint>
#include <memory>
#include <array>
#include <string>

#include "Sponge.h"

namespace Draupnir {

  /**
   * Crc-based cryptographic sponge - implementing the Sponge interface
   *
   * The template parameter establishes the crc's width.
   *
   */
  template <typename T>
  class CrcSponge : public Sponge {
    public:
      /**
       * Crc's size in bytes
       *
       */
      static constexpr std::size_t wordSize = sizeof(T);

      /**
       * Crc's size in bits
       *
       */
      static constexpr std::size_t bitSize = wordSize * 8;

      /**
       * A value with all 0 bits except for the LSb one
       *
       */
      static constexpr T lowBit = static_cast<T>(1);

      /**
       * A value with all 0 bits except for the MSb one
       *
       */
      static constexpr T highBit = lowBit << (bitSize - 1);

      /**
       * Main constructor
       *
       * @param generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
       * @param initialValue  Initial value to adopt for the running crc
       * @param xorValue  Value to xor with the running crc to generate a partial output
       * @param initialState  Initial state to adopt
       * @param soakingRounds  Number of transformation rounds to apply after soaking each block
       * @param squeezingRounds  Number of transformation rounds to apply after squeezing out a block
       */
      CrcSponge(T generator, T initialValue, T xorValue, std::array<T, bitSize> const initialState, std::size_t soakingRounds, std::size_t squeezingRounds) noexcept;

      /**
       * Copy constructor - defaulted
       *
       * @param other  CrcSponge to copy from
       */
      CrcSponge(CrcSponge const &other) noexcept = default;

      /**
       * Move constructor - defaulted
       *
       * @param other  CrcSponge to move from
       */
      CrcSponge(CrcSponge &&other) noexcept = default;

      /**
       * Assignment operator - defaulted
       *
       * @param other  CrcSponge to assign
       * @return the newly assigned CrcSponge
       */
      CrcSponge &operator=(CrcSponge const &other) noexcept = default;

      /**
       * Move-assignment operator - defaulted
       *
       * @param other  CrcSponge to move-assign
       * @return the newly move-assigned CrcSponge
       */
      CrcSponge &operator=(CrcSponge &&other) noexcept = default;

      /**
       * Virtual destructor - defaulted
       *
       */
      virtual ~CrcSponge() noexcept = default;

      /**
       * Squeeze a single byte from the sponge
       *
       * @return the squeezed out byte
       */
      virtual std::uint8_t squeeze() noexcept;

      /**
       * Soak a string into the sponge
       *
       * @param data  String to soak
       * @return the soaked sponge
       */
      virtual CrcSponge &soak(std::string const data) noexcept;

      /**
       * Apply a transformation step
       *
       * @param n  Number of transformation steps to apply (defaults to 1)
       * @return the stepped sponge
       */
      virtual CrcSponge &step(std::size_t n = 1) noexcept;

      /**
       * Reset the sponge to its initial state
       *
       * @return the reset sponge
       */
      virtual CrcSponge &reset() noexcept;

      /**
       * Dump the sponge's state as a string
       *
       * @return the dumped state
       */
      virtual std::string dump() const noexcept;

    protected:
      /**
       * Squeeze out a single block from the sponge
       *
       */
      void squeezeBlock() noexcept;

      /**
       * Soak a single (padded) block into the sponge
       *
       * @param block  Block to soak
       */
      void soakBlock(T const block) noexcept;

      /**
       * Apply the state-changing transformation
       *
       */
      void transform() noexcept;

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
       * Number of bytes remaining in the buffer
       *
       */
      std::size_t _remaining;

      /**
       * Crc table to use
       *
       * This table will be shared with every sibling to avoid unnecessary
       * duplication.
       *
       */
      std::shared_ptr<std::array<T, 256>> _crcTable;

      /**
       * Initial state to adopt
       *
       */
      std::array<T, bitSize> _initialState;

      /**
       * Current state
       *
       */
      std::array<T, bitSize> _state;

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

      /**
       * Running crc
       *
       */
      T _crc;

      /**
       * Output buffer to use for squeezing
       *
       */
      std::array<std::uint8_t, wordSize> _buffer;
  };

}

#include "CrcSponge.hpp"

#endif /* DRAUPNIR_CRC_SPONGE_H__ */

