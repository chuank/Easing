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

#pragma once

#if PLATFORM_ID != 6  // only the Photon is supported for now
   #error "This library only works on the Photon"
#endif

// This will load the definition for common Particle variable types
#include "Particle.h"

#ifndef __EASING_H__
#define __EASING_H__

#include "EasingConstants.h"

// include all the easing implementations
#include "easetypes/EaseBack.h"
#include "easetypes/EaseBounce.h"
#include "easetypes/EaseCircular.h"
#include "easetypes/EaseCubic.h"
#include "easetypes/EaseElastic.h"
#include "easetypes/EaseExponential.h"
#include "easetypes/EaseLinear.h"
#include "easetypes/EaseQuadratic.h"
#include "easetypes/EaseQuartic.h"
#include "easetypes/EaseQuintic.h"
#include "easetypes/EaseSine.h"


class Easing {
public:
  Easing(EasingBase _easebase, NUMBER _dur, NUMBER _totalChange, uint8_t _fps) const;

  void
  begin(void);

  NUMBER
  getDuration(void),
  getFPS(void);


private:

  NUMBER
    EASE_FPS = 25,   // set a 'refresh rate' for the easing curve, in frames/updates per second
    EASE_DUR = 3.0,  // sec
    EASE_GRAIN,      // sec
    EASE_GRAIN_USEC, // uSec
    FENCE_OFFSET;    // fencepost error offset flag; if 1000ms is divisible by FPS, we need another position update to complete the easing function
};

#endif  // __EASING_H__