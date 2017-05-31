#pragma once
#include <iostream>

template<class K, class V>
class table
{
private:
	K* arrKey;//
	V* arrVal;//
	size_t MaxSizeTable, countUsed;//

public://
	table(size_t size);//
	~table();//

	void dobavit(K k, V v);//

	void udalit(K k);//

	V& operator[](K k);//

	table& operator = (table& vt);//


	void resize(size_t newsized);//всё то же самое что и в просмотровой


	friend std::ostream& operator<<(std::ostream& os, table<K, V>& t)//оператор вывода в консоль
	{
		for (size_t i = 0; i < t.countUsed; i++)
		{
			os << t.arrKey[i] << " | " << t.arrVal[i] << std::endl;
		}

		return os;
	}

};

template<class K, class V>
table<K, V>::table(size_t size)
{
	MaxSizeTable = size;
	arrKey = new K[size];
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		arrKey[i] = NULL;
	}
	arrVal = new V[size];
	countUsed = 0;
}

template<class K, class V>
table<K, V>::~table()
{
	delete[]arrKey;
	delete[]arrVal;
}

template<class K, class V>
void table<K, V>::dobavit(K k, V v)
{
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		if (arrKey[i] == NULL || arrKey[i] >= k)//нашли пустой элемент или элемент в нужном положении
		{
			arrKey[countUsed] = k;//установили ключ в конец списка
			arrVal[countUsed++] = v;//тоже (значение)

			for (size_t x = i; x < countUsed - 1; x++)//сортируем от текущего до конца
			{
				K tk = arrKey[x];
				V tv = arrVal[x];

				arrKey[x] = arrKey[countUsed - 1];
				arrVal[x] = arrVal[countUsed - 1];
				arrKey[countUsed - 1] = tk;
				arrVal[countUsed - 1] = tv;
			}
			return;//выход из функции

		}
	}

	throw 1;//иначе таблица полна если не вышли раньше из функции

}

template<class K, class V>
void table<K, V>::udalit(K k)
{
	int shift = (countUsed / 2);
	int index = shift;
	do
	{
		if (arrKey[index] == k || arrKey[index] == NULL)//нашли
		{
			for (size_t x = index; x < countUsed; x++)//все после этого индекса передвинула на 1
			{
				arrKey[x] = arrKey[countUsed - 1];
				arrVal[x] = arrVal[countUsed - 1];
			}
			arrKey[countUsed--] = NULL;//очистили последний элемент в списке
			return;
		}
		shift /= 2;//алгоритм бинарного поиска
		if (arrKey[index] < k)
		{
			index -= shift;
		}
		else
		{
			index += shift;
		}

	} while (shift);
}

template<class K, class V>
V & table<K, V>::operator[](K k)
{

	int shift = (countUsed / 2);
	int index = shift;//алгоритм бинарного поиска
	do
	{
		if (arrKey[index] == k)
		{
			return arrVal[index];
		}
		shift = shift/2+shift%2;
		if (arrKey[index] > k)
		{
			index -= shift;
		}
		else
		{
			index += shift;
		}

	} while (shift);//сдвигаем пока движение не раво 0

	throw 1;
	
}

template<class K, class V>
table<K, V> & table<K, V>::operator=(table & vt)
{
	MaxSizeTable = vt.MaxSizeTable;
	arrKey = new K[MaxSizeTable];
	arrVal = new V[MaxSizeTable];
	countUsed = vt.countUsed;
	for (size_t i = 0; i < MaxSizeTable; i++)
	{
		arrKey[i] = vt.arrKey[i];
		arrVal[i] = vt.arrVal[i];
	}

	return *this;
}

template<class K, class V>
void table<K, V>::resize(size_t newsized)//так же как в просморовой
{
	if (newsized == MaxSizeTable)
		return;
	if (newsized < countUsed)
		throw 2;

	K* Tkey = new K[newsized];
	V* Tval = new V[newsized];
	size_t insertindex = 0;
	for (int i = 0; i < MaxSizeTable; i++)
	{
		Tkey[insertindex] = arrKey[i];
		Tval[insertindex] = arrVal[i];
		++insertindex;
		if (arrKey[i] == NULL)
			break;
	}
	delete[]arrKey, arrVal;
	arrKey = Tkey;
	arrVal = Tval;
	MaxSizeTable = newsized;
}
