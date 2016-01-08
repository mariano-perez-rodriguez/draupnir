#ifndef DRAUPNIR_ENVIRONMENT_H__
#define DRAUPNIR_ENVIRONMENT_H__

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <iterator>

#include "Sponge.h"
#include "vendor/value_ptr/value_ptr.h"


namespace Draupnir {

  /**
   * Stack-based execution environment for Draupnir
   *
   */
  class Environment {
    public:
      /**
       * Construct a new execution environment
       *
       * @param out  Ostream to use for output
       * @param err  Ostream to use for errors
       */
      Environment(std::ostream &out = std::cout, std::ostream &err = std::cerr) noexcept;

      /**
       * Copy constructor - defaulted
       *
       * @param other  Environment to copy
       */
      Environment(Environment const &other) noexcept = default;

      /**
       * Move constructor - defaulted
       *
       * @param other  Environment to move
       */
      Environment(Environment &&other) noexcept = default;

      /**
       * Assignment operator - defaulted
       *
       * @param other  Environment to assign
       * @return the copied Environment
       */
      Environment &operator=(Environment const &other) noexcept = default;

      /**
       * Move-assignment operator - defaulted
       *
       * @param other  Environment to move-assign
       * @return the copied Environment
       */
      Environment &operator=(Environment &&other) noexcept = default;

      /**
       * Destructor - defaulted
       *
       */
      ~Environment() noexcept = default;


      /**
       * Remove the given number of elements from the top of the stack
       *
       * @param n  Number of elements to remove
       * @return the resulting Environment
       */
      Environment &drop(std::size_t n = 1) noexcept;

      /**
       * Copy the given number of elements at the top of the stack the given number of times
       *
       * @param n  Number of times to copy
       * @param m  Number of elements to copy
       * @return the resulting Environment
       */
      Environment &copy(std::size_t n = 1, std::size_t m = 1) noexcept;

      /**
       * Move the given number of elements downwards from the top of the stack the given number of positions
       *
       * @param n  Number of elements to move
       * @param m  Number of positions to move them
       * @return the resulting Environment
       */
      Environment &sink(std::size_t n = 1, std::size_t m = 1) noexcept;


      /**
       * Generate the given number of raw bytes from the topmost Sponge
       *
       * @param count  Number of bytes to generate
       * @param hex  If true, generate the bytes as hex strings
       * @return the resulting Environment
       */
      Environment &raw(std::size_t count = 10, bool hex = false) noexcept;

      /**
       * Generate a natural number from 0 to the number given
       *
       * @param high  Maximum number to generate
       * @return the resulting Environment
       */
      Environment &natural(std::size_t high = 9) noexcept;

      /**
       * Generate a real number from 0.0 o the number given
       *
       * @param high  Maximum number to generate
       * @return the resulting Environment
       */
      Environment &real(long double high = 1.0l) noexcept;

      /**
       * Generate a permutation of the numbers between 0 and the given number
       *
       * @param highElem  Highest element to permute
       * @return the resulting Environment
       */
      Environment &permutation(std::size_t highElem = 9) noexcept;

      /**
       * Generate a cycle of the numbers between 0 and the given number
       *
       * @param highElem  Highest element to permute
       * @return the resulting Environment
       */
      Environment &cycle(std::size_t highElem = 9) noexcept;

      /**
       * Generate a derangement of the numbers between 0 and the given number
       *
       * @param highElem  Highest element to permute
       * @return the resulting Environment
       */
      Environment &derangement(std::size_t highElem = 9) noexcept;

      /**
       * Generate a sample of the given size, for the elements between 0 and the number given, using the given parts, either with or without replacements
       *
       * @param count  Number of samples to generate
       * @param highElem  Highest element to sample
       * @param parts  Part proportions to use
       * @param replacements  Whether to allow replacements or not
       * @return the resulting Environment
       */
      Environment &sample(std::size_t count = 1, std::size_t highElem = 9, std::vector<std::size_t> parts = {}, bool replacements = true) noexcept;


      // Environment &create(std::size_t width = 64, unsigned long long generator = 0ull, unsigned long long start = ~0ull, unsigned long long mask = ~0ull, )

      /**
       * Unserialize the given state and push it to the top of the stack
       *
       * @param state  State to unserialize
       * @return the resulting Environment
       */
      Environment &load(std::string &state);

      /**
       * Unserialize the given number of lines in the given file
       *
       * @param file  File to read state serializations from
       * @param count  Number of lines to deserialize (all if 0)
       * @return the resulting Environment
       */
      Environment &open(std::string &file, std::size_t count = 0);

      /**
       * Reset the given number of Sponges from the top of the stack to their starting states
       *
       * @param n  Number of Sponges to reset
       * @return the resulting Environment
       */
      Environment &reset(std::size_t n = 1) noexcept;

      /**
       * Soak the given data to the given number of Sponges from the top of the stack
       *
       * @param data  Data to soak
       * @param n  Number of Sponges to soak
       * @return the resulting Environment
       */
      Environment &soak(std::string &data, std::size_t n = 1) noexcept;

      /**
       *
       *
       */
      Environment &reseed(std::size_t m = 1, std::size_t n = 1, bool independent = false) noexcept;

      /**
       * Step the given number of Sponges from the top of the stack for the given number of steps
       *
       * @param n  The number of Sponges to step
       * @param m  The number of steps to take
       * @return the resulting Environment
       */
      Environment &step(std::size_t n = 1, std::size_t m = 1) noexcept;


      /**
       * Write the given data to the output stream
       *
       * @param what  What to write to the output stream
       * @return the resulting Environment
       */
      Environment &echo(std::string &what) noexcept;

      /**
       * Flushes the stack and dumps its representation to serr
       *
       * @param silent  If set, don't dump to serr
       * @return the resulting Environment
       */
      Environment &exit(bool silent = false) noexcept;

    protected:
      /**
       * Sponge stack
       *
       */
      std::vector<value_ptr<Sponge>> stack;

      /**
       * Using declaration for stack iterator offsets
       *
       */
      using stack_offset_type = typename std::iterator_traits<std::vector<value_ptr<Sponge>>::iterator>::difference_type;

      /**
       * Output stream
       *
       */
      std::ostream &sout;

      /**
       * Errors stream
       *
       */
      std::ostream &serr;
  };

}

#endif /* DRAUPNIR_ENVIRONMENT_H__ */

