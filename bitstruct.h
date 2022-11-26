/** @file bitstruct.h
 *
 * Example of usage:
 * @code
 * BITSTRUCT SomeRegister {
 *         BITFIELD(SR_FIELD1, 0, 4),
 *         BITFIELD(SR_FIELD2, 4, 4),
 * };
 * 
 * int x = 0x1234; // raw value of register
 * x = BITFIELD_SET(SR_FIELD1, x, 0x98);
 * printf("%0X", BITFIELD_GET(SR_FIELD1, x));
 * @endcode
 */

#ifndef _BITSTRUCT_H_
# define _BITSTRUCT_H_

/** Not shifted mask */
#define __BITSTRUCT_MASK(LEN) ((1<<(LEN))-1)

/** Implementation of getting bits, may be defined by user (for DSP, for ex.) */
#ifndef BITSTRUCT_GETBITS_IMPL
# define BITSTRUCT_GETBITS_IMPL(BS, OFFSET, LEN) \
    (((BS)>>(OFFSET)) & __BITSTRUCT_MASK(LEN))
#endif
/** Implementation of setting bits, may be defined by user (for DSP, for ex.) */
#ifndef BITSTRUCT_SETBITS_IMPL
# define BITSTRUCT_SETBITS_IMPL(BS, OFFSET, LEN, VALUE) \
    ((BS) & ~(__BITSTRUCT_MASK(LEN)<<(OFFSET)) | \
     (((VALUE) & __BITSTRUCT_MASK(LEN))<<(OFFSET)))
#endif

/** Used instead of struct operator */
#define BITSTRUCT enum
/** Field descriptor
 * @param NAME name of the field
 * @param OFFSET offset of the fields in bits from 0 bit 
 * @param LEN length of the fields in bits
 * @note In the program will be available next names:
 *
 * - <NAME>_OFF - offset of named field
 * - <NAME>_LEN - length of named field
 * - <NAME>_MASK - mask of named field (not shifted to offset!)
 *  */
#define BITFIELD(NAME, OFFSET, LEN) NAME##_OFF = (OFFSET), NAME##_LEN=(LEN), NAME##_MASK=__BITSTRUCT_MASK(LEN)
/** Getter for named with @a NAME field in some raw value @BS */
#define BITFIELD_GET(NAME, BS) \
  BITSTRUCT_GETBITS_IMPL(BS, NAME##_OFF, NAME##_LEN)
/** Setter for named with @a NAME field in some raw value @BS with new value @a VALUE */
#define BITFIELD_SET(NAME, BS, VALUE) \
  BITSTRUCT_SETBITS_IMPL(BS, NAME##_OFF, NAME##_LEN, VALUE)

#endif
