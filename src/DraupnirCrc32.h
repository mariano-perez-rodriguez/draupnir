#ifndef DRAUPNIR_CRC_32_H_
#define DRAUPNIR_CRC_32_H_

#include "Draupnir.h"

#include <cstdint>
#include <memory>


namespace Draupnir {
  // forward declaration
  class Crc32;
  class Crc32Builder;

  /**
   * Crc32 named constructor head
   *
   * This is a user-friendly way of constructing a Crc32 object.
   *
   * @return the Crc32Builder to use for construction
   */
  Crc32Builder crc32() noexcept;

  /**
   * Builder for the Crc32 class implementing the named-parameter-idiom
   *
   */
  class Crc32Builder {
    public:
      /**
       * Default constructor
       *
       */
      Crc32Builder() noexcept;

      /**
       * Copy constructor (defaulted) - should not be needed either way
       *
       */
      Crc32Builder(Crc32Builder const &other) noexcept = default;

      /**
       * Move constructor (defaulted) - should not be needed either way
       *
       */
      Crc32Builder(Crc32Builder &&other) noexcept = default;

      /**
       * Assignment operator (defaulted) - should not be needed either way
       *
       * @return a reference to the current object
       */
      Crc32Builder &operator=(Crc32Builder const &other) noexcept = default;

      /**
       * Move-assignment operator (defaulted) - should not be needed either way
       *
       * @return a reference to the current object
       */
      Crc32Builder &operator=(Crc32Builder &&other) noexcept = default;

      /**
       * Virtual destructor (defaulted)
       *
       */
      virtual ~Crc32Builder() noexcept = default;

      /**
       * Conversion operator to create a Crc32
       *
       * @return the constructed Crc32
       */
      operator Crc32() const noexcept;

      /**
       * Virtual copy constructor - should not be needed either way
       *
       * @return the constructed object
       */
      virtual Crc32Builder *clone() const noexcept;

      /**
       * Virtual default constructor - should not be needed either way
       *
       * @return the constructed object
       */
      virtual Crc32Builder *create() const noexcept;

      /**
       * Generator parameter materialization
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
       * @return a reference to the current object
       */
      Crc32Builder &generator(std::uint32_t __generator) noexcept;

      /**
       * Initial value parameter materialization
       *
       * @param __initialValue  Initial value to use for crc, defaults to all-1s
       * @return a reference to the current object
       */
      Crc32Builder &initialValue(std::uint32_t __initialValue) noexcept;

      /**
       * Xor value parameter materialization
       *
       * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
       * @return a reference to the current object
       */
      Crc32Builder &xorValue(std::uint32_t __xorValue) noexcept;

      /**
       * Soaking rounds parameter materialization
       *
       * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
       * @return a reference to the current object
       */
      Crc32Builder &soakingRounds(std::size_t __soakingRounds) noexcept;

      /**
       * Squeezing rounds parameter materialization
       *
       * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
       * @return a reference to the current object
       */
      Crc32Builder &squeezingRounds(std::size_t __squeezingRounds) noexcept;

      /**
       * Initial state parameter materialization
       *
       * @param __initialState  Initial state to use, defaults to pi
       * @return a reference to the current object
       */
      Crc32Builder &initialState(std::uint8_t const __initialState[128]) noexcept;

      /**
       * Force the building of a Draupnir RNG (useful for "auto" type specifiers)
       *
       * @return the constructed Crc32 object
       */
      Crc32 build() noexcept;

    protected:
      /**
       * Generator parameter
       *
       */
      std::uint32_t _generator;

      /**
       * Initial value parameter
       *
       */
      std::uint32_t _initialValue;

      /**
       * Xor value parameter
       *
       */
      std::uint32_t _xorValue;

      /**
       * Soaking rounds parameter
       *
       */
      std::size_t _soakingRounds;

      /**
       * Squeezing rounds parameter
       *
       */
      std::size_t _squeezingRounds;

      /**
       * Initial state parameter
       *
       */
      std::uint8_t _initialState[128];
  };

  /**
   * Class implementing the Crc32 RNG
   *
   */
  class Crc32 {
    public:
      /**
       * State description structure
       *
       */
      struct state_t {
        /**
         * Generator polynomial
         *
         */
        std::uint32_t generator;

        /**
         * Current running crc value
         *
         */
        std::uint32_t crc;

        /**
         * CRC initialization value
         *
         */
        std::uint32_t initialValue;

        /**
         * CRC xor value
         *
         */
        std::uint32_t xorValue;

        /**
         * Number of transformation rounds to apply on soaking
         *
         */
        std::size_t soakingRounds;

        /**
         * Number of transformation rounds to apply on squeezing
         *
         */
        std::size_t squeezingRounds;

        /**
         * Initial internal state array
         *
         */
        std::uint32_t initialState[32];

        /**
         * Internal state array
         *
         */
        std::uint32_t state[32];
      };

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
      Crc32(std::uint32_t __generator = 0x04c11db7u, std::uint32_t __initialValue = ~0u, std::uint32_t __xorValue = ~0u, std::size_t __soakingRounds = 8, std::size_t __squeezingRounds = 1, std::uint8_t const __initialState[128] = pi) noexcept;

      /**
       * Copy constructor (defaulted)
       *
       */
      Crc32(Crc32 const &other) noexcept = default;

      /**
       * Move constructor (defaulted)
       *
       */
      Crc32(Crc32 &&other) noexcept = default;

      /**
       * Assignment operator (defaulted)
       *
       * @return a reference to the current object
       */
      Crc32 &operator=(Crc32 const &other) noexcept = default;

      /**
       * Move-assignment operator (defaulted)
       *
       * @return a reference to the current object
       */
      Crc32 &operator=(Crc32 &&other) noexcept = default;

      /**
       * Virtual destructor (defaulted)
       *
       */
      virtual ~Crc32() noexcept = default;

      /**
       * Virtual copy constructor
       *
       * @return the constructed object
       */
      virtual Crc32 *clone() const noexcept;

      /**
       * Virtual default constructor
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
       * @param __initialValue  Initial value to use for crc, defaults to all-1s
       * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
       * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
       * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
       * @param __initialState  Initial state to use, defaults to pi
       * @return the constructed object
       */
      virtual Crc32 *create(std::uint32_t __generator = 0x04c11db7u, std::uint32_t __initialValue = ~0u, std::uint32_t __xorValue = ~0u, std::size_t __soakingRounds = 8, std::size_t __squeezingRounds = 1, std::uint8_t const __initialState[128] = pi) const noexcept;

      /**
       * Extract a byte from the RNG
       *
       * This method squeezes the Draupnir sponge and extracts a byte from it.
       *
       * @return the byte extracted
       */
      std::uint8_t getByte() noexcept;

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
      Crc32 &putBytes(std::uint8_t const *data, std::size_t len) noexcept;

      /**
       * Apply a transformation step
       *
       * This method applies a given number of rounds of the transformation
       * function to the Draupnir sponge.
       *
       * @param count  Number of rounds to apply, defaults to 1
       * @return the transformed object
       */
      Crc32 &step(std::size_t count = 1) noexcept;

      /**
       * Reset the Draupnir sponge
       *
       * This method resets the Draupnir sponge to the given state
       *
       * @param __initialState  State to reset to, defaults to pi
       * @return the reset object
       */
      Crc32 &reset(std::uint8_t const __initialState[128] = Draupnir::pi) noexcept;

      /**
       * Extract a state description structure
       *
       * @return the state description structure extracted form the current object
       */
      state_t state() const noexcept __attribute__((pure)) ;

    protected:
      /**
       * Apply the transformation function to the Draupnir sponge
       *
       */
      void transform() noexcept;

      /**
       * Squeeze the Draupnir sponge
       *
       * @return the squeezed 32 bits
       */
      std::uint32_t squeeze() noexcept;

      /**
       * Soak a 32 bit value into the sponge
       *
       * @param block  32 bits to soak into the sponge
       */
      void soak(std::uint32_t block) noexcept;

      /**
       * Build a CRC32 lookup table
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted
       * @return a new[]-allocated lookup table
       */
      static std::uint32_t *buildTable(std::uint32_t __generator) noexcept;

      /**
       * Create a new[] state and copy the given one
       *
       * @param __state  State to copy
       * @return a new[]-allocated copy of the given state
       */
      static std::uint32_t *copyState(std::uint32_t const *__state) noexcept;

    private:
      /**
       * Generator polynomial to use
       *
       */
      std::uint32_t _generator;

      /**
       * Current running crc value
       *
       */
      std::uint32_t _crc;

      /**
       * Value to initialize the crc to
       *
       */
      std::uint32_t _initialValue;

      /**
       * Value to xor in order to get the crc's output
       *
       */
      std::uint32_t _xorValue;

      /**
       * Number of transformation rounds to apply when soaking
       *
       */
      std::size_t _soakingRounds;

      /**
       * Number of transformation rounds to apply when squeezing
       *
       */
      std::size_t _squeezingRounds;

      /**
       * Initial internal state
       *
       */
      std::shared_ptr<std::uint32_t> _initialState;

      /**
       * Main internal state
       *
       */
      std::uint32_t _state[32];

      /**
       * Output buffer
       *
       */
      std::uint8_t _buffer[4];

      /**
       * Remaining bytes in the output buffer
       *
       */
      std::size_t _remaining;

      /**
       * CRC32 lookup table (shared among all siblings of this object)
       *
       */
      std::shared_ptr<std::uint32_t> _crcTable;
  };
}

#endif /* DRAUPNIR_CRC_32_H_ */

