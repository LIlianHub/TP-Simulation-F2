#ifndef MT_H
#define MT_H


#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */


/* Fonction utlisée*/

void init_by_array(unsigned long init_key[], int key_length);
double genrand_real2(void);
unsigned long genrand_int32(void);


#endif