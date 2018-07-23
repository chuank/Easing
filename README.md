# easing

Easing library port of the [Arduino Easing Library](http://andybrown.me.uk/2010/12/05/animation-on-the-arduino-with-easing-functions/) (Anthony Brown), for the Particle platform.

The Arduino Easing Library itself is an AVR port of the original ActionScript easing functions [Robert Penner](http://robertpenner.com/easing/). For those of you who used to develop heavily in AS2/AS3, this will be very familiar to you as the Tweener classes. For more background and examples of the easing functions go to: http://andybrown.me.uk/2010/12/05/animation-on-the-arduino-with-easing-functions/

## Usage

Refer to the basic example for a method that uses the [SparkIntervalTimer](https://github.com/pkourany/SparkIntervalTimer) library to trigger easing updates at regular time intervals. Note that this is just one method in implementing time-accurate easing in your Particle device.

It is up to you to implement your own approach to timing intervals, reversal (i.e. palindrome/yoyo animation).

See the [examples](examples) folder for more details.

_TODO: more examples_

## Documentation

Import the library. Use the Particle library management interface to do this.
```
#include "easing.h"
```

Instantiate an easing class according to your preference:
```
SineEase easeObj;
```

Besides a sinusoidal ease, you can also choose from:
```
BackEase easeObj;
BounceEase easeObj;
CircularEase easeObj;
CubicEase easeObj;
ElasticEase easeObj;
ExponentialEase easeObj;
LinearEase easeObj;
QuadraticEase easeObj;
QuarticEase easeObj;
QuinticEase easeObj;
```
(Refer to http://andybrown.me.uk/2010/12/05/animation-on-the-arduino-with-easing-functions/ on what each easing type does)

Initialise the easing object by defining the duration, in seconds, needed of the easing operation. Typically this is done in `setup()` or anywhere in your code right before the easing is triggered:
```
easeObj.setDuration(EASE_DUR);
```

Next, define the magnitude of the easing range. This consequently determines the resolution of the easing function along with setDuration. Depending on use case, a good starting range is 100. This means your easing function will output values from 0.0 to 100.0. Setting setDuration to 1 will give you a normalised range (0. to 1.), although you will lose PLENTY of resolution.
```
easeObj.setTotalChangeInPosition(100);
```

Finally, calculate the eased position by calling the easeIn / easeOut / easeInOut function. This is typically called in some looping / animation routine in your code:
```
easedPosition = easeObj.easeInOut(t);
```
(where `easedPosition` is a previously declared double to store the eased range, and `t` is a fractional increment between 0.0 and EASE_DUR (set in `setDuration`)).


## Additional Functions

Two of the easing methods allow further configuration:

### BackEase
__setOvershoot(NUMBER)__  
set the overshoot value. The higher the value the greater the overshoot.

### ElasticEase
__setPeriod(NUMBER)__  
set the period.  

__setAmplitude(NUMBER)__  
set the amplitude.


## Contributing

Here's how you can make changes to this library and eventually contribute those changes back.

To get started, [clone the library from GitHub to your local machine](https://help.github.com/articles/cloning-a-repository/).

Change the name of the library in `library.properties` to something different. You can add your name at the end.

Modify the sources in <src> and <examples> with the new behavior.

To compile an example, use `particle compile examples/usage` command in [Particle CLI](https://docs.particle.io/guide/tools-and-features/cli#update-your-device-remotely) or use our [Desktop IDE](https://docs.particle.io/guide/tools-and-features/dev/#compiling-code).

After your changes are done you can upload them with `particle library upload` or `Upload` command in the IDE. This will create a private (only visible by you) library that you can use in other projects. Do `particle library add easing_myname` to add the library to a project on your machine or add the easing_myname library to a project on the Web IDE or Desktop IDE.

At this point, you can create a [GitHub pull request](https://help.github.com/articles/about-pull-requests/) with your changes to the original library.

If you wish to make your library public, use `particle library publish` or `Publish` command.
