/* The comment below is needed for this file to be picked up by generate_ld */
/* RAM_POS: 0x800C6170 */

#include "gzip.h"
#include "asset_loading.h"
#include "PR/os_libc.h"

/************ .data ************/

huft *gHuftTable = NULL; // gzip_huft_alloc
s32 *gPackedHeader = NULL;
u8 *gzip_inflate_input = NULL;
u8 *gzip_inflate_output = NULL;

/*******************************/

/************ .bss ************/

u32 gzip_bit_buffer;
u32 gzip_num_bits;
s32 gHuftTablePos; // gzip_hufts

/******************************/

/**
 * Allocate space for the decompression heap and file header.
 */
void gzip_init(void) {
    gHuftTable = (huft *) mempool_alloc_safe(0x2800, COLOUR_TAG_BLACK);
    gPackedHeader = (s32 *) mempool_alloc_safe(0x10, COLOUR_TAG_BLACK);
}

/**
 * Converts a little endian value to big endian.
 * Official name: rzipUncompressSize
 * (so, this probably expects a gzip header)
 */
s32 byteswap32(u8 *arg0) {
    s32 value;
    value = *arg0++;
    value |= (*arg0++ << 8);
    value |= (*arg0++ << 16);
    value |= (*arg0++ << 24);
    return value;
}

/**
 * Returns the uncompressed size of a gzip compressed asset.
 * Official name: rzipUncompressSizeROM
 */
s32 get_asset_uncompressed_size(s32 assetIndex, s32 assetOffset) {
    load_asset_to_address(assetIndex, (u32) gPackedHeader, assetOffset, 8);
    return byteswap32((u8 *) gPackedHeader);
}

/**
 * Decompresses gzip data.
 * Returns the pointer to the decompressed data.
 * Official name: rzipUncompress
 */
u8 *gzip_inflate(u8 *compressedInput, u8 *decompressedOutput) {
    gzip_inflate_input = compressedInput + 5; // The compression header is 5 bytes.
    gzip_inflate_output = decompressedOutput;
    gzip_num_bits = 0;
    gzip_bit_buffer = 0;
    while (gzip_inflate_block() != 0) {} // Keep calling gzip_inflate_block() until it returns 0.
    return decompressedOutput;
}

/* Official name: huft_build */
void gzip_huft_build(u32 *b, u32 n, u32 s, u16 *d, u16 *e, huft **t, s32 *m) {
    u32 a;                   /* counter for codes of length k */
    u32 c[BMAX + 1];         /* bit length count table */
    u32 f;                   /* i repeats in table every f entries */
    s32 g;                   /* maximum code length */
    s32 h;                   /* table level */
    register u32 i;          /* counter, current code */
    register u32 j;          /* counter */
    register s32 k;          /* number of bits in current code */
    s32 l;                   /* bits per table (returned in m) */
    register u32 *p;         /* pointer into c[], b[], or v[] */
    register struct huft *q; /* points to current table */
    struct huft r;           /* table entry for structure assignment */
    struct huft *u[BMAX];    /* table stack */
    u32 v[N_MAX];            /* values in order of bit length */
    register s32 w;          /* bits before this table == (l * h) */
    u32 x[BMAX + 1];         /* bit offsets, then code stack */
    u32 *xp;                 /* pointer into x */
    s32 y;                   /* number of dummy codes added */
    u32 z;                   /* number of entries in current table */

    /* Generate counts for each bit length */
    bzero(c, sizeof(c));
    p = b;
    i = n;
    do {
        c[*p]++; /* assume all entries <= BMAX */
        p++;     /* Can't combine with above line (Solaris bug) */
    } while (--i);
    if (c[0] == n) /* null input--all zero length codes */
    {
        *t = NULL;
        *m = 0;
        return;
    }

    /* Find minimum and maximum length, bound *m by those */
    l = *m;
    for (j = 1; j <= BMAX; j++) {
        if (c[j]) {
            break;
        }
    }
    k = j; /* minimum code length */
    if ((u32) l < j) {
        l = j;
    }
    for (i = BMAX; i; i--) {
        if (c[i]) {
            break;
        }
    }
    g = i; /* maximum code length */
    if ((u32) l > i) {
        l = i;
    }
    *m = l;

    // Something is missing here.
    /* Adjust last length count to fill out codes, if needed */
    y = 1 << j;
    while (j < i) {
        y -= c[j];
        j++;
        y <<= 1;
    }
    y -= c[i];
    c[i] += y;

    /* Generate starting offsets into the value table for each length */
    x[1] = j = 0;
    p = c + 1;
    xp = x + 2;
    while (--i) { /* note that i == g from above */
        *xp++ = (j += *p++);
    }

    /* Make a table of values in order of bit lengths */
    p = b;
    i = 0;
    do {
        if ((j = *p++) != 0) {
            v[x[j]++] = i;
        }
    } while (++i < n);
    // n = x[g];              /* set n to length of v */

    /* Generate the Huffman codes and for each, make the table entries */
    x[0] = i = 0; /* first Huffman code is zero */
    p = v;        /* grab values in bit order */
    h = -1;       /* no tables yet--level -1 */
    w = -l;       /* bits decoded == (l * h) */
    u[0] = NULL;  /* just to keep compilers happy */
    q = NULL;     /* ditto */
    z = 0;        /* ditto */

    // gHuftTable and gHuftTablePos go in here somewhere.

    /* go through the bit lengths (k already is bits in shortest code) */
    for (; k <= g; k++) {
        a = c[k];
        while (a--) {
            /* here i is the Huffman code of length k bits for value *p */
            /* make tables up to required level */
            while (k > w + l) {
                h++;
                w += l; /* previous table always l bits */

                /* compute minimum size table less than or equal to l bits */
                z = (z = g - w) > (u32) l ? (u32) l : z; /* upper limit on table size */
                if ((f = 1 << (j = k - w)) > a + 1)      /* try a k-w bit table */
                {                                        /* too few codes for k-w bit table */
                    f -= a + 1;                          /* deduct codes from patterns left */
                    xp = c + k;
                    while (++j < z) /* try smaller tables up to z bits */
                    {
                        if ((f <<= 1) <= *++xp) {
                            break; /* enough codes to use up j bits */
                        }
                        f -= *xp; /* else deduct codes from patterns */
                    }
                }
                z = 1 << j; /* table entries for j-bit table */

                q = &gHuftTable[gHuftTablePos];
                gHuftTablePos += z + 1;

                *t = q + 1; /* link to list for huft_free() */
                *(t = &(q->v.t)) = NULL;
                u[h] = ++q; /* table starts after link */

                /* connect to last table, if there is one */
                if (h) {
                    x[h] = i;         /* save pattern for backing up */
                    r.b = l;          /* bits to dump before this table */
                    r.e = 16 + j;     /* bits in this table */
                    r.v.t = q;        /* pointer to this table */
                    j = i >> (w - l); /* (get around Turbo C bug) */
                    u[h - 1][j] = r;  /* connect to last table */
                }
            }

            /* set up table entry in r */
            r.b = k - w;
            if (p >= v + n) {
                r.e = 99; /* out of values--invalid code */
            } else if (*p < s) {
                r.e = *p < 256 ? 16 : 15; /* 256 is end-of-block code */
                r.v.n = *p;               /* simple code is just the value */
                p++;                      /* one compiler does not like *p++ */
            } else {
                r.e = ((u8 *) e)[*p - s]; /* non-simple--look up in lists */
                r.v.n = d[*p++ - s];
            }

            /* fill code-like entries with r */
            f = 1 << (k - w);
            for (j = i >> w; j < z; j += f) {
                q[j] = r;
            }

            /* backwards increment the k-bit code i */
            for (j = 1 << (k - 1); i & j; j >>= 1) {
                i ^= j;
            }
            i ^= j;

            /* backup over finished tables */
            while ((i & ((1 << w) - 1)) != x[h]) {
                h--; /* don't need to update q */
                w -= l;
            }
        }
    }
    return;
}
