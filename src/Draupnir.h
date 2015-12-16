#ifndef DRAUPNIR_H_
#define DRAUPNIR_H_

#include <cstdint>
#include <memory>

// forward declarations
class Draupnir;
class DraupnirCrc64Builder;
class DraupnirCrc64;

/**
 * Draupnir RNG static "distributor" class
 *
 * This class holds common constants and static methods for all the Draupnir
 * hierarchy.
 *
 */
class Draupnir {
  public:
    /**
     * DraupnirCrc64 named constructor head
     *
     * This is the only accessible way of constructing a DraupnirCrc64 object.
     *
     * @return the DraupnirCrc64Builder to use for construction
     */
    static DraupnirCrc64Builder crc64() noexcept;

    /**
     * Initial state consisting of all 0s
     *
     */
    static const std::uint8_t zeros[512];

    /**
     * Initial state consisting of all 1s
     *
     */
    static const std::uint8_t ones[512];

    /**
     * Initial state consisting of the decimal expansion of e
     *
     * Here, "e" is the Euler constant, the base for natural logarithms.
     *
     */
    static const std::uint8_t e[512];

    /**
     * Initial state consisting of the decimal expansion of pi
     *
     * Here, "pi" is the ratio of the diameter to the circumference.
     *
     */
    static const std::uint8_t pi[512];

    /**
     * Initial state consisting of the decimal expansion of gamma
     *
     * Here, "gamma" is the Euler-Mascheroni constant.
     *
     */
    static const std::uint8_t gamma[512];

    /**
     * Initial state consisting of the decimal expansion of omega
     *
     * Here, "gamma" is W(1), where "W" is Lambert's W function.
     *
     */
    static const std::uint8_t omega[512];

    /**
     * Initial state consisting of the decimal expansion of 1/e
     *
     * Here, "e" is the Euler constant, the base for natural logarithms.
     *
     */
    static const std::uint8_t invE[512];

    /**
     * Initial state consisting of the decimal expansion of 1/pi
     *
     * Here, "pi" is the ratio of the diameter to the circumference.
     *
     */
    static const std::uint8_t invPi[512];

    /**
     * Initial state consisting of the decimal expansion of 1/gamma
     *
     * Here, "gamma" is the Euler-Mascheroni constant.
     *
     */
    static const std::uint8_t invGamma[512];

    /**
     * Initial state consisting of the decimal expansion of 1/omega
     *
     * Here, "gamma" is W(1), where "W" is Lambert's W function.
     *
     */
    static const std::uint8_t invOmega[512];

    /**
     * Initial state consisting of the decimal expansion of sqrt(2)
     *
     */
    static const std::uint8_t sqrt2[512];

    /**
     * Initial state consisting of the decimal expansion of sqrt(3)
     *
     */
    static const std::uint8_t sqrt3[512];

    /**
     * Initial state consisting of the decimal expansion of sqrt(5)
     *
     */
    static const std::uint8_t sqrt5[512];

    /**
     * Initial state consisting of the decimal expansion of sqrt(7)
     *
     */
    static const std::uint8_t sqrt7[512];

    /**
     * Initial state consisting of the decimal expansion of sqrt(11)
     *
     */
    static const std::uint8_t sqrt11[512];

    /**
     * Initial state consisting of the decimal expansion of 1/sqrt(2)
     *
     */
    static const std::uint8_t invSqrt2[512];

    /**
     * Initial state consisting of the decimal expansion of 1/sqrt(3)
     *
     */
    static const std::uint8_t invSqrt3[512];

    /**
     * Initial state consisting of the decimal expansion of 1/sqrt(5)
     *
     */
    static const std::uint8_t invSqrt5[512];

    /**
     * Initial state consisting of the decimal expansion of 1/sqrt(7)
     *
     */
    static const std::uint8_t invSqrt7[512];

    /**
     * Initial state consisting of the decimal expansion of 1/sqrt(11)
     *
     */
    static const std::uint8_t invSqrt11[512];
};

/**
 * Builder for the DraupnirCrc64 class implementing the named-parameter-idiom
 *
 */
class DraupnirCrc64Builder {
  // needed in order for Draupnir to call the protected constructor
  friend Draupnir;
  // needed in order for DraupnirCrc64 to inspect the protected members
  friend DraupnirCrc64;

  public:
    /**
     * Copy constructor (defaulted) - should not be needed either way
     *
     */
    DraupnirCrc64Builder(const DraupnirCrc64Builder &other) noexcept = default;

    /**
     * Move constructor (defaulted) - should not be needed either way
     *
     */
    DraupnirCrc64Builder(DraupnirCrc64Builder &&other) noexcept = default;

    /**
     * Assignment operator (defaulted) - should not be needed either way
     *
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &operator=(const DraupnirCrc64Builder &other) noexcept = default;

    /**
     * Move-assignment operator (defaulted) - should not be needed either way
     *
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &operator=(DraupnirCrc64Builder &&other) noexcept = default;

    /**
     * Virtual destructor (defaulted)
     *
     */
    virtual ~DraupnirCrc64Builder() noexcept = default;

    /**
     * Virtual copy constructor - should not be needed either way
     *
     * @return the constructed object
     */
    virtual DraupnirCrc64Builder *clone() const noexcept;

    /**
     * Virtual default constructor - should not be needed either way
     *
     * @return the constructed object
     */
    virtual DraupnirCrc64Builder *create() const noexcept;

    /**
     * Generator parameter materialization
     *
     * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &generator(std::uint64_t __generator) noexcept;

    /**
     * Initial value parameter materialization
     *
     * @param __initialValue  Initial value to use for crc, defaults to all-1s
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &initialValue(std::uint64_t __initialValue) noexcept;

    /**
     * Xor value parameter materialization
     *
     * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &xorValue(std::uint64_t __xorValue) noexcept;

    /**
     * Soaking rounds parameter materialization
     *
     * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &soakingRounds(std::size_t __soakingRounds) noexcept;

    /**
     * Squeezing rounds parameter materialization
     *
     * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &squeezingRounds(std::size_t __squeezingRounds) noexcept;

    /**
     * Initial state parameter materialization
     *
     * @param __initialState  Initial state to use, defaults to pi
     * @return a reference to the current object
     */
    DraupnirCrc64Builder &initialState(std::uint8_t const __initialState[512]) noexcept;

  protected:
    /**
     * Protected default constructor
     *
     * The constructor is protected to only allow construction through Draupnir.
     *
     */
    DraupnirCrc64Builder() noexcept;

  private:
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
 * Class implementing the DraupnirCrc64 RNG
 *
 */
class DraupnirCrc64 {
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
       * Internal state array
       *
       */
      std::uint64_t state[64];
    };

    /**
     * Implicit conversion constructor to implement named-constructor-with-named-parameters idiom
     *
     * @param builder  A DraupnirCrc64Builder object to use for parameters
     */
    DraupnirCrc64(const DraupnirCrc64Builder &builder) noexcept;

    /**
     * Copy constructor (defaulted)
     *
     */
    DraupnirCrc64(const DraupnirCrc64 &other) noexcept = default;

    /**
     * Move constructor (defaulted)
     *
     */
    DraupnirCrc64(DraupnirCrc64 &&other) noexcept = default;

    /**
     * Assignment operator (defaulted)
     *
     * @return a reference to the current object
     */
    DraupnirCrc64 &operator=(const DraupnirCrc64 &other) noexcept = default;

    /**
     * Move-assignment operator (defaulted)
     *
     * @return a reference to the current object
     */
    DraupnirCrc64 &operator=(DraupnirCrc64 &&other) noexcept = default;

    /**
     * Virtual destructor (defaulted)
     *
     */
    virtual ~DraupnirCrc64() noexcept = default;

    /**
     * Virtual copy constructor
     *
     * @return the constructed object
     */
    virtual DraupnirCrc64 *clone() const noexcept;

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
    virtual DraupnirCrc64 *create(std::uint64_t __generator = 0x42f0e1eba9ea3693ull, std::uint64_t __initialValue = ~0ull, std::uint64_t __xorValue = ~0ull, std::size_t __soakingRounds = 8, std::size_t __squeezingRounds = 1, const std::uint8_t __initialState[512] = Draupnir::pi) const noexcept;

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
    DraupnirCrc64 &putBytes(const std::uint8_t *data, std::size_t len) noexcept;

    /**
     * Apply a transformation step
     *
     * This method applies a given number of rounds of the transformation
     * function to the Draupnir sponge.
     *
     * @param count  Number of rounds to apply, defaults to 1
     * @return the transformed object
     */
    DraupnirCrc64 &step(std::size_t count = 1) noexcept;

    /**
     * Reset the Draupnir sponge
     *
     * This method resets the Draupnir sponge to the given state
     *
     * @param __initialState  State to reset to, defaults to pi
     * @return the reset object
     */
    DraupnirCrc64 &reset(const std::uint8_t __initialState[512] = Draupnir::pi) noexcept;

    /**
     * Extract a state description structure
     *
     * @return the state description structure extracted form the current object
     */
    state_t state() const noexcept __attribute__((pure)) ;

  protected:
    /**
     * DraupnirCrc64 constructor
     *
     * @param __generator  Generator polynomial to use, little endian, with its most significant bit omitted, defaults to ECMA
     * @param __initialValue  Initial value to use for crc, defaults to all-1s
     * @param __xorValue  Value to XOR with the crc to obtain the result, defaults to all-1s
     * @param __soakingRounds  Number of transformation rounds to apply after soaking, defaults to 8
     * @param __squeezingRounds  Rounds  Number of transformation rounds to apply after squeezing, defaults to 1
     * @param __initialState  Initial state to use, defaults to pi
     */
    DraupnirCrc64(std::uint64_t __generator, std::uint64_t __initialValue, std::uint64_t __xorValue, std::size_t __soakingRounds, std::size_t __squeezingRounds, const std::uint8_t __initialState[512]) noexcept;

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
    std::shared_ptr<uint64_t> _crcTable;
};

#endif /* DRAUPNIR_H_ */

