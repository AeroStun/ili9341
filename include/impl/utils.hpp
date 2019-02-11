#pragma once

constexpr unsigned char operator""_uc(unsigned long long a) noexcept {
  return static_cast<unsigned char>(a);
}