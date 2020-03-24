/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//             LOBACHEVSKY STATE UNIVERSITY OF NIZHNY NOVGOROD             //
//                                                                         //
//                       Copyright (c) 2016 by UNN.                        //
//                          All Rights Reserved.                           //
//                                                                         //
//  File:      types.h                                                     //
//                                                                         //
//  Purpose:   Header file for random generator class                      //
//                                                                         //
//  Author(s): Lebedev I.                                                  //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#ifndef __TYPES_H__
#define __TYPES_H__

/**
\file types.h

\authors Лебедев И.
\date 2015-2016
\copyright ННГУ им. Н.И. Лобачевского

\brief Объявление класса #TInteger

\details Объявление класса #TInteger и его реализация
*/

#include <stdio.h>
#include <string>
#include <algorithm>

#include "property.h"

using namespace std;



/* ======================================================================== *\
**  Объявление классов                                                      **
\* ======================================================================== */



/**
Класс логического чисел
*/
template <class Owner>
class TBool : public TParameterProperty<bool, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TBool, bool);

  TBool(bool value = 0):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};


/**
Класс логического чисел
*/
template <class Owner>
class TFlag : public TBool<Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TFlag, bool);

  TFlag(bool value = 0):TBool(value)
  {
    mIsFlag = true;
  }

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс целых чисел
*/
template <class Owner>
class TInt : public TParameterProperty<int, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TInt, int);

  TInt(int value = 0):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();


};

/**
Класс действительных чисел
*/
template <class Owner>
class TDouble : public TParameterProperty<double, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TDouble, double);

  TDouble(double value = 0):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс строк
*/
template <class Owner>
class TString : public TParameterProperty<string, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TString, string);

  TString(string value = ""):TParameterProperty(value) {}

  /// Приведение к строке
  virtual operator string();
};

/**
Класс массива целых чисел
*/
template <class Owner>
class TInts : public TParameterProperty<int*, Owner>
{
protected:

  /// Копирование внутренних значений
  virtual void CopyValue(int* value);
public:

  /// Задает размер массива элементов
  virtual void SetSize(int size);
  /// Возвращает Размер массива элементов
  virtual int GetSize();

  TInts(int* value = 0) : TParameterProperty(value) { }

  virtual ~TInts();

  /// Базовые переопределения
  BasicMethods(TInts, int*);

  /// Парсер строки
  virtual void operator = (string data);
  /// Приведение к строке
  virtual operator string();
  /// Перегрузка оператора индексации
  virtual int& operator [] (int index);
};

/**
Класс массива целых чисел
*/
template <class Owner>
class TDoubles : public TParameterProperty<double*, Owner>
{
protected:

  /// Копирование внутренних значений
  virtual void CopyValue(double* value);
public:

  /// Задает размер массива элементов
  virtual void SetSize(int size);
  /// Возвращает Размер массива элементов
  virtual int GetSize();

  TDoubles(double* value = 0) : TParameterProperty(value) { }

  virtual ~TDoubles();

  /// Базовые переопределения
  BasicMethods(TDoubles, double*);


  /// Парсер строки
  virtual void operator = (string data);
  /// Приведение к строке
  virtual operator string();
  /// Перегрузка оператора индексации
  virtual double& operator [] (int index);
};

/**
Класс для перечисления типа методов
*/
template <class Owner>
class TETypeMethod : public TParameterProperty<ETypeMethod, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TETypeMethod, ETypeMethod);

  TETypeMethod(ETypeMethod value = StandartMethod):TParameterProperty(ETypeMethod(0)) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс для перечисления типов сепарабельного поиска
*/
template <class Owner>
class TESeparableMethodType : public TParameterProperty<ESeparableMethodType, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TESeparableMethodType, ESeparableMethodType);

  TESeparableMethodType(ESeparableMethodType value = Off):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};



/**
Класс для перечисления типов запуска локального поиска
*/
template <class Owner>
class TELocalMethodScheme : public TParameterProperty<ELocalMethodScheme, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TELocalMethodScheme, ELocalMethodScheme);

  TELocalMethodScheme(ELocalMethodScheme value = None):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс для перечисления типов критерия остановки
*/
template <class Owner>
class TEStopCondition : public TParameterProperty<EStopCondition, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TEStopCondition, EStopCondition);

  TEStopCondition(EStopCondition value = Accuracy):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс для перечисления типов способов вычисления
*/
template <class Owner>
class TETypeCalculation : public TParameterProperty<ETypeCalculation, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TETypeCalculation, ETypeCalculation);

  TETypeCalculation(ETypeCalculation value = OMP):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс для перечисления типов процесса
*/
template <class Owner>
class TETypeProcess : public TParameterProperty<ETypeProcess, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TETypeProcess, ETypeProcess);

  TETypeProcess(ETypeProcess value = SynchronousProcess):TParameterProperty(ETypeProcess(value)) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};

/**
Класс для перечисления типов процесса
*/
template <class Owner>
class TEMapType : public TParameterProperty<EMapType, Owner>
{
public:
  /// Базовые переопределения
  BasicMethods(TEMapType, EMapType);

  TEMapType(EMapType value = mpRotated):TParameterProperty(value) {}

  /// Парсер строки
  virtual void operator = (string data);

  /// Приведение к строке
  virtual operator string();
};


/* ======================================================================== *\
**  Служебные функции                                                       **
\* ======================================================================== */


/// Шаблонная функция для реализации перегрузки операции индексации
template<class Type, class Owner>
Type& Indexer(int index, Type* mValue, int mSize, TBaseProperty<Owner>* obj)
{
  if (((index >= 0) && (index < mSize)) && (mValue != 0))
    return mValue[index];
  else
  {
    if (mValue == 0)
    {
      obj->SetSize(1);
    }
    return (*((Type**)obj->GetValue()))[0];
  }
}


/* ======================================================================== *\
**  Реализация методов класса     TBool                                     **
\* ======================================================================== */

/// Парсер строки
template <class Owner>
void TBool<Owner>::operator = (string data)
{
  if ((data == "false") || (data == "0"))
    *this = false;
  if ((data == "true") || (data == "1"))
    *this = true;
}

/// Приведение к строке
template <class Owner>
TBool<Owner>::operator string()
{
  string result;
  if (mValue == false)
    result = "false";
  if (mValue == true)
    result = "true";
  return result;
}



/* ======================================================================== *\
**  Реализация методов класса     TFlag                                     **
\* ======================================================================== */

/// Парсер строки
template <class Owner>
void TFlag<Owner>::operator = (string data)
{
  TBool::operator = (data);
}

/// Приведение к строке
template <class Owner>
TFlag<Owner>::operator string()
{
  return TBool::operator string();
}

/* ======================================================================== *\
**  Реализация методов класса     TInt                                     **
\* ======================================================================== */

template <class Owner>
void TInt<Owner>::operator = (string data)
{
  int val = 0;
  sscanf(data.data(), "%d", &val);
  *this = val;
}

/// Приведение к строке
template <class Owner>
TInt<Owner>::operator string()
{
  string result;
  char ch[256];
  sprintf(ch, "%d", mValue);
  result = ch;
  return result;
}

/* ======================================================================== *\
**  Реализация методов класса     TDouble                                   **
\* ======================================================================== */


/// Парсер строки
template <class Owner>
void TDouble<Owner>::operator = (string data)
{
  double val = 0;
  sscanf(data.data(), "%lf", &val);
  *this = val;
}

/// Приведение к строке
template <class Owner>
TDouble<Owner>::operator string()
{
  string result;
  char ch[256];
  sprintf(ch, "%lf", mValue);
  result = ch;
  return result;
}

/* ======================================================================== *\
**  Реализация методов класса     TString                                   **
\* ======================================================================== */

/// Приведение к строке
template <class Owner>
TString<Owner>::operator string()
{
  return mValue;
}


/* ======================================================================== *\
**  Реализация методов класса     TInts                                   **
\* ======================================================================== */


/// Копирование внутренних значений
template <class Owner>
void TInts<Owner>::CopyValue(int* value)
{
  if (mValue != 0)
    delete [] mValue;
  mValue = 0;
  if (mSize > 0)
  {
    mValue = new int [mSize];
    for (int i = 0; i < mSize; i++)
      mValue[i] = value[i];
  }
}


/// Задает размер массива элементов
template <class Owner>
void TInts<Owner>::SetSize(int size)
{
  if (size > 0)
  {
    mIsChange = true;
    int* buf = 0;
    if (mValue != 0)
    {
      buf = new int [mSize];
      for (int i = 0; i < mSize; i++)
      {
        buf[i] = mValue[i];
      }

      delete [] mValue;
      mValue = 0;
    }
    else
    {
      mSize = 0;
    }

    mValue = new int [size];

    for (int i = 0; i < size; i++)
      mValue[i] = 0;

    if (buf != 0)
    {
      for (int i = 0; i < std::min(mSize, size); i++)
        mValue[i] = buf[i];
      delete [] buf;
    }
    mSize = size;
  }

}
/// Возвращает Размер массива элементов
template <class Owner>
int TInts<Owner>::GetSize()
{
  return mSize;
}


template <class Owner>
TInts<Owner>::~TInts()
{
  if (mValue != 0)
    delete [] mValue;
  mValue = 0;
  mSize = 0;
}



/// Парсер строки
template <class Owner>
void TInts<Owner>::operator = (string data)
{
  //sscanf(data.data(), "%d", &mValue);

  int l = 0;
  char *s = new char[data.size() + 1];

  strcpy(s, data.c_str());

  char *pp = strtok(s, mSeparator.c_str());
  int tt[100];
  int t = 0;
  while (pp != 0)
  {
    sscanf(pp, "%d", &t);
    tt[l] = t;
    pp = strtok(NULL, mSeparator.c_str());
    l++;
  }

  SetSize(l);
  *this = tt;

  delete[] s;

}

/// Приведение к строке
template <class Owner>
TInts<Owner>::operator string()
{
  string result;
  char ch[256];

  for (int i = 0; i < mSize - 1; i++)
  {
    memset(ch, 0, 256);
    sprintf(ch, "%d", mValue[i]);
    result += ch + mSeparator;
  }

  if ((mSize - 1) > 0)
  {
    memset(ch, 0, 256);
    sprintf(ch, "%d", mValue[mSize - 1]);
    result += ch;
  }

  return result;
}

/// Перегрузка оператора индексации
template <class Owner>
int& TInts<Owner>::operator [] (int index)
{
  return Indexer(index, mValue, mSize, this);
}

/* ======================================================================== *\
**  Реализация методов класса     TDoubles                                   **
\* ======================================================================== */



/// Копирование внутренних значений
template <class Owner>
void TDoubles<Owner>::CopyValue(double* value)
{
  if (mValue != 0)
    delete [] mValue;
  mValue = 0;
  if (mSize > 0)
  {
    mValue = new double [mSize];
    for (int i = 0; i < mSize; i++)
      mValue[i] = value[i];
  }
}


/// Задает размер массива элементов
template <class Owner>
void TDoubles<Owner>::SetSize(int size)
{
  if (size > 0)
  {
    mIsChange = true;
    double* buf = 0;
    if (mValue != 0)
    {
      buf = new double [mSize];
      for (int i = 0; i < mSize; i++)
      {
        buf[i] = mValue[i];
      }

      delete [] mValue;
      mValue = 0;
    }
    else
    {
      mSize = 0;
    }

    mValue = new double [size];

    for (int i = 0; i < size; i++)
      mValue[i] = 0;
    if (buf != 0)
    {
      for (int i = 0; i < std::min(mSize, size); i++)
        mValue[i] = buf[i];
      delete [] buf;
    }
    mSize = size;
  }
}
/// Возвращает Размер массива элементов
template <class Owner>
int TDoubles<Owner>::GetSize()
{
  return mSize;
}


template <class Owner>
TDoubles<Owner>::~TDoubles()
{
  if (mValue != 0)
    delete [] mValue;
  mValue = 0;
  mSize = 0;
}

/// Парсер строки
template <class Owner>
void TDoubles<Owner>::operator = (string data)
{
  //sscanf(data.data(), "%d", &mValue);

  int l = 0;
  char *s = new char[data.size() + 1];

  strcpy(s, data.c_str());

  char *pp = strtok(s, mSeparator.c_str());
  double tt[100];
  double t = 0;
  while (pp != 0)
  {
    sscanf(pp, "%lf", &t);
    tt[l] = t;
    pp = strtok(NULL, mSeparator.c_str());
    l++;
  }

  SetSize(l);
  *this = tt;
  delete[] s;
}

/// Приведение к строке
template <class Owner>
TDoubles<Owner>::operator string()
{
  string result;
  char ch[256];

  for (int i = 0; i < mSize - 1; i++)
  {
    memset(ch, 0, 256);
    sprintf(ch, "%lf", mValue[i]);
    result += ch + mSeparator;
  }

  if ((mSize - 1) > 0)
  {
    memset(ch, 0, 256);
    sprintf(ch, "%lf", mValue[mSize - 1]);
    result += ch;
  }

  return result;
}

/// Перегрузка оператора индексации
template <class Owner>
double& TDoubles<Owner>::operator [] (int index)
{
  return Indexer(index, mValue, mSize, this);
}

/* ======================================================================== *\
**  Реализация методов класса     TETypeMethod                                   **
\* ======================================================================== */


/// Парсер строки
template <class Owner>
void TETypeMethod<Owner>::operator = (string data)
{
  if ((data == "StandartMethod") || (data == "0"))
    *this = StandartMethod;
  if ((data == "HybridMethod") || (data == "1"))
    *this = HybridMethod;
  if ((data == "ManyNumPointMethod") || (data == "2"))
    *this = ManyNumPointMethod;
  if ((data == "UniformSearchMethod") || (data == "3"))
    *this = UniformSearchMethod;
  if ((data == "GlobalSearchMethod") || (data == "4"))
    *this = GlobalSearchMethod;
  if ((data == "MCO_Method") || (data == "5"))
    *this = MCO_Method;
}

/// Приведение к строке
template <class Owner>
TETypeMethod<Owner>::operator string()
{
  string s;
  if (mValue == StandartMethod)
    s = "StandartMethod";
  if (mValue == HybridMethod)
    s = "HybridMethod";
  if (mValue == ManyNumPointMethod)
    s = "ManyNumPointMethod";
  if (mValue == UniformSearchMethod)
    s = "UniformSearchMethod";
  if (mValue == GlobalSearchMethod)
    s = "GlobalSearchMethod";
  if (mValue == MCO_Method)
    s = "MCO_Method";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TESeparableMethodType                                   **
\* ======================================================================== */


/// Парсер строки
template <class Owner>
void TESeparableMethodType<Owner>::operator = (string data)
{
  if ((data == "Off") || (data == "0"))
    *this = Off;
  if ((data == "GridSearch") || (data == "1"))
    *this = GridSearch;
  if ((data == "GlobalMethod") || (data == "2"))
    *this = GlobalMethod;
}

/// Приведение к строке
template <class Owner>
TESeparableMethodType<Owner>::operator string()
{
  string s;
  if (mValue == Off)
    s = "Off";
  if (mValue == GridSearch)
    s = "GridSearch";
  if (mValue == GlobalMethod)
    s = "GlobalMethod";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TELocalMethodScheme                                   **
\* ======================================================================== */


/// Парсер строки
template <class Owner>
void TELocalMethodScheme<Owner>::operator = (string data)
{
  if ((data == "None") || (data == "0"))
    *this = None;
  if ((data == "FinalStart") || (data == "1"))
    *this = FinalStart;
  if ((data == "IntegratedOnePoint") || (data == "2"))
    *this = IntegratedOnePoint;
  if ((data == "IntegratedManyPoints") || (data == "3"))
    *this = IntegratedManyPoints;
}

/// Приведение к строке
template <class Owner>
TELocalMethodScheme<Owner>::operator string()
{
  string s;
  if (mValue == FinalStart)
    s = "FinalStart";
  if (mValue == None)
    s = "None";
  if (mValue == IntegratedOnePoint)
    s = "IntegratedOnePoint";
  if (mValue == IntegratedManyPoints)
    s = "IntegratedManyPoints";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TEStopCondition                                   **
\* ======================================================================== */

/// Парсер строки
template <class Owner>
void TEStopCondition<Owner>::operator = (string data)
{
  if (data == "Accuracy" || data == "0")
    *this = Accuracy;
  if (data == "OptimumVicinity" || data == "1")
    *this = OptimumVicinity;
  if (data == "OptimumVicinity2" || data == "2")
    *this = OptimumVicinity2;
  if (data == "OptimumValue" || data == "3")
    *this = OptimumValue;
}

/// Приведение к строке
template <class Owner>
TEStopCondition<Owner>::operator string()
{
  string s;
  if (mValue == Accuracy)
    s = "Accuracy";
  if (mValue == OptimumVicinity)
    s = "OptimumVicinity";
  if (mValue == OptimumVicinity2)
    s = "OptimumVicinity2";
  if (mValue == OptimumValue)
    s = "OptimumValue";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TETypeCalculation                                   **
\* ======================================================================== */

/// Парсер строки
template <class Owner>
void TETypeCalculation<Owner>::operator = (string data)
{
  if ((data == "OMP") || (data == "0"))
    *this = OMP;
  if ((data == "CUDA") || (data == "1"))
    *this = CUDA;
  if ((data == "PHI") || (data == "2"))
    *this = PHI;
}

/// Приведение к строке
template <class Owner>
TETypeCalculation<Owner>::operator string()
{
  string s;
  if (mValue == OMP)
    s = "OMP";
  if (mValue == CUDA)
    s = "CUDA";
  if (mValue == PHI)
    s = "PHI";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TETypeProcess                                   **
\* ======================================================================== */


/// Парсер строки
template <class Owner>
void TETypeProcess<Owner>::operator = (string data)
{
  if ((data == "SynchronousProcess") || (data == "0"))
    *this = SynchronousProcess;
  if ((data == "SynchronousProcessNew") || (data == "1"))
    *this = SynchronousProcessNew;
  if ((data == "AsynchronousProcess") || (data == "2"))
    *this = AsynchronousProcess;
}

/// Приведение к строке
template <class Owner>
TETypeProcess<Owner>::operator string()
{
  string s;
  if (mValue == SynchronousProcess)
    s = "SynchronousProcess";
  if (mValue == SynchronousProcessNew)
    s = "SynchronousProcessNew";
  if (mValue == AsynchronousProcess)
    s = "AsynchronousProcess";
  return s;
}

/* ======================================================================== *\
**  Реализация методов класса     TEMapType                                   **
\* ======================================================================== */

/// Парсер строки
template <class Owner>
void TEMapType<Owner>::operator = (string data)
{
  if ((data == "mpRotated") || (data == "0"))
    *this = mpRotated;
  if ((data == "mpShifted") || (data == "1"))
    *this = mpShifted;
}

/// Приведение к строке
template <class Owner>
TEMapType<Owner>::operator string()
{
  string s;
  if (mValue == mpRotated)
    s = "mpRotated";
  if (mValue == mpShifted)
    s = "mpShifted";
  return s;
}


#endif //__TYPES_H__
// - end of file ----------------------------------------------------------------------------------
