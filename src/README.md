## Index

- [Description](#description)
- [Files](#files)

* * *

## Description

This is the main source directory for Draupnir.

## Files

This directory contains the following files:

- [`main.cpp`](./main.cpp): the main driver file.
- [`Draupnir.h`](./Draupnir.h): the library's entry point; this file includes all needed headers and defines a couple of `typedef`s for convenience.
- [`Constants.h`](./Constants.h), [`Constants.cpp`](./Constants.cpp): the static constants used for initial state definition.
- [`Sponge.h`](./Sponge.h): the `Sponge` interface implemented by the Draupnir generators.
- [`CrcSponge.h`](./CrcSponge.h), [`CrcSponge.hpp`](./CrcSponge.hpp): the `CrcSponge` template class, implementing the `Sponge` interface.
- [`CrcSpongeBuilder.h`](./CrcSpongeBuilder.h), [`CrcSpongeBuilder.hpp`](./CrcSpongeBuilder.hpp): the named constructors and named parameters realizations.
- [`Random.h`](./Random.h), [`Random.hpp`](./Random.hpp): randomization algorithms built on top of a sponge (including uniform generation, Fisher-Yates Shuffle, Sattolo's Shuffle, derangements, Reservoir Sampling, Vose's Alias Method, Chao's Weighted Reservoir Sampling, etc).
