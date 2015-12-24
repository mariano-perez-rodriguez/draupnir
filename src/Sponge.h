#ifndef DRAUPNIR_SPONGE_H__
#define DRAUPNIR_SPONGE_H__

#include <cstdint>

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

}

#endif /* DRAUPNIR_SPONGE_H__ */

