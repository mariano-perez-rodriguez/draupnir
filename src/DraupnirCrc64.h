#ifndef DRAUPNIR_CRC_64_H_
#define DRAUPNIR_CRC_64_H_

#include "Draupnir.h"

#include <cstdint>
#include <memory>


namespace Draupnir {
  // forward declaration
  class Crc64;
  class Crc64Builder;

  /**
   * Crc64 named constructor head
   *
   * This is a user-friendly way of constructing a Crc64 object.
   *
   * @return the Crc64Builder to use for construction
   */
  Crc64Builder crc64() noexcept;

  /**
   * Builder for the Crc64 class implementing the named-parameter-idiom
   *
   */
  class Crc64Builder {
    public:
      /**
       * Default constructor
       *
       */
      Crc64Builder() noexcept;

      /**
       * Copy constructor (defaulted) - should not be needed either way
       *
       */
      Crc64Builder(Crc64Builder const &other) noexcept = default;

      /**
       * Move constructor (defaulted) - should not be needed either way
       *
       */
      Crc64Builder(Crc64Builder &&other) noexcept = default;

      /**
       * Assignment operator (defaulted) - should not be needed either way
       *
       * @return a reference to the current object
       */
      Crc64Builder &operator=(Crc64Builder const &other) noexcept = default;

      /**
       * Move-assignment operator (defaulted) - should not be needed either way
       *
       * @return a reference to the current object
       */
      Crc64Builder &operator=(Crc64Builder &&other) noexcept = default;

      /**
       * Virtual destructor (defaulted)
       *
       */
      virtual ~Crc64Builder() noexcept = default;

      /**
       * Conversion operator to create a Crc64
       *
       * @return the constructed Crc64
       */
      operator Crc64() const noexcept;

      /**
       * Virtual copy constructor - should not be needed either way
       *
       * @return the constructed object
       */
      virtual Crc64Builder *clone() const noexcept;

      /**
       * Virtual default constructor - should not be needed either way
       *
       * @return the constructed object
       */
      virtual Crc64Builder *create() const noexcept;

      /**
       * Generator parameter materialization
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
       * @return a reference to the current object
       */
      Crc64Builder &generator(std::uint64_t __generator) noexcept;

      /**
       * Initial value parameter materialization
       *
       * @param __initialValue  Initial value to use for crc, defaults to all-1s
       * @return a reference to the current object
       */
      Crc64Builder &initialValue(std::uint64_t __initialValue) noexcept;

      /**
       * Xor value parameter materialization
       *
       * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
       * @return a reference to the current object
       */
      Crc64Builder &xorValue(std::uint64_t __xorValue) noexcept;

      /**
       * Soaking rounds parameter materialization
       *
       * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
       * @return a reference to the current object
       */
      Crc64Builder &soakingRounds(std::size_t __soakingRounds) noexcept;

      /**
       * Squeezing rounds parameter materialization
       *
       * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
       * @return a reference to the current object
       */
      Crc64Builder &squeezingRounds(std::size_t __squeezingRounds) noexcept;

      /**
       * Initial state parameter materialization
       *
       * @param __initialState  Initial state to use, defaults to pi
       * @return a reference to the current object
       */
      Crc64Builder &initialState(std::uint8_t const __initialState[512]) noexcept;

      /**
       * Force the building of a Draupnir RNG (useful for "auto" type specifiers)
       *
       * @return the constructed Crc64 object
       */
      Crc64 build() noexcept;

    protected:
      /**
       * Generator parameter
       *
       */
      std::uint64_t _generator;

      /**
       * Initial value parameter
       *
       */
      std::uint64_t _initialValue;

      /**
       * Xor value parameter
       *
       */
      std::uint64_t _xorValue;

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
      std::uint8_t _initialState[512];
  };

  /**
   * Class implementing the Crc64 RNG
   *
   */
  class Crc64 {
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
        std::uint64_t generator;

        /**
         * Current running crc value
         *
         */
        std::uint64_t crc;

        /**
         * CRC initialization value
         *
         */
        std::uint64_t initialValue;

        /**
         * CRC xor value
         *
         */
        std::uint64_t xorValue;

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
        std::uint64_t initialState[64];

        /**
         * Internal state array
         *
         */
        std::uint64_t state[64];
      };

      /**
       * Crc64 constructor
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
       * @param __initialValue  Initial value to use for crc, defaults to all-1s
       * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
       * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
       * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
       * @param __initialState  Initial state to use, defaults to pi
       */
      Crc64(std::uint64_t __generator = 0x42f0e1eba9ea3693ull, std::uint64_t __initialValue = ~0ull, std::uint64_t __xorValue = ~0ull, std::size_t __soakingRounds = 8, std::size_t __squeezingRounds = 1, std::uint8_t const __initialState[512] = pi) noexcept;

      /**
       * Copy constructor (defaulted)
       *
       */
      Crc64(Crc64 const &other) noexcept = default;

      /**
       * Move constructor (defaulted)
       *
       */
      Crc64(Crc64 &&other) noexcept = default;

      /**
       * Assignment operator (defaulted)
       *
       * @return a reference to the current object
       */
      Crc64 &operator=(Crc64 const &other) noexcept = default;

      /**
       * Move-assignment operator (defaulted)
       *
       * @return a reference to the current object
       */
      Crc64 &operator=(Crc64 &&other) noexcept = default;

      /**
       * Virtual destructor (defaulted)
       *
       */
      virtual ~Crc64() noexcept = default;

      /**
       * Virtual copy constructor
       *
       * @return the constructed object
       */
      virtual Crc64 *clone() const noexcept;

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
      virtual Crc64 *create(std::uint64_t __generator = 0x42f0e1eba9ea3693ull, std::uint64_t __initialValue = ~0ull, std::uint64_t __xorValue = ~0ull, std::size_t __soakingRounds = 8, std::size_t __squeezingRounds = 1, std::uint8_t const __initialState[512] = pi) const noexcept;

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
      Crc64 &putBytes(std::uint8_t const *data, std::size_t len) noexcept;

      /**
       * Apply a transformation step
       *
       * This method applies a given number of rounds of the transformation
       * function to the Draupnir sponge.
       *
       * @param count  Number of rounds to apply, defaults to 1
       * @return the transformed object
       */
      Crc64 &step(std::size_t count = 1) noexcept;

      /**
       * Reset the Draupnir sponge
       *
       * This method resets the Draupnir sponge to the given state
       *
       * @param __initialState  State to reset to, defaults to pi
       * @return the reset object
       */
      Crc64 &reset(std::uint8_t const __initialState[512] = Draupnir::pi) noexcept;

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
       * @return the squeezed 64 bits
       */
      std::uint64_t squeeze() noexcept;

      /**
       * Soak a 64 bit value into the sponge
       *
       * @param block  64 bits to soak into the sponge
       */
      void soak(std::uint64_t block) noexcept;

      /**
       * Build a CRC64 lookup table
       *
       * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted
       * @return a new[]-allocated lookup table
       */
      static std::uint64_t *buildTable(std::uint64_t __generator) noexcept;

      /**
       * Create a new[] state and copy the given one
       *
       * @param __state  State to copy
       * @return a new[]-allocated copy of the given state
       */
      static std::uint64_t *copyState(std::uint64_t const *__state) noexcept;

    private:
      /**
       * Generator polynomial to use
       *
       */
      std::uint64_t _generator;

      /**
       * Current running crc value
       *
       */
      std::uint64_t _crc;

      /**
       * Value to initialize the crc to
       *
       */
      std::uint64_t _initialValue;

      /**
       * Value to xor in order to get the crc's output
       *
       */
      std::uint64_t _xorValue;

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
      std::shared_ptr<std::uint64_t> _initialState;

      /**
       * Main internal state
       *
       */
      std::uint64_t _state[64];

      /**
       * Output buffer
       *
       */
      std::uint8_t _buffer[8];

      /**
       * Remaining bytes in the output buffer
       *
       */
      std::size_t _remaining;

      /**
       * CRC64 lookup table (shared among all siblings of this object)
       *
       */
      std::shared_ptr<std::uint64_t> _crcTable;
  };
}

#endif /* DRAUPNIR_CRC_64_H_ */

