#ifndef FLATBUFFERS_GENERATED_CSPROTO_CSPROTO_H_
#define FLATBUFFERS_GENERATED_CSPROTO_CSPROTO_H_

#include "flatbuffers/include/flatbuffers/flatbuffers.h"

namespace CSProto {

struct TouchInfo;

struct ShakeOnline;

struct ShakeOnlineR;

struct ShakeOffline;

struct ShakeOfflineR;

struct ShakeKick;

struct ShakeKickR;

struct ShakeQueryAuth;

struct ShakeQueryAuthR;

struct ControlMtu;

struct ControlMtuR;

struct ControlDelay;

struct ControlDelayR;

struct ControlApp;

struct ControlAppR;

struct ControlKillApp;

struct ControlKillAppR;

struct ControlAVFmt;

struct ControlAVFmtR;

struct ControlAVTrans;

struct ControlAVTransR;

struct ControlIFrame;

struct ControlAudio;

struct ControlAudioR;

struct ControlVideo;

struct ControlVideoR;

struct ControlScreen;

struct ControlTime;

struct InputString;

struct InputGameController;

struct InputKeyboard;

struct InputMouseKey;

struct InputMouseWheel;

struct InputMouseMove;

struct InputCursor;

struct InputTouch;

struct InputLocation;

struct InputAccelerometer;

struct InputAltimeter;

struct InputGyro;

struct InputMagnetometer;

struct InputPedometer;

struct InputProximity;

struct InputAmbientLight;

struct InputTemperature;

struct InputMoisture;

struct OutputString;

struct OutputScreen;

struct OutputVibration;

struct OutputCursor;

struct AVAudio;

struct AVVideo;

struct AVSubTitle;

struct AuthList;

struct ResolutionLevel;

MANUALLY_ALIGNED_STRUCT(4) TouchInfo FLATBUFFERS_FINAL_CLASS {
 private:
  int32_t x_;
  int32_t y_;
  float force_;

 public:
  TouchInfo() {
    memset(this, 0, sizeof(TouchInfo));
  }
  TouchInfo(const TouchInfo &_o) {
    memcpy(this, &_o, sizeof(TouchInfo));
  }
  TouchInfo(int32_t _x, int32_t _y, float _force)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        force_(flatbuffers::EndianScalar(_force)) {
  }
  int32_t x() const {
    return flatbuffers::EndianScalar(x_);
  }
  int32_t y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float force() const {
    return flatbuffers::EndianScalar(force_);
  }
};
STRUCT_END(TouchInfo, 12);

struct ShakeOnline FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ID = 4,
    VT_TOKEN = 6,
    VT_SERVER = 8,
    VT_APP = 10,
    VT_TYPE = 12
  };
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  const flatbuffers::String *token() const {
    return GetPointer<const flatbuffers::String *>(VT_TOKEN);
  }
  const flatbuffers::String *server() const {
    return GetPointer<const flatbuffers::String *>(VT_SERVER);
  }
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  int32_t type() const {
    return GetField<int32_t>(VT_TYPE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ID) &&
           verifier.Verify(id()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TOKEN) &&
           verifier.Verify(token()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SERVER) &&
           verifier.Verify(server()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           VerifyField<int32_t>(verifier, VT_TYPE) &&
           verifier.EndTable();
  }
};

struct ShakeOnlineBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(ShakeOnline::VT_ID, id);
  }
  void add_token(flatbuffers::Offset<flatbuffers::String> token) {
    fbb_.AddOffset(ShakeOnline::VT_TOKEN, token);
  }
  void add_server(flatbuffers::Offset<flatbuffers::String> server) {
    fbb_.AddOffset(ShakeOnline::VT_SERVER, server);
  }
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ShakeOnline::VT_APP, app);
  }
  void add_type(int32_t type) {
    fbb_.AddElement<int32_t>(ShakeOnline::VT_TYPE, type, 0);
  }
  ShakeOnlineBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeOnlineBuilder &operator=(const ShakeOnlineBuilder &);
  flatbuffers::Offset<ShakeOnline> Finish() {
    const auto end = fbb_.EndTable(start_, 5);
    auto o = flatbuffers::Offset<ShakeOnline>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeOnline> CreateShakeOnline(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> id = 0,
    flatbuffers::Offset<flatbuffers::String> token = 0,
    flatbuffers::Offset<flatbuffers::String> server = 0,
    flatbuffers::Offset<flatbuffers::String> app = 0,
    int32_t type = 0) {
  ShakeOnlineBuilder builder_(_fbb);
  builder_.add_type(type);
  builder_.add_app(app);
  builder_.add_server(server);
  builder_.add_token(token);
  builder_.add_id(id);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeOnline> CreateShakeOnlineDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *id = nullptr,
    const char *token = nullptr,
    const char *server = nullptr,
    const char *app = nullptr,
    int32_t type = 0) {
  return CSProto::CreateShakeOnline(
      _fbb,
      id ? _fbb.CreateString(id) : 0,
      token ? _fbb.CreateString(token) : 0,
      server ? _fbb.CreateString(server) : 0,
      app ? _fbb.CreateString(app) : 0,
      type);
}

struct ShakeOnlineR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_ID = 8,
    VT_TOKEN = 10,
    VT_SERVER = 12,
    VT_APP = 14,
    VT_TYPE = 16
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  const flatbuffers::String *id() const {
    return GetPointer<const flatbuffers::String *>(VT_ID);
  }
  const flatbuffers::String *token() const {
    return GetPointer<const flatbuffers::String *>(VT_TOKEN);
  }
  const flatbuffers::String *server() const {
    return GetPointer<const flatbuffers::String *>(VT_SERVER);
  }
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  int32_t type() const {
    return GetField<int32_t>(VT_TYPE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ID) &&
           verifier.Verify(id()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TOKEN) &&
           verifier.Verify(token()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SERVER) &&
           verifier.Verify(server()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           VerifyField<int32_t>(verifier, VT_TYPE) &&
           verifier.EndTable();
  }
};

struct ShakeOnlineRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ShakeOnlineR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ShakeOnlineR::VT_MSG, msg);
  }
  void add_id(flatbuffers::Offset<flatbuffers::String> id) {
    fbb_.AddOffset(ShakeOnlineR::VT_ID, id);
  }
  void add_token(flatbuffers::Offset<flatbuffers::String> token) {
    fbb_.AddOffset(ShakeOnlineR::VT_TOKEN, token);
  }
  void add_server(flatbuffers::Offset<flatbuffers::String> server) {
    fbb_.AddOffset(ShakeOnlineR::VT_SERVER, server);
  }
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ShakeOnlineR::VT_APP, app);
  }
  void add_type(int32_t type) {
    fbb_.AddElement<int32_t>(ShakeOnlineR::VT_TYPE, type, 0);
  }
  ShakeOnlineRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeOnlineRBuilder &operator=(const ShakeOnlineRBuilder &);
  flatbuffers::Offset<ShakeOnlineR> Finish() {
    const auto end = fbb_.EndTable(start_, 7);
    auto o = flatbuffers::Offset<ShakeOnlineR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeOnlineR> CreateShakeOnlineR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    flatbuffers::Offset<flatbuffers::String> id = 0,
    flatbuffers::Offset<flatbuffers::String> token = 0,
    flatbuffers::Offset<flatbuffers::String> server = 0,
    flatbuffers::Offset<flatbuffers::String> app = 0,
    int32_t type = 0) {
  ShakeOnlineRBuilder builder_(_fbb);
  builder_.add_type(type);
  builder_.add_app(app);
  builder_.add_server(server);
  builder_.add_token(token);
  builder_.add_id(id);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeOnlineR> CreateShakeOnlineRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    const char *id = nullptr,
    const char *token = nullptr,
    const char *server = nullptr,
    const char *app = nullptr,
    int32_t type = 0) {
  return CSProto::CreateShakeOnlineR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      id ? _fbb.CreateString(id) : 0,
      token ? _fbb.CreateString(token) : 0,
      server ? _fbb.CreateString(server) : 0,
      app ? _fbb.CreateString(app) : 0,
      type);
}

struct ShakeOffline FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           verifier.EndTable();
  }
};

struct ShakeOfflineBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ShakeOffline::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ShakeOffline::VT_MSG, msg);
  }
  ShakeOfflineBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeOfflineBuilder &operator=(const ShakeOfflineBuilder &);
  flatbuffers::Offset<ShakeOffline> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ShakeOffline>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeOffline> CreateShakeOffline(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0) {
  ShakeOfflineBuilder builder_(_fbb);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeOffline> CreateShakeOfflineDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr) {
  return CSProto::CreateShakeOffline(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0);
}

struct ShakeOfflineR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           verifier.EndTable();
  }
};

struct ShakeOfflineRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ShakeOfflineR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ShakeOfflineR::VT_MSG, msg);
  }
  ShakeOfflineRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeOfflineRBuilder &operator=(const ShakeOfflineRBuilder &);
  flatbuffers::Offset<ShakeOfflineR> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ShakeOfflineR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeOfflineR> CreateShakeOfflineR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0) {
  ShakeOfflineRBuilder builder_(_fbb);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeOfflineR> CreateShakeOfflineRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr) {
  return CSProto::CreateShakeOfflineR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0);
}

struct ShakeKick FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           verifier.EndTable();
  }
};

struct ShakeKickBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ShakeKick::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ShakeKick::VT_MSG, msg);
  }
  ShakeKickBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeKickBuilder &operator=(const ShakeKickBuilder &);
  flatbuffers::Offset<ShakeKick> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ShakeKick>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeKick> CreateShakeKick(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0) {
  ShakeKickBuilder builder_(_fbb);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeKick> CreateShakeKickDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr) {
  return CSProto::CreateShakeKick(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0);
}

struct ShakeKickR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           verifier.EndTable();
  }
};

struct ShakeKickRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ShakeKickR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ShakeKickR::VT_MSG, msg);
  }
  ShakeKickRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeKickRBuilder &operator=(const ShakeKickRBuilder &);
  flatbuffers::Offset<ShakeKickR> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ShakeKickR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeKickR> CreateShakeKickR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0) {
  ShakeKickRBuilder builder_(_fbb);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ShakeKickR> CreateShakeKickRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr) {
  return CSProto::CreateShakeKickR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0);
}

struct ShakeQueryAuth FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_QUERYAUTHORITY = 4
  };
  bool queryauthority() const {
    return GetField<uint8_t>(VT_QUERYAUTHORITY, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_QUERYAUTHORITY) &&
           verifier.EndTable();
  }
};

struct ShakeQueryAuthBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_queryauthority(bool queryauthority) {
    fbb_.AddElement<uint8_t>(ShakeQueryAuth::VT_QUERYAUTHORITY, static_cast<uint8_t>(queryauthority), 0);
  }
  ShakeQueryAuthBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeQueryAuthBuilder &operator=(const ShakeQueryAuthBuilder &);
  flatbuffers::Offset<ShakeQueryAuth> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ShakeQueryAuth>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeQueryAuth> CreateShakeQueryAuth(
    flatbuffers::FlatBufferBuilder &_fbb,
    bool queryauthority = false) {
  ShakeQueryAuthBuilder builder_(_fbb);
  builder_.add_queryauthority(queryauthority);
  return builder_.Finish();
}

struct ShakeQueryAuthR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_HASAUTHORITY = 4
  };
  bool hasauthority() const {
    return GetField<uint8_t>(VT_HASAUTHORITY, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_HASAUTHORITY) &&
           verifier.EndTable();
  }
};

struct ShakeQueryAuthRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_hasauthority(bool hasauthority) {
    fbb_.AddElement<uint8_t>(ShakeQueryAuthR::VT_HASAUTHORITY, static_cast<uint8_t>(hasauthority), 0);
  }
  ShakeQueryAuthRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ShakeQueryAuthRBuilder &operator=(const ShakeQueryAuthRBuilder &);
  flatbuffers::Offset<ShakeQueryAuthR> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ShakeQueryAuthR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ShakeQueryAuthR> CreateShakeQueryAuthR(
    flatbuffers::FlatBufferBuilder &_fbb,
    bool hasauthority = false) {
  ShakeQueryAuthRBuilder builder_(_fbb);
  builder_.add_hasauthority(hasauthority);
  return builder_.Finish();
}

struct ControlMtu FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SEG = 4
  };
  const flatbuffers::Vector<int8_t> *seg() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_SEG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SEG) &&
           verifier.Verify(seg()) &&
           verifier.EndTable();
  }
};

struct ControlMtuBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_seg(flatbuffers::Offset<flatbuffers::Vector<int8_t>> seg) {
    fbb_.AddOffset(ControlMtu::VT_SEG, seg);
  }
  ControlMtuBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlMtuBuilder &operator=(const ControlMtuBuilder &);
  flatbuffers::Offset<ControlMtu> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlMtu>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlMtu> CreateControlMtu(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> seg = 0) {
  ControlMtuBuilder builder_(_fbb);
  builder_.add_seg(seg);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlMtu> CreateControlMtuDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int8_t> *seg = nullptr) {
  return CSProto::CreateControlMtu(
      _fbb,
      seg ? _fbb.CreateVector<int8_t>(*seg) : 0);
}

struct ControlMtuR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SEG = 4
  };
  const flatbuffers::Vector<int8_t> *seg() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_SEG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_SEG) &&
           verifier.Verify(seg()) &&
           verifier.EndTable();
  }
};

struct ControlMtuRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_seg(flatbuffers::Offset<flatbuffers::Vector<int8_t>> seg) {
    fbb_.AddOffset(ControlMtuR::VT_SEG, seg);
  }
  ControlMtuRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlMtuRBuilder &operator=(const ControlMtuRBuilder &);
  flatbuffers::Offset<ControlMtuR> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlMtuR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlMtuR> CreateControlMtuR(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> seg = 0) {
  ControlMtuRBuilder builder_(_fbb);
  builder_.add_seg(seg);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlMtuR> CreateControlMtuRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int8_t> *seg = nullptr) {
  return CSProto::CreateControlMtuR(
      _fbb,
      seg ? _fbb.CreateVector<int8_t>(*seg) : 0);
}

struct ControlDelay FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TIME = 4,
    VT_DATA = 6
  };
  const flatbuffers::String *time() const {
    return GetPointer<const flatbuffers::String *>(VT_TIME);
  }
  const flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TIME) &&
           verifier.Verify(time()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct ControlDelayBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_time(flatbuffers::Offset<flatbuffers::String> time) {
    fbb_.AddOffset(ControlDelay::VT_TIME, time);
  }
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(ControlDelay::VT_DATA, data);
  }
  ControlDelayBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlDelayBuilder &operator=(const ControlDelayBuilder &);
  flatbuffers::Offset<ControlDelay> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ControlDelay>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlDelay> CreateControlDelay(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> time = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  ControlDelayBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_time(time);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlDelay> CreateControlDelayDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *time = nullptr,
    const std::vector<int8_t> *data = nullptr) {
  return CSProto::CreateControlDelay(
      _fbb,
      time ? _fbb.CreateString(time) : 0,
      data ? _fbb.CreateVector<int8_t>(*data) : 0);
}

struct ControlDelayR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TIME = 4,
    VT_DATA = 6
  };
  const flatbuffers::String *time() const {
    return GetPointer<const flatbuffers::String *>(VT_TIME);
  }
  const flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TIME) &&
           verifier.Verify(time()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct ControlDelayRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_time(flatbuffers::Offset<flatbuffers::String> time) {
    fbb_.AddOffset(ControlDelayR::VT_TIME, time);
  }
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(ControlDelayR::VT_DATA, data);
  }
  ControlDelayRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlDelayRBuilder &operator=(const ControlDelayRBuilder &);
  flatbuffers::Offset<ControlDelayR> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ControlDelayR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlDelayR> CreateControlDelayR(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> time = 0,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  ControlDelayRBuilder builder_(_fbb);
  builder_.add_data(data);
  builder_.add_time(time);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlDelayR> CreateControlDelayRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *time = nullptr,
    const std::vector<int8_t> *data = nullptr) {
  return CSProto::CreateControlDelayR(
      _fbb,
      time ? _fbb.CreateString(time) : 0,
      data ? _fbb.CreateVector<int8_t>(*data) : 0);
}

struct ControlApp FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_APP = 4
  };
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           verifier.EndTable();
  }
};

struct ControlAppBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ControlApp::VT_APP, app);
  }
  ControlAppBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAppBuilder &operator=(const ControlAppBuilder &);
  flatbuffers::Offset<ControlApp> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlApp>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlApp> CreateControlApp(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> app = 0) {
  ControlAppBuilder builder_(_fbb);
  builder_.add_app(app);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlApp> CreateControlAppDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *app = nullptr) {
  return CSProto::CreateControlApp(
      _fbb,
      app ? _fbb.CreateString(app) : 0);
}

struct ControlAppR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_APP = 8
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           verifier.EndTable();
  }
};

struct ControlAppRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlAppR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlAppR::VT_MSG, msg);
  }
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ControlAppR::VT_APP, app);
  }
  ControlAppRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAppRBuilder &operator=(const ControlAppRBuilder &);
  flatbuffers::Offset<ControlAppR> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<ControlAppR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAppR> CreateControlAppR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    flatbuffers::Offset<flatbuffers::String> app = 0) {
  ControlAppRBuilder builder_(_fbb);
  builder_.add_app(app);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlAppR> CreateControlAppRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    const char *app = nullptr) {
  return CSProto::CreateControlAppR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      app ? _fbb.CreateString(app) : 0);
}

struct ControlKillApp FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_APP = 4
  };
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           verifier.EndTable();
  }
};

struct ControlKillAppBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ControlKillApp::VT_APP, app);
  }
  ControlKillAppBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlKillAppBuilder &operator=(const ControlKillAppBuilder &);
  flatbuffers::Offset<ControlKillApp> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlKillApp>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlKillApp> CreateControlKillApp(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> app = 0) {
  ControlKillAppBuilder builder_(_fbb);
  builder_.add_app(app);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlKillApp> CreateControlKillAppDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *app = nullptr) {
  return CSProto::CreateControlKillApp(
      _fbb,
      app ? _fbb.CreateString(app) : 0);
}

struct ControlKillAppR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_APP = 8
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  const flatbuffers::String *app() const {
    return GetPointer<const flatbuffers::String *>(VT_APP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_APP) &&
           verifier.Verify(app()) &&
           verifier.EndTable();
  }
};

struct ControlKillAppRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlKillAppR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlKillAppR::VT_MSG, msg);
  }
  void add_app(flatbuffers::Offset<flatbuffers::String> app) {
    fbb_.AddOffset(ControlKillAppR::VT_APP, app);
  }
  ControlKillAppRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlKillAppRBuilder &operator=(const ControlKillAppRBuilder &);
  flatbuffers::Offset<ControlKillAppR> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<ControlKillAppR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlKillAppR> CreateControlKillAppR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    flatbuffers::Offset<flatbuffers::String> app = 0) {
  ControlKillAppRBuilder builder_(_fbb);
  builder_.add_app(app);
  builder_.add_msg(msg);
  builder_.add_code(code);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlKillAppR> CreateControlKillAppRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    const char *app = nullptr) {
  return CSProto::CreateControlKillAppR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      app ? _fbb.CreateString(app) : 0);
}

struct ControlAVFmt FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_AFMT = 4,
    VT_APROFILE = 6,
    VT_ACHANNEL = 8,
    VT_ASMPRATE = 10,
    VT_ABITRATE = 12,
    VT_VFMT = 14,
    VT_VPROFILE = 16,
    VT_VWIDTH = 18,
    VT_VHEIGHT = 20,
    VT_VFPS = 22,
    VT_VBITRATE = 24
  };
  uint8_t afmt() const {
    return GetField<uint8_t>(VT_AFMT, 0);
  }
  uint8_t aprofile() const {
    return GetField<uint8_t>(VT_APROFILE, 0);
  }
  uint8_t achannel() const {
    return GetField<uint8_t>(VT_ACHANNEL, 2);
  }
  uint16_t asmprate() const {
    return GetField<uint16_t>(VT_ASMPRATE, 44100);
  }
  uint32_t abitrate() const {
    return GetField<uint32_t>(VT_ABITRATE, 131072);
  }
  uint8_t vfmt() const {
    return GetField<uint8_t>(VT_VFMT, 0);
  }
  uint8_t vprofile() const {
    return GetField<uint8_t>(VT_VPROFILE, 0);
  }
  uint16_t vwidth() const {
    return GetField<uint16_t>(VT_VWIDTH, 1024);
  }
  uint16_t vheight() const {
    return GetField<uint16_t>(VT_VHEIGHT, 576);
  }
  uint16_t vfps() const {
    return GetField<uint16_t>(VT_VFPS, 30);
  }
  uint32_t vbitrate() const {
    return GetField<uint32_t>(VT_VBITRATE, 5242880);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_AFMT) &&
           VerifyField<uint8_t>(verifier, VT_APROFILE) &&
           VerifyField<uint8_t>(verifier, VT_ACHANNEL) &&
           VerifyField<uint16_t>(verifier, VT_ASMPRATE) &&
           VerifyField<uint32_t>(verifier, VT_ABITRATE) &&
           VerifyField<uint8_t>(verifier, VT_VFMT) &&
           VerifyField<uint8_t>(verifier, VT_VPROFILE) &&
           VerifyField<uint16_t>(verifier, VT_VWIDTH) &&
           VerifyField<uint16_t>(verifier, VT_VHEIGHT) &&
           VerifyField<uint16_t>(verifier, VT_VFPS) &&
           VerifyField<uint32_t>(verifier, VT_VBITRATE) &&
           verifier.EndTable();
  }
};

struct ControlAVFmtBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_afmt(uint8_t afmt) {
    fbb_.AddElement<uint8_t>(ControlAVFmt::VT_AFMT, afmt, 0);
  }
  void add_aprofile(uint8_t aprofile) {
    fbb_.AddElement<uint8_t>(ControlAVFmt::VT_APROFILE, aprofile, 0);
  }
  void add_achannel(uint8_t achannel) {
    fbb_.AddElement<uint8_t>(ControlAVFmt::VT_ACHANNEL, achannel, 2);
  }
  void add_asmprate(uint16_t asmprate) {
    fbb_.AddElement<uint16_t>(ControlAVFmt::VT_ASMPRATE, asmprate, 44100);
  }
  void add_abitrate(uint32_t abitrate) {
    fbb_.AddElement<uint32_t>(ControlAVFmt::VT_ABITRATE, abitrate, 131072);
  }
  void add_vfmt(uint8_t vfmt) {
    fbb_.AddElement<uint8_t>(ControlAVFmt::VT_VFMT, vfmt, 0);
  }
  void add_vprofile(uint8_t vprofile) {
    fbb_.AddElement<uint8_t>(ControlAVFmt::VT_VPROFILE, vprofile, 0);
  }
  void add_vwidth(uint16_t vwidth) {
    fbb_.AddElement<uint16_t>(ControlAVFmt::VT_VWIDTH, vwidth, 1024);
  }
  void add_vheight(uint16_t vheight) {
    fbb_.AddElement<uint16_t>(ControlAVFmt::VT_VHEIGHT, vheight, 576);
  }
  void add_vfps(uint16_t vfps) {
    fbb_.AddElement<uint16_t>(ControlAVFmt::VT_VFPS, vfps, 30);
  }
  void add_vbitrate(uint32_t vbitrate) {
    fbb_.AddElement<uint32_t>(ControlAVFmt::VT_VBITRATE, vbitrate, 5242880);
  }
  ControlAVFmtBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAVFmtBuilder &operator=(const ControlAVFmtBuilder &);
  flatbuffers::Offset<ControlAVFmt> Finish() {
    const auto end = fbb_.EndTable(start_, 11);
    auto o = flatbuffers::Offset<ControlAVFmt>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAVFmt> CreateControlAVFmt(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t afmt = 0,
    uint8_t aprofile = 0,
    uint8_t achannel = 2,
    uint16_t asmprate = 44100,
    uint32_t abitrate = 131072,
    uint8_t vfmt = 0,
    uint8_t vprofile = 0,
    uint16_t vwidth = 1024,
    uint16_t vheight = 576,
    uint16_t vfps = 30,
    uint32_t vbitrate = 5242880) {
  ControlAVFmtBuilder builder_(_fbb);
  builder_.add_vbitrate(vbitrate);
  builder_.add_abitrate(abitrate);
  builder_.add_vfps(vfps);
  builder_.add_vheight(vheight);
  builder_.add_vwidth(vwidth);
  builder_.add_asmprate(asmprate);
  builder_.add_vprofile(vprofile);
  builder_.add_vfmt(vfmt);
  builder_.add_achannel(achannel);
  builder_.add_aprofile(aprofile);
  builder_.add_afmt(afmt);
  return builder_.Finish();
}

struct ControlAVFmtR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_AFMT = 8,
    VT_APROFILE = 10,
    VT_ACHANNEL = 12,
    VT_ASMPRATE = 14,
    VT_ABITRATE = 16,
    VT_VFMT = 18,
    VT_VPROFILE = 20,
    VT_VWIDTH = 22,
    VT_VHEIGHT = 24,
    VT_VFPS = 26,
    VT_VBITRATE = 28
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  uint8_t afmt() const {
    return GetField<uint8_t>(VT_AFMT, 0);
  }
  uint8_t aprofile() const {
    return GetField<uint8_t>(VT_APROFILE, 0);
  }
  uint8_t achannel() const {
    return GetField<uint8_t>(VT_ACHANNEL, 2);
  }
  uint32_t asmprate() const {
    return GetField<uint32_t>(VT_ASMPRATE, 44100);
  }
  uint32_t abitrate() const {
    return GetField<uint32_t>(VT_ABITRATE, 131072);
  }
  uint8_t vfmt() const {
    return GetField<uint8_t>(VT_VFMT, 0);
  }
  uint8_t vprofile() const {
    return GetField<uint8_t>(VT_VPROFILE, 0);
  }
  uint16_t vwidth() const {
    return GetField<uint16_t>(VT_VWIDTH, 1024);
  }
  uint16_t vheight() const {
    return GetField<uint16_t>(VT_VHEIGHT, 576);
  }
  uint16_t vfps() const {
    return GetField<uint16_t>(VT_VFPS, 30);
  }
  uint32_t vbitrate() const {
    return GetField<uint32_t>(VT_VBITRATE, 5242880);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<uint8_t>(verifier, VT_AFMT) &&
           VerifyField<uint8_t>(verifier, VT_APROFILE) &&
           VerifyField<uint8_t>(verifier, VT_ACHANNEL) &&
           VerifyField<uint32_t>(verifier, VT_ASMPRATE) &&
           VerifyField<uint32_t>(verifier, VT_ABITRATE) &&
           VerifyField<uint8_t>(verifier, VT_VFMT) &&
           VerifyField<uint8_t>(verifier, VT_VPROFILE) &&
           VerifyField<uint16_t>(verifier, VT_VWIDTH) &&
           VerifyField<uint16_t>(verifier, VT_VHEIGHT) &&
           VerifyField<uint16_t>(verifier, VT_VFPS) &&
           VerifyField<uint32_t>(verifier, VT_VBITRATE) &&
           verifier.EndTable();
  }
};

struct ControlAVFmtRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlAVFmtR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlAVFmtR::VT_MSG, msg);
  }
  void add_afmt(uint8_t afmt) {
    fbb_.AddElement<uint8_t>(ControlAVFmtR::VT_AFMT, afmt, 0);
  }
  void add_aprofile(uint8_t aprofile) {
    fbb_.AddElement<uint8_t>(ControlAVFmtR::VT_APROFILE, aprofile, 0);
  }
  void add_achannel(uint8_t achannel) {
    fbb_.AddElement<uint8_t>(ControlAVFmtR::VT_ACHANNEL, achannel, 2);
  }
  void add_asmprate(uint32_t asmprate) {
    fbb_.AddElement<uint32_t>(ControlAVFmtR::VT_ASMPRATE, asmprate, 44100);
  }
  void add_abitrate(uint32_t abitrate) {
    fbb_.AddElement<uint32_t>(ControlAVFmtR::VT_ABITRATE, abitrate, 131072);
  }
  void add_vfmt(uint8_t vfmt) {
    fbb_.AddElement<uint8_t>(ControlAVFmtR::VT_VFMT, vfmt, 0);
  }
  void add_vprofile(uint8_t vprofile) {
    fbb_.AddElement<uint8_t>(ControlAVFmtR::VT_VPROFILE, vprofile, 0);
  }
  void add_vwidth(uint16_t vwidth) {
    fbb_.AddElement<uint16_t>(ControlAVFmtR::VT_VWIDTH, vwidth, 1024);
  }
  void add_vheight(uint16_t vheight) {
    fbb_.AddElement<uint16_t>(ControlAVFmtR::VT_VHEIGHT, vheight, 576);
  }
  void add_vfps(uint16_t vfps) {
    fbb_.AddElement<uint16_t>(ControlAVFmtR::VT_VFPS, vfps, 30);
  }
  void add_vbitrate(uint32_t vbitrate) {
    fbb_.AddElement<uint32_t>(ControlAVFmtR::VT_VBITRATE, vbitrate, 5242880);
  }
  ControlAVFmtRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAVFmtRBuilder &operator=(const ControlAVFmtRBuilder &);
  flatbuffers::Offset<ControlAVFmtR> Finish() {
    const auto end = fbb_.EndTable(start_, 13);
    auto o = flatbuffers::Offset<ControlAVFmtR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAVFmtR> CreateControlAVFmtR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    uint8_t afmt = 0,
    uint8_t aprofile = 0,
    uint8_t achannel = 2,
    uint32_t asmprate = 44100,
    uint32_t abitrate = 131072,
    uint8_t vfmt = 0,
    uint8_t vprofile = 0,
    uint16_t vwidth = 1024,
    uint16_t vheight = 576,
    uint16_t vfps = 30,
    uint32_t vbitrate = 5242880) {
  ControlAVFmtRBuilder builder_(_fbb);
  builder_.add_vbitrate(vbitrate);
  builder_.add_abitrate(abitrate);
  builder_.add_asmprate(asmprate);
  builder_.add_msg(msg);
  builder_.add_code(code);
  builder_.add_vfps(vfps);
  builder_.add_vheight(vheight);
  builder_.add_vwidth(vwidth);
  builder_.add_vprofile(vprofile);
  builder_.add_vfmt(vfmt);
  builder_.add_achannel(achannel);
  builder_.add_aprofile(aprofile);
  builder_.add_afmt(afmt);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlAVFmtR> CreateControlAVFmtRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    uint8_t afmt = 0,
    uint8_t aprofile = 0,
    uint8_t achannel = 2,
    uint32_t asmprate = 44100,
    uint32_t abitrate = 131072,
    uint8_t vfmt = 0,
    uint8_t vprofile = 0,
    uint16_t vwidth = 1024,
    uint16_t vheight = 576,
    uint16_t vfps = 30,
    uint32_t vbitrate = 5242880) {
  return CSProto::CreateControlAVFmtR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      afmt,
      aprofile,
      achannel,
      asmprate,
      abitrate,
      vfmt,
      vprofile,
      vwidth,
      vheight,
      vfps,
      vbitrate);
}

struct ControlAVTrans FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_AUDIO = 4,
    VT_VIDEO = 6,
    VT_SUBTITLE = 8
  };
  bool audio() const {
    return GetField<uint8_t>(VT_AUDIO, 1) != 0;
  }
  bool video() const {
    return GetField<uint8_t>(VT_VIDEO, 1) != 0;
  }
  bool subtitle() const {
    return GetField<uint8_t>(VT_SUBTITLE, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_AUDIO) &&
           VerifyField<uint8_t>(verifier, VT_VIDEO) &&
           VerifyField<uint8_t>(verifier, VT_SUBTITLE) &&
           verifier.EndTable();
  }
};

struct ControlAVTransBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_audio(bool audio) {
    fbb_.AddElement<uint8_t>(ControlAVTrans::VT_AUDIO, static_cast<uint8_t>(audio), 1);
  }
  void add_video(bool video) {
    fbb_.AddElement<uint8_t>(ControlAVTrans::VT_VIDEO, static_cast<uint8_t>(video), 1);
  }
  void add_subtitle(bool subtitle) {
    fbb_.AddElement<uint8_t>(ControlAVTrans::VT_SUBTITLE, static_cast<uint8_t>(subtitle), 0);
  }
  ControlAVTransBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAVTransBuilder &operator=(const ControlAVTransBuilder &);
  flatbuffers::Offset<ControlAVTrans> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<ControlAVTrans>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAVTrans> CreateControlAVTrans(
    flatbuffers::FlatBufferBuilder &_fbb,
    bool audio = true,
    bool video = true,
    bool subtitle = false) {
  ControlAVTransBuilder builder_(_fbb);
  builder_.add_subtitle(subtitle);
  builder_.add_video(video);
  builder_.add_audio(audio);
  return builder_.Finish();
}

struct ControlAVTransR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_AUDIO = 8,
    VT_VIDEO = 10,
    VT_SUBTITLE = 12
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool audio() const {
    return GetField<uint8_t>(VT_AUDIO, 1) != 0;
  }
  bool video() const {
    return GetField<uint8_t>(VT_VIDEO, 1) != 0;
  }
  bool subtitle() const {
    return GetField<uint8_t>(VT_SUBTITLE, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<uint8_t>(verifier, VT_AUDIO) &&
           VerifyField<uint8_t>(verifier, VT_VIDEO) &&
           VerifyField<uint8_t>(verifier, VT_SUBTITLE) &&
           verifier.EndTable();
  }
};

struct ControlAVTransRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlAVTransR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlAVTransR::VT_MSG, msg);
  }
  void add_audio(bool audio) {
    fbb_.AddElement<uint8_t>(ControlAVTransR::VT_AUDIO, static_cast<uint8_t>(audio), 1);
  }
  void add_video(bool video) {
    fbb_.AddElement<uint8_t>(ControlAVTransR::VT_VIDEO, static_cast<uint8_t>(video), 1);
  }
  void add_subtitle(bool subtitle) {
    fbb_.AddElement<uint8_t>(ControlAVTransR::VT_SUBTITLE, static_cast<uint8_t>(subtitle), 0);
  }
  ControlAVTransRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAVTransRBuilder &operator=(const ControlAVTransRBuilder &);
  flatbuffers::Offset<ControlAVTransR> Finish() {
    const auto end = fbb_.EndTable(start_, 5);
    auto o = flatbuffers::Offset<ControlAVTransR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAVTransR> CreateControlAVTransR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    bool audio = true,
    bool video = true,
    bool subtitle = false) {
  ControlAVTransRBuilder builder_(_fbb);
  builder_.add_msg(msg);
  builder_.add_code(code);
  builder_.add_subtitle(subtitle);
  builder_.add_video(video);
  builder_.add_audio(audio);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlAVTransR> CreateControlAVTransRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    bool audio = true,
    bool video = true,
    bool subtitle = false) {
  return CSProto::CreateControlAVTransR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      audio,
      video,
      subtitle);
}

struct ControlIFrame FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_RESERVED = 4
  };
  int8_t reserved() const {
    return GetField<int8_t>(VT_RESERVED, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_RESERVED) &&
           verifier.EndTable();
  }
};

struct ControlIFrameBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_reserved(int8_t reserved) {
    fbb_.AddElement<int8_t>(ControlIFrame::VT_RESERVED, reserved, 0);
  }
  ControlIFrameBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlIFrameBuilder &operator=(const ControlIFrameBuilder &);
  flatbuffers::Offset<ControlIFrame> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlIFrame>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlIFrame> CreateControlIFrame(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t reserved = 0) {
  ControlIFrameBuilder builder_(_fbb);
  builder_.add_reserved(reserved);
  return builder_.Finish();
}

struct ControlAudio FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MODE = 4,
    VT_BITRATE = 6
  };
  uint8_t mode() const {
    return GetField<uint8_t>(VT_MODE, 0);
  }
  uint32_t bitrate() const {
    return GetField<uint32_t>(VT_BITRATE, 131072);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_MODE) &&
           VerifyField<uint32_t>(verifier, VT_BITRATE) &&
           verifier.EndTable();
  }
};

struct ControlAudioBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_mode(uint8_t mode) {
    fbb_.AddElement<uint8_t>(ControlAudio::VT_MODE, mode, 0);
  }
  void add_bitrate(uint32_t bitrate) {
    fbb_.AddElement<uint32_t>(ControlAudio::VT_BITRATE, bitrate, 131072);
  }
  ControlAudioBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAudioBuilder &operator=(const ControlAudioBuilder &);
  flatbuffers::Offset<ControlAudio> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<ControlAudio>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAudio> CreateControlAudio(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t mode = 0,
    uint32_t bitrate = 131072) {
  ControlAudioBuilder builder_(_fbb);
  builder_.add_bitrate(bitrate);
  builder_.add_mode(mode);
  return builder_.Finish();
}

struct ControlAudioR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_PROFILE = 8,
    VT_CHANNEL = 10,
    VT_SMPRATE = 12,
    VT_BITRATE = 14
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  uint8_t profile() const {
    return GetField<uint8_t>(VT_PROFILE, 0);
  }
  uint8_t channel() const {
    return GetField<uint8_t>(VT_CHANNEL, 2);
  }
  uint32_t smprate() const {
    return GetField<uint32_t>(VT_SMPRATE, 44100);
  }
  uint32_t bitrate() const {
    return GetField<uint32_t>(VT_BITRATE, 131072);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<uint8_t>(verifier, VT_PROFILE) &&
           VerifyField<uint8_t>(verifier, VT_CHANNEL) &&
           VerifyField<uint32_t>(verifier, VT_SMPRATE) &&
           VerifyField<uint32_t>(verifier, VT_BITRATE) &&
           verifier.EndTable();
  }
};

struct ControlAudioRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlAudioR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlAudioR::VT_MSG, msg);
  }
  void add_profile(uint8_t profile) {
    fbb_.AddElement<uint8_t>(ControlAudioR::VT_PROFILE, profile, 0);
  }
  void add_channel(uint8_t channel) {
    fbb_.AddElement<uint8_t>(ControlAudioR::VT_CHANNEL, channel, 2);
  }
  void add_smprate(uint32_t smprate) {
    fbb_.AddElement<uint32_t>(ControlAudioR::VT_SMPRATE, smprate, 44100);
  }
  void add_bitrate(uint32_t bitrate) {
    fbb_.AddElement<uint32_t>(ControlAudioR::VT_BITRATE, bitrate, 131072);
  }
  ControlAudioRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlAudioRBuilder &operator=(const ControlAudioRBuilder &);
  flatbuffers::Offset<ControlAudioR> Finish() {
    const auto end = fbb_.EndTable(start_, 6);
    auto o = flatbuffers::Offset<ControlAudioR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlAudioR> CreateControlAudioR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    uint8_t profile = 0,
    uint8_t channel = 2,
    uint32_t smprate = 44100,
    uint32_t bitrate = 131072) {
  ControlAudioRBuilder builder_(_fbb);
  builder_.add_bitrate(bitrate);
  builder_.add_smprate(smprate);
  builder_.add_msg(msg);
  builder_.add_code(code);
  builder_.add_channel(channel);
  builder_.add_profile(profile);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlAudioR> CreateControlAudioRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    uint8_t profile = 0,
    uint8_t channel = 2,
    uint32_t smprate = 44100,
    uint32_t bitrate = 131072) {
  return CSProto::CreateControlAudioR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      profile,
      channel,
      smprate,
      bitrate);
}

struct ControlVideo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MODE = 4,
    VT_BITRATE = 6,
    VT_FPS = 8,
    VT_MAXIFRAME = 10
  };
  uint8_t mode() const {
    return GetField<uint8_t>(VT_MODE, 0);
  }
  uint32_t bitrate() const {
    return GetField<uint32_t>(VT_BITRATE, 5242880);
  }
  uint32_t fps() const {
    return GetField<uint32_t>(VT_FPS, 30);
  }
  uint32_t maxiframe() const {
    return GetField<uint32_t>(VT_MAXIFRAME, 100);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_MODE) &&
           VerifyField<uint32_t>(verifier, VT_BITRATE) &&
           VerifyField<uint32_t>(verifier, VT_FPS) &&
           VerifyField<uint32_t>(verifier, VT_MAXIFRAME) &&
           verifier.EndTable();
  }
};

struct ControlVideoBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_mode(uint8_t mode) {
    fbb_.AddElement<uint8_t>(ControlVideo::VT_MODE, mode, 0);
  }
  void add_bitrate(uint32_t bitrate) {
    fbb_.AddElement<uint32_t>(ControlVideo::VT_BITRATE, bitrate, 5242880);
  }
  void add_fps(uint32_t fps) {
    fbb_.AddElement<uint32_t>(ControlVideo::VT_FPS, fps, 30);
  }
  void add_maxiframe(uint32_t maxiframe) {
    fbb_.AddElement<uint32_t>(ControlVideo::VT_MAXIFRAME, maxiframe, 100);
  }
  ControlVideoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlVideoBuilder &operator=(const ControlVideoBuilder &);
  flatbuffers::Offset<ControlVideo> Finish() {
    const auto end = fbb_.EndTable(start_, 4);
    auto o = flatbuffers::Offset<ControlVideo>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlVideo> CreateControlVideo(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t mode = 0,
    uint32_t bitrate = 5242880,
    uint32_t fps = 30,
    uint32_t maxiframe = 100) {
  ControlVideoBuilder builder_(_fbb);
  builder_.add_maxiframe(maxiframe);
  builder_.add_fps(fps);
  builder_.add_bitrate(bitrate);
  builder_.add_mode(mode);
  return builder_.Finish();
}

struct ControlVideoR FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_CODE = 4,
    VT_MSG = 6,
    VT_PROFILE = 8,
    VT_WIDTH = 10,
    VT_HEIGHT = 12,
    VT_FPS = 14,
    VT_BITRATE = 16,
    VT_BITMODE = 18
  };
  int32_t code() const {
    return GetField<int32_t>(VT_CODE, 0);
  }
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  uint8_t profile() const {
    return GetField<uint8_t>(VT_PROFILE, 0);
  }
  uint16_t width() const {
    return GetField<uint16_t>(VT_WIDTH, 1024);
  }
  uint16_t height() const {
    return GetField<uint16_t>(VT_HEIGHT, 576);
  }
  uint16_t fps() const {
    return GetField<uint16_t>(VT_FPS, 30);
  }
  uint32_t bitrate() const {
    return GetField<uint32_t>(VT_BITRATE, 5242880);
  }
  uint8_t bitmode() const {
    return GetField<uint8_t>(VT_BITMODE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_CODE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           VerifyField<uint8_t>(verifier, VT_PROFILE) &&
           VerifyField<uint16_t>(verifier, VT_WIDTH) &&
           VerifyField<uint16_t>(verifier, VT_HEIGHT) &&
           VerifyField<uint16_t>(verifier, VT_FPS) &&
           VerifyField<uint32_t>(verifier, VT_BITRATE) &&
           VerifyField<uint8_t>(verifier, VT_BITMODE) &&
           verifier.EndTable();
  }
};

struct ControlVideoRBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_code(int32_t code) {
    fbb_.AddElement<int32_t>(ControlVideoR::VT_CODE, code, 0);
  }
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(ControlVideoR::VT_MSG, msg);
  }
  void add_profile(uint8_t profile) {
    fbb_.AddElement<uint8_t>(ControlVideoR::VT_PROFILE, profile, 0);
  }
  void add_width(uint16_t width) {
    fbb_.AddElement<uint16_t>(ControlVideoR::VT_WIDTH, width, 1024);
  }
  void add_height(uint16_t height) {
    fbb_.AddElement<uint16_t>(ControlVideoR::VT_HEIGHT, height, 576);
  }
  void add_fps(uint16_t fps) {
    fbb_.AddElement<uint16_t>(ControlVideoR::VT_FPS, fps, 30);
  }
  void add_bitrate(uint32_t bitrate) {
    fbb_.AddElement<uint32_t>(ControlVideoR::VT_BITRATE, bitrate, 5242880);
  }
  void add_bitmode(uint8_t bitmode) {
    fbb_.AddElement<uint8_t>(ControlVideoR::VT_BITMODE, bitmode, 0);
  }
  ControlVideoRBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlVideoRBuilder &operator=(const ControlVideoRBuilder &);
  flatbuffers::Offset<ControlVideoR> Finish() {
    const auto end = fbb_.EndTable(start_, 8);
    auto o = flatbuffers::Offset<ControlVideoR>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlVideoR> CreateControlVideoR(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    flatbuffers::Offset<flatbuffers::String> msg = 0,
    uint8_t profile = 0,
    uint16_t width = 1024,
    uint16_t height = 576,
    uint16_t fps = 30,
    uint32_t bitrate = 5242880,
    uint8_t bitmode = 0) {
  ControlVideoRBuilder builder_(_fbb);
  builder_.add_bitrate(bitrate);
  builder_.add_msg(msg);
  builder_.add_code(code);
  builder_.add_fps(fps);
  builder_.add_height(height);
  builder_.add_width(width);
  builder_.add_bitmode(bitmode);
  builder_.add_profile(profile);
  return builder_.Finish();
}

inline flatbuffers::Offset<ControlVideoR> CreateControlVideoRDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t code = 0,
    const char *msg = nullptr,
    uint8_t profile = 0,
    uint16_t width = 1024,
    uint16_t height = 576,
    uint16_t fps = 30,
    uint32_t bitrate = 5242880,
    uint8_t bitmode = 0) {
  return CSProto::CreateControlVideoR(
      _fbb,
      code,
      msg ? _fbb.CreateString(msg) : 0,
      profile,
      width,
      height,
      fps,
      bitrate,
      bitmode);
}

struct ControlScreen FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ZOOM = 4
  };
  float zoom() const {
    return GetField<float>(VT_ZOOM, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_ZOOM) &&
           verifier.EndTable();
  }
};

struct ControlScreenBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_zoom(float zoom) {
    fbb_.AddElement<float>(ControlScreen::VT_ZOOM, zoom, 0.0f);
  }
  ControlScreenBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlScreenBuilder &operator=(const ControlScreenBuilder &);
  flatbuffers::Offset<ControlScreen> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlScreen>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlScreen> CreateControlScreen(
    flatbuffers::FlatBufferBuilder &_fbb,
    float zoom = 0.0f) {
  ControlScreenBuilder builder_(_fbb);
  builder_.add_zoom(zoom);
  return builder_.Finish();
}

struct ControlTime FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TIME = 4
  };
  int32_t time() const {
    return GetField<int32_t>(VT_TIME, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_TIME) &&
           verifier.EndTable();
  }
};

struct ControlTimeBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_time(int32_t time) {
    fbb_.AddElement<int32_t>(ControlTime::VT_TIME, time, 0);
  }
  ControlTimeBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ControlTimeBuilder &operator=(const ControlTimeBuilder &);
  flatbuffers::Offset<ControlTime> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<ControlTime>(end);
    return o;
  }
};

inline flatbuffers::Offset<ControlTime> CreateControlTime(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t time = 0) {
  ControlTimeBuilder builder_(_fbb);
  builder_.add_time(time);
  return builder_.Finish();
}

struct InputString FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_STR = 4
  };
  const flatbuffers::String *str() const {
    return GetPointer<const flatbuffers::String *>(VT_STR);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_STR) &&
           verifier.Verify(str()) &&
           verifier.EndTable();
  }
};

struct InputStringBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_str(flatbuffers::Offset<flatbuffers::String> str) {
    fbb_.AddOffset(InputString::VT_STR, str);
  }
  InputStringBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputStringBuilder &operator=(const InputStringBuilder &);
  flatbuffers::Offset<InputString> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<InputString>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputString> CreateInputString(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> str = 0) {
  InputStringBuilder builder_(_fbb);
  builder_.add_str(str);
  return builder_.Finish();
}

inline flatbuffers::Offset<InputString> CreateInputStringDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *str = nullptr) {
  return CSProto::CreateInputString(
      _fbb,
      str ? _fbb.CreateString(str) : 0);
}

struct InputGameController FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_INDEX = 4,
    VT_BUTTONS = 6,
    VT_LT = 8,
    VT_RT = 10,
    VT_LX = 12,
    VT_LY = 14,
    VT_RX = 16,
    VT_RY = 18
  };
  uint8_t index() const {
    return GetField<uint8_t>(VT_INDEX, 0);
  }
  uint16_t buttons() const {
    return GetField<uint16_t>(VT_BUTTONS, 0);
  }
  uint8_t lt() const {
    return GetField<uint8_t>(VT_LT, 0);
  }
  uint8_t rt() const {
    return GetField<uint8_t>(VT_RT, 0);
  }
  int16_t lx() const {
    return GetField<int16_t>(VT_LX, 0);
  }
  int16_t ly() const {
    return GetField<int16_t>(VT_LY, 0);
  }
  int16_t rx() const {
    return GetField<int16_t>(VT_RX, 0);
  }
  int16_t ry() const {
    return GetField<int16_t>(VT_RY, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_INDEX) &&
           VerifyField<uint16_t>(verifier, VT_BUTTONS) &&
           VerifyField<uint8_t>(verifier, VT_LT) &&
           VerifyField<uint8_t>(verifier, VT_RT) &&
           VerifyField<int16_t>(verifier, VT_LX) &&
           VerifyField<int16_t>(verifier, VT_LY) &&
           VerifyField<int16_t>(verifier, VT_RX) &&
           VerifyField<int16_t>(verifier, VT_RY) &&
           verifier.EndTable();
  }
};

struct InputGameControllerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_index(uint8_t index) {
    fbb_.AddElement<uint8_t>(InputGameController::VT_INDEX, index, 0);
  }
  void add_buttons(uint16_t buttons) {
    fbb_.AddElement<uint16_t>(InputGameController::VT_BUTTONS, buttons, 0);
  }
  void add_lt(uint8_t lt) {
    fbb_.AddElement<uint8_t>(InputGameController::VT_LT, lt, 0);
  }
  void add_rt(uint8_t rt) {
    fbb_.AddElement<uint8_t>(InputGameController::VT_RT, rt, 0);
  }
  void add_lx(int16_t lx) {
    fbb_.AddElement<int16_t>(InputGameController::VT_LX, lx, 0);
  }
  void add_ly(int16_t ly) {
    fbb_.AddElement<int16_t>(InputGameController::VT_LY, ly, 0);
  }
  void add_rx(int16_t rx) {
    fbb_.AddElement<int16_t>(InputGameController::VT_RX, rx, 0);
  }
  void add_ry(int16_t ry) {
    fbb_.AddElement<int16_t>(InputGameController::VT_RY, ry, 0);
  }
  InputGameControllerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputGameControllerBuilder &operator=(const InputGameControllerBuilder &);
  flatbuffers::Offset<InputGameController> Finish() {
    const auto end = fbb_.EndTable(start_, 8);
    auto o = flatbuffers::Offset<InputGameController>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputGameController> CreateInputGameController(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t index = 0,
    uint16_t buttons = 0,
    uint8_t lt = 0,
    uint8_t rt = 0,
    int16_t lx = 0,
    int16_t ly = 0,
    int16_t rx = 0,
    int16_t ry = 0) {
  InputGameControllerBuilder builder_(_fbb);
  builder_.add_ry(ry);
  builder_.add_rx(rx);
  builder_.add_ly(ly);
  builder_.add_lx(lx);
  builder_.add_buttons(buttons);
  builder_.add_rt(rt);
  builder_.add_lt(lt);
  builder_.add_index(index);
  return builder_.Finish();
}

struct InputKeyboard FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_KEY = 4,
    VT_PRESSED = 6
  };
  uint8_t key() const {
    return GetField<uint8_t>(VT_KEY, 0);
  }
  bool pressed() const {
    return GetField<uint8_t>(VT_PRESSED, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_KEY) &&
           VerifyField<uint8_t>(verifier, VT_PRESSED) &&
           verifier.EndTable();
  }
};

struct InputKeyboardBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_key(uint8_t key) {
    fbb_.AddElement<uint8_t>(InputKeyboard::VT_KEY, key, 0);
  }
  void add_pressed(bool pressed) {
    fbb_.AddElement<uint8_t>(InputKeyboard::VT_PRESSED, static_cast<uint8_t>(pressed), 0);
  }
  InputKeyboardBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputKeyboardBuilder &operator=(const InputKeyboardBuilder &);
  flatbuffers::Offset<InputKeyboard> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputKeyboard>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputKeyboard> CreateInputKeyboard(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t key = 0,
    bool pressed = false) {
  InputKeyboardBuilder builder_(_fbb);
  builder_.add_pressed(pressed);
  builder_.add_key(key);
  return builder_.Finish();
}

struct InputMouseKey FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_KEY = 4,
    VT_PRESSED = 6
  };
  uint8_t key() const {
    return GetField<uint8_t>(VT_KEY, 0);
  }
  bool pressed() const {
    return GetField<uint8_t>(VT_PRESSED, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_KEY) &&
           VerifyField<uint8_t>(verifier, VT_PRESSED) &&
           verifier.EndTable();
  }
};

struct InputMouseKeyBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_key(uint8_t key) {
    fbb_.AddElement<uint8_t>(InputMouseKey::VT_KEY, key, 0);
  }
  void add_pressed(bool pressed) {
    fbb_.AddElement<uint8_t>(InputMouseKey::VT_PRESSED, static_cast<uint8_t>(pressed), 0);
  }
  InputMouseKeyBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputMouseKeyBuilder &operator=(const InputMouseKeyBuilder &);
  flatbuffers::Offset<InputMouseKey> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputMouseKey>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputMouseKey> CreateInputMouseKey(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t key = 0,
    bool pressed = false) {
  InputMouseKeyBuilder builder_(_fbb);
  builder_.add_pressed(pressed);
  builder_.add_key(key);
  return builder_.Finish();
}

struct InputMouseWheel FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6
  };
  int16_t x() const {
    return GetField<int16_t>(VT_X, 0);
  }
  int16_t y() const {
    return GetField<int16_t>(VT_Y, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_X) &&
           VerifyField<int16_t>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct InputMouseWheelBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(int16_t x) {
    fbb_.AddElement<int16_t>(InputMouseWheel::VT_X, x, 0);
  }
  void add_y(int16_t y) {
    fbb_.AddElement<int16_t>(InputMouseWheel::VT_Y, y, 0);
  }
  InputMouseWheelBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputMouseWheelBuilder &operator=(const InputMouseWheelBuilder &);
  flatbuffers::Offset<InputMouseWheel> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputMouseWheel>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputMouseWheel> CreateInputMouseWheel(
    flatbuffers::FlatBufferBuilder &_fbb,
    int16_t x = 0,
    int16_t y = 0) {
  InputMouseWheelBuilder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputMouseMove FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6
  };
  int16_t x() const {
    return GetField<int16_t>(VT_X, 0);
  }
  int16_t y() const {
    return GetField<int16_t>(VT_Y, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int16_t>(verifier, VT_X) &&
           VerifyField<int16_t>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct InputMouseMoveBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(int16_t x) {
    fbb_.AddElement<int16_t>(InputMouseMove::VT_X, x, 0);
  }
  void add_y(int16_t y) {
    fbb_.AddElement<int16_t>(InputMouseMove::VT_Y, y, 0);
  }
  InputMouseMoveBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputMouseMoveBuilder &operator=(const InputMouseMoveBuilder &);
  flatbuffers::Offset<InputMouseMove> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputMouseMove>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputMouseMove> CreateInputMouseMove(
    flatbuffers::FlatBufferBuilder &_fbb,
    int16_t x = 0,
    int16_t y = 0) {
  InputMouseMoveBuilder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputCursor FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct InputCursorBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(InputCursor::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(InputCursor::VT_Y, y, 0.0f);
  }
  InputCursorBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputCursorBuilder &operator=(const InputCursorBuilder &);
  flatbuffers::Offset<InputCursor> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputCursor>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputCursor> CreateInputCursor(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f) {
  InputCursorBuilder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputTouch FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_INDEX = 4,
    VT_TYPE = 6,
    VT_TOUCH = 8
  };
  int32_t index() const {
    return GetField<int32_t>(VT_INDEX, 0);
  }
  uint8_t type() const {
    return GetField<uint8_t>(VT_TYPE, 0);
  }
  const flatbuffers::Vector<const TouchInfo *> *touch() const {
    return GetPointer<const flatbuffers::Vector<const TouchInfo *> *>(VT_TOUCH);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_INDEX) &&
           VerifyField<uint8_t>(verifier, VT_TYPE) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TOUCH) &&
           verifier.Verify(touch()) &&
           verifier.EndTable();
  }
};

struct InputTouchBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_index(int32_t index) {
    fbb_.AddElement<int32_t>(InputTouch::VT_INDEX, index, 0);
  }
  void add_type(uint8_t type) {
    fbb_.AddElement<uint8_t>(InputTouch::VT_TYPE, type, 0);
  }
  void add_touch(flatbuffers::Offset<flatbuffers::Vector<const TouchInfo *>> touch) {
    fbb_.AddOffset(InputTouch::VT_TOUCH, touch);
  }
  InputTouchBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputTouchBuilder &operator=(const InputTouchBuilder &);
  flatbuffers::Offset<InputTouch> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<InputTouch>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputTouch> CreateInputTouch(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t index = 0,
    uint8_t type = 0,
    flatbuffers::Offset<flatbuffers::Vector<const TouchInfo *>> touch = 0) {
  InputTouchBuilder builder_(_fbb);
  builder_.add_touch(touch);
  builder_.add_index(index);
  builder_.add_type(type);
  return builder_.Finish();
}

inline flatbuffers::Offset<InputTouch> CreateInputTouchDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t index = 0,
    uint8_t type = 0,
    const std::vector<const TouchInfo *> *touch = nullptr) {
  return CSProto::CreateInputTouch(
      _fbb,
      index,
      type,
      touch ? _fbb.CreateVector<const TouchInfo *>(*touch) : 0);
}

struct InputLocation FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_LONGITUDE = 4,
    VT_LATITUDE = 6,
    VT_ALTITUDE = 8,
    VT_FLOOR = 10,
    VT_HORIZONTALACCURACY = 12,
    VT_VERTICALACCURACY = 14,
    VT_SPEED = 16,
    VT_DIRECTION = 18,
    VT_TIMESTAMP = 20
  };
  float longitude() const {
    return GetField<float>(VT_LONGITUDE, 0.0f);
  }
  float latitude() const {
    return GetField<float>(VT_LATITUDE, 0.0f);
  }
  float altitude() const {
    return GetField<float>(VT_ALTITUDE, 0.0f);
  }
  float floor() const {
    return GetField<float>(VT_FLOOR, 0.0f);
  }
  float horizontalaccuracy() const {
    return GetField<float>(VT_HORIZONTALACCURACY, 0.0f);
  }
  float verticalaccuracy() const {
    return GetField<float>(VT_VERTICALACCURACY, 0.0f);
  }
  float speed() const {
    return GetField<float>(VT_SPEED, 0.0f);
  }
  float direction() const {
    return GetField<float>(VT_DIRECTION, 0.0f);
  }
  const flatbuffers::String *timestamp() const {
    return GetPointer<const flatbuffers::String *>(VT_TIMESTAMP);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_LONGITUDE) &&
           VerifyField<float>(verifier, VT_LATITUDE) &&
           VerifyField<float>(verifier, VT_ALTITUDE) &&
           VerifyField<float>(verifier, VT_FLOOR) &&
           VerifyField<float>(verifier, VT_HORIZONTALACCURACY) &&
           VerifyField<float>(verifier, VT_VERTICALACCURACY) &&
           VerifyField<float>(verifier, VT_SPEED) &&
           VerifyField<float>(verifier, VT_DIRECTION) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_TIMESTAMP) &&
           verifier.Verify(timestamp()) &&
           verifier.EndTable();
  }
};

struct InputLocationBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_longitude(float longitude) {
    fbb_.AddElement<float>(InputLocation::VT_LONGITUDE, longitude, 0.0f);
  }
  void add_latitude(float latitude) {
    fbb_.AddElement<float>(InputLocation::VT_LATITUDE, latitude, 0.0f);
  }
  void add_altitude(float altitude) {
    fbb_.AddElement<float>(InputLocation::VT_ALTITUDE, altitude, 0.0f);
  }
  void add_floor(float floor) {
    fbb_.AddElement<float>(InputLocation::VT_FLOOR, floor, 0.0f);
  }
  void add_horizontalaccuracy(float horizontalaccuracy) {
    fbb_.AddElement<float>(InputLocation::VT_HORIZONTALACCURACY, horizontalaccuracy, 0.0f);
  }
  void add_verticalaccuracy(float verticalaccuracy) {
    fbb_.AddElement<float>(InputLocation::VT_VERTICALACCURACY, verticalaccuracy, 0.0f);
  }
  void add_speed(float speed) {
    fbb_.AddElement<float>(InputLocation::VT_SPEED, speed, 0.0f);
  }
  void add_direction(float direction) {
    fbb_.AddElement<float>(InputLocation::VT_DIRECTION, direction, 0.0f);
  }
  void add_timestamp(flatbuffers::Offset<flatbuffers::String> timestamp) {
    fbb_.AddOffset(InputLocation::VT_TIMESTAMP, timestamp);
  }
  InputLocationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputLocationBuilder &operator=(const InputLocationBuilder &);
  flatbuffers::Offset<InputLocation> Finish() {
    const auto end = fbb_.EndTable(start_, 9);
    auto o = flatbuffers::Offset<InputLocation>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputLocation> CreateInputLocation(
    flatbuffers::FlatBufferBuilder &_fbb,
    float longitude = 0.0f,
    float latitude = 0.0f,
    float altitude = 0.0f,
    float floor = 0.0f,
    float horizontalaccuracy = 0.0f,
    float verticalaccuracy = 0.0f,
    float speed = 0.0f,
    float direction = 0.0f,
    flatbuffers::Offset<flatbuffers::String> timestamp = 0) {
  InputLocationBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_direction(direction);
  builder_.add_speed(speed);
  builder_.add_verticalaccuracy(verticalaccuracy);
  builder_.add_horizontalaccuracy(horizontalaccuracy);
  builder_.add_floor(floor);
  builder_.add_altitude(altitude);
  builder_.add_latitude(latitude);
  builder_.add_longitude(longitude);
  return builder_.Finish();
}

inline flatbuffers::Offset<InputLocation> CreateInputLocationDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    float longitude = 0.0f,
    float latitude = 0.0f,
    float altitude = 0.0f,
    float floor = 0.0f,
    float horizontalaccuracy = 0.0f,
    float verticalaccuracy = 0.0f,
    float speed = 0.0f,
    float direction = 0.0f,
    const char *timestamp = nullptr) {
  return CSProto::CreateInputLocation(
      _fbb,
      longitude,
      latitude,
      altitude,
      floor,
      horizontalaccuracy,
      verticalaccuracy,
      speed,
      direction,
      timestamp ? _fbb.CreateString(timestamp) : 0);
}

struct InputAccelerometer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  float z() const {
    return GetField<float>(VT_Z, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           VerifyField<float>(verifier, VT_Z) &&
           verifier.EndTable();
  }
};

struct InputAccelerometerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(InputAccelerometer::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(InputAccelerometer::VT_Y, y, 0.0f);
  }
  void add_z(float z) {
    fbb_.AddElement<float>(InputAccelerometer::VT_Z, z, 0.0f);
  }
  InputAccelerometerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputAccelerometerBuilder &operator=(const InputAccelerometerBuilder &);
  flatbuffers::Offset<InputAccelerometer> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<InputAccelerometer>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputAccelerometer> CreateInputAccelerometer(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f,
    float z = 0.0f) {
  InputAccelerometerBuilder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputAltimeter FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ALTITUDE = 4,
    VT_PRESSURE = 6
  };
  float altitude() const {
    return GetField<float>(VT_ALTITUDE, 0.0f);
  }
  float pressure() const {
    return GetField<float>(VT_PRESSURE, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_ALTITUDE) &&
           VerifyField<float>(verifier, VT_PRESSURE) &&
           verifier.EndTable();
  }
};

struct InputAltimeterBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_altitude(float altitude) {
    fbb_.AddElement<float>(InputAltimeter::VT_ALTITUDE, altitude, 0.0f);
  }
  void add_pressure(float pressure) {
    fbb_.AddElement<float>(InputAltimeter::VT_PRESSURE, pressure, 0.0f);
  }
  InputAltimeterBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputAltimeterBuilder &operator=(const InputAltimeterBuilder &);
  flatbuffers::Offset<InputAltimeter> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<InputAltimeter>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputAltimeter> CreateInputAltimeter(
    flatbuffers::FlatBufferBuilder &_fbb,
    float altitude = 0.0f,
    float pressure = 0.0f) {
  InputAltimeterBuilder builder_(_fbb);
  builder_.add_pressure(pressure);
  builder_.add_altitude(altitude);
  return builder_.Finish();
}

struct InputGyro FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  float z() const {
    return GetField<float>(VT_Z, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           VerifyField<float>(verifier, VT_Z) &&
           verifier.EndTable();
  }
};

struct InputGyroBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(InputGyro::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(InputGyro::VT_Y, y, 0.0f);
  }
  void add_z(float z) {
    fbb_.AddElement<float>(InputGyro::VT_Z, z, 0.0f);
  }
  InputGyroBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputGyroBuilder &operator=(const InputGyroBuilder &);
  flatbuffers::Offset<InputGyro> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<InputGyro>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputGyro> CreateInputGyro(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f,
    float z = 0.0f) {
  InputGyroBuilder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputMagnetometer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6,
    VT_Z = 8
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  float z() const {
    return GetField<float>(VT_Z, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           VerifyField<float>(verifier, VT_Z) &&
           verifier.EndTable();
  }
};

struct InputMagnetometerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(InputMagnetometer::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(InputMagnetometer::VT_Y, y, 0.0f);
  }
  void add_z(float z) {
    fbb_.AddElement<float>(InputMagnetometer::VT_Z, z, 0.0f);
  }
  InputMagnetometerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputMagnetometerBuilder &operator=(const InputMagnetometerBuilder &);
  flatbuffers::Offset<InputMagnetometer> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<InputMagnetometer>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputMagnetometer> CreateInputMagnetometer(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f,
    float z = 0.0f) {
  InputMagnetometerBuilder builder_(_fbb);
  builder_.add_z(z);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct InputPedometer FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_STARTDATE = 4,
    VT_ENDDATE = 6,
    VT_STEPS = 8,
    VT_DISTANCE = 10,
    VT_AVERAGEACTIVEPACE = 12,
    VT_CURRENTPACE = 14,
    VT_CURRENTCADENCE = 16,
    VT_FLOORSASC = 18,
    VT_FLOORSDES = 20
  };
  const flatbuffers::String *startdate() const {
    return GetPointer<const flatbuffers::String *>(VT_STARTDATE);
  }
  const flatbuffers::String *enddate() const {
    return GetPointer<const flatbuffers::String *>(VT_ENDDATE);
  }
  float steps() const {
    return GetField<float>(VT_STEPS, 0.0f);
  }
  float distance() const {
    return GetField<float>(VT_DISTANCE, 0.0f);
  }
  float averageactivepace() const {
    return GetField<float>(VT_AVERAGEACTIVEPACE, 0.0f);
  }
  float currentpace() const {
    return GetField<float>(VT_CURRENTPACE, 0.0f);
  }
  float currentcadence() const {
    return GetField<float>(VT_CURRENTCADENCE, 0.0f);
  }
  float floorsasc() const {
    return GetField<float>(VT_FLOORSASC, 0.0f);
  }
  float floorsdes() const {
    return GetField<float>(VT_FLOORSDES, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_STARTDATE) &&
           verifier.Verify(startdate()) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_ENDDATE) &&
           verifier.Verify(enddate()) &&
           VerifyField<float>(verifier, VT_STEPS) &&
           VerifyField<float>(verifier, VT_DISTANCE) &&
           VerifyField<float>(verifier, VT_AVERAGEACTIVEPACE) &&
           VerifyField<float>(verifier, VT_CURRENTPACE) &&
           VerifyField<float>(verifier, VT_CURRENTCADENCE) &&
           VerifyField<float>(verifier, VT_FLOORSASC) &&
           VerifyField<float>(verifier, VT_FLOORSDES) &&
           verifier.EndTable();
  }
};

struct InputPedometerBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_startdate(flatbuffers::Offset<flatbuffers::String> startdate) {
    fbb_.AddOffset(InputPedometer::VT_STARTDATE, startdate);
  }
  void add_enddate(flatbuffers::Offset<flatbuffers::String> enddate) {
    fbb_.AddOffset(InputPedometer::VT_ENDDATE, enddate);
  }
  void add_steps(float steps) {
    fbb_.AddElement<float>(InputPedometer::VT_STEPS, steps, 0.0f);
  }
  void add_distance(float distance) {
    fbb_.AddElement<float>(InputPedometer::VT_DISTANCE, distance, 0.0f);
  }
  void add_averageactivepace(float averageactivepace) {
    fbb_.AddElement<float>(InputPedometer::VT_AVERAGEACTIVEPACE, averageactivepace, 0.0f);
  }
  void add_currentpace(float currentpace) {
    fbb_.AddElement<float>(InputPedometer::VT_CURRENTPACE, currentpace, 0.0f);
  }
  void add_currentcadence(float currentcadence) {
    fbb_.AddElement<float>(InputPedometer::VT_CURRENTCADENCE, currentcadence, 0.0f);
  }
  void add_floorsasc(float floorsasc) {
    fbb_.AddElement<float>(InputPedometer::VT_FLOORSASC, floorsasc, 0.0f);
  }
  void add_floorsdes(float floorsdes) {
    fbb_.AddElement<float>(InputPedometer::VT_FLOORSDES, floorsdes, 0.0f);
  }
  InputPedometerBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputPedometerBuilder &operator=(const InputPedometerBuilder &);
  flatbuffers::Offset<InputPedometer> Finish() {
    const auto end = fbb_.EndTable(start_, 9);
    auto o = flatbuffers::Offset<InputPedometer>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputPedometer> CreateInputPedometer(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> startdate = 0,
    flatbuffers::Offset<flatbuffers::String> enddate = 0,
    float steps = 0.0f,
    float distance = 0.0f,
    float averageactivepace = 0.0f,
    float currentpace = 0.0f,
    float currentcadence = 0.0f,
    float floorsasc = 0.0f,
    float floorsdes = 0.0f) {
  InputPedometerBuilder builder_(_fbb);
  builder_.add_floorsdes(floorsdes);
  builder_.add_floorsasc(floorsasc);
  builder_.add_currentcadence(currentcadence);
  builder_.add_currentpace(currentpace);
  builder_.add_averageactivepace(averageactivepace);
  builder_.add_distance(distance);
  builder_.add_steps(steps);
  builder_.add_enddate(enddate);
  builder_.add_startdate(startdate);
  return builder_.Finish();
}

inline flatbuffers::Offset<InputPedometer> CreateInputPedometerDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *startdate = nullptr,
    const char *enddate = nullptr,
    float steps = 0.0f,
    float distance = 0.0f,
    float averageactivepace = 0.0f,
    float currentpace = 0.0f,
    float currentcadence = 0.0f,
    float floorsasc = 0.0f,
    float floorsdes = 0.0f) {
  return CSProto::CreateInputPedometer(
      _fbb,
      startdate ? _fbb.CreateString(startdate) : 0,
      enddate ? _fbb.CreateString(enddate) : 0,
      steps,
      distance,
      averageactivepace,
      currentpace,
      currentcadence,
      floorsasc,
      floorsdes);
}

struct InputProximity FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_PROXIMITY = 4
  };
  bool proximity() const {
    return GetField<uint8_t>(VT_PROXIMITY, 0) != 0;
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_PROXIMITY) &&
           verifier.EndTable();
  }
};

struct InputProximityBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_proximity(bool proximity) {
    fbb_.AddElement<uint8_t>(InputProximity::VT_PROXIMITY, static_cast<uint8_t>(proximity), 0);
  }
  InputProximityBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputProximityBuilder &operator=(const InputProximityBuilder &);
  flatbuffers::Offset<InputProximity> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<InputProximity>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputProximity> CreateInputProximity(
    flatbuffers::FlatBufferBuilder &_fbb,
    bool proximity = false) {
  InputProximityBuilder builder_(_fbb);
  builder_.add_proximity(proximity);
  return builder_.Finish();
}

struct InputAmbientLight FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_RESERVED = 4
  };
  float reserved() const {
    return GetField<float>(VT_RESERVED, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_RESERVED) &&
           verifier.EndTable();
  }
};

struct InputAmbientLightBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_reserved(float reserved) {
    fbb_.AddElement<float>(InputAmbientLight::VT_RESERVED, reserved, 0.0f);
  }
  InputAmbientLightBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputAmbientLightBuilder &operator=(const InputAmbientLightBuilder &);
  flatbuffers::Offset<InputAmbientLight> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<InputAmbientLight>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputAmbientLight> CreateInputAmbientLight(
    flatbuffers::FlatBufferBuilder &_fbb,
    float reserved = 0.0f) {
  InputAmbientLightBuilder builder_(_fbb);
  builder_.add_reserved(reserved);
  return builder_.Finish();
}

struct InputTemperature FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_TEMPERATURE = 4
  };
  float temperature() const {
    return GetField<float>(VT_TEMPERATURE, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_TEMPERATURE) &&
           verifier.EndTable();
  }
};

struct InputTemperatureBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_temperature(float temperature) {
    fbb_.AddElement<float>(InputTemperature::VT_TEMPERATURE, temperature, 0.0f);
  }
  InputTemperatureBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputTemperatureBuilder &operator=(const InputTemperatureBuilder &);
  flatbuffers::Offset<InputTemperature> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<InputTemperature>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputTemperature> CreateInputTemperature(
    flatbuffers::FlatBufferBuilder &_fbb,
    float temperature = 0.0f) {
  InputTemperatureBuilder builder_(_fbb);
  builder_.add_temperature(temperature);
  return builder_.Finish();
}

struct InputMoisture FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MOISTURE = 4
  };
  float moisture() const {
    return GetField<float>(VT_MOISTURE, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_MOISTURE) &&
           verifier.EndTable();
  }
};

struct InputMoistureBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_moisture(float moisture) {
    fbb_.AddElement<float>(InputMoisture::VT_MOISTURE, moisture, 0.0f);
  }
  InputMoistureBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  InputMoistureBuilder &operator=(const InputMoistureBuilder &);
  flatbuffers::Offset<InputMoisture> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<InputMoisture>(end);
    return o;
  }
};

inline flatbuffers::Offset<InputMoisture> CreateInputMoisture(
    flatbuffers::FlatBufferBuilder &_fbb,
    float moisture = 0.0f) {
  InputMoistureBuilder builder_(_fbb);
  builder_.add_moisture(moisture);
  return builder_.Finish();
}

struct OutputString FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_MSG = 4
  };
  const flatbuffers::String *msg() const {
    return GetPointer<const flatbuffers::String *>(VT_MSG);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_MSG) &&
           verifier.Verify(msg()) &&
           verifier.EndTable();
  }
};

struct OutputStringBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_msg(flatbuffers::Offset<flatbuffers::String> msg) {
    fbb_.AddOffset(OutputString::VT_MSG, msg);
  }
  OutputStringBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  OutputStringBuilder &operator=(const OutputStringBuilder &);
  flatbuffers::Offset<OutputString> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<OutputString>(end);
    return o;
  }
};

inline flatbuffers::Offset<OutputString> CreateOutputString(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> msg = 0) {
  OutputStringBuilder builder_(_fbb);
  builder_.add_msg(msg);
  return builder_.Finish();
}

inline flatbuffers::Offset<OutputString> CreateOutputStringDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *msg = nullptr) {
  return CSProto::CreateOutputString(
      _fbb,
      msg ? _fbb.CreateString(msg) : 0);
}

struct OutputScreen FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ROTATION = 4,
    VT_WIDTH = 6,
    VT_HEIGHT = 8,
    VT_FPS = 10
  };
  int8_t rotation() const {
    return GetField<int8_t>(VT_ROTATION, 0);
  }
  uint16_t width() const {
    return GetField<uint16_t>(VT_WIDTH, 1280);
  }
  uint16_t height() const {
    return GetField<uint16_t>(VT_HEIGHT, 720);
  }
  uint16_t fps() const {
    return GetField<uint16_t>(VT_FPS, 60);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int8_t>(verifier, VT_ROTATION) &&
           VerifyField<uint16_t>(verifier, VT_WIDTH) &&
           VerifyField<uint16_t>(verifier, VT_HEIGHT) &&
           VerifyField<uint16_t>(verifier, VT_FPS) &&
           verifier.EndTable();
  }
};

struct OutputScreenBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_rotation(int8_t rotation) {
    fbb_.AddElement<int8_t>(OutputScreen::VT_ROTATION, rotation, 0);
  }
  void add_width(uint16_t width) {
    fbb_.AddElement<uint16_t>(OutputScreen::VT_WIDTH, width, 1280);
  }
  void add_height(uint16_t height) {
    fbb_.AddElement<uint16_t>(OutputScreen::VT_HEIGHT, height, 720);
  }
  void add_fps(uint16_t fps) {
    fbb_.AddElement<uint16_t>(OutputScreen::VT_FPS, fps, 60);
  }
  OutputScreenBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  OutputScreenBuilder &operator=(const OutputScreenBuilder &);
  flatbuffers::Offset<OutputScreen> Finish() {
    const auto end = fbb_.EndTable(start_, 4);
    auto o = flatbuffers::Offset<OutputScreen>(end);
    return o;
  }
};

inline flatbuffers::Offset<OutputScreen> CreateOutputScreen(
    flatbuffers::FlatBufferBuilder &_fbb,
    int8_t rotation = 0,
    uint16_t width = 1280,
    uint16_t height = 720,
    uint16_t fps = 60) {
  OutputScreenBuilder builder_(_fbb);
  builder_.add_fps(fps);
  builder_.add_height(height);
  builder_.add_width(width);
  builder_.add_rotation(rotation);
  return builder_.Finish();
}

struct OutputVibration FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_L = 4,
    VT_R = 6
  };
  uint16_t l() const {
    return GetField<uint16_t>(VT_L, 0);
  }
  uint16_t r() const {
    return GetField<uint16_t>(VT_R, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint16_t>(verifier, VT_L) &&
           VerifyField<uint16_t>(verifier, VT_R) &&
           verifier.EndTable();
  }
};

struct OutputVibrationBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_l(uint16_t l) {
    fbb_.AddElement<uint16_t>(OutputVibration::VT_L, l, 0);
  }
  void add_r(uint16_t r) {
    fbb_.AddElement<uint16_t>(OutputVibration::VT_R, r, 0);
  }
  OutputVibrationBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  OutputVibrationBuilder &operator=(const OutputVibrationBuilder &);
  flatbuffers::Offset<OutputVibration> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<OutputVibration>(end);
    return o;
  }
};

inline flatbuffers::Offset<OutputVibration> CreateOutputVibration(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint16_t l = 0,
    uint16_t r = 0) {
  OutputVibrationBuilder builder_(_fbb);
  builder_.add_r(r);
  builder_.add_l(l);
  return builder_.Finish();
}

struct OutputCursor FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_X = 4,
    VT_Y = 6
  };
  float x() const {
    return GetField<float>(VT_X, 0.0f);
  }
  float y() const {
    return GetField<float>(VT_Y, 0.0f);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_X) &&
           VerifyField<float>(verifier, VT_Y) &&
           verifier.EndTable();
  }
};

struct OutputCursorBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_x(float x) {
    fbb_.AddElement<float>(OutputCursor::VT_X, x, 0.0f);
  }
  void add_y(float y) {
    fbb_.AddElement<float>(OutputCursor::VT_Y, y, 0.0f);
  }
  OutputCursorBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  OutputCursorBuilder &operator=(const OutputCursorBuilder &);
  flatbuffers::Offset<OutputCursor> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<OutputCursor>(end);
    return o;
  }
};

inline flatbuffers::Offset<OutputCursor> CreateOutputCursor(
    flatbuffers::FlatBufferBuilder &_fbb,
    float x = 0.0f,
    float y = 0.0f) {
  OutputCursorBuilder builder_(_fbb);
  builder_.add_y(y);
  builder_.add_x(x);
  return builder_.Finish();
}

struct AVAudio FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4
  };
  const flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct AVAudioBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(AVAudio::VT_DATA, data);
  }
  AVAudioBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AVAudioBuilder &operator=(const AVAudioBuilder &);
  flatbuffers::Offset<AVAudio> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<AVAudio>(end);
    return o;
  }
};

inline flatbuffers::Offset<AVAudio> CreateAVAudio(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  AVAudioBuilder builder_(_fbb);
  builder_.add_data(data);
  return builder_.Finish();
}

inline flatbuffers::Offset<AVAudio> CreateAVAudioDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int8_t> *data = nullptr) {
  return CSProto::CreateAVAudio(
      _fbb,
      data ? _fbb.CreateVector<int8_t>(*data) : 0);
}

struct AVVideo FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4
  };
  const flatbuffers::Vector<int8_t> *data() const {
    return GetPointer<const flatbuffers::Vector<int8_t> *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct AVVideoBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(flatbuffers::Offset<flatbuffers::Vector<int8_t>> data) {
    fbb_.AddOffset(AVVideo::VT_DATA, data);
  }
  AVVideoBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AVVideoBuilder &operator=(const AVVideoBuilder &);
  flatbuffers::Offset<AVVideo> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<AVVideo>(end);
    return o;
  }
};

inline flatbuffers::Offset<AVVideo> CreateAVVideo(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<int8_t>> data = 0) {
  AVVideoBuilder builder_(_fbb);
  builder_.add_data(data);
  return builder_.Finish();
}

inline flatbuffers::Offset<AVVideo> CreateAVVideoDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<int8_t> *data = nullptr) {
  return CSProto::CreateAVVideo(
      _fbb,
      data ? _fbb.CreateVector<int8_t>(*data) : 0);
}

struct AVSubTitle FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4
  };
  const flatbuffers::String *data() const {
    return GetPointer<const flatbuffers::String *>(VT_DATA);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           verifier.EndTable();
  }
};

struct AVSubTitleBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(flatbuffers::Offset<flatbuffers::String> data) {
    fbb_.AddOffset(AVSubTitle::VT_DATA, data);
  }
  AVSubTitleBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AVSubTitleBuilder &operator=(const AVSubTitleBuilder &);
  flatbuffers::Offset<AVSubTitle> Finish() {
    const auto end = fbb_.EndTable(start_, 1);
    auto o = flatbuffers::Offset<AVSubTitle>(end);
    return o;
  }
};

inline flatbuffers::Offset<AVSubTitle> CreateAVSubTitle(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> data = 0) {
  AVSubTitleBuilder builder_(_fbb);
  builder_.add_data(data);
  return builder_.Finish();
}

inline flatbuffers::Offset<AVSubTitle> CreateAVSubTitleDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *data = nullptr) {
  return CSProto::CreateAVSubTitle(
      _fbb,
      data ? _fbb.CreateString(data) : 0);
}

struct AuthList FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_DATA = 4,
    VT_ERRORCODE = 6
  };
  const flatbuffers::String *data() const {
    return GetPointer<const flatbuffers::String *>(VT_DATA);
  }
  int32_t errorcode() const {
    return GetField<int32_t>(VT_ERRORCODE, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<flatbuffers::uoffset_t>(verifier, VT_DATA) &&
           verifier.Verify(data()) &&
           VerifyField<int32_t>(verifier, VT_ERRORCODE) &&
           verifier.EndTable();
  }
};

struct AuthListBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_data(flatbuffers::Offset<flatbuffers::String> data) {
    fbb_.AddOffset(AuthList::VT_DATA, data);
  }
  void add_errorcode(int32_t errorcode) {
    fbb_.AddElement<int32_t>(AuthList::VT_ERRORCODE, errorcode, 0);
  }
  AuthListBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  AuthListBuilder &operator=(const AuthListBuilder &);
  flatbuffers::Offset<AuthList> Finish() {
    const auto end = fbb_.EndTable(start_, 2);
    auto o = flatbuffers::Offset<AuthList>(end);
    return o;
  }
};

inline flatbuffers::Offset<AuthList> CreateAuthList(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> data = 0,
    int32_t errorcode = 0) {
  AuthListBuilder builder_(_fbb);
  builder_.add_errorcode(errorcode);
  builder_.add_data(data);
  return builder_.Finish();
}

inline flatbuffers::Offset<AuthList> CreateAuthListDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *data = nullptr,
    int32_t errorcode = 0) {
  return CSProto::CreateAuthList(
      _fbb,
      data ? _fbb.CreateString(data) : 0,
      errorcode);
}

struct ResolutionLevel FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_LEVEL = 4,
    VT_WIDTH = 6,
    VT_HEIGHT = 8
  };
  uint8_t level() const {
    return GetField<uint8_t>(VT_LEVEL, 2);
  }
  uint16_t width() const {
    return GetField<uint16_t>(VT_WIDTH, 480);
  }
  uint16_t height() const {
    return GetField<uint16_t>(VT_HEIGHT, 800);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<uint8_t>(verifier, VT_LEVEL) &&
           VerifyField<uint16_t>(verifier, VT_WIDTH) &&
           VerifyField<uint16_t>(verifier, VT_HEIGHT) &&
           verifier.EndTable();
  }
};

struct ResolutionLevelBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_level(uint8_t level) {
    fbb_.AddElement<uint8_t>(ResolutionLevel::VT_LEVEL, level, 2);
  }
  void add_width(uint16_t width) {
    fbb_.AddElement<uint16_t>(ResolutionLevel::VT_WIDTH, width, 480);
  }
  void add_height(uint16_t height) {
    fbb_.AddElement<uint16_t>(ResolutionLevel::VT_HEIGHT, height, 800);
  }
  ResolutionLevelBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ResolutionLevelBuilder &operator=(const ResolutionLevelBuilder &);
  flatbuffers::Offset<ResolutionLevel> Finish() {
    const auto end = fbb_.EndTable(start_, 3);
    auto o = flatbuffers::Offset<ResolutionLevel>(end);
    return o;
  }
};

inline flatbuffers::Offset<ResolutionLevel> CreateResolutionLevel(
    flatbuffers::FlatBufferBuilder &_fbb,
    uint8_t level = 2,
    uint16_t width = 480,
    uint16_t height = 800) {
  ResolutionLevelBuilder builder_(_fbb);
  builder_.add_height(height);
  builder_.add_width(width);
  builder_.add_level(level);
  return builder_.Finish();
}

}  // namespace CSProto

#endif
