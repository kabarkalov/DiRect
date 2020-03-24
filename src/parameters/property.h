/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      property.h                                                  //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __PROPERTY_H__
#define __PROPERTY_H__

/**
\file property.h

\authors Лебедев И.
\date 2015-2016
\copyright ННГУ им. Н.И. Лобачевского

\brief Объявление базоых классов для свойств

*/

#include <string>
#include "common.h"
using namespace std;

/* ======================================================================== *\
**  Объявление классов                                                      **
\* ======================================================================== */


/**
Базовый класс имеющий владельца
*/

class IBaseClass
{
protected:

public:

  /// Копирует данные из указателя в этот объект
  virtual void Copy(void* data) = 0;
  /// Задает данные приводя void* к типу объекта
  virtual void SetValue(void* data) = 0;
  /// Возвращает указатель на данные хранящиеся в объекте
  virtual void* GetValue() = 0;
  /// Приводит к строке
  virtual string ToString() = 0;
  /// Получение значения из строки
  virtual void FromString(string val) = 0;

  virtual ~IBaseClass() {}

  /// Задает разделитель элементов массива
  virtual void SetSeparator(string separator) = 0;
  /// Возвращает разделитель элементов массива
  virtual string GetSeparator() = 0;

  /// Задает размер массива элементов
  virtual void SetSize(int size) = 0;
  /// Возвращает Размер массива элементов
  virtual int GetSize() = 0;

  /// Имя свойства
  virtual string GetName() = 0;
  /// Текст справки
  virtual string GetHelp() = 0;
  /// Короткое имя для домандной строки
  virtual string GetLink() = 0;

  /// Имя свойства
  virtual void SetName(string name) = 0;
  /// Текст справки
  virtual void SetHelp(string help) = 0;
  /// Короткое имя для домандной строки
  virtual void SetLink(string link) = 0;
  /// Возвращает справку по свойству
  virtual string GetHelpString() = 0;
  /// Возвращает текущего состояния параметра
  virtual string GetCurrentStringValue() = 0;
  /// Совпадает ли имя параметра со введенной строкой
  virtual bool IsNameEqual(string name) = 0;

  /// Возвращает прочиталось ли значение параметра из аргументов консоли или конфиг файла
  virtual bool GetIsReadValue() = 0;
  /// Задает прочиталось ли значение параметра из аргументов консоли или конфиг файла
  virtual void SetIsReadValue(bool isReadValue) = 0;

  /// Является ли свойство флагом, и задавать значение не требуется.
  virtual bool IsFlag() = 0;
  /// Проверяет правильность значения
  virtual int CheckValue() = 0;
};


/**
Базовый класс имеющий владельца
*/
template <class Owner>
class TBaseProperty : public IBaseClass
{
protected:

  /// Тип метода внешней проверки данных, принимает номер свойства возвращает код ошибки
  typedef int (Owner::*tCheckValue)(int);

  /// Владелец объекта
  Owner* mOwner;
  /// Прочиталось ли значение параметра из аргументов консоли или конфиг файла
  bool mIsReadValue;
public:
  /// Перегрузка оператора копрования двух объектов
  virtual void operator = (TBaseProperty<Owner>& data);
  /// Перегрузка оператора копрования для указателя
  virtual void operator = (TBaseProperty<Owner>* data);

  /// Создает объект data
  virtual void Clone(TBaseProperty<Owner>** data) = 0;

  TBaseProperty(Owner* owner): mOwner(owner), mIsReadValue(false) {}
  virtual ~TBaseProperty() {}

  /** Инициализация свойства
  \param[in] owner - класс владелец свойства
  \param[in] checkMethod - метод проверки правильности введенных данных
  \param[in] index - номер свойства
  \param[in] separator - разделитель элементов массива
  \param[in] size - размер массива значений, для типов данных не являющимися масивами - всегда равен 1
  \param[in] name - имя свойства
  \param[in] help - выводимая на консоль справка
  \param[in] link - короткая строка для запуска
  \param[in] defValue - значение по умолчанию
  */
  virtual void InitializationParameterProperty(Owner * owner,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue) = 0;

    /// Возвращает прочиталось ли значение параметра из аргументов консоли или конфиг файла
  virtual bool GetIsReadValue()
  {
    return mIsReadValue;
  }
  /// Задает прочиталось ли значение параметра из аргументов консоли или конфиг файла
  virtual void SetIsReadValue(bool isReadValue)
  {
    mIsReadValue = isReadValue;
  }

};

/**
Базовый класс для свойств
*/
template <class Type, class Owner>
class TTypedProperty : public TBaseProperty<Owner>
{
protected:

  /// Тип метода возвращающего внешние данные
  typedef Type (Owner::*tGetter)();
  /// Тип метода задающего внешние данные
  typedef void (Owner::*tSetter)(Type);

  /// Индек свойства
  int mIndex;

  /// Метод возвращающий внешние данные
  tGetter mGetter;
  /// Метод задающий внешние данные
  tSetter mSetter;
  /// Внешняя проверка данных
  tCheckValue mCheckValue;
  /// Внутренные данные
  Type mValue;
  /// Какие данные использовать анутренние или внешние
  bool mIsHaveValue;
  /// Было ли изменено свойство после инициализации
  bool mIsChange;
  /// Является ли свойство флагом, и задавать значение не требуется
  bool mIsFlag;

  /// Копирование внутренних значений
  virtual void CopyValue(Type value);
public:

  /// Задает использовать ли внутренние данные или внешние
  void SetIsHaveValue(bool isHaveValue);
  /// Какие данные используются, внутренние или внешние
  bool GetIsHaveValue();

  /// Задает индекс свойства для проверки
  void SetIndex(int index);
  /// Возвращает индекс свойства для проверки
  int GetIndex();

  /// Перегруженный оператор приведения типа, геттер
  virtual operator Type();
  /// Перегруженный оператор присваивания, сеттер
  virtual void operator =(Type data);

  /// Перегрузка оператора копрования двух объектов
  virtual void operator = (TTypedProperty<Type, Owner>& data);
  /// Перегрузка оператора копрования для указателя
  virtual void operator = (TTypedProperty<Type, Owner>* data);

  /// Копирует данные из указателя в этот объект
  virtual void Copy(void* data);
  /// Задает данные приводя к void* к типу объекта
  virtual void SetValue(void* data);
  /// Возвращает указатель на данные хранящиеся в объекте
  virtual void* GetValue();
  /// Инициализация методов
  virtual void Init(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod);

  /// Возвращиет данные в соответствии с правилами
  virtual Type GetData();
  /// Возвращает принадлежащие объекту данные
  virtual Type GetAvailableData() const;
  /// Было ли изменено свойство после инициализации
  virtual bool GetIsChange();

  TTypedProperty();
  TTypedProperty(Type value);
  TTypedProperty(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod, Type value);
  virtual ~TTypedProperty();

  /// Задает функцию сеттер
  virtual void SetSetter(tSetter setter)
  {
    mSetter = setter;
  }
  ///// Возвращает функцию сеттер
  virtual tSetter GetSetter()
  {
    return mSetter;
  }
  /// Задает функцию геттер
  virtual void SetGetter(tGetter getter)
  {
    mGetter = getter;
  }
  ///// Возвращает функцию геттер
  virtual tGetter GetGetter()
  {
    return mGetter;
  }
  /// Задает функцию проверяющую значение
  virtual void SetCheckValue(tCheckValue checkValue)
  {
    mCheckValue = checkValue;
  }
  /// Возвращает функцию проверяющую значения
  virtual tCheckValue GetCheckValue()
  {
    return mCheckValue;
  }

  /// Является ли свойство флагом, и задавать значение не требуется.
  virtual bool IsFlag()
  {
    return mIsFlag;
  }

  /// Проверяет правильность значения
  virtual int CheckValue()
  {
    int err = 0;
    if (mCheckValue != 0)
      err = (mOwner->*mCheckValue)(mIndex);
    return err;
  }

};

/**
Базовый класс для свойств параметров, имеет полную реализацию
*/
template <class Type, class Owner>
class TParameterProperty : public TTypedProperty<Type, Owner>
{
protected:
  /// Разделитель массива
  string mSeparator;
  /// Размер массива
  int mSize;
  /// Имя свойства
  string mName;
  /// Текст справки
  string mHelp;
  /// Короткое имя для домандной строки
  string mLink;

  /// Полное консольное имя из имени
  string GetFullLink();

public:
  /// Перегрузка оператора копрования двух объектов
  virtual void operator = (TParameterProperty<Type, Owner>&  data);
  /// Перегрузка оператора копрования для указателя
  virtual void operator = (TParameterProperty<Type, Owner>* data);

  /// Создает объект data
  virtual void Clone(TBaseProperty<Owner>** data);

  /// Задает разделитель элементов массива
  virtual void SetSeparator(string separator);
  /// Возвращает разделитель элементов массива
  virtual string GetSeparator();

  /// Задает размер массива элементов
  virtual void SetSize(int size);
  /// Возвращает Размер массива элементов
  virtual int GetSize();

  /// Имя свойства
  virtual string GetName();
  /// Текст справки
  virtual string GetHelp();
  /// Короткое имя для домандной строки
  virtual string GetLink();

  /// Имя свойства
  virtual void SetName(string name);
  /// Текст справки
  virtual void SetHelp(string help);
  /// Короткое имя для домандной строки
  virtual void SetLink(string link);
  /// Возвращает справку по свойству
  virtual string GetHelpString();
  /// Возвращает текущего состояния параметра
  virtual string GetCurrentStringValue();

  /// Приводит к строке
  virtual string ToString();
  /// Получение значения из строки
  virtual void FromString(string val);

  /// Совпадает ли имя параметра со введенной строкой
  virtual bool IsNameEqual(string name);

  /** Инициализация свойства
  \param[in] owner - класс владелец свойства
  \param[in] checkMethod - метод проверки правильности введенных данных
  \param[in] index - номер свойства
  \param[in] separator - разделитель элементов массива
  \param[in] size - размер массива значений, для типов данных не являющимися масивами - всегда равен 1
  \param[in] name - имя свойства
  \param[in] help - выводимая на консоль справка
  \param[in] link - короткая строка для запуска
  \param[in] defValue - значение по умолчанию
  */
  virtual void InitializationParameterProperty(Owner * owner,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue);

  /** Инициализация свойства
  \param[in] owner - класс владелец свойства
  \param[in] getMethod - геттер
  \param[in] setMethod - сеттер
  \param[in] checkMethod - метод проверки правильности введенных данных
  \param[in] index - номер свойства
  \param[in] separator - разделитель элементов массива
  \param[in] size - размер массива значений, для типов данных не являющимися масивами - всегда равен 1
  \param[in] name - имя свойства
  \param[in] help - выводимая на консоль справка
  \param[in] link - короткая строка для запуска
  \param[in] defValue - значение по умолчанию
  */
  virtual void InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, int index, string separator, int size, string name,
    string help, string link, string defValue);

  TParameterProperty();
  TParameterProperty(Type value);
  TParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
    tCheckValue checkMethod, Type value);

};


/* ======================================================================== *\
**  Реализация методов класса     TBaseProperty                                 **
\* ======================================================================== */

//Перегрузка оператора копрования двух объектов
template <class Owner>
void TBaseProperty<Owner>::operator = (TBaseProperty<Owner>& data)
{
  mOwner = data.mOwner;
}

///// Перегрузка оператора копрования для указателя
template <class Owner>
void TBaseProperty<Owner>::operator = (TBaseProperty<Owner>* data)
{
  mOwner = data->mOwner;
}


/* ======================================================================== *\
**  Реализация методов класса     TTypedProperty                                 **
\* ======================================================================== */

/// Копирование внутренних значений
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::CopyValue(Type value)
{
  mValue = value;
}

/// Задает использовать ли внутренние данные или внешние
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetIsHaveValue(bool isHaveValue)
{
  mIsHaveValue = isHaveValue;
}
/// Какие данные используются, внутренние или внешние
template <class Type, class Owner>
bool TTypedProperty<Type, Owner>::GetIsHaveValue()
{
  return mIsHaveValue;
}

/// Задает индекс свойства для проверки
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetIndex(int index)
{
  mIndex = index;
}
/// Возвращает индекс свойства для проверки
template <class Type, class Owner>
int TTypedProperty<Type, Owner>::GetIndex()
{
  return mIndex;
}

/// Перегруженный оператор приведения типа, геттер
template <class Type, class Owner>
TTypedProperty<Type, Owner>::operator Type()
{
  if ((mIsHaveValue) || (mGetter == 0))
    return mValue;
  else
    return (mOwner->*mGetter)();
}

/// Перегруженный оператор присваивания, сеттер
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator =(Type data)
{
  Type oldVal = mValue;
  mIsChange = true;
  if ((mIsHaveValue) || (mSetter == 0))
    CopyValue(data);
  else
    (mOwner->*mSetter)(data);
  int err = 0;
  if (mCheckValue != 0)
    err = (mOwner->*mCheckValue)(mIndex);
  if (err != 0)
  {
    CopyValue(oldVal);
  }
}

/// Перегрузка оператора копрования двух объектов
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator = (TTypedProperty<Type, Owner>& data)
{
  CopyValue(data.mValue);
  mIsHaveValue = data.mIsHaveValue;
  mGetter = data.mGetter;
  mSetter = data.mSetter;
  mCheckValue = data.mCheckValue;
  mOwner = data.mOwner;
  mIndex = data.mIndex;
  mIsChange = data.mIsChange;
}

/// Перегрузка оператора копрования для указателя
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::operator = (TTypedProperty<Type, Owner>* data)
{
  CopyValue(data->mValue);
  mIsHaveValue = data->mIsHaveValue;
  mGetter = data->mGetter;
  mSetter = data->mSetter;
  mCheckValue = data->mCheckValue;
  mOwner = data->mOwner;
  mIndex = data->mIndex;
  mIsChange = data->mIsChange;
}

/// Копирует данные из указателя в этот объект
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::Copy(void* data)
{
  operator = ((TTypedProperty<Type, Owner>*)data);
}
/// Задает данные приводя к void* к типу объекта
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::SetValue(void* data)
{
  *this = *((Type*)(data));
}
/// Возвращает указатель на данные хранящиеся в объекте
template <class Type, class Owner>
void* TTypedProperty<Type, Owner>::GetValue()
{
  if ((mIsHaveValue) || (mGetter == 0))
    return (void*)&mValue;
  else
  {
    Type* val = new Type ((mOwner->*mGetter)());
    return (void*)val;
  }
}

/// Инициализация методов
template <class Type, class Owner>
void TTypedProperty<Type, Owner>::Init(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod)
{
  mOwner = owner;
  mGetter = getMethod;
  mSetter = setMethod;
  mCheckValue = checkMethod;
  if ((getMethod != 0) || (setMethod != 0))
    mIsHaveValue = false;
  else
    mIsHaveValue = true;
  mIsChange = false;
};

/// Возвращиет данные в соответствии с правилами
template <class Type, class Owner>
Type TTypedProperty<Type, Owner>::GetData()
{
  return operator Type();
}
/// Возвращает принадлежащие объекту данные
template <class Type, class Owner>
Type TTypedProperty<Type, Owner>::GetAvailableData() const
{
  return mValue;
}

/// Было ли изменено свойство после инициализации
template <class Type, class Owner>
bool TTypedProperty<Type, Owner>::GetIsChange()
{
  return mIsChange;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty() : TBaseProperty(0), mGetter(0), mSetter(0), mCheckValue(0)
{
  mIsHaveValue = true;
  mIndex = 0;
  mIsChange = false;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty(Type value) : TBaseProperty(0), mGetter(0), mSetter(0), mCheckValue(0)
{
  CopyValue(value);
  mIsHaveValue = true;
  mIndex = 0;
  mIsChange = false;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::TTypedProperty(Owner * owner, tGetter getMethod, tSetter setMethod, tCheckValue checkMethod, Type value) :
TBaseProperty(owner), mGetter(getMethod), mSetter(setMethod), mCheckValue(checkMethod)
{
  CopyValue(value);
  if ((getMethod != 0) || (setMethod != 0))
    mIsHaveValue = false;
  else
    mIsHaveValue = true;
  mIsChange = false;
  mIndex = 0;
  mIsFlag = false;
}

template <class Type, class Owner>
TTypedProperty<Type, Owner>::~TTypedProperty()
{}

/* ======================================================================== *\
**  Реализация методов класса     TParameterProperty                                 **
\* ======================================================================== */

/// Перегрузка оператора копрования двух объектов
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::operator = (TParameterProperty<Type, Owner>&  data)
{
  mSeparator = data.mSeparator;
  mSize = data.mSize;
  mName = data.mName;
  mHelp = data.mHelp;
  mLink = data.mLink;
  mIsFlag = data.mIsFlag;
  TTypedProperty::operator=(data);
}

/// Перегрузка оператора копрования для указателя
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::operator = (TParameterProperty<Type, Owner>* data)
{
  mSeparator = data->mSeparator;
  mSize = data->mSize;
  mName = data->mName;
  mHelp = data->mHelp;
  mLink = data->mLink;
  mIsFlag = data->mIsFlag;
  TTypedProperty::operator=(data);
}

/// Создает объект data
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::Clone(TBaseProperty<Owner>** data)
{
  *data = new TParameterProperty<Type, Owner>();
  **data = *this;
}

/// Задает разделитель элементов массива
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetSeparator(string separator)
{
  mSeparator = separator;
}
/// Возвращает разделитель элементов массива
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetSeparator()
{
  return mSeparator;
}
/// Задает размер массива элементов
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetSize(int size)
{
  //if (size > 0)
  //  mSize = size;
}
/// Возвращает Размер массива элементов
template <class Type, class Owner>
int TParameterProperty<Type, Owner>::GetSize()
{
  return mSize;
}

/// Имя свойства
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetName()
{
  return mName;
}
/// Текст справки
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetHelp()
{
  return mHelp;
}
/// Короткое имя для домандной строки
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetLink()
{
  return mLink;
}

/// Имя свойства
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetName(string name)
{
  mName = name;
}
/// Текст справки
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetHelp(string help)
{
  mHelp = help;
}
/// Короткое имя для домандной строки
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::SetLink(string link)
{
  mLink = link;
}
/// Возвращает справку по свойству
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetHelpString()
{
  string result = "";
  result = result + GetName() + " (" + GetLink() + ") - \'" + GetHelp() + "\' default:\t" + ToString();
  return result;
}

/// Возвращает текущего состояния параметра
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetCurrentStringValue()
{
  string result = "";
  result = result + GetName() + " = " + ToString();
  return result;
}

/// Приводит к строке
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::ToString()
{
  return "";
}
/// Получение значения из строки
template <class Type, class Owner>
void TParameterProperty<Type, Owner>::FromString(string val)
{}

/// Полное консольное имя из имени
template <class Type, class Owner>
string TParameterProperty<Type, Owner>::GetFullLink()
{
  return "-" + GetName();
}

/// Совпадает ли имя параметра со введенной строкой
template <class Type, class Owner>
bool TParameterProperty<Type, Owner>::IsNameEqual(string name)
{
  if ((name == GetFullLink()) || (name == GetLink()) || (name == GetName()))
    return true;
  else
    return false;
}

template <class Type, class Owner>
void TParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner,
  tCheckValue checkMethod, int index, string separator, int size, string name,
  string help, string link, string defValue)
{
  TTypedProperty<Type, Owner>::Init(owner, 0, 0, checkMethod);

  SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  mIsChange = false;
}

template <class Type, class Owner>
void TParameterProperty<Type, Owner>::InitializationParameterProperty(Owner * owner, tGetter getMethod, tSetter setMethod,
  tCheckValue checkMethod, int index, string separator, int size, string name,
  string help, string link, string defValue)
{
  TTypedProperty<Type, Owner>::Init(owner, getMethod, setMethod, checkMethod);

  SetIndex(index);
  SetSeparator(separator);
  SetSize(size);
  SetName(name);
  SetHelp(help);
  SetLink(link);

  FromString(defValue);
  mIsChange = false;
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(): mSize(1), TTypedProperty()
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(Type value) : mSize(1), TTypedProperty(value)
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

template <class Type, class Owner>
TParameterProperty<Type, Owner>::TParameterProperty(Owner * owner, tGetter getMethod,
  tSetter setMethod, tCheckValue checkMethod, Type value) :
mSize(1), TTypedProperty(mOwner, mGetter, mSetter, mCheckValue, value)
{
  mSeparator = "_";
  mName = "";
  mHelp = "";
  mLink = "";
}

#endif //__TYPES_H__
// - end of file ----------------------------------------------------------------------------------
