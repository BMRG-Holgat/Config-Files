// SPDX-License-Identifier: GPL-3.0-or-later
// ESP32_Relay_X4_Modbus_v1.3: direct GPIO, active-low relays and inputs.
// First four VPINs are relay outputs; the next four are debounced inputs.
#ifndef IO_LCTECH_X4_H
#define IO_LCTECH_X4_H

#include <Arduino.h>
#include "IODevice.h"
#include "DIAG.h"

class LCTechX4 : public IODevice {
public:
  static void disableOutputs() {
    for (int i = 0; i < 4; ++i) {
      digitalWrite(RELAY_PINS[i], HIGH); // Preload OFF before enabling the output.
      pinMode(RELAY_PINS[i], OUTPUT);
    }
  }

  static void create(VPIN firstVpin) {
    if (checkNoOverlap(firstVpin, 8))
      new LCTechX4(firstVpin);
  }

protected:
  explicit LCTechX4(VPIN firstVpin) : IODevice(firstVpin, 8) {
    addDevice(this);
  }

  void _begin() override {
    disableOutputs();
    _relayState = 0;
    for (int i = 0; i < 4; ++i) pinMode(INPUT_PINS[i], INPUT);
    _inputState = _candidateState = readInputs();
    const unsigned long now = micros();
    for (int i = 0; i < 4; ++i) _changeSince[i] = now;
    _deviceState = DEVSTATE_NORMAL;
    delayUntil(now + SCAN_US);
    _display();
  }

  void _write(VPIN vpin, int value) override {
    const int channel = vpin - _firstVpin;
    if (channel < 0 || channel >= 4) return; // Inputs are read-only.
    const uint8_t mask = uint8_t(1U << channel);
    if (value) _relayState |= mask;
    else _relayState &= uint8_t(~mask);
    digitalWrite(RELAY_PINS[channel], value ? LOW : HIGH);
  }

  int _read(VPIN vpin) override {
    const int channel = vpin - _firstVpin;
    if (channel < 0 || channel >= 8) return 0;
    if (channel < 4)
      return (_relayState & (1U << channel)) != 0; // Commanded state only.
    return (_inputState & (1U << (channel - 4))) != 0;
  }

  bool _configure(VPIN vpin, ConfigTypeEnum configType,
                  int paramCount, int params[]) override {
    (void)params; // The board's optocoupler circuitry fixes polarity/pullups.
    const int channel = vpin - _firstVpin;
    return configType == CONFIGURE_INPUT && paramCount == 1
        && channel >= 4 && channel < 8;
  }

  void _loop(unsigned long currentMicros) override {
    const uint8_t sample = readInputs();
    for (int i = 0; i < 4; ++i) {
      const uint8_t mask = uint8_t(1U << i);
      if ((sample ^ _candidateState) & mask) {
        _candidateState ^= mask;
        _changeSince[i] = currentMicros;
      } else if (((_candidateState ^ _inputState) & mask)
                 && currentMicros - _changeSince[i] >= DEBOUNCE_US) {
        _inputState ^= mask;
      }
    }
    delayUntil(currentMicros + SCAN_US);
  }

  void _display() override {
    DIAG(F("LCTech X4 v1.3 relay VPINs %u-%u, commanded mask=%x"),
         (int)_firstVpin, (int)_firstVpin + 3, _relayState);
    DIAG(F("LCTech X4 v1.3 input VPINs %u-%u, active mask=%x (IN1=bit0)"),
         (int)_firstVpin + 4, (int)_firstVpin + 7, _inputState);
  }

private:
  static constexpr uint8_t RELAY_PINS[4] = {23, 5, 4, 13};
  static constexpr uint8_t INPUT_PINS[4] = {25, 26, 27, 33};
  static constexpr unsigned long SCAN_US = 10000UL;
  static constexpr unsigned long DEBOUNCE_US = 30000UL;
  uint8_t _relayState = 0;
  uint8_t _inputState = 0;
  uint8_t _candidateState = 0;
  unsigned long _changeSince[4] = {};

  uint8_t readInputs() {
    uint8_t active = 0;
    for (int i = 0; i < 4; ++i)
      if (digitalRead(INPUT_PINS[i]) == LOW) active |= uint8_t(1U << i);
    return active;
  }
};
#endif
