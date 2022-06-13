#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>

size_t naive(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    for (size_t k = 0; k < bitmapsize; ++k) {
        uint64_t bitset = bitmap[k];
        size_t p = k * 64;
        for (int i = 0; i < 64; i++) {
            if ((bitset >> i) & 0x1)
                out[pos++] = p + i;
        }
    }
    return pos;
}

size_t improved(uint64_t *bitmap, size_t bitmapsize, uint32_t *out)
{
    size_t pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t t = bitset & -bitset;
            int r = __builtin_ctzll(bitset);
            out[pos++] = k * 64 + r;
            bitset ^= t;                           
        }
    }
    return pos;
}

void swap(uint64_t *a, uint64_t *b)
{
    uint64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

uint64_t make_bitmap(int set_bit_num){
    uint64_t array[64]={0};
    uint64_t bitmap=0;
    for (int i = 0; i < set_bit_num; i++){//只設定set_bit_num 個 1 到陣列
        array[i] = 1;
    }
    for (int i = 0; i < 64; i++){ //shuffle array[]
        int rand_i=rand() % 64;
        while(i==rand_i)
            rand_i=rand() % 64;

        swap(&array[i], &array[rand_i]);
    }
    for (int i = 0; i < 64; i++){
        bitmap^= array[i]<<(63-i) ;//轉換有問題
    }    
    for (int i = 0; i < 64; i++)
        printf("%ld ",array[i]);

    printf("\r\n");
    printf("bitmap=%ld\r\n",bitmap);
    return bitmap;
}


int main(int argc, char *argv[]){
    make_bitmap(1);
    make_bitmap(5);
    make_bitmap(5);
    return 0;

}
