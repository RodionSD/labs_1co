#include <cctype>
#include <iostream>
using namespace std;

class Alpha
{
private:
    unsigned bin[2];
public:
    Alpha() {bin[1]=0, bin[0]=0;};
    Alpha(char*);
    operator char*(); //перегрузка оператора приведения типа
    int pop(unsigned int); //компонентный метод подсчета единичных разрядов
    int operator() (Alpha&, Alpha&); //перегрузка оператора () компонентным методом
    int operator , (Alpha&);
};

int Alpha::operator, (Alpha& y)
{
    unsigned b = bin[1] & y.bin[1];
    return pop(bin[1] & y.bin[1]); //оператор побитового ИЛИ
}

int Alpha::operator() (Alpha& x, Alpha& y)
{
    return pop(x.bin[1] ^ y.bin[1]); //оператор побитового ИЛИ
}

int Alpha::pop(unsigned int b)
{
    
    int i=0; //фиксация числа выполненных итераций метода
    while (b !=0) //реализация цикла пока есть единичные разряды
    {
        b = b & (b - 1);
        i++;
      
    }
    return i; //число единичных разрядов в числе b
}

Alpha::Alpha(char *s) {   //конструктор множества букв по строке
    bin[0] = 0;
    bin[1] = 0;
    while (*s) {
        if(*s == tolower(*s))   //проверка на то, является ли буква строчной
        {
            bin[1] |= (1 << (*s - 'a'));   //подстановка буквы в ее разряд
        }
        else
        {
            bin[0] |= (1 << (*s - 'A'));
        }
        s++;
    }
}


 
Alpha::operator char*()
{
    static  char s[32]; //массив для запаси раскодированных символов
    unsigned  w=bin[1]; //копирование переменной чтобы не потерять значение при сдвиге
    int i=0, j=0;
    
    while(w > 0)
    {
        if(w & 1)
        s[j++]='a'+i;
        i++;
        w = w >> 1;
    }
    s[j]='\0';
    return (s); //возврат переменной типа указанной в названии
}


int main (int argc, char* argv[])
{
    //проверка на ввод элементов
        if (argc < 2 || argc>=3) {
            cout << "Wrong input"<< endl;
            return 1;
        }
    char arr[6]="aeiou";
    Alpha x(argv[1]);
    Alpha y(arr);
    int z;
    z=(x,y); //вызов конструктора по умолчанию
   
   cout<<"("<< (char*)x<< ","<< (char*)y<< ")"<< "="<< z <<endl; //приведение к типу строки где оператор вывод уже перегружен в библиотеке iostream
    return (0);
}
