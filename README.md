# ML-KEM on OP-TEE using OpenSSL 4.1.0

Implementation of ML-KEM inside an OP-TEE Trusted
Application on QEMU ARM64 using OpenSSL 4.1.0.

## Architecture

- Normal World: Client Application
- Secure World: Trusted Application
- Cryptographic library: OpenSSL 4.1.0 (libcrypto.a)

## Supported algorithms

- ML-KEM-512
- ML-KEM-768
- ML-KEM-1024

## Operations

1. Key Generation
2. Encapsulation
3. Decapsulation
4. Shared-secret verification

## Environment

- Ubuntu 24.04 (VMware)
- OP-TEE
- QEMU ARM64
- Buildroot Linux
- OpenSSL 4.1.0

## OpenSSL modifications

See patches/openssl-optee.patch.

## Results

ML-KEM-768: PASS
ML-KEM-1024: PASS

ML-KEM-512 has been added to the source code.
Its QEMU execution result should be confirmed separately.

## Notes

Research prototype. The OpenSSL compatibility layer
and RNG integration have not been independently
security-audited.
