#include <common.h>


//void main()
//{
//    uint8 A[10];
//    float value= -123.456789;
//    uint8 i;
//   Float2Char(value,A);
//   printf("%s",A);
//}


uint8 Float2Char(float value,uint8 *array)
{
   float DecimalPart;
   uint32 IntegerPart;
   uint8 i = 0, j = 0, temp;
   //分离整数和小数
    if(value < 0)
    {
       value = -value ;
       array[i++] = '-';
    }
    else
       array[i++] = '+';
   IntegerPart = (uint32)value;
   DecimalPart =  value - IntegerPart;
    //处理整数
    if(0 == IntegerPart)//整数部分为0
       array[i++] = '0';
    else
    {
       while(0 != IntegerPart)
       {
           array[i++ ] = IntegerPart%10 + '0';
           IntegerPart/=10;
       }
       i--;
       for(j = 1; j < (i+1)/2; j++)
           {
               temp = array[j];
               array[j] = array[i -j+1];
               array[i-j+1] = temp;
           }
       i++;
    }


  array[i++] = '.';
   //处理小数
  array[i++] = (uint32)(DecimalPart * 10)%10 + '0';
  array[i++] = (uint32)(DecimalPart * 100)%10 + '0';
  array[i++] = (uint32)(DecimalPart * 1000)%10 + '0';
  array[i++] = (uint32)(DecimalPart * 10000)%10 + '0';
  array[i]   = '\0';
  
   return i;
}