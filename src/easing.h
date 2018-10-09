#pragma once

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

   Basic.ino
   This example demonstrates how the easing library can be used along with the SparkIntervalTimer
   to create a repeating 'tween' from 0.0 to 100.0 using a sine easing curve. Remember to import the
   SparkIntervalTimer library to use this example.
 */

// This will load the definition for common Particle variable types
#include "Particle.h"

#ifndef __35B04FAD_DF21_40e9_8652_8E61F19D3912
#define __35B04FAD_DF21_40e9_8652_8E61F19D3912

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

#endif
