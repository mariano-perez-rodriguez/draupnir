#include "DraupnirCrc32.h"

namespace Draupnir {

  /**
   * Crc32 named constructor head
   *
   * This is the only accessible way of constructing a Crc32 object.
   *
   * @return the Crc32Builder to use for construction
   */
  Crc32Builder crc32() noexcept {
    return Crc32Builder();
  }

  /**
   * Default constructor
   *
   */
  Crc32Builder::Crc32Builder() noexcept
  :
  _generator {0x04c11db7u},
  _initialValue {~0u},
  _xorValue {~0u},
  _soakingRounds {8},
  _squeezingRounds {1}
  {
    for (std::size_t i = 0; i < 128; i++) {
      _initialState[i] = pi[i];
    }
  }

  /**
   * Conversion operator to create a Crc32
   *
   * @return the constructed Crc32
   */
  Crc32Builder::operator Crc32() const noexcept {
    return Crc32(_generator, _initialValue, _xorValue, _soakingRounds, _squeezingRounds, _initialState);
  }

  /**
   * Virtual copy constructor - should not be needed either way
   *
   * @return the constructed object
   */
  Crc32Builder *Crc32Builder::clone() const noexcept {
    return new Crc32Builder(*this);
  }

  /**
   * Virtual default constructor - should not be needed either way
   *
   * @return the constructed object
   */
  Crc32Builder *Crc32Builder::create() const noexcept {
    return new Crc32Builder();
  }

  /**
   * Generator parameter materialization
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ANSI
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::generator(std::uint32_t __generator) noexcept {
    _generator = __generator;
    return *this;
  }

  /**
   * Initial value parameter materialization
   *
   * @param __initialValue  Initial value to use for crc, defaults to all-1s
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::initialValue(std::uint32_t __initialValue) noexcept {
    _initialValue = __initialValue;
    return *this;
  }

  /**
   * Xor value parameter materialization
   *
   * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::xorValue(std::uint32_t __xorValue) noexcept {
    _xorValue = __xorValue;
    return *this;
  }

  /**
   * Soaking rounds parameter materialization
   *
   * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::soakingRounds(std::size_t __soakingRounds) noexcept {
    _soakingRounds = __soakingRounds;
    return *this;
  }

  /**
   * Squeezing rounds parameter materialization
   *
   * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::squeezingRounds(std::size_t __squeezingRounds) noexcept {
    _squeezingRounds = __squeezingRounds;
    return *this;
  }

  /**
   * Initial state parameter materialization
   *
   * @param __initialState  Initial state to use, defaults to pi
   * @return a reference to the current object
   */
  Crc32Builder &Crc32Builder::initialState(std::uint8_t const __initialState[128]) noexcept {
    for (std::size_t i = 0; i < 128; i++) {
      _initialState[i] = __initialState[i];
    }
    return *this;
  }

  /**
   * Force the building of a Draupnir RNG (useful for "auto" type specifiers)
   *
   * @return the constructed Crc32 object
   */
  Crc32 Crc32Builder::build() noexcept {
    return *this;
  }


  /**
   * Crc32 constructor
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ANSI
   * @param __initialValue  Initial value to use for crc, defaults to all-1s
   * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
   * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
   * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
   * @param __initialState  Initial state to use, defaults to pi
   */
  Crc32::Crc32(std::uint32_t __generator, std::uint32_t __initialValue, std::uint32_t __xorValue, std::size_t __soakingRounds, std::size_t __squeezingRounds, std::uint8_t const __initialState[128]) noexcept
    :
  _generator {__generator},
  _crc {__initialValue},
  _initialValue {__initialValue},
  _xorValue {__xorValue},
  _soakingRounds {__soakingRounds},
  _squeezingRounds {__squeezingRounds},
  _initialState {copyState(reinterpret_cast<std::uint32_t const *>(__initialState)), std::default_delete<std::uint32_t[]>()},
  _remaining {0},
  _crcTable {buildTable(_generator), std::default_delete<std::uint32_t[]>()}
  {
    reset(__initialState);
  }

  /**
   * Virtual copy constructor
   *
   * @return the constructed object
   */
  Crc32 *Crc32::clone() const noexcept {
    return new Crc32(*this);
  }

  /**
   * Virtual default constructor
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ANSI
   * @param __initialValue  Initial value to use for crc, defaults to all-1s
   * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
   * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
   * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
   * @param __initialState  Initial state to use, defaults to pi
   * @return the constructed object
   */
  Crc32 *Crc32::create(std::uint32_t __generator, std::uint32_t __initialValue, std::uint32_t __xorValue, std::size_t __soakingRounds, std::size_t __squeezingRounds, std::uint8_t const __initialState[128]) const noexcept {
    return new Crc32(__generator, __initialValue, __xorValue, __soakingRounds, __squeezingRounds, __initialState);
  }

  /**
   * Extract a byte from the RNG
   *
   * This method squeezes the Draupnir sponge and extracts a byte from it.
   *
   * @return the byte extracted
   */
  std::uint8_t Crc32::getByte() noexcept {
    if (_remaining <= 0) {
      std::uint32_t temp = squeeze();
      _buffer[0] = static_cast<std::uint8_t>(temp >> 24);
      _buffer[1] = static_cast<std::uint8_t>(temp >> 16);
      _buffer[2] = static_cast<std::uint8_t>(temp >>  8);
      _buffer[3] = static_cast<std::uint8_t>(temp      );
      _remaining = 4;
    }

    return _buffer[--_remaining];
  }

  /**
   * Inject a byte string into the RNG
   *
   * This method soakes the Draupnir RNG in (a multi.rate padding of) the
   * given byte string.
   *
   * @param data  Pointer to a byte string
   * @param len  Length of the byte stream
   * @return the soaked object
   */
  Crc32 &Crc32::putBytes(std::uint8_t const *data, std::size_t len) noexcept {
    std::size_t i;

    // deal with 32-bit chunks
    for (i = 0; 4 <= len; len -= 4, i += 4) {
      soak(*reinterpret_cast<std::uint32_t const *>(&data[i]));
    }

    // deal with remaining semi-chunks
    {
      std::uint32_t block = 0u;
      for (std::size_t m = len; 0 < m; m--, i++) {
        block |= data[i]; block <<= 8;
      }
      // add the multi-rate-padding "header" as the last byte
      block |= 0x80u;
      // if we have to make room, do so now (nb. if n == 7 we have all we need)
      if (len < 7) {
        block <<= 8 * (7 - len);
      }
      // add the multi-rate-padding "tail" as the last byte
      block |= 0x01u;

      // now soak the resulting last block
      soak(block);
    }

    // return a reference to the sponge
    return *this;
  }

  /**
   * Apply a transformation step
   *
   * This method applies a given number of rounds of the transformation
   * function to the Draupnir sponge.
   *
   * @param count  Number of rounds to apply, defaults to 1
   * @return the transformed object
   */
  Crc32 &Crc32::step(std::size_t count) noexcept {
    for (std::size_t i = 0; i < count; i++) {
      transform();
    }

    return *this;
  }

  /**
   * Reset the Draupnir sponge
   *
   * This method resets the Draupnir sponge to the given state
   *
   * @param __initialState  State to reset to, defaults to pi
   * @return the reset object
   */
  Crc32 &Crc32::reset(std::uint8_t const __initialState[128]) noexcept {
    std::uint32_t const *init = reinterpret_cast<std::uint32_t const *>(__initialState);
    for (std::size_t i = 0; i < 32; i++) {
      _state[i] = init[i];
    }

    return *this;
  }

  /**
   * Extract a state description structure
   *
   * @return the state description structure extracted form the current object
   */
  Crc32::state_t Crc32::state() const noexcept {
    Crc32::state_t result;
    result.generator       = _generator;
    result.crc             = _crc;
    result.initialValue    = _initialValue;
    result.soakingRounds   = _soakingRounds;
    result.squeezingRounds = _squeezingRounds;
    for (std::size_t i = 0; i < 32; i++) {
      result.initialState[i] = _initialState.get()[i];
    }
    for (std::size_t i = 0; i < 32; i++) {
      result.state[i] = _state[i];
    }
    return result;
  }

  /**
   * Apply the transformation function to the Draupnir sponge
   *
   */
  void Crc32::transform() noexcept {
    static std::uint32_t temp[32];

    // fill temporary and clear current state
    std::uint8_t *data = reinterpret_cast<std::uint8_t *>(_state);
    for (std::size_t i = 0, j = 0; i < 128; i += 4, j++) {
      for (std::size_t k = 0; k < 4; k++) {
        _crc = _crcTable.get()[(_crc ^ *(data++)) & 0xfful] ^ (_crc >> 8);
      }
      temp[j] = _crc ^ _xorValue;
      _state[j] = 0u;
    }

    // transpose temporary into state
    for (std::size_t i = 0; i < 31; i++) {
      _state[0] ^= static_cast<std::uint32_t>((temp[i] & 0x80000000u) != 0) << (31 - i);
      for (std::size_t j = 1; j < 32; j++) {
        _state[j] ^= static_cast<std::uint32_t>((temp[i] & (0x80000000u >> j)) != 0) << (31 - i);
      }
    }
    _state[0] ^= static_cast<std::uint32_t>((temp[31] & 0x80000000u) != 0);
    for (std::size_t j = 1; j < 32; j++) {
      _state[j] ^= static_cast<std::uint32_t>((temp[31] & (0x80000000u >> j)) != 0);
    }
  }

  /**
   * Squeeze the Draupnir sponge
   *
   * @return the squeezed 32 bits
   */
  std::uint32_t Crc32::squeeze() noexcept {
    std::uint32_t diag = 0u;
    for (std::size_t i = 1; i < 32; i += 2) {
      diag |= _state[i] & ((0x80000000u >> i) | (0x00000001u << i));
    }
    step(_squeezingRounds);
    return diag;
  }

  /**
   * Soak a 32 bit value into the sponge
   *
   * @param block  32 bits to soak into the sponge
   */
  void Crc32::soak(std::uint32_t block) noexcept {
    _state[0] ^= (_state[0] ^ block) & 0x80000001u;
    for (std::size_t i = 2; i < 32; i += 2) {
      // derived from: https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
      _state[i] ^= (_state[i] ^ block) & ((0x80000000u >> i) | (0x00000001u << i));
    }
    step(_soakingRounds);
  }

  /**
   * Build a CRC32 lookup table
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted
   * @return a new[]-allocated lookup table
   */
  std::uint32_t *Crc32::buildTable(std::uint32_t __generator) noexcept {
    // returned array
    std::uint32_t *table = new std::uint32_t[256]();

    // calculate initial slice
    for (std::size_t i = 0; i < 256; i++) {
      // get the reversed byte to the top
      table[i] = static_cast<std::uint32_t>(i << 24);

      // divide away
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
      table[i] = (table[i] << 1) ^ ((table[i] & 0x80000000u) ? __generator : 0u);
    }

    // return the generated table
    return table;
  }

  /**
   * Create a new[] state and copy the given one
   *
   * @param __state  State to copy
   * @return a new[]-allocated copy of the given state
   */
  std::uint32_t *Crc32::copyState(std::uint32_t const *__state) noexcept {
    std::uint32_t *result = new std::uint32_t[32];
    for (std::size_t i = 0; i < 32; i++) {
      result[i] = __state[i];
    }
    return result;
  }

}

