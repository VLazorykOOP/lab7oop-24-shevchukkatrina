#include "example.h"
#include <string.h>
#include <iostream>
namespace Fun {
// Написати функцію - шаблон послідовного пошуку в максимального серед 4 елементів.
// Написати специфікацію функції - шаблон для типу char* .
// Розробити програму тестування шаблона для декількох типів 
// та специфікації доданого шаблона.   
////


 //using namespace std;
    using std::cout;
    using std::endl;
    using std::ostream;
    using std::istream;

    class TLong {    //  long long 8 -byte
        long long hi, lo;  // 16 byte 
    public:
        TLong() :hi(0), lo(0) {}
        TLong(long long h, long long l) :hi(h), lo(l) {}
        TLong& operator = (const TLong& s) {
            hi = s.hi; lo = s.lo; return *this;
        };
        bool      operator > (const TLong& s) {
            if (hi > s.hi) return true;
            if (hi == s.hi && lo >= s.lo) return true;
            return false;
        }
        friend ostream& operator<<(ostream& os,
            TLong& s);
    };

    ostream& operator<<(ostream& os, TLong& s) {
        os << "H " << s.hi << ":L " << s.lo << "  ";
        return os;
    }
    //  функція - шаблон
    template <typename T>
    T max(T x, T y, T z, T u) {
        T t = x > y ? x : y;
        T r = z > u ? z : u;
        return t > r ? t : r;
    }
    // специфікація функції - шаблон для типу char*
    template<>  char* max(char* x, char* y, char* z, char* u)
    {
        char* t = strcmp(x, y) ? x : y;
        char* r = strcmp(z, u) ? z : u;
        return  strcmp(t, r) ? t : r;
    }


    int fmain()
    {
        cout << "template\n";
        int  a = 5, b = 4, k;
        double r, t = 3.5, q = 3.05;
        char c, s = 'a', n = 'f';
        TLong l, i(100, 50), j(50, 100), e(75, 75), f(4, 200);
        k = max(a, 13, b, 5);   cout << "k= " << k << endl;
        r = max(t, q, 3.45, 9.32); cout << "r= " << r << endl;
        c = max(s, 'r', n, 'z');  cout << "c= " << c << endl;
        l = max(i, j, e, f);    cout << "l= " << l << endl;
        char* s1 = (char*)"text", * s2 = (char*)"txt", * s3 = (char*)"pltext",
            * s4 = (char*)"room", * s5;
        s5 = max<char*>(s1, s2, s3, s4); cout << " s5 =  " << s5 << endl;
        return 0;
    }


}
namespace Stk {

    using namespace std;
    class TLong {    //  long long 8 -byte
        long long hi, lo;  // 16 byte 
    public:
        TLong() :hi(0), lo(0) {}
        TLong(long long h, long long l) :hi(h), lo(l) {}
        TLong& operator = (const TLong& s) {
            hi = s.hi; lo = s.lo; return *this;
        };
        bool      operator > (const TLong& s) {
            if (hi > s.hi) return true;
            if (hi == s.hi && lo >= s.lo) return true;
            return false;
        }
        friend ostream& operator<<(ostream& os,
            TLong& s);
    };
    ostream& operator<<(ostream& os, TLong& s) {
        os << "H " << s.hi << ":L " << s.lo << "  ";
        return os;
    }
    //  stack - шаблон


    template <typename T = double, int SIZE = 100>   // <class T>
    class stack_n
    {
        T m_stk[SIZE];   // Містить елементи стека.
        int tos;        // Індекс вершини стека.
    public:
        stack_n() { tos = 0; }    // Ініціалізує стек.
        void push(T obj);        // Заштовхує об'єкт у стек.
        T pop() {        // Виштовхує об'єкт зі стека.
            if (tos == 0) { cout << "Стек порожній.\n"; return 0; }
            tos--; return m_stk[tos];
        }
    };
    // Функція що визначається за межами класу
    template <typename T, int SIZE>
    void stack_n<T, SIZE>::push(T obj) {
        if (tos == SIZE) { cout << "Стек повний. \n"; return; }
        m_stk[tos] = obj; tos++;
    }

    typename char* pchar;
    template <int SIZE>   // <class T>
    class stack_n<char*, SIZE>
    {
        char* m_stk[SIZE];   // Містить елементи стека.
        int tos;        // Індекс вершини стека.
    public:
        stack_n() { tos = 0; }    // Ініціалізує стек.
        void push(char* obj);        // Заштовхує об'єкт у стек.
        char* pop() {        // Виштовхує об'єкт зі стека.
            if (tos == 0) { cout << "Стек порожній.\n"; return 0; }
            tos--; return m_stk[tos];
        }
    };
    // Функція що визначається за межами класу
    template <int SIZE>
    void stack_n<char*, SIZE>::push(char* obj) {
        if (tos == SIZE) { cout << "Стек повний. \n"; return; }
        m_stk[tos] = obj; tos++;
    }
    int smain()
    {
        int i;
        setlocale(LC_CTYPE, "ukr");
        std::cout << "Стек тести !\n";
        stack_n<char, 10> s1, s2;
        s1.push('a');  s2.push('x');  s1.push('b');
        s2.push('y');  s1.push('c');  s2.push('z');
        for (i = 0; i < 3; i++) cout << "Виштовхуємо s1: " << s1.pop() << "\n";
        for (i = 0; i < 3; i++) cout << "Виштовхуємо s2: " << s2.pop() << "\n";
        // Демонстрація стека дійсних чисел
        stack_n<double> ds1, ds2; // Створюємо дві стеки дійсних чисел.
        ds1.push(1.1);  ds2.push(2.2); ds1.push(3.3);
        ds2.push(4.4);  ds1.push(5.5); ds2.push(6.6);
        for (i = 0; i < 3; i++) cout << "Виштовхуємо ds1: " << ds1.pop() << "\n";
        for (i = 0; i < 3; i++) cout << "Виштовхуємо ds2: " << ds2.pop() << "\n";
        stack_n <TLong, 10> ln1, ln2;
        ln1.push(TLong(5, 4));   ln1.push(TLong(50000, 4));   ln1.push(TLong(5, 400000));
        ln2.push(TLong(3673865, 643287));   ln2.push(TLong(56748, 64374));   ln2.push(TLong(36287, 40530));
        char* st1 = (char*)"text", * st2 = (char*)"txt", * st3 = (char*)"pltext",
            * st4 = (char*)"room", * st5 = (char*)"text2";

        stack_n <char*, 5> ss;
        ss.push(st3); ss.push(st4); ss.push(st5); ss.push(st1);
        ss.push(st2);
        for (i = 0; i < 5; i++) cout << "Виштовхуємо ss: " << ss.pop() << "\n";
        return 0;
    }
}
void example()
{
    Fun::fmain();
    Stk::smain();
}