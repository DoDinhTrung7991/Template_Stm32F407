#ifndef _BIT_OPERATOR_H_
#define _BIT_OPERATOR_H_

#define SET_BIT(REG, BITPOS) ((REG) |= (1UL << (BITPOS)))
#define CLEAR_BIT(REG, BITPOS) ((REG) &= ~(1UL << (BITPOS)))

#define READ_REG(REG, CLEARMASK, BITPOS) (((REG) >> (BITPOS)) & (CLEARMASK))
#define WRITE_REG(REG, CLEARMASK, BITPOS, VALUE) ((REG) = (((REG) & ~((CLEARMASK) << (BITPOS))) | ((VALUE) << (BITPOS))))

#endif
