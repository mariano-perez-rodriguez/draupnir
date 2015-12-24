#ifndef CRC_SPONGE_HPP__
#define CRC_SPONGE_HPP__

#include "CrcSponge.h"

namespace {

  /**
   * Build a 256-entry crc lookup table with the given generator
   *
   * This function builds a 256-entry crc lookup table using the given generator.
   *
   * @param generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
   * @return a 256-entry array of the same type as the generator
   */
  template <typename T>
  static std::array<T, 256> *buildTable(T const &generator) {
    constexpr T zero = static_cast<T>(0);
    constexpr T highBit = static_cast<T>(1) << ((sizeof(T) * 8) - 1);
    constexpr std::size_t offset = ((sizeof(T) - 1) * 8);

    // returned array
    std::array<T, 256> *table = new std::array<T, 256>();

    // calculate initial slice
    for (std::size_t i = 0; i < 256; i++) {
      // get the reversed byte to the top
      (*table)[i] = static_cast<T>(i << offset);

      // divide away
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
      (*table)[i] = static_cast<T>(((*table)[i] << 1) ^ (((*table)[i] & highBit) ? generator : zero));
    }

    // return the generated table
    return table;
  }

}


namespace Draupnir {

  /**
   * CrcSponge main constructor
   *
   * @param generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
   * @param initialValue  Initial value to adopt for the running crc
   * @param xorValue  Value to xor with the running crc to generate a partial output
   * @param initialState  Initial state to adopt
   * @param soakingRounds  Number of transformation rounds to apply after soaking each block
   * @param squeezingRounds  Number of transformation rounds to apply after squeezing out a block
   */
  template <typename T>
  CrcSponge<T>::CrcSponge(T generator, T initialValue, T xorValue, std::array<T, bitSize> const initialState, std::size_t soakingRounds, std::size_t squeezingRounds) noexcept
    :
  _soakingRounds {soakingRounds},
  _squeezingRounds {squeezingRounds},
  _remaining {0},
  _crcTable {buildTable<T>(generator)},
  _initialState {bitSize},
  _state {bitSize},
  _generator {generator},
  _initialValue {initialValue},
  _xorValue {xorValue},
  _crc {initialValue},
  _buffer {wordSize}
  {
    _initialState = initialState;
    _state = _initialState;
  }

  /**
   * Squeeze a single byte from the sponge
   *
   * @return the squeezed out byte
   */
  template <typename T>
  std::uint8_t CrcSponge<T>::squeeze() noexcept {
    if (_remaining <= 0) {
      squeezeBlock();
    }
    return _buffer[--_remaining];
  }

  /**
   * Squeeze out a single block from the sponge
   *
   */
  template <typename T>
  void CrcSponge<T>::squeezeBlock() noexcept {
    T diag = 0;

    for (std::size_t i = 1; i < bitSize; i += 2) {
      diag = static_cast<T>(diag | (_state[i] & ((highBit >> i) | (lowBit << i))));
    }
    step(_squeezingRounds);

    for (std::size_t i = 0, j = bitSize - 8; i < wordSize - 1; i++, j -= 8) {
      _buffer[i] = static_cast<std::uint8_t>(diag >> j);
    }
    _buffer[wordSize - 1] = static_cast<std::uint8_t>(diag);

    _remaining = wordSize;
  }

  /**
   * Soak a byte array into the sponge
   *
   * @param data  Byte array's pointer
   * @param len  Byte array's length
   * @return the soaked sponge
   */
  template <typename T>
  CrcSponge<T> &CrcSponge<T>::soak(std::uint8_t const *data, std::size_t len) noexcept {
    std::size_t i;

    // deal with bitSize-bit chunks
    for (i = 0; wordSize <= len; len -= wordSize, i += wordSize) {
      soakBlock(*reinterpret_cast<T const *>(&data[i]));
    }

    // deal with remaining semi-chunks
    {
      T block = 0;
      for (std::size_t m = len; 0 < m; m--, i++) {
        block = static_cast<T>((block | data[i]) << 8);
      }
      // add the multi-rate-padding "header" as the last byte
      block |= 0x80;
      // if we have to make room, do so now (nb. if n == wordSize - 1 we have all we need)
      if (len < wordSize - 1) {
        block = static_cast<T>(block << (8 * ((wordSize - 1) - len)));
      }
      // add the multi-rate-padding "tail" as the last byte
      block |= 0x01;

      // now soak the resulting last block
      soakBlock(block);
    }

    // return a reference to the sponge
    return *this;
  }

  /**
   * Soak a single (padded) block into the sponge
   *
   * @param block  Block to soak
   */
  template <typename T>
  void CrcSponge<T>::soakBlock(T const block) noexcept {
    _state[0] = static_cast<T>(_state[0] ^ ((_state[0] ^ block) & (highBit | lowBit)));
    for (std::size_t i = 2; i < bitSize; i += 2) {
      // derived from: https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
      _state[i] = static_cast<T>(_state[i] ^ ((_state[i] ^ block) & ((highBit >> i) | (lowBit << i))));
    }
    _remaining = 0;
    step(_soakingRounds);
  }

  /**
   * Apply a transformation step
   *
   * @param n  Number of transformation steps to apply (defaults to 1)
   * @return the stepped sponge
   */
  template <typename T>
  CrcSponge<T> &CrcSponge<T>::step(std::size_t n) noexcept {
    while (n--) {
      transform();
    }
    return *this;
  }

  /**
   * Reset the sponge to its initial state
   *
   * @return the reset sponge
   */
  template <typename T>
  CrcSponge<T> &CrcSponge<T>::reset() noexcept {
    _crc = _initialValue;
    _state = _initialState;

    return *this;
  }

  /**
   * Apply the state-changing transformation
   *
   */
  template <typename T>
  void CrcSponge<T>::transform() noexcept {
    static std::array<T, bitSize> temp;

    // fill temporary and clear current state
    std::uint8_t const *data = reinterpret_cast<std::uint8_t const *>(_state.data());
    for (std::size_t i = 0; i < bitSize; i++) {
      for (std::size_t k = 0; k < 8; k++) {
        _crc = static_cast<T>((*_crcTable.get())[(_crc ^ *(data++)) & static_cast<T>(0xff)] ^ (_crc >> 8));
      }
      temp[i] = _crc ^ _xorValue;
      _state[i] = static_cast<T>(0);
    }

    // transpose temporary into state
    for (std::size_t i = 0; i < bitSize - 1; i++) {
      _state[0] = static_cast<T>(_state[0] ^ (static_cast<T>((temp[i] & highBit) != 0) << (bitSize - 1 - i)));
      for (std::size_t j = 1; j < bitSize; j++) {
        _state[j] = static_cast<T>(_state[j] ^ (static_cast<T>((temp[i] & (highBit >> j)) != 0) << (bitSize - 1 - i)));
      }
    }
    _state[0] = static_cast<T>(_state[0] ^ static_cast<T>((temp[bitSize - 1] & highBit) != 0));
    for (std::size_t j = 1; j < bitSize; j++) {
      _state[j] = static_cast<T>(_state[j] ^ static_cast<T>((temp[bitSize - 1] & (highBit >> j)) != 0));
    }
  }

}

#endif /* CRC_SPONGE_HPP__ */

