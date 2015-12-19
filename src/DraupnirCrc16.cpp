#include "DraupnirCrc16.h"

namespace Draupnir {

  /**
   * Crc16 named constructor head
   *
   * This is the only accessible way of constructing a Crc16 object.
   *
   * @return the Crc16Builder to use for construction
   */
  Crc16Builder crc16() noexcept {
    return Crc16Builder();
  }

  /**
   * Default constructor
   *
   */
  Crc16Builder::Crc16Builder() noexcept
  :
  _generator {U16(0x8005)},
  _initialValue {U16(~0)},
  _xorValue {U16(~0)},
  _soakingRounds {8},
  _squeezingRounds {1}
  {
    for (std::size_t i = 0; i < 32; i++) {
      _initialState[i] = pi[i];
    }
  }

  /**
   * Conversion operator to create a Crc16
   *
   * @return the constructed Crc16
   */
  Crc16Builder::operator Crc16() const noexcept {
    return Crc16(_generator, _initialValue, _xorValue, _soakingRounds, _squeezingRounds, _initialState);
  }

  /**
   * Virtual copy constructor - should not be needed either way
   *
   * @return the constructed object
   */
  Crc16Builder *Crc16Builder::clone() const noexcept {
    return new Crc16Builder(*this);
  }

  /**
   * Virtual default constructor - should not be needed either way
   *
   * @return the constructed object
   */
  Crc16Builder *Crc16Builder::create() const noexcept {
    return new Crc16Builder();
  }

  /**
   * Generator parameter materialization
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ANSI
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::generator(std::uint16_t __generator) noexcept {
    _generator = __generator;
    return *this;
  }

  /**
   * Initial value parameter materialization
   *
   * @param __initialValue  Initial value to use for crc, defaults to all-1s
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::initialValue(std::uint16_t __initialValue) noexcept {
    _initialValue = __initialValue;
    return *this;
  }

  /**
   * Xor value parameter materialization
   *
   * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::xorValue(std::uint16_t __xorValue) noexcept {
    _xorValue = __xorValue;
    return *this;
  }

  /**
   * Soaking rounds parameter materialization
   *
   * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::soakingRounds(std::size_t __soakingRounds) noexcept {
    _soakingRounds = __soakingRounds;
    return *this;
  }

  /**
   * Squeezing rounds parameter materialization
   *
   * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::squeezingRounds(std::size_t __squeezingRounds) noexcept {
    _squeezingRounds = __squeezingRounds;
    return *this;
  }

  /**
   * Initial state parameter materialization
   *
   * @param __initialState  Initial state to use, defaults to pi
   * @return a reference to the current object
   */
  Crc16Builder &Crc16Builder::initialState(std::uint8_t const __initialState[32]) noexcept {
    for (std::size_t i = 0; i < 32; i++) {
      _initialState[i] = __initialState[i];
    }
    return *this;
  }

  /**
   * Force the building of a Draupnir RNG (useful for "auto" type specifiers)
   *
   * @return the constructed Crc16 object
   */
  Crc16 Crc16Builder::build() noexcept {
    return *this;
  }


  /**
   * Crc16 constructor
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ANSI
   * @param __initialValue  Initial value to use for crc, defaults to all-1s
   * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
   * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
   * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
   * @param __initialState  Initial state to use, defaults to pi
   */
  Crc16::Crc16(std::uint16_t __generator, std::uint16_t __initialValue, std::uint16_t __xorValue, std::size_t __soakingRounds, std::size_t __squeezingRounds, std::uint8_t const __initialState[32]) noexcept
    :
  _generator {__generator},
  _crc {__initialValue},
  _initialValue {__initialValue},
  _xorValue {__xorValue},
  _soakingRounds {__soakingRounds},
  _squeezingRounds {__squeezingRounds},
  _initialState {copyState(reinterpret_cast<std::uint16_t const *>(__initialState)), std::default_delete<std::uint16_t[]>()},
  _remaining {0},
  _crcTable {buildTable(_generator), std::default_delete<std::uint16_t[]>()}
  {
    reset(__initialState);
  }

  /**
   * Virtual copy constructor
   *
   * @return the constructed object
   */
  Crc16 *Crc16::clone() const noexcept {
    return new Crc16(*this);
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
  Crc16 *Crc16::create(std::uint16_t __generator, std::uint16_t __initialValue, std::uint16_t __xorValue, std::size_t __soakingRounds, std::size_t __squeezingRounds, std::uint8_t const __initialState[32]) const noexcept {
    return new Crc16(__generator, __initialValue, __xorValue, __soakingRounds, __squeezingRounds, __initialState);
  }

  /**
   * Extract a byte from the RNG
   *
   * This method squeezes the Draupnir sponge and extracts a byte from it.
   *
   * @return the byte extracted
   */
  std::uint8_t Crc16::getByte() noexcept {
    if (_remaining <= 0) {
      std::uint16_t temp = squeeze();
      _buffer[0] = static_cast<std::uint8_t>(temp >>  8);
      _buffer[1] = static_cast<std::uint8_t>(temp      );
      _remaining = 2;
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
  Crc16 &Crc16::putBytes(std::uint8_t const *data, std::size_t len) noexcept {
    std::size_t i;

    // deal with 16-bit chunks
    for (i = 0; 2 <= len; len -= 2, i += 2) {
      soak(*reinterpret_cast<std::uint16_t const *>(&data[i]));
    }

    // deal with remaining semi-chunks
    {
      std::uint16_t block = U16(0);
      for (std::size_t m = len; 0 < m; m--, i++) {
        block = static_cast<std::uint16_t>((block | data[i]) << 8);
      }
      // add the multi-rate-padding "header" as the last byte
      block = static_cast<std::uint16_t>(block | U16(0x80));
      // if we have to make room, do so now (nb. if n == 7 we have all we need)
      if (len < 7) {
        block = static_cast<std::uint16_t>(block << (8 * (7 - len)));
      }
      // add the multi-rate-padding "tail" as the last byte
      block = static_cast<std::uint16_t>(block | U16(0x01));

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
  Crc16 &Crc16::step(std::size_t count) noexcept {
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
  Crc16 &Crc16::reset(std::uint8_t const __initialState[32]) noexcept {
    std::uint16_t const *init = reinterpret_cast<std::uint16_t const *>(__initialState);
    for (std::size_t i = 0; i < 16; i++) {
      _state[i] = init[i];
    }

    return *this;
  }

  /**
   * Extract a state description structure
   *
   * @return the state description structure extracted form the current object
   */
  Crc16::state_t Crc16::state() const noexcept {
    Crc16::state_t result;
    result.generator       = _generator;
    result.crc             = _crc;
    result.initialValue    = _initialValue;
    result.soakingRounds   = _soakingRounds;
    result.squeezingRounds = _squeezingRounds;
    for (std::size_t i = 0; i < 16; i++) {
      result.initialState[i] = _initialState.get()[i];
    }
    for (std::size_t i = 0; i < 16; i++) {
      result.state[i] = _state[i];
    }
    return result;
  }

  /**
   * Apply the transformation function to the Draupnir sponge
   *
   */
  void Crc16::transform() noexcept {
    static std::uint16_t temp[16];

    // fill temporary and clear current state
    std::uint8_t *data = reinterpret_cast<std::uint8_t *>(_state);
    for (std::size_t i = 0, j = 0; i < 32; i += 2, j++) {
      for (std::size_t k = 0; k < 2; k++) {
        _crc = _crcTable.get()[(_crc ^ *(data++)) & U16(0xff)] ^ static_cast<std::uint16_t>(_crc >> 8);
      }
      temp[j] = _crc ^ _xorValue;
      _state[j] = U16(0);
    }

    // transpose temporary into state
    for (std::size_t i = 0; i < 15; i++) {
      _state[0] ^= static_cast<std::uint16_t>(((temp[i] & U16(0x8000)) != 0) << (15 - i));
      for (std::size_t j = 1; j < 16; j++) {
        _state[j] ^= static_cast<std::uint16_t>(((temp[i] & (U16(0x8000) >> j)) != 0) << (15 - i));
      }
    }
    _state[0] = static_cast<std::uint16_t>(_state[0] ^ ((temp[15] & U16(0x8000)) != 0));
    for (std::size_t j = 1; j < 16; j++) {
      _state[j] = static_cast<std::uint16_t>(_state[j] ^ ((temp[15] & (U16(0x8000) >> j)) != 0));
    }
  }

  /**
   * Squeeze the Draupnir sponge
   *
   * @return the squeezed 16 bits
   */
  std::uint16_t Crc16::squeeze() noexcept {
    std::uint16_t diag = U16(0);
    for (std::size_t i = 1; i < 16; i += 2) {
      diag = static_cast<std::uint16_t>(diag | (_state[i] & ((U16(0x8000) >> i) | (U16(0x0001) << i))));
    }
    step(_squeezingRounds);
    return diag;
  }

  /**
   * Soak a 16 bit value into the sponge
   *
   * @param block  16 bits to soak into the sponge
   */
  void Crc16::soak(std::uint16_t block) noexcept {
    _state[0] = static_cast<std::uint16_t>(_state[0] ^ ((_state[0] ^ block) & U16(0x8001)));
    for (std::size_t i = 2; i < 16; i += 2) {
      // derived from: https://graphics.stanford.edu/~seander/bithacks.html#MaskedMerge
      _state[i] = static_cast<std::uint16_t>(_state[i] ^ ((_state[i] ^ block) & ((U16(0x8000) >> i) | (U16(0x0001) << i))));
    }
    step(_soakingRounds);
  }

  /**
   * Build a CRC16 lookup table
   *
   * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted
   * @return a new[]-allocated lookup table
   */
  std::uint16_t *Crc16::buildTable(std::uint16_t __generator) noexcept {
    // returned array
    std::uint16_t *table = new std::uint16_t[256]();

    // calculate initial slice
    for (std::size_t i = 0; i < 256; i++) {
      // get the reversed byte to the top
      table[i] = static_cast<std::uint16_t>(i << 8);

      // divide away
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
      table[i] = static_cast<std::uint16_t>((table[i] << 1) ^ ((table[i] & U16(0x8000)) ? __generator : U16(0)));
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
  std::uint16_t *Crc16::copyState(std::uint16_t const *__state) noexcept {
    std::uint16_t *result = new std::uint16_t[16];
    for (std::size_t i = 0; i < 16; i++) {
      result[i] = __state[i];
    }
    return result;
  }

}

