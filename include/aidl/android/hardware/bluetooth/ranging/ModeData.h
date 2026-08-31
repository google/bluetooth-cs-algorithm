/*
 * Copyright 2026 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * This file is auto-generated.  DO NOT MODIFY.
 * Using: out/host/linux-x86/bin/aidl --lang=ndk --structured --version 2 --hash 1ce66c3f521da97079f169b56452be7371c4a61f -t --stability vintf --min_sdk_version 33 --ninja -d out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging/android/hardware/bluetooth/ranging/ModeData.cpp.d -h out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/include/staging -o out/soong/.intermediates/hardware/interfaces/bluetooth/ranging/aidl/android.hardware.bluetooth.ranging-V2-ndk-source/gen/staging -Nhardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2 hardware/interfaces/bluetooth/ranging/aidl/aidl_api/android.hardware.bluetooth.ranging/2/android/hardware/bluetooth/ranging/ModeData.aidl
 *
 * DO NOT CHECK THIS FILE INTO A CODE TREE (e.g. git, etc..).
 * ALWAYS GENERATE THIS FILE FROM UPDATED AIDL COMPILER
 * AS A BUILD INTERMEDIATE ONLY. THIS IS NOT SOURCE CODE.
 */
#pragma once

#include <array>
#include <cassert>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>
// #include <android/binder_enums.h>
// #include <android/binder_interface_utils.h>
// #include <android/binder_parcelable_utils.h>
// #include <android/binder_to_string.h>
#include <aidl/android/hardware/bluetooth/ranging/ModeOneData.h>
#include <aidl/android/hardware/bluetooth/ranging/ModeThreeData.h>
#include <aidl/android/hardware/bluetooth/ranging/ModeTwoData.h>
#include <aidl/android/hardware/bluetooth/ranging/ModeZeroData.h>
#ifdef BINDER_STABILITY_SUPPORT
#include <android/binder_stability.h>
#endif  // BINDER_STABILITY_SUPPORT

#ifndef __BIONIC__
#define __assert2(a,b,c,d) ((void)0)
#endif

namespace aidl::android::hardware::bluetooth::ranging {
class ModeOneData;
class ModeThreeData;
class ModeTwoData;
class ModeZeroData;
}  // namespace aidl::android::hardware::bluetooth::ranging
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
class ModeData {
public:
  typedef std::false_type fixed_size;
  static const char* descriptor;

  enum class Tag : int32_t {
    modeZeroData = 0,
    modeOneData = 1,
    modeTwoData = 2,
    modeThreeData = 3,
  };

  // Expose tag symbols for legacy code
  static const inline Tag modeZeroData = Tag::modeZeroData;
  static const inline Tag modeOneData = Tag::modeOneData;
  static const inline Tag modeTwoData = Tag::modeTwoData;
  static const inline Tag modeThreeData = Tag::modeThreeData;

  template<typename _Tp>
  static constexpr bool _not_self = !std::is_same_v<std::remove_cv_t<std::remove_reference_t<_Tp>>, ModeData>;

  ModeData() : _value(std::in_place_index<static_cast<size_t>(modeZeroData)>, ::aidl::android::hardware::bluetooth::ranging::ModeZeroData()) { }

  template <typename _Tp, typename = std::enable_if_t<
      _not_self<_Tp> &&
      std::is_constructible_v<std::variant<::aidl::android::hardware::bluetooth::ranging::ModeZeroData, ::aidl::android::hardware::bluetooth::ranging::ModeOneData, ::aidl::android::hardware::bluetooth::ranging::ModeTwoData, ::aidl::android::hardware::bluetooth::ranging::ModeThreeData>, _Tp>
    >>
  // NOLINTNEXTLINE(google-explicit-constructor)
  constexpr ModeData(_Tp&& _arg)
      : _value(std::forward<_Tp>(_arg)) {}

  template <size_t _Np, typename... _Tp>
  constexpr explicit ModeData(std::in_place_index_t<_Np>, _Tp&&... _args)
      : _value(std::in_place_index<_Np>, std::forward<_Tp>(_args)...) {}

  template <Tag _tag, typename... _Tp>
  static ModeData make(_Tp&&... _args) {
    return ModeData(std::in_place_index<static_cast<size_t>(_tag)>, std::forward<_Tp>(_args)...);
  }

  template <Tag _tag, typename _Tp, typename... _Up>
  static ModeData make(std::initializer_list<_Tp> _il, _Up&&... _args) {
    return ModeData(std::in_place_index<static_cast<size_t>(_tag)>, std::move(_il), std::forward<_Up>(_args)...);
  }

  Tag getTag() const {
    return static_cast<Tag>(_value.index());
  }

  template <Tag _tag>
  const auto& get() const {
    if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
    return std::get<static_cast<size_t>(_tag)>(_value);
  }

  template <Tag _tag>
  auto& get() {
    if (getTag() != _tag) { __assert2(__FILE__, __LINE__, __PRETTY_FUNCTION__, "bad access: a wrong tag"); }
    return std::get<static_cast<size_t>(_tag)>(_value);
  }

  template <Tag _tag, typename... _Tp>
  void set(_Tp&&... _args) {
    _value.emplace<static_cast<size_t>(_tag)>(std::forward<_Tp>(_args)...);
  }

  // binder_status_t readFromParcel(const AParcel* _parcel);
  // binder_status_t writeToParcel(AParcel* _parcel) const;

  inline bool operator==(const ModeData& _rhs) const {
    return _value == _rhs._value;
  }
  inline bool operator<(const ModeData& _rhs) const {
    return _value < _rhs._value;
  }
  inline bool operator!=(const ModeData& _rhs) const {
    return !(*this == _rhs);
  }
  inline bool operator>(const ModeData& _rhs) const {
    return _rhs < *this;
  }
  inline bool operator>=(const ModeData& _rhs) const {
    return !(*this < _rhs);
  }
  inline bool operator<=(const ModeData& _rhs) const {
    return !(_rhs < *this);
  }

  // static const ::ndk::parcelable_stability_t _aidl_stability = ::ndk::STABILITY_VINTF;
  // inline std::string toString() const {
  //   std::ostringstream os;
  //   os << "ModeData{";
  //   switch (getTag()) {
  //   case modeZeroData: os << "modeZeroData: " << ::android::internal::ToString(get<modeZeroData>()); break;
  //   case modeOneData: os << "modeOneData: " << ::android::internal::ToString(get<modeOneData>()); break;
  //   case modeTwoData: os << "modeTwoData: " << ::android::internal::ToString(get<modeTwoData>()); break;
  //   case modeThreeData: os << "modeThreeData: " << ::android::internal::ToString(get<modeThreeData>()); break;
  //   }
  //   os << "}";
  //   return os.str();
  // }
private:
  std::variant<::aidl::android::hardware::bluetooth::ranging::ModeZeroData, ::aidl::android::hardware::bluetooth::ranging::ModeOneData, ::aidl::android::hardware::bluetooth::ranging::ModeTwoData, ::aidl::android::hardware::bluetooth::ranging::ModeThreeData> _value;
};
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
namespace aidl {
namespace android {
namespace hardware {
namespace bluetooth {
namespace ranging {
[[nodiscard]] static inline std::string toString(ModeData::Tag val) {
  switch(val) {
  case ModeData::Tag::modeZeroData:
    return "modeZeroData";
  case ModeData::Tag::modeOneData:
    return "modeOneData";
  case ModeData::Tag::modeTwoData:
    return "modeTwoData";
  case ModeData::Tag::modeThreeData:
    return "modeThreeData";
  default:
    return std::to_string(static_cast<int32_t>(val));
  }
}
}  // namespace ranging
}  // namespace bluetooth
}  // namespace hardware
}  // namespace android
}  // namespace aidl
// namespace ndk {
// namespace internal {
// #pragma clang diagnostic push
// #pragma clang diagnostic ignored "-Wc++17-extensions"
// template <>
// constexpr inline std::array<aidl::android::hardware::bluetooth::ranging::ModeData::Tag, 4> enum_values<aidl::android::hardware::bluetooth::ranging::ModeData::Tag> = {
//   aidl::android::hardware::bluetooth::ranging::ModeData::Tag::modeZeroData,
//   aidl::android::hardware::bluetooth::ranging::ModeData::Tag::modeOneData,
//   aidl::android::hardware::bluetooth::ranging::ModeData::Tag::modeTwoData,
//   aidl::android::hardware::bluetooth::ranging::ModeData::Tag::modeThreeData,
// };
// #pragma clang diagnostic pop
// }  // namespace internal
// }  // namespace ndk
