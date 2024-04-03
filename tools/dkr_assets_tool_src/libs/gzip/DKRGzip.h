#pragma once

/*
 * This is a custom version of gzip that was made specifically for the 
 * Diddy Kong Racing decompilation project, since I cannot get zlib to
 * produce matching compressed files.
 *
 * The main difference with this version of gzip is that you can pass in
 * a simple byte array instead of having to use the FILE structure.
 *
 * This library can only compress files at the moment.
 *
 * Feel free to use it for your own project. The license is the same as gzip.
 */
 
#ifdef __cplusplus
extern "C"
{
#endif

unsigned char* dkr_gzip_compress(unsigned char* input, int inputSize, int gzipLevel, int* outputSize);

#ifdef __cplusplus
} // extern "C"
#endif