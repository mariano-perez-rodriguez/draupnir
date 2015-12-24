## Index

- [Description](#description)
- [Files](#files)

* * *

## Description

This is the main source directory for Draupnir.

## Files

This directory contains the following files:

- `main.cpp`: the main driver file.
- `Draupnir.h`: the library's entry point; this file includes all needed headers and defines a couple of `typedef`s for convenience.
- `Constants.h`, `Constants.cpp`: the static constants used for initial state definition.
- `Sponge.h`: the `Sponge` interface implemented by the Draupnir generators.
- `CrcSponge.h`, `CrcSponge.hpp`: the `CrcSponge` template class, implementing the `Sponge` interface.
- `CrcSpongeBuilder.h`, `CrcSpongeBuilder.hpp`: the named constructors and named parameters realizations.
