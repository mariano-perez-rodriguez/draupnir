#include <cstdint>
#include <memory>
#include <array>

namespace Draupnir {

/**
 * Simplified cryptographic sponge interface
 *
 * This interface presents a simplified view of a cryptographic sponge, by
 * providing the methods:
 *
 *   - squeeze: squeeze a SINGLE BYTE from the sponge (this simplification
 *       allows for each sponge to implement its own buffering and still yield
 *       a uniform interface),
 *   - soak: soak a byte array into the sponge,
 *   - step: apply a single transformation step (this allows for users to apply
 *       any arbitrary stepping policy beyond that of the strictly necessary
 *       ones for sponge functioning),
 *   - reset: reset the sponge to its initial state (this is just a convenience
 *       method).
 *
 */
class Sponge {
  public:
    /**
     * Virtual destructor - defaulted
     *
     */
    virtual ~Sponge() noexcept = default;

    /**
     * Squeeze a single byte from the sponge - pure virtual
     *
     * @return the squeezed out byte
     */
    virtual std::uint8_t squeeze() noexcept = 0;

    /**
     * Soak a byte array into the sponge - pure virtual
     *
     * @param data  Byte array's pointer
     * @param len  Byte array's length
     * @return the soaked sponge
     */
    virtual Sponge &soak(std::uint8_t const *data, std::size_t len) noexcept = 0;

    /**
     * Apply a transformation step - pure virtual
     *
     * @param n  Number of transformation steps to apply (defaults to 1)
     * @return the stepped sponge
     */
    virtual Sponge &step(std::size_t n = 1) noexcept = 0;

    /**
     * Reset the sponge to its initial state - pure virtual
     *
     * @return the reset sponge
     */
    virtual Sponge &reset() noexcept = 0;
};

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
     * Soak a byte array into the sponge
     *
     * @param data  Byte array's pointer
     * @param len  Byte array's length
     * @return the soaked sponge
     */
    virtual CrcSponge &soak(std::uint8_t const *data, std::size_t len) noexcept;

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
    CrcSpongeBuilder &generator(T __generator) noexcept;

    /**
     * Set the initial value to use
     *
     * @param __initialValue  Initial value to adopt for the running crc
     * @return the current CrcSpongeBuilder
     */
    CrcSpongeBuilder &initialValue(T __initialValue) noexcept;

    /**
     * Set the xor value to use
     *
     * @param __xorValue  Value to xor with the running crc to generate a partial output
     * @return the current CrcSpongeBuilder
     */
    CrcSpongeBuilder &xorValue(T __xorValue) noexcept;

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
    CrcSpongeBuilder &initialState(std::array<T, CrcSponge<T>::bitSize> const __initialState) noexcept;

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


/**
 * Build a 256-entry crc lookup table with the given generator
 *
 * This function builds a 256-entry crc lookup table using the given generator.
 *
 * @param generator  Generator polynomial to use - given in non-reversed form with its most significant bit omitted
 * @return a 256-entry array of the same type as the generator
 */
template <typename T>
std::array<T, 256> *buildTable(T const &generator) {
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


/**
 * The first 4096 bits of pi as a byte stream
 *
 */
constexpr std::array<std::uint8_t, 512> pi = {{
  0x24u, 0x3fu, 0x6au, 0x88u, 0x85u, 0xa3u, 0x08u, 0xd3u, 0x13u, 0x19u, 0x8au, 0x2eu, 0x03u, 0x70u, 0x73u, 0x44u,
  0xa4u, 0x09u, 0x38u, 0x22u, 0x29u, 0x9fu, 0x31u, 0xd0u, 0x08u, 0x2eu, 0xfau, 0x98u, 0xecu, 0x4eu, 0x6cu, 0x89u,
  0x45u, 0x28u, 0x21u, 0xe6u, 0x38u, 0xd0u, 0x13u, 0x77u, 0xbeu, 0x54u, 0x66u, 0xcfu, 0x34u, 0xe9u, 0x0cu, 0x6cu,
  0xc0u, 0xacu, 0x29u, 0xb7u, 0xc9u, 0x7cu, 0x50u, 0xddu, 0x3fu, 0x84u, 0xd5u, 0xb5u, 0xb5u, 0x47u, 0x09u, 0x17u,
  0x92u, 0x16u, 0xd5u, 0xd9u, 0x89u, 0x79u, 0xfbu, 0x1bu, 0xd1u, 0x31u, 0x0bu, 0xa6u, 0x98u, 0xdfu, 0xb5u, 0xacu,
  0x2fu, 0xfdu, 0x72u, 0xdbu, 0xd0u, 0x1au, 0xdfu, 0xb7u, 0xb8u, 0xe1u, 0xafu, 0xedu, 0x6au, 0x26u, 0x7eu, 0x96u,
  0xbau, 0x7cu, 0x90u, 0x45u, 0xf1u, 0x2cu, 0x7fu, 0x99u, 0x24u, 0xa1u, 0x99u, 0x47u, 0xb3u, 0x91u, 0x6cu, 0xf7u,
  0x08u, 0x01u, 0xf2u, 0xe2u, 0x85u, 0x8eu, 0xfcu, 0x16u, 0x63u, 0x69u, 0x20u, 0xd8u, 0x71u, 0x57u, 0x4eu, 0x69u,
  0xa4u, 0x58u, 0xfeu, 0xa3u, 0xf4u, 0x93u, 0x3du, 0x7eu, 0x0du, 0x95u, 0x74u, 0x8fu, 0x72u, 0x8eu, 0xb6u, 0x58u,
  0x71u, 0x8bu, 0xcdu, 0x58u, 0x82u, 0x15u, 0x4au, 0xeeu, 0x7bu, 0x54u, 0xa4u, 0x1du, 0xc2u, 0x5au, 0x59u, 0xb5u,
  0x9cu, 0x30u, 0xd5u, 0x39u, 0x2au, 0xf2u, 0x60u, 0x13u, 0xc5u, 0xd1u, 0xb0u, 0x23u, 0x28u, 0x60u, 0x85u, 0xf0u,
  0xcau, 0x41u, 0x79u, 0x18u, 0xb8u, 0xdbu, 0x38u, 0xefu, 0x8eu, 0x79u, 0xdcu, 0xb0u, 0x60u, 0x3au, 0x18u, 0x0eu,
  0x6cu, 0x9eu, 0x0eu, 0x8bu, 0xb0u, 0x1eu, 0x8au, 0x3eu, 0xd7u, 0x15u, 0x77u, 0xc1u, 0xbdu, 0x31u, 0x4bu, 0x27u,
  0x78u, 0xafu, 0x2fu, 0xdau, 0x55u, 0x60u, 0x5cu, 0x60u, 0xe6u, 0x55u, 0x25u, 0xf3u, 0xaau, 0x55u, 0xabu, 0x94u,
  0x57u, 0x48u, 0x98u, 0x62u, 0x63u, 0xe8u, 0x14u, 0x40u, 0x55u, 0xcau, 0x39u, 0x6au, 0x2au, 0xabu, 0x10u, 0xb6u,
  0xb4u, 0xccu, 0x5cu, 0x34u, 0x11u, 0x41u, 0xe8u, 0xceu, 0xa1u, 0x54u, 0x86u, 0xafu, 0x7cu, 0x72u, 0xe9u, 0x93u,
  0xb3u, 0xeeu, 0x14u, 0x11u, 0x63u, 0x6fu, 0xbcu, 0x2au, 0x2bu, 0xa9u, 0xc5u, 0x5du, 0x74u, 0x18u, 0x31u, 0xf6u,
  0xceu, 0x5cu, 0x3eu, 0x16u, 0x9bu, 0x87u, 0x93u, 0x1eu, 0xafu, 0xd6u, 0xbau, 0x33u, 0x6cu, 0x24u, 0xcfu, 0x5cu,
  0x7au, 0x32u, 0x53u, 0x81u, 0x28u, 0x95u, 0x86u, 0x77u, 0x3bu, 0x8fu, 0x48u, 0x98u, 0x6bu, 0x4bu, 0xb9u, 0xafu,
  0xc4u, 0xbfu, 0xe8u, 0x1bu, 0x66u, 0x28u, 0x21u, 0x93u, 0x61u, 0xd8u, 0x09u, 0xccu, 0xfbu, 0x21u, 0xa9u, 0x91u,
  0x48u, 0x7cu, 0xacu, 0x60u, 0x5du, 0xecu, 0x80u, 0x32u, 0xefu, 0x84u, 0x5du, 0x5du, 0xe9u, 0x85u, 0x75u, 0xb1u,
  0xdcu, 0x26u, 0x23u, 0x02u, 0xebu, 0x65u, 0x1bu, 0x88u, 0x23u, 0x89u, 0x3eu, 0x81u, 0xd3u, 0x96u, 0xacu, 0xc5u,
  0x0fu, 0x6du, 0x6fu, 0xf3u, 0x83u, 0xf4u, 0x42u, 0x39u, 0x2eu, 0x0bu, 0x44u, 0x82u, 0xa4u, 0x84u, 0x20u, 0x04u,
  0x69u, 0xc8u, 0xf0u, 0x4au, 0x9eu, 0x1fu, 0x9bu, 0x5eu, 0x21u, 0xc6u, 0x68u, 0x42u, 0xf6u, 0xe9u, 0x6cu, 0x9au,
  0x67u, 0x0cu, 0x9cu, 0x61u, 0xabu, 0xd3u, 0x88u, 0xf0u, 0x6au, 0x51u, 0xa0u, 0xd2u, 0xd8u, 0x54u, 0x2fu, 0x68u,
  0x96u, 0x0fu, 0xa7u, 0x28u, 0xabu, 0x51u, 0x33u, 0xa3u, 0x6eu, 0xefu, 0x0bu, 0x6cu, 0x13u, 0x7au, 0x3bu, 0xe4u,
  0xbau, 0x3bu, 0xf0u, 0x50u, 0x7eu, 0xfbu, 0x2au, 0x98u, 0xa1u, 0xf1u, 0x65u, 0x1du, 0x39u, 0xafu, 0x01u, 0x76u,
  0x66u, 0xcau, 0x59u, 0x3eu, 0x82u, 0x43u, 0x0eu, 0x88u, 0x8cu, 0xeeu, 0x86u, 0x19u, 0x45u, 0x6fu, 0x9fu, 0xb4u,
  0x7du, 0x84u, 0xa5u, 0xc3u, 0x3bu, 0x8bu, 0x5eu, 0xbeu, 0xe0u, 0x6fu, 0x75u, 0xd8u, 0x85u, 0xc1u, 0x20u, 0x73u,
  0x40u, 0x1au, 0x44u, 0x9fu, 0x56u, 0xc1u, 0x6au, 0xa6u, 0x4eu, 0xd3u, 0xaau, 0x62u, 0x36u, 0x3fu, 0x77u, 0x06u,
  0x1bu, 0xfeu, 0xdfu, 0x72u, 0x42u, 0x9bu, 0x02u, 0x3du, 0x37u, 0xd0u, 0xd7u, 0x24u, 0xd0u, 0x0au, 0x12u, 0x48u,
  0xdbu, 0x0fu, 0xeau, 0xd3u, 0x49u, 0xf1u, 0xc0u, 0x9bu, 0x07u, 0x53u, 0x72u, 0xc9u, 0x80u, 0x99u, 0x1bu, 0x7bu,
}};


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

#include <iostream>

using namespace std;

/**
 * Print the Draupnir logo to cerr
 *
 */
static void showLogo() {
  cerr << "\n"
          "---------------------------\n"
          "   /\\                      \n"
          "   \\/  Draupnir v0.0.1     \n"
          "   /\\                      \n"
          "---------------------------\n"
          "\n";
}


int main(int argc, char *argv[]) {
  showLogo();

  cerr << "Arguments:" << endl;
  for (int i = 0; i < argc; i++) {
    cerr << "  " << i << ": " << argv[i] << endl;
  }
  cerr << endl;

  Draupnir::CrcSponge64 d = Draupnir::CrcSponge64Builder();

  while (true) {
    cout << d.squeeze();
  }
  return 0;
}

