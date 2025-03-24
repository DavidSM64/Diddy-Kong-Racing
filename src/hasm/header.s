.section .data

.word 0x80371240       /* PI BSB Domain 1 register */
.word 0x0000000F       /* Clockrate setting */
.ifdef BOOT_6103
.word 0x80000400       /* Entrypoint address */
.else
.word 0x80100400       /* Entrypoint address */
.endif
.word 0x00001447       /* Revision */

.ifdef VERSION_us_v77
.word 0x53D440E7       /* Checksum 1 */
.word 0x7519B011       /* Checksum 2 */
.endif
.ifdef VERSION_pal_v77
.word 0xFD73F775       /* Checksum 1 */
.word 0x9724755A       /* Checksum 2 */
.endif
.ifdef VERSION_jpn_v79
.word 0x7435C9BB       /* Checksum 1 */
.word 0x39763CF4       /* Checksum 2 */
.endif
.ifdef VERSION_us_v80
.word 0xE402430D       /* Checksum 1 */
.word 0xD2FCFC9D       /* Checksum 2 */
.endif
.ifdef VERSION_pal_v80
.word 0x596E145B       /* Checksum 1 */
.word 0xF7D9879F       /* Checksum 2 */
.endif

.word 0x00000000       /* Unknown 1 */
.word 0x00000000       /* Unknown 2 */
.ascii "Diddy Kong Racing   " /* Internal name */
.word 0x00000000       /* Unknown 3 */
.word 0x0000004E       /* Cartridge */
.ascii "DY"            /* Cartridge ID */

.ifdef VERSION_us_v77
.ascii "E"             /* Country code */
.byte 0x00             /* Version */
.endif
.ifdef VERSION_pal_v77
.ascii "P"             /* Country code */
.byte 0x00             /* Version */
.endif
.ifdef VERSION_jpn_v79
.ascii "J"             /* Country code */
.byte 0x00             /* Version */
.endif
.ifdef VERSION_us_v80
.ascii "E"             /* Country code */
.byte 0x01             /* Version */
.endif
.ifdef VERSION_pal_v80
.ascii "P"             /* Country code */
.byte 0x01             /* Version */
.endif
