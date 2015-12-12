
# Use g++ as the default compiler
CC = g++

# Reset CFLAGS
CFLAGS =

# Language flags
CFLAGS += -std=gnu++1y
CFLAGS += -fno-enforce-eh-specs
# CFLAGS += -fsized-deallocation
CFLAGS += -fstrict-enums
CFLAGS += -fvisibility-inlines-hidden

# Verbosity flags
# CFLAGS += -v
CFLAGS += -fmessage-length=0
CFLAGS += -fdiagnostics-color=auto
CFLAGS += -ftabstop=2

# Warnings flags
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Wconversion
CFLAGS += -Wformat=2
# CFLAGS += -Wformat-signedness
# CFLAGS += -Wnull-dereference
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wswitch-default
CFLAGS += -Wswitch-enum
CFLAGS += -Wunused-parameter
CFLAGS += -Wuninitialized
CFLAGS += -Wsuggest-attribute=pure
CFLAGS += -Wsuggest-attribute=const
CFLAGS += -Wsuggest-attribute=noreturn
CFLAGS += -Wsuggest-attribute=format
# CFLAGS += -Wsuggest-final-types
# CFLAGS += -Wsuggest-final-methods
# CFLAGS += -Wsuggest-override
# CFLAGS += -Wduplicated-cond
CFLAGS += -Wtrampolines
CFLAGS += -Wfloat-equal
CFLAGS += -Wshadow
CFLAGS += -Wunsafe-loop-optimizations
CFLAGS += -Wpointer-arith
CFLAGS += -Wcast-qual
CFLAGS += -Wcast-align
CFLAGS += -Wconditionally-supported
CFLAGS += -Wconversion
CFLAGS += -Wzero-as-null-pointer-constant
CFLAGS += -Wdate-time
CFLAGS += -Wuseless-cast
CFLAGS += -Wsign-conversion
CFLAGS += -Wlogical-op
CFLAGS += -Waggregate-return
CFLAGS += -Wno-aggressive-loop-optimizations
CFLAGS += -Wmissing-declarations
CFLAGS += -Wnormalized=nfkc
CFLAGS += -Wpacked
CFLAGS += -Wpadded
CFLAGS += -Wredundant-decls
CFLAGS += -Winline
CFLAGS += -Winvalid-pch
CFLAGS += -Wvector-operation-performance
CFLAGS += -Wvla
CFLAGS += -Wdisabled-optimization
CFLAGS += -Wstack-protector
CFLAGS += -Wctor-dtor-privacy
CFLAGS += -Wnoexcept
CFLAGS += -Weffc++
CFLAGS += -Wold-style-cast
CFLAGS += -Woverloaded-virtual
CFLAGS += -Wsign-promo
CFLAGS += -Wcomments
CFLAGS += -Wundef
CFLAGS += -Wunused-macros

# Machine options
CFLAGS += -march=native
CFLAGS += -mtune=native
CFLAGS += -mfpmath=sse
CFLAGS += -malign-double
# CFLAGS += -malign-data=cacheline
CFLAGS += -mpc80
CFLAGS += -mmmx
CFLAGS += -msse
CFLAGS += -msse2
CFLAGS += -msse3
CFLAGS += -mssse3
CFLAGS += -msse4
CFLAGS += -msse4a
CFLAGS += -msse4.1
CFLAGS += -msse4.2
CFLAGS += -mavx
CFLAGS += -mavx2
CFLAGS += -mavx512f
CFLAGS += -mavx512pf
CFLAGS += -mavx512er
CFLAGS += -mavx512cd
# CFLAGS += -mavx512vl
# CFLAGS += -mavx512bw
# CFLAGS += -mavx512dq
# CFLAGS += -mavx512ifma
# CFLAGS += -mavx512vbmi
CFLAGS += -msha
CFLAGS += -maes
CFLAGS += -mpclmul
# CFLAGS += -mclfushopt
CFLAGS += -mfsgsbase
CFLAGS += -mrdrnd
CFLAGS += -mf16c
CFLAGS += -mfma
CFLAGS += -mfma4
CFLAGS += -mno-fma4
CFLAGS += -mprefetchwt1
CFLAGS += -mxop
CFLAGS += -mlwp
CFLAGS += -m3dnow
CFLAGS += -mpopcnt
CFLAGS += -mabm
CFLAGS += -mbmi
CFLAGS += -mbmi2
CFLAGS += -mlzcnt
CFLAGS += -mfxsr
CFLAGS += -mxsave
CFLAGS += -mxsaveopt
# CFLAGS += -mxsavec
# CFLAGS += -mxsaves
CFLAGS += -mrtm
CFLAGS += -mtbm
# CFLAGS += -mmpx
# CFLAGS += -mmwaitx
# CFLAGS += -mclzero
CFLAGS += -mvzeroupper
CFLAGS += -mcx16
CFLAGS += -msahf
CFLAGS += -mmovbe
CFLAGS += -mcrc32
CFLAGS += -mtls-dialect=gnu2
CFLAGS += -maccumulate-outgoing-args
CFLAGS += -momit-leaf-frame-pointer
# CFLAGS += -mskip-rax-setup
CFLAGS += -mavx256-split-unaligned-load
CFLAGS += -mavx256-split-unaligned-store
CFLAGS += -m64

# Code generation options
CFLAGS += -fwrapv
CFLAGS += -freg-struct-return
CFLAGS += -fshort-enums



# Use g++ as the default linker
LD = g++

# Reset LDFLAGS
LDFLAGS =


draupnir: main.o
	${LD} ${LDFLAGS} -o "draupnir"  "main.o" "Crc64.o"


main.o: main.cpp
	${CC} ${CFLAGS} -c -o "main.o"  "main.cpp"


.PHONY: clean
clean:
	-@rm -f *.o draupnir
