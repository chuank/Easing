/*
   Example usage for the Particle Easing library
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

   Basic.ino
   This example demonstrates how the easing library can be used along with the SparkIntervalTimer
   to create a repeating 'tween' from 0.0 to 100.0 using a sine easing curve. Remember to import the
   SparkIntervalTimer library to use this example.
 */

#include "SparkIntervalTimer.h"
#include "easing.h"

// Declare an instance of the easing object – in this example we are using EaseCubic:
// EaseBack easeObj;
// EaseBounce easeObj;
// EaseCircular easeObj;
// EaseCubic easeObj;
// EaseElastic easeObj;
// EaseExponential easeObj;
// EaseLinear easeObj;
// EaseQuadratic easeObj;
// EaseQuartic easeObj;
// EaseQuintic easeObj;
EaseSine easeObj;

// Create IntervalTimer object to update easing position at regular intervals
IntervalTimer myTimer;

// Initialise variables to keep track of normalised (0.-1.) easing position
// Note: has to be a double for accuracy!
double easedPosition = 0.0;

volatile bool easeUpdateFlag = false;                               // volatile boolean to keep ISR minimal

const uint8_t EASE_FPS        = 25;                                 // set a 'refresh rate' for the easing curve, in frames/updates per second
const double  EASE_DUR        = 3.0;                                // sec
const double  EASE_GRAIN      = (1000. / EASE_FPS) / 1000.;         // sec
const double  EASE_GRAIN_USEC = EASE_GRAIN * 1000 * 1000;           // uSec
const double  FENCE_OFFSET    = (1000 % EASE_FPS) ? 0 : EASE_GRAIN; // fencepost error offset flag; if 1000ms is divisible by FPS, we need another position update to complete the easing function

double t = 0.0;                                                     // sec; current point of the ease between 0. and EASE_DUR

// debug
long elapsed;       // debug var to track elapsed time for each complete ease

void setup() {
  delay(2000);

  Serial.begin(115200);
  Serial.print("GRAIN:" );
  Serial.println(EASE_GRAIN);

  easeObj.setDuration(EASE_DUR);         // sets the duration of the ease

  // setTotalChangeInPosition defines the magnitude of the easing range.
  // It also consequently determines the resolution of the easing function with setDuration.
  // Depending on use case, a good starting range is 100. Setting this to 1 will give you a
  // normalised range (0. to 1.) – although you will lose PLENTY of resolution
  easeObj.setTotalChangeInPosition(100);

  myTimer.begin(updateEaseISR, EASE_GRAIN_USEC, uSec);        // start ease update timer

  // debug
  elapsed = millis() - (EASE_GRAIN * 1000);
}


void loop() {
  processEase();
}


////////////

void updateEaseISR() {      // ISR, keep it minimal!
  easeUpdateFlag = true;
}


void processEase() {                                 // main ease update function
  if (easeUpdateFlag) {
    if (t <= (EASE_DUR + FENCE_OFFSET)) calcEase();  // calculate next easing position

    if (t > (EASE_DUR + FENCE_OFFSET)) {             // cycle reached; loopback
      // debug
      long d = millis() - elapsed - (EASE_GRAIN * 1000);
      Serial.printlnf("\t\t%dms", d);
      elapsed = millis();

      t = 0.0;              // reset time to zero
    }
    easeUpdateFlag = false; // ready for next ISR update
  }
}


void calcEase() {
  easedPosition = easeObj.easeInOut(t);
  t            += EASE_GRAIN;
  Serial.printlnf("%f\t\t%f", (t - EASE_GRAIN), easedPosition);     // debug
}
