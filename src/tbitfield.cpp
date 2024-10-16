// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len < 1) throw "bad value";
    BitLen = len;                      
    MemLen = BitLen/(sizeof(TELEM)*8) +1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; ++i) {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    TELEM res;
    res = (TELEM(1)) << ((sizeof(TELEM) * 8) - n - 1);
    return res;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n > BitLen)) throw "bad value";
    int num_block =GetMemIndex(n);
    int num_bit = n % (sizeof(TELEM) * 8);
    pMem[num_block] = pMem[num_block] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0 )|| (n > BitLen)) throw "bad value";
    int num_block = GetMemIndex(n);
    //int num_bit = n % (sizeof(TELEM) * 8);
    pMem[num_block] = pMem[num_block] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || (n > BitLen)) throw "bad value";
    int num_block = GetMemIndex(n);
    if ((pMem[num_block] & GetMemMask(n)) == 0) return 0 ;
    else return 1;

}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    delete[] pMem;
    pMem = new TELEM[MemLen];

    if (BitLen != bf.BitLen) throw "Different sizes";

    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];

    return *this;;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    int chek = 1;
    if (BitLen != bf.BitLen) return 0;
    for (int i = 0; i < MemLen; ++i) {
        if (pMem[i] != bf.pMem[i]) chek = 0;

    }
    return chek;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField res(std::max(this->BitLen, bf.BitLen));
    int mxMlen = std::max(this->MemLen, bf.MemLen);
    for (int i = 0; i < mxMlen; ++i) {
        if (i < mxMlen) res.pMem[i] = pMem[i] | bf.pMem[i];
         } 

    return res;

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

    TBitField res(std::max(this->BitLen, bf.BitLen));
    int mxMlen = std::max(this->MemLen, bf.MemLen);
    for (int i = 0; i < mxMlen; ++i) {
        res.pMem[i] = pMem[i] & bf.pMem[i];
    }
    return res;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; ++i) {
        res.pMem[i] = ~pMem[i];
    }
    for (int i = BitLen; i < MemLen*(sizeof(TELEM)*8); ++i) {
        TELEM num_block = i / (sizeof(TELEM(i))*8);
        TELEM num_bit = i % (sizeof(TELEM(i))*8);
        res.pMem[num_block] = res.pMem[num_block] & ~GetMemMask(num_bit);
    }

    return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    char val;
    for (int i = 0; i < bf.BitLen; ++i) {
        istr >> val;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; ++i) {
        ostr << bf.GetBit(i);
    }
    return ostr;
}
