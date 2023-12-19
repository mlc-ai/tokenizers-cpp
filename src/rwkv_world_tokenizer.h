/*!
 *  Copyright (c) 2023 by Contributors daquexian
 * \file rwkv_world_tokenizer.h
 * \brief Implementation of llm chat.
 */
#ifndef RWKV_WORLD_TOKENIZER_H_
#define RWKV_WORLD_TOKENIZER_H_

#include <exception>
#include <sstream>
#include <stdexcept>
#include <string>

#define STRINGIFY(...) STRINGIFY_(__VA_ARGS__)
#define STRINGIFY_(...) #__VA_ARGS__
#define RV_CHECK(...)                                                         \
  for (bool _rv_check_status = (__VA_ARGS__); !_rv_check_status;)             \
  throw FRException() << ("Check \"" STRINGIFY(__VA_ARGS__) "\" failed at " + \
                          std::to_string(__LINE__) + " in " __FILE__ "\n  > Error msg: ")
struct FRException : public std::runtime_error {
  FRException() : std::runtime_error("") {}
  const char* what() const noexcept override { return msg.c_str(); }
  template <typename T>
  FRException& operator<<(const T& s) {
    std::stringstream ss;
    ss << s;
    msg += ss.str();
    return *this;
  }
  std::string msg;
};

#endif  // RWKV_WORLD_TOKENIZER_H_
