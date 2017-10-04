// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = BitLen / sizeof(TELEM) + 1;
	pMem = new TELEM[MemLen];
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 8 * sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
	int gmi = GetMemIndex(n);
	TELEM gmm = GetMemMask(n);
	pMem[gmi] = pMem[gmi] | gmm;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	int gmi = GetMemIndex(n);
	TELEM gmm = GetMemMask(n);
	pMem[gmi] = pMem[gmi] & ~gmm;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw n;

	int gmi = GetMemIndex(n);
	TELEM gmm = GetMemMask(n);
	gmm &= pMem[gmi];
	if (pMem[gmi] == 0) return 0 ;
	else return 1;
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		delete[] pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;

	for (int i = 0; i < MemLen - 1; i++)
		if (pMem[i] != bf.pMem[i]) return 0;

	for(int i = MemLen * sizeof(TELEM); i < BitLen; i++)
		if(GetBit(i) != bf.GetBit(i)) return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField result(BitLen);
	
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = bf.pMem[i] | pMem[i];

	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField result(BitLen);
	
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = bf.pMem[i] & pMem[i];

	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = ~pMem[i];

	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
}
