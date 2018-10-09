/*
   Particle Easing library
   Copyright 2017 Chuan Khoo

   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in the
   Software without restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies of the Software,
   and to permit persons to whom the Software is furnished to do so, subject to the
   following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
   INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
   PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
   HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
   OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
   SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Easing.h"
#include "SparkIntervalTimer.h"

IntervalTimer easeTimer;
NUMBER        easedPosition  = 0.0;
volatile bool easeUpdateFlag = false; // volatile boolean to keep ISR minimal
double        t = 0.0;                // sec; current point of the ease between 0. and EASE_DUR

// debug
#ifdef __EASING_DEBUG__
long elapsed;            // debug var to track elapsed time for each complete ease
#endif

EasingBase easeObj;         // type of easing as declared during instantiation
uint8_t    EASE_FPS;        // frames per second
NUMBER     EASE_DUR;        // sec
NUMBER     EASE_GRAIN;      // sec
NUMBER     EASE_GRAIN_USEC; // uSec
NUMBER     FENCE_OFFSET;    // fencepost error offset flag; if 1000ms is divisible by FPS, we need another position update to complete the easing function

Easing::Easing(EasingBase _easebase, NUMBER _dur = 3.0, NUMBER _totalChange, uint8_t _fps = 25) {
  // CONSTRUCTOR
  easeObj         = _easebase;
  EASE_FPS        = _fps,                                         // set a 'refresh rate' for the easing curve, in frames/updates per second
  EASE_DUR        = _dur;
  EASE_GRAIN      = (1000. / EASE_FPS) / 1000.;
  EASE_GRAIN_USEC = EASE_GRAIN * 1000 * 1000;
  FENCE_OFFSET    = (1000 % EASE_FPS) ? 0 : EASE_GRAIN;

  easeTimer.begin(updateEaseISR, EASE_GRAIN_USEC, uSec);        // start ease update timer
}


void Easing::updateEaseISR() {
  easeUpdateFlag = true;
}


void Easing::updateEase() {
  if (easeUpdateFlag) {
    if (t <= (EASE_DUR + FENCE_OFFSET)) calcEase();  // calculate next easing position

    if (t > (EASE_DUR + FENCE_OFFSET)) {             // cycle reached; loopback
      // debugging
      #ifdef __EASING_DEBUG__
      long d = millis() - elapsed - (EASE_GRAIN * 1000);
      Serial.printlnf("\t\t%dms", d);
      elapsed = millis();
      #endif

      t = 0.0;              // reset time to zero
    }
    easeUpdateFlag = false; // ready for next ISR update
  }
}


void Easing::calcEase() {
  easedPosition = easeObj.easeInOut(t);
  t            += EASE_GRAIN;
  #ifdef __EASING_DEBUG__
  Serial.printlnf("%f\t\t%f", (t - EASE_GRAIN), easedPosition);     // debug
  #endif
}