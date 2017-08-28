//
// Copyright (c) 2017 
// Author: 3grbn3@gmail.com (Gerben)
//
// A wrapper for primitive types and char arrays
//

#ifndef VALUE_H
#define VALUE_H

#include <stdlib.h>
#include <string>
//#include <iostream>

namespace gve {

class Value {

  public:
    Value();
    Value(const Value& other);
    Value(Value&& other);
    Value(std::string& v);
    template <typename T>
    Value(T v) : type_(t_null), value_(NULL), size_(0){
      *this = v;
    }
  
    ~Value();
    
    enum field_type {
      t_null       = 0,
      t_bool       = 1,
      t_char       = 2,
      t_wchar      = 3,
      t_short      = 4,
      t_int        = 5,
      t_long       = 6,
      t_longlong   = 7,
      t_float      = 8,
      t_double     = 9,
      t_longdouble = 10,
      t_cstring    = 11
    };

    field_type type(){
      return type_;
    }
    
    Value& operator=(const Value&& other);
    Value& operator=(const Value& other);

    void operator=(bool value);
    void operator=(char value);
    void operator=(wchar_t value);
    void operator=(short value);
    void operator=(int value);
    void operator=(long value);
    void operator=(long long value);
    void operator=(float value);
    void operator=(double value);
    void operator=(long double value);
    void operator=(const char* value);
    void operator=(std::string& str);

    template <typename T>
    Value& operator+=(T b){
      T v = value<T>();
      v += b;
      set(v);
      return *this;
    }

    template <typename T>
    Value& operator-=(T b){
      T v = value<T>();
      v -= b;
      set(v);
      return *this;
    }

    template <typename T>
    Value& operator*=(T b){
      T v = value<T>();
      v *= b;
      set(v);
      return *this;
    }

    template <typename T>
    Value& operator/=(T b){
      T v = value<T>();
      v /= b;
      set(v);
      return *this;
    }

    template <typename T>
    Value& operator%=(T b){
      T v = value<T>();
      v %= b;
      set(v);
      return *this;
    }

    template <typename T>
    bool operator==(T b){
      T v = value<T>();
      return v == b;
    }

    operator bool() const;
    operator char() const;
    operator wchar_t() const;
    operator short() const;
    operator int() const;
    operator long() const;
    operator long long() const;
    operator float() const;
    operator double() const;
    operator long double() const;
    operator const char*() const;

    template<class T>
    T value() const;

    friend std::ostream& operator<< (std::ostream& stream, const Value& any);

  private:
    void* value_;
    field_type type_;
    size_t size_;

    template<class T>
    void set(T value);

    virtual void *allocate(size_t size);
    virtual void deallocate(void *ptr);
};

template <class T>
const Value operator+(const Value& a, T b){
  Value r = a;
  r += b;
  return r;
}

template <class T>
const Value operator-(const Value& a, T b){
  Value r = a;
  r -= b;
  return r;
}

template <class T>
const Value operator/(const Value& a, T b){
  Value r = a;
  r /= b;
  return r;
}

template <class T>
const Value operator*(const Value& a, T b){
  Value r = a;
  r *= b;
  return r;
}

template <class T>
const Value operator%(const Value& a, T b){
  Value r = a;
  r %= b;
  return r;
}

template <class T>
const Value operator^(const Value& a, T b){
  Value r = a;
  r ^= b;
  return r;
}

template <class T>
const bool operator>(const Value& a, T b){
  T v = a;
  return v > b;
}

template <class T>
const bool operator<(const Value& a, T b){
  T v = a;
  return v < b;
}

}

#endif
