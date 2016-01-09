#include "Environment.h"

#include <algorithm>
#include <iomanip>
#include <limits>
#include <fstream>

#include "Random.h"


namespace Draupnir {

/**
 * Construct a new execution environment
 *
 * @param out  Ostream to use for output
 * @param err  Ostream to use for errors
 */
Environment::Environment(std::ostream &out, std::ostream &err) noexcept : stack{}, sout{out}, serr{err} {}


/**
 * Remove the given number of elements from the top of the stack
 *
 * @param n  Number of elements to remove
 * @return the resulting Environment
 */
Environment &Environment::drop(std::size_t n) noexcept {
  std::size_t nn = std::max(0ul, std::min(stack.size(), n));
  if (0 != nn) {
    stack.erase(stack.end() - static_cast<stack_offset_type>(nn), stack.end());
  }
  return *this;
}

/**
 * Copy the given number of elements at the top of the stack the given number of times
 *
 * @param n  Number of times to copy
 * @param m  Number of elements to copy
 * @return the resulting Environment
 */
Environment &Environment::copy(std::size_t n, std::size_t m) noexcept {
  std::size_t mm = std::max(0ul, std::min(stack.size(), m));
  if (0 != mm) {
    for (std::size_t i = 0; i < n; i++) {
      for (std::size_t j = 0; j < mm; j++) {
        stack.push_back(value_ptr<Sponge>(stack[stack.size() - mm + j]->clone()));
      }
    }
  }
  return *this;
}

/**
 * Move the given number of elements downwards from the top of the stack the given number of positions
 *
 * @param n  Number of elements to move
 * @param m  Number of positions to move them
 * @return the resulting Environment
 */
Environment &Environment::sink(std::size_t n, std::size_t m) noexcept {
  n = std::min(n, stack.size());
  m = std::min(m, stack.size() - n);

  if (0 != n && 0 != m) {
    std::rotate(
        stack.end() - static_cast<stack_offset_type>(n + m),
        stack.end() - static_cast<stack_offset_type>(n    ),
        stack.end()
    );
  }

  return *this;
}


/**
 * Generate the given number of raw bytes from the topmost Sponge
 *
 * @param count  Number of bytes to generate
 * @param hex  If true, generate the bytes as hex strings
 * @return the resulting Environment
 */
Environment &Environment::raw(std::size_t count, bool hex) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0);
  if (hex) { sout << std::hex; }
  while (count--) {
    sout << stack.back()->squeeze();
  }
  sout.flags(flags);

  return *this;
}

/**
 * Generate a natural number from 0 to the number given
 *
 * @param high  Maximum number to generate
 * @return the resulting Environment
 */
Environment &Environment::natural(std::size_t high) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0) << std::dec << Random::natural<std::uint64_t>(*stack.back(), high) << std::endl;
  sout.flags(flags);

  return *this;
}

/**
 * Generate a real number from 0.0 o the number given
 *
 * @param high  Maximum number to generate
 * @return the resulting Environment
 */
Environment &Environment::real(long double high) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::fixed
       << std::setw(0)
       << std::setprecision(std::numeric_limits<long double>::digits10 + 1)
       << std::dec
       << (Random::real(*stack.back()) * high)
       << std::endl;
  sout.flags(flags);

  return *this;
}

/**
 * Generate a permutation of the numbers between 0 and the given number
 *
 * @param highElem  Highest element to permute
 * @return the resulting Environment
 */
Environment &Environment::permutation(std::size_t highElem) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0) << std::dec;
  for (std::size_t x : Random::permutation(*stack.back(), highElem)) {
    sout << x << " ";
  }
  sout << std::endl;
  sout.flags(flags);

  return *this;
}

/**
 * Generate a cycle of the numbers between 0 and the given number
 *
 * @param highElem  Highest element to permute
 * @return the resulting Environment
 */
Environment &Environment::cycle(std::size_t highElem) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0) << std::dec;
  for (std::size_t x : Random::cycle(*stack.back(), highElem)) {
    sout << x << " ";
  }
  sout << std::endl;
  sout.flags(flags);

  return *this;
}

/**
 * Generate a derangement of the numbers between 0 and the given number
 *
 * @param highElem  Highest element to permute
 * @return the resulting Environment
 */
Environment &Environment::derangement(std::size_t highElem) noexcept {
  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0) << std::dec;
  for (std::size_t x : Random::derangement(*stack.back(), highElem)) {
    sout << x << " ";
  }
  sout << std::endl;
  sout.flags(flags);

  return *this;
}

/**
 * Generate a sample of the given size, for the elements between 0 and the number given, using the given parts, either with or without replacements
 *
 * @param count  Number of samples to generate
 * @param highElem  Highest element to sample
 * @param parts  Part proportions to use
 * @param replacements  Whether to allow replacements or not
 * @return the resulting Environment
 */
Environment &Environment::sample(std::size_t count, std::size_t highElem, std::vector<std::size_t> parts, bool replacements) noexcept {
  std::vector<std::size_t> s;

  if (replacements) {
    if (parts.empty()) {
      s = Random::uniformSampleWithReplacement(*stack.back(), highElem, count);
    } else {
      s = Random::nonUniformSampleWithReplacement(*stack.back(), parts, count);
    }
  } else {
    if (parts.empty()) {
      s = Random::uniformSampleWithoutReplacement(*stack.back(), highElem, count);
    } else {
      s = Random::nonUniformSampleWithoutReplacement(*stack.back(), parts, count);
    }
  }

  std::ios::fmtflags flags(sout.flags());
  sout << std::setw(0) << std::dec;
  for (std::size_t x : s) {
    sout << x << " ";
  }
  sout << std::endl;
  sout.flags(flags);

  return *this;
}


/**
 * Unserialize the given state and push it to the top of the stack
 *
 * @param state  State to unserialize
 * @return the resulting Environment
 */
Environment &Environment::load(std::string &state) {
  // ???
}

/**
 * Unserialize the given number of lines in the given file
 *
 * @param file  File to read state serializations from
 * @param count  Number of lines to deserialize (all if 0)
 * @return the resulting Environment
 */
Environment &Environment::open(std::string &file, std::size_t count) {
  std::ifstream input(file);
  std::string line;

  while (std::getline(input, line)) {
    load(line);
  }

  return *this;
}

/**
 * Reset the given number of Sponges from the top of the stack to their starting states
 *
 * @param n  Number of Sponges to reset
 * @return the resulting Environment
 */
Environment &Environment::reset(std::size_t n) noexcept {
  n = std::min(n, stack.size());

  std::for_each(stack.rbegin(), stack.rbegin() + static_cast<stack_offset_type>(n), [](auto &x){ x->reset(); });

  return *this;
}

/**
 * Soak the given data to the given number of Sponges from the top of the stack
 *
 * @param data  Data to soak
 * @param n  Number of Sponges to soak
 * @return the resulting Environment
 */
Environment &Environment::soak(std::string &data, std::size_t n) noexcept {
  n = std::min(n, stack.size());

  std::for_each(stack.rbegin(), stack.rbegin() + static_cast<stack_offset_type>(n), [&data](auto &x){ x->soak(data); });

  return *this;
}

/**
 *
 *
 */
Environment &Environment::reseed(std::size_t m, std::size_t n, bool independent) noexcept {
  // ???
}

/**
 * Step the given number of Sponges from the top of the stack for the given number of steps
 *
 * @param n  The number of Sponges to step
 * @param m  The number of steps to take
 * @return the resulting Environment
 */
Environment &Environment::step(std::size_t n, std::size_t m) noexcept {
  n = std::min(n, stack.size());

  if (0 != m) {
    std::for_each(stack.rbegin(), stack.rbegin() + static_cast<stack_offset_type>(n), [m](auto &x){ x->step(m); });
  }

  return *this;
}


/**
 * Write the given data to the output stream
 *
 * @param what  What to write to the output stream
 * @return the resulting Environment
 */
Environment &Environment::echo(std::string &what) noexcept {
  sout << what;

  return *this;
}

/**
 * Flushes the stack and dumps its representation to serr
 *
 * @param silent  If set, don't dump to serr
 * @return the resulting Environment
 */
Environment &Environment::exit(bool silent) noexcept {
  if (!silent) {
    for (auto &s : stack) {
      serr << s->dump() << std::endl;
    }
  }

  return *this;
}

}

