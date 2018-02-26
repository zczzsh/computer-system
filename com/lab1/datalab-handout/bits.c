/* 
 * CS:APP Data Lab 
 * 
 * <2016229090 朱思翰>
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
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
   return ~(~x|~y) ;
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
    int b=x>>(n<<3);  //  n左移3位就是乘以8，然后将x右移8n位来选择我们需要的位置
    b= b& 0xFF;  // 与全1做与运算得到结果
    return b;
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
    int b=~(1<<31);  //就是除符号位以外，其它的全为1
    int a=b>>n;   
    a=(a<<1)+1;  //左移的优先级低于+，注意括号，对其实现移动n-1位的操作
    return (x>>n)&a;
}


/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int n=0x1|0x1<<8|0x1<<16|0X1<<24; //相当于把n定义成1个有四个元素的数组，每个元素都为1
  int count=0;
  count+=x&n; //对x的每一位与n相与，把结果加到count中，count也相当于一个四个元素的数组
  count+=x>>1&n;
  count+=x>>2&n;
  count+=x>>3&n;
  count+=x>>4&n;
  count+=x>>5&n;
  count+=x>>6&n;
  count+=x>>7&n;
  return (count&0xf)+(count>>8&0xf)+(count>>16&0xf)+(count>>24&0xf);//把count的每八位移到低八位，作为一个单独的数相加
}


/* 
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int bang(int x) {
  int a=~x+1;    // x取负号
  int b=(x>>31)&0x01;   
  int c=(a>>31)&0x01;   //  得到x和～x+1的符号位的值
  return (0x01^(b|c));  // 如果x非0，则x和～x+1的符号位至少有一个为1，如果x为0则两者都为0
}


/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return (1<<31);  //最小的补码
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
 
  int b=(~n+1)+32;  //移动32-n位，留下最后的n位
    //左移b位，然后再右移b位
  return !(x^((x<<b)>>b));  // 如果此时不能用n位表示时，异或结果肯定非0
}


/* 
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
    int a=x>>31;  //符号位
    int b=(1<<n)+(~1+1);  //偏移码 2的n次方减1
    int c=a&b;     //  正数时无需要加偏移量，但是负数时需要加上偏移量完成向0取整
    return (x+c)>>n;
}


/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return (~x+1);   //取负是对每一位求补加1
}


/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  return !((x>>31)|!x);  //x>>31是符号位。此时正数时需要返回1，符号为为0，此时与!x取或再取反，得到1   
                          // 0和负数需要返回0,0的时候符号位为0，但是!x=1；负数时符号位为1，!x=0，所以满足条件
}


/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int a=x>>31;
  int b=y>>31;  // 取两者的符号位
     // 同号的时候两者需要做减法，异号时y正x负为1，x正y负为0
  int c=~x+1;
  int d=(!((y+c)>>31)) & (!(a^b));  // 同号时虽然a，b的值不影响结果，但是必须a，b保持一致时才能有结果，故采用!(a^b)来使其值永远为1
  int e= a&(!b);   //异号时a为1，b为0时结果为1；a为0，b为1时结果为0；
  return d|e;
}


/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4  
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
  int count=0;
  int n=0x1|0x1<<8|0x1<<16|0X1<<24;
  x=x|x>>1;  //通过计算把1右移到的次数来实现ilog2的函数
  x=x|x>>2;
  x=x|x>>4;
  x=x|x>>8;
  x=x|x>>16; // 利用或和右移，把1后的所有0变为1
  count+=x&n;
  count+=x>>1&n;
  count+=x>>2&n;
  count+=x>>3&n;
  count+=x>>4&n;
  count+=x>>5&n;
  count+=x>>6&n;
  count+=x>>7&n;
  return (count&0xf)+(count>>8&0xf)+(count>>16&0xf)+(count>>24&0xf)+(~1+1); // 即BitCount函数 
}


/* 
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
//单精度浮点数：符号位为1位，阶码段为8位，剩下23位为小数字段
 unsigned a=uf^0x80000000;  // 符号位取反  (符号位为0时与1异或为1，为1时与1异或为0）
 unsigned b=uf&0x7fffffff;  //取除符号位外的部分
 if(b>0x7f800000)  // 阶码全1，为无穷或者NaN
  a=uf;
 return a;
}


/* 
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
//不懂咋做
  unsigned n=0;
  unsigned temp;
  unsigned flag=0;
  unsigned frac=x;
  unsigned s=0;
  if (x==0) return 0;
  if (x<0)
  { 
    s=0x80000000;
    frac=-x;
  }
  while(1) //循环操作，得到小数字段
  {
    temp=frac;
    frac<<=1;
    n++;
    if (temp & 0x80000000) break;
  }
  if (((frac&0x01ff)>0x0100)||((frac&0x03ff)==0x0300)) //对超过float精度表示范围的数的取舍
  flag=1;
  return s+((159-n)<<23)+(frac>>9)+flag; //159-n=127+32-n

}


/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {  
   unsigned a=uf;
  // 主要分三种情况考虑，第一种是非规格化，第二种是规格化，第三种是特殊值
  
  // 第一种，非规格化，阶码全为0，分两种情况：第一是可以直接左移一位，第二是需要向阶码位进一位，但因为阶码全为0，所以同样可以执行左移一位
   if ((a & 0x7F800000) == 0)
  {
     a = ((a & 0x007FFFFF)<<1) | (0x80000000 & a); // 将小数域左移一位，然后保留符号位
  }
  // 第二种，规格化，阶码不全为0，也不全为1，此时×2时只需要将阶码加1即可
  else if((a & 0x7F800000) != 0x7F800000)
  {
      a =a+0x00800000;
  }
  // 第三种，无穷和NaN，直接返回其本身就好，即什么都不做
  return a;

}
