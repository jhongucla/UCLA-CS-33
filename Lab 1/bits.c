/* 
 * CS:APP Data Lab 
 * 
 * <Justin Hong 604565186>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
    /* invx=-1 when x=0 and negx=0 when x=0 so the least significant bit is 1
     When x!=0 the least significant bit is 0 so 0&1 = 0 */
    int invx = ~x;
    int negx = invx + 1;
    return ((~negx & invx)>>31)&1;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
    /* Add bits by splitting the bits in half repeatedly using masks */
    int mask1 = 0x55;
    int mask2 = 0x33;
    int mask3 = 0x0F;
    mask1 = (mask1<<8)+0x55;
    mask1 = (mask1<<8)+0x55;
    mask1 = (mask1<<8)+0x55;
    mask2 = (mask2<<8)+0x33;
    mask2 = (mask2<<8)+0x33;
    mask2 = (mask2<<8)+0x33;
    mask3 = (mask3<<8)+0x0F;
    mask3 = (mask3<<8)+0x0F;
    mask3 = (mask3<<8)+0x0F;
    // the splitting is done here
    x = x + (~((x>>1) & mask1) + 1);
    x = (x & mask2) + ((x >>2) & mask2);
    x = (x & mask3) + ((x >>4) & mask3);
    x = x + (x>>8);
    x = x + (x>>16);
    // there are at most 32 bits so we only need the last 6 bits
    return x&0x3F;
}
/*
 * bitOr - x|y using only ~ and &
 *   Example: bitOr(6, 5) = 7
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitOr(int x, int y) {
    /* not of not x and not y is the logical equivalent of or */
    return ~(~x & ~y);
}
/*
 * bitRepeat - repeat x's low-order n bits until word is full.
 *   Can assume that 1 <= n <= 32.
 *   Examples: bitRepeat(1, 1) = -1
 *             bitRepeat(7, 4) = 0x77777777
 *             bitRepeat(0x13f, 8) = 0x3f3f3f3f
 *             bitRepeat(0xfffe02, 9) = 0x10080402
 *             bitRepeat(-559038737, 31) = -559038737
 *             bitRepeat(-559038737, 32) = -559038737
 *   Legal ops: int and unsigned ! ~ & ^ | + - * / % << >>
 *             (This is more general than the usual integer coding rules.)
 *   Max ops: 40
 *   Rating: 4
 */
int bitRepeat(int x, int n)
{
    /* uses a mask to isolate the bits to repeat and then repeats the bits
     Then checks if the bits can be repeated again and does so if possible */
    int mask = -1<<(n-1);
    int shift = ~((32-(2*n))>>31);
    int repeated = ~(mask<<1)&x;
    repeated = (repeated << n) | repeated;
    repeated = (repeated << ((2*n) & shift))|repeated;
    shift =  ~((32-(4*n))>>31);
    repeated = (repeated << ((4*n) & shift))|repeated;
    shift =  ~((32-(8*n))>>31);
    repeated = (repeated << ((8*n) & shift))|repeated;
    shift = ~((32-(16*n))>>31);
    repeated = (repeated << ((16*n) & shift))|repeated;
    return repeated;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
    /* x is shifted left and then shifted right by 32-n bits
     If x is unchanged then it can be represented as an n-bit integer */
    int shift = 33 + ~n;
    return !(((x<<shift)>>shift)^x);
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
    /* x is first shifted right by n*(2^3) bits
     The mask 0xFF is used so only the least significant byte is returned */
    return (0xFF & (x >> (n << 3)));
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
    /* x<=y if x<=y and the signs of x and y are the same or if x is negative and the signs of x and y are different */
    int sign = ((~x+y+1)>>31)&1;
    int msb = 1 << 31;
    int xmsb = msb&x;
    int ymsb = msb&y;
    int diffsigns = ((xmsb^ymsb)>>31)&1;
    return (diffsigns&(xmsb>>31))|(!sign&!diffsigns);
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
    /* x&(1<<31) checks whether the number is negative
     !x checks whether the number is zero
     The number is positive it's both not negative and not zero */
    return !((x&(1<<31)) | !x);
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
    /* A mask is applied to the arithmetically right shifted x
     It changes arithmetically shifted bits to logical */
    return (x >> n) & ~(((1 << 31) >> n) << 1);
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
    /* the minimum two's complement integer is 1 followed by 31 zeroes in binary */
    return 1 << 31;
}
