# TA source files
global-incdirs-y += include
global-incdirs-y += compat/include

srcs-y += mlkem_bench_ta.c
srcs-y += mlkem_ops.c

# OP-TEE compatibility layer
srcs-y += compat/optee_compat.c
srcs-y += compat/string_compat.c
srcs-y += compat/stdlib_compat.c

# OpenSSL 4.1.0 headers
global-incdirs-y += ../build_openssl/include
global-incdirs-y += ../third_party/openssl-4.1.0/include

# OpenSSL static library
libdirs += ../build_openssl
libnames += crypto
libdeps += ../build_openssl/libcrypto.a
