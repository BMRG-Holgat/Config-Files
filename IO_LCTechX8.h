// SPDX-License-Identifier: GPL-3.0-or-later
// LCTech ESP32 X8 Modbus: 74HC595 relays and 74HC165 inputs on a shared bus.
// First 8 VPINs are outputs; next 8 are active-high, debounced inputs.
#ifndef IO_LCTECH_X8_H
#define IO_LCTECH_X8_H

#include <Arduino.h>
#include "IODevice.h"
#include "DIAG.h"

class LCTechX8 : public IODevice {
public:
  static void disableOutputs() {
    digitalWrite(OE, HIGH);
    pinMode(OE, OUTPUT);
  }

  static void create(VPIN firstVpin) {
    if (checkNoOverlap(firstVpin, 16))
      new LCTechX8(firstVpin);
  }

protected:
  explicit LCTechX8(VPIN firstVpin) : IODevice(firstVpin, 16) {
    addDevice(this);
  }

  void _begin() override {
    disableOutputs();
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);
    pinMode(DATA_OUT, OUTPUT);
    pinMode(DATA_IN, INPUT);
    digitalWrite(CLOCK, LOW);
    digitalWrite(DATA_OUT, LOW);
    digitalWrite(LATCH, LOW);
    _relayState = 0;
    flush();
    // Seed the startup snapshot; subsequent changes must pass debounce.
    _inputState = _candidateState = readInputs();
    const unsigned long now = micros();
    for (int i = 0; i < 8; ++i) _changeSince[i] = now;
    digitalWrite(OE, LOW);
    _deviceState = DEVSTATE_NORMAL;
    delayUntil(now + SCAN_US);
    _display();
  }

  void _write(VPIN vpin, int value) override {
    const int channel = vpin - _firstVpin;
    if (channel < 0 || channel >= 8) return; // Inputs are read-only.
    const uint8_t mask = uint8_t(1U << channel);
    if (value) _relayState |= mask; // SET = relay on.
    else _relayState &= uint8_t(~mask); // RESET = relay off.
    flush();
  }

  int _read(VPIN vpin) override {
    const int channel = vpin - _firstVpin;
    if (channel < 0 || channel >= 16) return 0;
    if (channel < 8)
      return (_relayState & (1U << channel)) != 0; // Commanded, not contact feedback.
    return (_inputState & (1U << (channel - 8))) != 0;
  }

  bool _configure(VPIN vpin, ConfigTypeEnum configType,
                  int paramCount, int params[]) override {
    (void)params; // Optocoupler circuitry sets polarity; no selectable pullup.
    const int channel = vpin - _firstVpin;
    return configType == CONFIGURE_INPUT && paramCount == 1
        && channel >= 8 && channel < 16;
  }

  void _loop(unsigned long currentMicros) override {
    const uint8_t sample = readInputs();
    for (int i = 0; i < 8; ++i) {
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
    DIAG(F("LCTech X8 relay VPINs %u-%u, commanded mask=%x"),
         (int)_firstVpin, (int)_firstVpin + 7, _relayState);
    DIAG(F("LCTech X8 input VPINs %u-%u, active mask=%x (IN1=bit0)"),
         (int)_firstVpin + 8, (int)_firstVpin + 15, _inputState);
  }

private:
  static constexpr uint8_t OE = 13;
  static constexpr uint8_t LATCH = 25;
  static constexpr uint8_t CLOCK = 26;
  static constexpr uint8_t DATA_IN = 27;
  static constexpr uint8_t DATA_OUT = 33;
  static constexpr unsigned long SCAN_US = 10000UL;
  static constexpr unsigned long DEBOUNCE_US = 30000UL;
  uint8_t _relayState = 0;
  uint8_t _inputState = 0;
  uint8_t _candidateState = 0;
  unsigned long _changeSince[8] = {};

  void flush() {
    digitalWrite(CLOCK, LOW);
    digitalWrite(LATCH, LOW);
    shiftOut(DATA_OUT, CLOCK, MSBFIRST, uint8_t(~_relayState));
    digitalWrite(LATCH, HIGH);
    // Shift register and output latch now contain the same valid relay byte.
  }

  uint8_t readInputs() {
    const uint8_t relayByte = uint8_t(~_relayState);
    digitalWrite(CLOCK, LOW);
    digitalWrite(LATCH, LOW); // Parallel load of 74HC165.
    delayMicroseconds(10);
    digitalWrite(LATCH, HIGH);
    // This edge also latches the 595: its previous shift image is still valid.
    uint8_t raw = 0;
    for (int i = 7; i >= 0; --i) {
      raw = uint8_t((raw << 1) | (digitalRead(DATA_IN) ? 1 : 0));
      // Restore the relay image using the SAME eight clocks as the input read.
      digitalWrite(DATA_OUT, (relayByte & (1U << i)) ? HIGH : LOW);
      digitalWrite(CLOCK, HIGH);
      delayMicroseconds(2);
      digitalWrite(CLOCK, LOW);
      delayMicroseconds(2);
    }
    // Commit the restored image. Every latch edge contains the same relay state.
    digitalWrite(LATCH, LOW);
    delayMicroseconds(10);
    digitalWrite(LATCH, HIGH);

    // Board wiring: IN1..8 correspond to raw bits 4,3,5,2,6,1,7,0.
    // Physical LOW is active; HAL input states are HIGH when active.
    static constexpr uint8_t masks[8] = {0x10, 0x08, 0x20, 0x04, 0x40, 0x02, 0x80, 0x01};
    uint8_t active = 0;
    for (int i = 0; i < 8; ++i)
      if (!(raw & masks[i])) active |= uint8_t(1U << i);
    return active;
  }
};
#endif
