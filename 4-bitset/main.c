#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>

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
        bitmap^= array[i]<<(63-i) ;//轉換成 Big-Endian
    }    
    //for (int i = 0; i < 64; i++)
        //printf("%ld ",array[i]);

    //printf("\r\n");
    //printf("bitmap=%ld\r\n",bitmap);
    return bitmap;
}


int main(int argc, char *argv[]){
/*     
    make_bitmap(1);
    make_bitmap(5);
    make_bitmap(5); 
*/
    char bit_density = 1;
	int data_size = atoi(argv[1]); //輸入參數 決定你 bitmap[]變數要產生 1000 或10000 筆資料
    printf("size =%d\r\n",data_size);
    if(data_size==0){
        printf("without enter data size\r\n");

    }
    //FILE *txt;
	//txt = fopen("bitmap_test_output","w");
	//if(!txt){
	//	printf("open failure");
	//	return 1;
	//}

    //uint64_t bitmap[data_size]={0};
    //uint32_t out[data_size * 64]={0};
    uint64_t *bitmap= calloc(data_size, sizeof(uint64_t));
    uint32_t *out= calloc(data_size * 64, sizeof(uint64_t));
    unsigned long long total_nai = 0, total_imp = 0;
    for(bit_density=1;bit_density<=64;bit_density++){//點的稀疏程度從1～64點
        for(int i=0;i<data_size;i++){ //每個點稀疏的實驗資料產生 data_size筆
            bitmap[i]=make_bitmap(bit_density);
        }
        struct timespec t1, t2, t3;
        clock_gettime(CLOCK_MONOTONIC, &t1);
        naive(bitmap, data_size, out); //真正跑分析的函式
        clock_gettime(CLOCK_MONOTONIC, &t2);
        improved(bitmap, data_size, out);//真正跑分析的函式
        clock_gettime(CLOCK_MONOTONIC, &t3);
        total_nai += (unsigned long long) (t2.tv_sec * 1e9 + t2.tv_nsec) -
                     (t1.tv_sec * 1e9 + t1.tv_nsec);
        total_imp += (unsigned long long) (t3.tv_sec * 1e9 + t3.tv_nsec) -
                     (t2.tv_sec * 1e9 + t2.tv_nsec);
        //fprintf("bit_density=%u,%llu,%llu\n", (const char *)bit_density, total_nai, total_imp);  
        printf("bit_density=%d,%llu,%llu\n", bit_density, total_nai, total_imp);         
    }
    free(bitmap);
    free(out);
    //fclose(txt);
    return 0;

}
