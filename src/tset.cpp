// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField)
{

    MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = 0;
}

TSet::operator TBitField()
{
    return TBitField(0);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if ((Elem < 0) || (Elem >= MaxPower)) throw "bad value";
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    //if ((Elem < 0) || (Elem >= MaxPower)) throw "bad value";
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    BitField.ClrBit(Elem);                             
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    this->MaxPower = s.MaxPower;
    this->BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    if ((MaxPower == s.MaxPower) && (BitField == s.BitField)) return 1;
    else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
    int MaxMp = std::max(this->MaxPower, s.MaxPower);
    TSet res = TSet(MaxMp);
    res.BitField = (this->BitField | s.BitField);
    return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    TSet res(*this);
    res.InsElem(Elem);
    return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    TSet res(MaxPower + 1);
    this->BitField.ClrBit(Elem);
    res.BitField = this->BitField;
    return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    int mxp = std::max(this->MaxPower, s.MaxPower);
    TSet res(mxp);
    res.BitField = (BitField & s.BitField);
    return res;
}

TSet TSet::operator~(void) // дополнение
{
    TSet res(MaxPower);
    res.BitField = ~BitField;
    return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    istr >> s.BitField;
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    ostr << s.BitField;
    return ostr;
}
