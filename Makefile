
################################################################################
# This constants provide support for deterministic builds
################################################################################

# fix the pwd
PWD  := '/proc/self/cwd'
# the timestamp is taken here once
TS   := $(shell LC_ALL=C TZ=UTC date -u '+%a %b %e %H:%M:%S %Y')
# the date and time are extracted from the timestamp
DATE := $(shell LC_ALL=C TZ=UTC date -u --date='${TS}' '+%b %e %Y')
TIME := $(shell LC_ALL=C TZ=UTC date -u --date='${TS}' '+%H:%M:%S')


################################################################################
# Executable selection
################################################################################

# Use g++ as the default compiler
CC = g++

# Strip program to use
STRIP = PWD=${PWD} LC_ALL=C TZ=UTC strip


################################################################################
# Flags for CC's operation
################################################################################

# Language flags
#
# These flags control the intended dialect, the extensions to use, and the code
# generation conventions that apply
#
CC_LANG_FLAGS  =
CC_LANG_FLAGS += -std=gnu++1y
CC_LANG_FLAGS += -fno-enforce-eh-specs
CC_LANG_FLAGS += -fstrict-enums -fshort-enums
CC_LANG_FLAGS += -fvisibility-inlines-hidden
CC_LANG_FLAGS += -fwrapv
CC_LANG_FLAGS += -freg-struct-return
#
# not currently supported:
#
# CC_LANG_FLAGS += -fsized-deallocation


# Verbosity flags
#
# These flags control diagnostic messages
#
CC_VERB_FLAGS  =
# CC_VERB_FLAGS += -v
CC_VERB_FLAGS += -fmessage-length=0
CC_VERB_FLAGS += -fdiagnostics-color=auto
CC_VERB_FLAGS += -ftabstop=2


# Warnings flags
#
# These flags control generated warnings
#
CC_WARN_FLAGS  =
CC_WARN_FLAGS += -Wall -Wextra -Wconversion -Wsign-conversion
CC_WARN_FLAGS += -Wformat=2
CC_WARN_FLAGS += -Wmissing-include-dirs -Winvalid-pch
CC_WARN_FLAGS += -Wswitch-default -Wswitch-enum
CC_WARN_FLAGS += -Wunused-parameter -Wuninitialized
CC_WARN_FLAGS += -Wsuggest-attribute=pure -Wsuggest-attribute=const -Wsuggest-attribute=noreturn -Wsuggest-attribute=format
CC_WARN_FLAGS += -Wfloat-equal
CC_WARN_FLAGS += -Wshadow
CC_WARN_FLAGS += -Wunsafe-loop-optimizations -Wno-aggressive-loop-optimizations
CC_WARN_FLAGS += -Wpointer-arith -Wzero-as-null-pointer-constant
CC_WARN_FLAGS += -Wcast-qual -Wcast-align -Wuseless-cast -Wold-style-cast -Wconversion -Wsign-promo
CC_WARN_FLAGS += -Wconditionally-supported
CC_WARN_FLAGS += -Wdate-time
CC_WARN_FLAGS += -Wlogical-op
CC_WARN_FLAGS += -Waggregate-return
CC_WARN_FLAGS += -Wmissing-declarations -Wredundant-decls
CC_WARN_FLAGS += -Wnormalized=nfkc
CC_WARN_FLAGS += -Wpacked -Wpadded
CC_WARN_FLAGS += -Winline
CC_WARN_FLAGS += -Wvector-operation-performance
CC_WARN_FLAGS += -Wvla
CC_WARN_FLAGS += -Wdisabled-optimization
CC_WARN_FLAGS += -Wstack-protector -Wtrampolines
CC_WARN_FLAGS += -Wnoexcept
CC_WARN_FLAGS += -Weffc++ -Woverloaded-virtual -Wctor-dtor-privacy
CC_WARN_FLAGS += -Wcomments -Wundef -Wunused-macros
#
# not currently supported:
#
# CC_WARN_FLAGS += -Wformat-signedness
# CC_WARN_FLAGS += -Wnull-dereference
# CC_WARN_FLAGS += -Wsuggest-final-types -Wsuggest-final-methods -Wsuggest-override
# CC_WARN_FLAGS += -Wduplicated-cond


# Machine flags
#
# These flags control the generated assembly code
#
CC_MACH_FLAGS  =
CC_MACH_FLAGS += -march=native -mtune=native -m64
CC_MACH_FLAGS += -mfpmath=sse -mpc80 -malign-double
CC_MACH_FLAGS += -mmmx
CC_MACH_FLAGS += -msse -msse2 -msse3 -mssse3 -msse4 -msse4a -msse4.1 -msse4.2
CC_MACH_FLAGS += -mavx -mavx2 -mavx512f -mavx512pf -mavx512er -mavx512cd
CC_MACH_FLAGS += -m3dnow
CC_MACH_FLAGS += -mabm -mbmi -mbmi2
CC_MACH_FLAGS += -mf16c -mfma -mfma4
CC_MACH_FLAGS += -maes
CC_MACH_FLAGS += -mpclmul
CC_MACH_FLAGS += -mfsgsbase
CC_MACH_FLAGS += -mrdrnd
CC_MACH_FLAGS += -mxop
CC_MACH_FLAGS += -mlwp
CC_MACH_FLAGS += -msha
CC_MACH_FLAGS += -mpopcnt
CC_MACH_FLAGS += -mprefetchwt1
CC_MACH_FLAGS += -mlzcnt
CC_MACH_FLAGS += -mfxsr
CC_MACH_FLAGS += -mxsave -mxsaveopt
CC_MACH_FLAGS += -mrtm -mtbm
CC_MACH_FLAGS += -mvzeroupper
CC_MACH_FLAGS += -mcx16
CC_MACH_FLAGS += -msahf
CC_MACH_FLAGS += -mmovbe
CC_MACH_FLAGS += -mcrc32
CC_MACH_FLAGS += -mtls-dialect=gnu2
CC_MACH_FLAGS += -maccumulate-outgoing-args -momit-leaf-frame-pointer
CC_MACH_FLAGS += -mavx256-split-unaligned-load -mavx256-split-unaligned-store
#
# not currently supported:
#
# CC_MACH_FLAGS += -malign-data=cacheline
# CC_MACH_FLAGS += -mavx512vl -mavx512bw -mavx512dq -mavx512ifma -mavx512vbmi
# CC_MACH_FLAGS += -mclfushopt
# CC_MACH_FLAGS += -mxsavec -mxsaves
# CC_MACH_FLAGS += -mmpx
# CC_MACH_FLAGS += -mmwaitx
# CC_MACH_FLAGS += -mclzero
# CC_MACH_FLAGS += -mskip-rax-setup


# Deterministic build flags
#
# These flags control the deterministic build setup
#
CC_DETB_FLAGS  =
CC_DETB_FLAGS += -Wno-builtin-macro-redefined
CC_DETB_FLAGS += -fno-guess-branch-probability
CC_DETB_FLAGS += -frandom-seed=$(shell echo $< | sha512sum | sed 's/\(.*\) .*/\1/')
CC_DETB_FLAGS += -D__DATE__='${DATE}'
CC_DETB_FLAGS += -D__TIME__='${TIME}'
CC_DETB_FLAGS += -D__TIMESTAMP__='${TS}'


# Optimization flags
#
# These flags control applicable optimizations
#
CC_OPT_FLAGS  =
CC_OPT_FLAGS += -O3
CC_OPT_FLAGS += -fmerge-all-constants
CC_OPT_FLAGS += -fmodulo-sched -fmodulo-sched-allow-regmoves -freschedule-modulo-scheduled-loops
CC_OPT_FLAGS += -fgcse-sm -fgcse-las -fgcse-after-reload
CC_OPT_FLAGS += -funsafe-loop-optimizations
CC_OPT_FLAGS += -fdeclone-ctor-dtor -fdevirtualize-speculatively
CC_OPT_FLAGS += -flive-range-shrinkage
CC_OPT_FLAGS += -fsched-pressure -fsched-spec-load -fsched-spec-load-dangerous -fsched2-use-superblocks
CC_OPT_FLAGS += -fselective-scheduling -fselective-scheduling2 -fsel-sched-pipelining -fsel-sched-pipelining-outer-loops
CC_OPT_FLAGS += -fipa-pta
CC_OPT_FLAGS += -fisolate-erroneous-paths-attribute
CC_OPT_FLAGS += -floop-interchange -floop-strip-mine -floop-block -floop-nest-optimize -floop-parallelize-all
CC_OPT_FLAGS += -fgraphite-identity
CC_OPT_FLAGS += -ftree-loop-linear  -ftree-loop-if-convert-stores -ftree-loop-distribution -ftree-loop-im -ftree-loop-ivcanon
CC_OPT_FLAGS += -funroll-loops -fpeel-loops -funswitch-loops
CC_OPT_FLAGS += -fivopts
CC_OPT_FLAGS += -ftree-vectorize -fvect-cost-model=cheap -fsimd-cost-model=cheap
CC_OPT_FLAGS += -fvariable-expansion-in-unroller
CC_OPT_FLAGS += -flto -ffat-lto-objects
CC_OPT_FLAGS += -ffast-math -fassociative-math -fno-signed-zeros -fno-trapping-math
CC_OPT_FLAGS += -fcx-fortran-rules
CC_OPT_FLAGS += -ftracer
CC_OPT_FLAGS += -fbranch-target-load-optimize -fbtr-bb-exclusive
#
# not currently supported:
#
# CC_OPT_FLAGS += -fdevirtualize-at-ltrans
# CC_OPT_FLAGS += -fno-semantic-interposition
# CC_OPT_FLAGS += -floop-unroll-and-jam
# CC_OPT_FLAGS += -flto-odr-type-merging
# CC_OPT_FLAGS += -fbranch-target-load-optimize2
# CC_OPT_FLAGS += -fstdarg-opt


# Debug flags
#
# These flags control the debugging information output
#
CC_DBG_FLAGS  =
CC_DBG_FLAGS += -g3
CC_DBG_FLAGS += -feliminate-unused-debug-symbols
CC_DBG_FLAGS += -fdebug-types-section
CC_DBG_FLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined
CC_DBG_FLAGS += -fvar-tracking
# CC_DBG_FLAGS += -fvar-tracking-assignments  # too slooooooooow
#
# not currently supported:
#
# CC_DBG_FLAGS += -fsanitize=float-divide-by-zero
# CC_DBG_FLAGS += -fsanitize=float-cast-overflow
# CC_DBG_FLAGS += -fcheck-pointer-bounds
# CC_DBG_FLAGS += -fchecking


################################################################################
# Flags for STRIP's operation
################################################################################

# Stripping flags
#
# These flags control which symbols to strip
#
STRIP_FLAGS  =
STRIP_FLAGS += -s


################################################################################
# Program invocations
################################################################################

CC_INV = PWD=${PWD} LC_ALL=C TZ=UTC ${CC} ${CC_LANG_FLAGS} ${CC_VERB_FLAGS} ${CC_WARN_FLAGS} ${CC_MACH_FLAGS} ${CC_OPT_FLAGS} ${CC_DETB_FLAGS}

STRIP_INV = PWD=${PWD} LC_ALL=C TZ=UTC ${STRIP} ${STRIP_FLAGS}


################################################################################
################################################################################
################################################################################

draupnir: main.o
	${CC_INV} -o "draupnir"  "main.o"
	${STRIP_INV} "draupnir"


main.o: main.cpp
	${CC_INV} -c -o "main.o"  "main.cpp"


################################################################################

.PHONY: clean
clean:
	-@rm -f *.o draupnir
