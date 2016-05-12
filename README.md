# Курсач по системному программированию
2015-2016
вариант 16

писалось на c++ 

Задание
____________________________________________________________________________________________________________________________________
  Ідентифікатори:
Містять великі і малі букви латинского алфавіту та цифри. Починаються з букви. Великі та малі букви не відрізняються. Довжина ідентифікаторів не більше 8 символів
  Константи: 
Шістнадцятерічні та текстові константи
  Директиви:
END, SEGMENT - без операндів, ENDS, программа може мати тільки один сегмент кодів і тільки один сегмент даних
EQU, IF-ELSE-ENDIF
DB,DW,DD з одним операндом - константою (строкові константи тільки для DB)
  Розрядність даних та адрес:
32 - розрядні дані та зміщення в сегменті, 16 -розрядні дані та зміщення не використовуються
  Адресація операндів пам'яті:
Індексна адресація із множником (Val1[ecx+eax*2],Val1[edx+edi*4] і т.п.)
  Заміна сегментів:
Префікси заміни сегментів можуть задаватись явно, а при необхідності автоматично генеруються транслятором

Машинні команди:
Sti
Dec reg
Inc mem
And reg,reg
Or reg,mem
Cmp mem,reg
Mov reg,imm
Add mem,imm
Jnz
   
Де reg – 8  або 32-розрядні РЗП
mem – адреса операнда в пам’яті
imm – 8  або 32-розрядні безпосередні дані (константи)
____________________________________________________________________________________________________________________________________