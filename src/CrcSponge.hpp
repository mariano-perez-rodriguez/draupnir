#ifndef DRAUPNIR_CRC_SPONGE_HPP__
#define DRAUPNIR_CRC_SPONGE_HPP__

#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

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
  static std::array<T, 256> *buildTable(T const &generator) noexcept {
    constexpr T zero = static_cast<T>(0);
    constexpr T highBit = static_cast<T>(1) << ((sizeof(T) * 8) - 1);
    constexpr std::size_t offset = ((sizeof(T) - 1) * 8);

    // returned array
    std::array<T, 256> *table = new std::array<T, 256>();

    // calculate initial slice
    std::size_t i = 0;
    for (auto &entry : *table) {
      // get the reversed byte to the top
      entry = static_cast<T>(i++ << offset);

      // divide away
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
      entry = static_cast<T>((entry << 1) ^ ((entry & highBit) ? generator : zero));
    }

    // return the generated table
    return table;
  }

  /**
   * Calculate the ECMA crc64 of the given message using all-1s initial state and xor mask
   *
   * @param message  Message to calculate the crc64 for
   * @return the calculated crc64
   */
  std::uint64_t ecmaCrc64(std::string const &message) noexcept {
    // This table was generated for the ECMA polynomial (ie. 0x42f0e1eba9ea3693)
    // using the REVERSED schedule.
    //
    static std::uint64_t crcTable[256] = {
        0x0000000000000000ul, 0xb32e4cbe03a75f6ful, 0xf4843657a840a05bul, 0x47aa7ae9abe7ff34ul, 0x7bd0c384ff8f5e33ul, 0xc8fe8f3afc28015cul, 0x8f54f5d357cffe68ull, 0x3c7ab96d5468a107ul,
        0xf7a18709ff1ebc66ul, 0x448fcbb7fcb9e309ul, 0x0325b15e575e1c3dul, 0xb00bfde054f94352ul, 0x8c71448d0091e255ul, 0x3f5f08330336bd3aul, 0x78f572daa8d1420eull, 0xcbdb3e64ab761d61ul,
        0x7d9ba13851336649ul, 0xceb5ed8652943926ul, 0x891f976ff973c612ul, 0x3a31dbd1fad4997dul, 0x064b62bcaebc387aul, 0xb5652e02ad1b6715ul, 0xf2cf54eb06fc9821ull, 0x41e11855055bc74eul,
        0x8a3a2631ae2dda2ful, 0x39146a8fad8a8540ul, 0x7ebe1066066d7a74ul, 0xcd905cd805ca251bul, 0xf1eae5b551a2841cul, 0x42c4a90b5205db73ul, 0x056ed3e2f9e22447ull, 0xb6409f5cfa457b28ul,
        0xfb374270a266cc92ul, 0x48190ecea1c193fdul, 0x0fb374270a266cc9ul, 0xbc9d3899098133a6ul, 0x80e781f45de992a1ul, 0x33c9cd4a5e4ecdceul, 0x7463b7a3f5a932faull, 0xc74dfb1df60e6d95ul,
        0x0c96c5795d7870f4ul, 0xbfb889c75edf2f9bul, 0xf812f32ef538d0aful, 0x4b3cbf90f69f8fc0ul, 0x774606fda2f72ec7ul, 0xc4684a43a15071a8ul, 0x83c230aa0ab78e9cull, 0x30ec7c140910d1f3ul,
        0x86ace348f355aadbul, 0x3582aff6f0f2f5b4ul, 0x7228d51f5b150a80ul, 0xc10699a158b255eful, 0xfd7c20cc0cdaf4e8ul, 0x4e526c720f7dab87ul, 0x09f8169ba49a54b3ull, 0xbad65a25a73d0bdcul,
        0x710d64410c4b16bdul, 0xc22328ff0fec49d2ul, 0x85895216a40bb6e6ul, 0x36a71ea8a7ace989ul, 0x0adda7c5f3c4488eul, 0xb9f3eb7bf06317e1ul, 0xfe5991925b84e8d5ull, 0x4d77dd2c5823b7baul,
        0x64b62bcaebc387a1ul, 0xd7986774e864d8ceul, 0x90321d9d438327faul, 0x231c512340247895ul, 0x1f66e84e144cd992ul, 0xac48a4f017eb86fdul, 0xebe2de19bc0c79c9ull, 0x58cc92a7bfab26a6ul,
        0x9317acc314dd3bc7ul, 0x2039e07d177a64a8ul, 0x67939a94bc9d9b9cul, 0xd4bdd62abf3ac4f3ul, 0xe8c76f47eb5265f4ul, 0x5be923f9e8f53a9bul, 0x1c4359104312c5afull, 0xaf6d15ae40b59ac0ul,
        0x192d8af2baf0e1e8ul, 0xaa03c64cb957be87ul, 0xeda9bca512b041b3ul, 0x5e87f01b11171edcul, 0x62fd4976457fbfdbul, 0xd1d305c846d8e0b4ul, 0x96797f21ed3f1f80ull, 0x2557339fee9840eful,
        0xee8c0dfb45ee5d8eul, 0x5da24145464902e1ul, 0x1a083bacedaefdd5ul, 0xa9267712ee09a2baul, 0x955cce7fba6103bdul, 0x267282c1b9c65cd2ul, 0x61d8f8281221a3e6ull, 0xd2f6b4961186fc89ul,
        0x9f8169ba49a54b33ul, 0x2caf25044a02145cul, 0x6b055fede1e5eb68ul, 0xd82b1353e242b407ul, 0xe451aa3eb62a1500ul, 0x577fe680b58d4a6ful, 0x10d59c691e6ab55bull, 0xa3fbd0d71dcdea34ul,
        0x6820eeb3b6bbf755ul, 0xdb0ea20db51ca83aul, 0x9ca4d8e41efb570eul, 0x2f8a945a1d5c0861ul, 0x13f02d374934a966ul, 0xa0de61894a93f609ul, 0xe7741b60e174093dull, 0x545a57dee2d35652ul,
        0xe21ac88218962d7aul, 0x5134843c1b317215ul, 0x169efed5b0d68d21ul, 0xa5b0b26bb371d24eul, 0x99ca0b06e7197349ul, 0x2ae447b8e4be2c26ul, 0x6d4e3d514f59d312ull, 0xde6071ef4cfe8c7dul,
        0x15bb4f8be788911cul, 0xa6950335e42fce73ul, 0xe13f79dc4fc83147ul, 0x521135624c6f6e28ul, 0x6e6b8c0f1807cf2ful, 0xdd45c0b11ba09040ul, 0x9aefba58b0476f74ull, 0x29c1f6e6b3e0301bul,
        0xc96c5795d7870f42ul, 0x7a421b2bd420502dul, 0x3de861c27fc7af19ul, 0x8ec62d7c7c60f076ul, 0xb2bc941128085171ul, 0x0192d8af2baf0e1eul, 0x4638a2468048f12aull, 0xf516eef883efae45ul,
        0x3ecdd09c2899b324ul, 0x8de39c222b3eec4bul, 0xca49e6cb80d9137ful, 0x7967aa75837e4c10ul, 0x451d1318d716ed17ul, 0xf6335fa6d4b1b278ul, 0xb199254f7f564d4cull, 0x02b769f17cf11223ul,
        0xb4f7f6ad86b4690bul, 0x07d9ba1385133664ul, 0x4073c0fa2ef4c950ul, 0xf35d8c442d53963ful, 0xcf273529793b3738ul, 0x7c0979977a9c6857ul, 0x3ba3037ed17b9763ull, 0x888d4fc0d2dcc80cul,
        0x435671a479aad56dul, 0xf0783d1a7a0d8a02ul, 0xb7d247f3d1ea7536ul, 0x04fc0b4dd24d2a59ul, 0x3886b22086258b5eul, 0x8ba8fe9e8582d431ul, 0xcc0284772e652b05ull, 0x7f2cc8c92dc2746aul,
        0x325b15e575e1c3d0ul, 0x8175595b76469cbful, 0xc6df23b2dda1638bul, 0x75f16f0cde063ce4ul, 0x498bd6618a6e9de3ul, 0xfaa59adf89c9c28cul, 0xbd0fe036222e3db8ull, 0x0e21ac88218962d7ul,
        0xc5fa92ec8aff7fb6ul, 0x76d4de52895820d9ul, 0x317ea4bb22bfdfedul, 0x8250e80521188082ul, 0xbe2a516875702185ul, 0x0d041dd676d77eeaul, 0x4aae673fdd3081deull, 0xf9802b81de97deb1ul,
        0x4fc0b4dd24d2a599ul, 0xfceef8632775faf6ul, 0xbb44828a8c9205c2ul, 0x086ace348f355aadul, 0x34107759db5dfbaaul, 0x873e3be7d8faa4c5ul, 0xc094410e731d5bf1ull, 0x73ba0db070ba049eul,
        0xb86133d4dbcc19fful, 0x0b4f7f6ad86b4690ul, 0x4ce50583738cb9a4ul, 0xffcb493d702be6cbul, 0xc3b1f050244347ccul, 0x709fbcee27e418a3ul, 0x3735c6078c03e797ull, 0x841b8ab98fa4b8f8ul,
        0xadda7c5f3c4488e3ul, 0x1ef430e13fe3d78cul, 0x595e4a08940428b8ul, 0xea7006b697a377d7ul, 0xd60abfdbc3cbd6d0ul, 0x6524f365c06c89bful, 0x228e898c6b8b768bull, 0x91a0c532682c29e4ul,
        0x5a7bfb56c35a3485ul, 0xe955b7e8c0fd6beaul, 0xaeffcd016b1a94deul, 0x1dd181bf68bdcbb1ul, 0x21ab38d23cd56ab6ul, 0x9285746c3f7235d9ul, 0xd52f0e859495caedull, 0x6601423b97329582ul,
        0xd041dd676d77eeaaul, 0x636f91d96ed0b1c5ul, 0x24c5eb30c5374ef1ul, 0x97eba78ec690119eul, 0xab911ee392f8b099ul, 0x18bf525d915feff6ul, 0x5f1528b43ab810c2ull, 0xec3b640a391f4fadul,
        0x27e05a6e926952ccul, 0x94ce16d091ce0da3ul, 0xd3646c393a29f297ul, 0x604a2087398eadf8ul, 0x5c3099ea6de60cfful, 0xef1ed5546e415390ul, 0xa8b4afbdc5a6aca4ull, 0x1b9ae303c601f3cbul,
        0x56ed3e2f9e224471ul, 0xe5c372919d851b1eul, 0xa26908783662e42aul, 0x114744c635c5bb45ul, 0x2d3dfdab61ad1a42ul, 0x9e13b115620a452dul, 0xd9b9cbfcc9edba19ull, 0x6a978742ca4ae576ul,
        0xa14cb926613cf817ul, 0x1262f598629ba778ul, 0x55c88f71c97c584cul, 0xe6e6c3cfcadb0723ul, 0xda9c7aa29eb3a624ul, 0x69b2361c9d14f94bul, 0x2e184cf536f3067full, 0x9d36004b35545910ul,
        0x2b769f17cf112238ul, 0x9858d3a9ccb67d57ul, 0xdff2a94067518263ul, 0x6cdce5fe64f6dd0cul, 0x50a65c93309e7c0bul, 0xe388102d33392364ul, 0xa4226ac498dedc50ull, 0x170c267a9b79833ful,
        0xdcd7181e300f9e5eul, 0x6ff954a033a8c131ul, 0x28532e49984f3e05ul, 0x9b7d62f79be8616aul, 0xa707db9acf80c06dul, 0x14299724cc279f02ul, 0x5383edcd67c06036ull, 0xe0ada17364673f59ul,
    };

    // process each byte in turn
    std::uint64_t crc = ~0ul;
    for (auto chr : message) {
      crc = crcTable[static_cast<std::uint8_t>(crc) ^ chr] ^ (crc >> 8);
    }

    // invert result (detect appended 0s)
    return ~crc;
  }

  /**
   * Split the given string by the given delimiter
   *
   * @param data  Data to split
   * @param delim  Delimiter character to use
   * @return a string vector containing the parts in data
   */
  std::vector<std::string> splitByDelimiter(std::string const &data, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(data);
    std::string item;
    while (std::getline(ss, item, delim)) {
        result.push_back(item);
    }
    return result;
  }

  /**
   * Parse the given string as if it were an hex number of the templated size
   *
   * @param data  String to parse
   * @return the parsed number
   * @throws std::invalid_argument if conversion failed
   * @throws std::out_of_range if value doesn't fit an unsigned long long
   */
  template <typename T>
  constexpr T parseHex(std::string const &data) {
    return static_cast<T>(std::stoull(data, nullptr, 16));
  }

  /**
   * Generic stringstream-based conversion to string
   *
   * @param data  Data to convert
   * @return the string representation of data
   * @throws whatever the insertion operator for data's type throws
   */
  template <typename T>
  std::string to_string(T const &data) {
    std::stringstream ss;
    ss << data;
    return ss.str();
  }

}


namespace Draupnir {

  /**
   * Load a dumped state into a new CrcSponge
   *
   * @param dump  Dumped state
   * @param delim  Delimiter character to use (defaults to ':')
   * @return the constructed CrcSponge
   * @throws std::invalid_argument in case the version segment is not recognized
   * @throws whatever loadV* throws
   */
  template <typename T>
  CrcSponge<T> CrcSponge<T>::load(std::string const &dump, char delim) {
    std::vector<std::string> parts = splitByDelimiter(dump, delim);

    // determine version
    switch (parseHex<std::size_t>(parts[0])) {
      case 1:
        return loadV1(parts, delim);
      default:
        throw std::invalid_argument("Unrecognized version: '" + parts[0] + "'");
    }
  }

  /**
   * Virtual copy-constructor - pure virtual
   *
   * @return the constructed CrcSponge
   */
  template <typename T>
  CrcSponge<T> *CrcSponge<T>::clone() noexcept {
    return new CrcSponge(*this);
  }

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
  CrcSponge<T>::CrcSponge(T const &generator, T const &initialValue, T const &xorValue, std::array<T, bitSize> const &initialState, std::size_t soakingRounds, std::size_t squeezingRounds) noexcept
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
   * Soak a string into the sponge
   *
   * @param data  String to soak
   * @return the soaked sponge
   */
  template <typename T>
  CrcSponge<T> &CrcSponge<T>::soak(std::string const &data) noexcept {
    std::size_t i, len = data.length();

    // deal with bitSize-bit chunks
    for (i = 0; wordSize <= len; len -= wordSize, i += wordSize) {
      soakBlock(*reinterpret_cast<T const *>(&data[i]));
    }

    // deal with remaining semi-chunks
    {
      T block = 0;
      for (std::size_t m = len; 0 < m; m--, i++) {
        block = static_cast<T>((block | static_cast<T>(data[i])) << 8);
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
  void CrcSponge<T>::soakBlock(T const &block) noexcept {
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
   * Dump the sponge's state as a string using the current version
   *
   * @param delim  Delimiter character to use (defaults to ':')
   * @return the dumped state
   */
  template <typename T>
  std::string CrcSponge<T>::dump(char delim) const noexcept {
    std::stringstream result;

    // version
    result << std::hex << std::setw(4) << std::setfill('0') << 0x0001 << delim;
    result << dumpV1(delim);

    return result.str();
  }

  /**
   * Load a version 1 dumped state into a new CrcSponge
   *
   * @param dump  Dumped state
   * @param delim  Delimiter character to use (defaults to ':')
   * @return the constructed CrcSponge
   * @throws std::invalid_argument in case there are not the required number of parts
   * @throws std::invalid_argument in case the checksum failed
   * @throws std::invalid_argument in case a 0 squeezing or soaking round count is given
   * @throws std::invalid_argument in case an even generator is given
   * @throws std::domain_error in case the width specified in the dump and the templated one differ
   */
  template <typename T>
  CrcSponge<T> CrcSponge<T>::loadV1(std::vector<std::string> const &parts, char delim) {
    // verify parts size
    if (parts.size() != 11) {
      throw std::invalid_argument("Malformed dump");
    }

    // verify checksum
    std::string chk;
    for (std::size_t i = 0; i < 10; i++) {
      chk += parts[i] + delim;
    }
    if (parts[10] != to_string(ecmaCrc64(chk))) {
      throw std::invalid_argument("Checksum failed");
    }

    // verify soaking / squeezing rounds
    std::size_t soakingRounds   = parseHex<std::size_t>(parts[1]);
    std::size_t squeezingRounds = parseHex<std::size_t>(parts[2]);
    if (soakingRounds == 0) {
      throw std::invalid_argument("Zero soaking rounds not allowed");
    }
    if (squeezingRounds == 0) {
      throw std::invalid_argument("Zero squeezing rounds not allowed");
    }

    // verify width
    if (bitSize != parseHex<std::size_t>(parts[3])) {
      throw std::domain_error("Unsupported width: '" + to_string(parseHex<std::size_t>(parts[3])) + "'");
    }

    // verify generator
    T generator = parseHex<std::size_t>(parts[4]);
    if (0 == generator % 2) {
      throw std::invalid_argument("Even generator: '" + parts[4] + "'");
    }

    // extract xor value and initial value
    T xorValue     = parseHex<std::size_t>(parts[5]);
    T initialValue = parseHex<std::size_t>(parts[6]);

    // extract initial state
    std::array<T, bitSize> initialState;
    for (std::size_t i = 0, k = 0; i < parts[7].length(); i += wordSize * 2, k++) {
      initialState[k] = parseHex<T>(parts[8].substr(i, wordSize * 2));
    }

    // extract current crc value
    T crc = parseHex<std::size_t>(parts[8]);

    // extract current state
    std::array<T, bitSize> state;
    for (std::size_t i = 0, k = 0; i < parts[9].length(); i += wordSize * 2, k++) {
      state[k] = parseHex<T>(parts[8].substr(i, wordSize * 2));
    }

    // build new CrcSponge
    CrcSponge<T> result = CrcSponge(generator, initialValue, xorValue, initialState, soakingRounds, squeezingRounds);

    // set current crc
    result._crc = crc;
    // set current state
    for (std::size_t i = 0; i < bitSize; i++) {
      result._state[i] = state[i];
    }

    return result;
  }

  /**
   * Dump the sponge's state as a string using version 1
   *
   * @param delim  Delimiter character to use (defaults to ':')
   * @return the dumped state
   */
  template <typename T>
  std::string CrcSponge<T>::dumpV1(char delim) const noexcept {
    std::stringstream result;

    // soaking rounds
    result << std::hex << std::setw(4) << std::setfill('0') << _soakingRounds << delim;
    // squeezing rounds
    result << std::hex << std::setw(4) << std::setfill('0') << _squeezingRounds << delim;
    // width
    result << std::hex << std::setw(4) << std::setfill('0') << bitSize << delim;
    // generator
    result << std::hex << std::setw(nibbleSize) << std::setfill('0') << _generator << delim;
    // xor value
    result << std::hex << std::setw(nibbleSize) << std::setfill('0') << _xorValue << delim;
    // initial value
    result << std::hex << std::setw(nibbleSize) << std::setfill('0') << _initialValue << delim;
    // initial state
    for (auto row : _initialState) {
      result << std::hex << std::setw(nibbleSize) << std::setfill('0') << row;
    }
    result << delim;
    // crc
    result << std::hex << std::setw(nibbleSize) << std::setfill('0') << _crc << delim;
    // state
    for (auto row : _state) {
      result << std::hex << std::setw(nibbleSize) << std::setfill('0') << row;
    }
    result << delim;
    // checksum
    result << std::hex << std::setw(nibbleSize) << std::setfill('0') << ecmaCrc64(result.str());

    return result.str();
  }

}

#endif /* DRAUPNIR_CRC_SPONGE_HPP__ */

