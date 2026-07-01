// trace/Value.hpp
// Deprecated Value type for Exception as Value
/*
#pragma once

#include <expected>
// #include <memory>
#include <iostream>

#include "types/Error.hpp"

namespace tea {

template <typename T>
class Value {
 private:
  std::expected<T, Trigger> value_;

  explicit Value(std::expected<T, Trigger> value) : value_(std::move(value)) {
  }

 public:
  static Value<T> Ok(T value) {
    return Value<T>(std::expected<T, Trigger>(std::in_place, std::move(value)));
  }

  static Value<T> Err(Trigger error) {
    return Value<T>(std::unexpected(error));
  }

  bool isOk() const {
    return value_.has_value();
  }
  bool isErr() const {
    return !value_.has_value();
  }

  T& value() {
    if (!isOk()) {
      throw std::runtime_error("Accessing value of error result");
    }
    return value_.value();
  }

  const T& value() const {
    if (!isOk()) {
      throw std::runtime_error("Accessing value of error result");
    }
    return value_.value();
  }

  Trigger error() const {
    if (isOk()) {
      throw std::runtime_error("Accessing error of successful result");
    }
    return value_.error();
  }

  template <typename Func>
  auto map(Func&& func) const -> Value<decltype(func(std::declval<T>()))> {
    using ReturnType = decltype(func(std::declval<T>()));
    if (isErr()) {
      return Value<ReturnType>::Err(error());
    }
    return Value<ReturnType>::Ok(func(value()));
  }

  template <typename Func>
  auto andThen(Func&& func) const -> decltype(func(std::declval<T>())) {
    if (isErr()) {
      return decltype(func(std::declval<T>()))::Err(error());
    }
    return func(value());
  }

  std::expected<T, Trigger> toExpected() const {
    return value_;
  }

  explicit operator bool() const {
    return isOk();
  }

  bool operator==(const Value& other) const {
    return value_ == other.value_;
  }

  friend std::ostream& operator<<(std::ostream& os, const Value& val) {
    if (val.isOk()) {
      os << "Ok(" << val.value() << ")";
    } else {
      os << "Err(" << static_cast<int>(val.error()) << ")";
    }
    return os;
  }
};

template <typename T>
Value<T> Ok(T value) {
  return Value<T>::Ok(std::move(value));
}

template <typename T>
Value<T> Err(Trigger error) {
  return Value<T>::Err(error);
}

}  // namespace tea

*/