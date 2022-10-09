Rectifying Octave
===

This [lv2 plugin](https://en.wikipedia.org/wiki/LV2) does a pure octave by inverting all negative values of the input. This is basically what an electronic rectifier (not the famous rectifier ampplifiers) does.

It is similiar to what fuzz octave pedals try to do but accomplishes this in an idealized manner without simulating electronic components and of course without the fuzz.

This is achieved without adding any notable latency as would be done by pedals using an FFT approach or similar.

A potentially problematic DC offset is removed by subtracting a rolling moving average of 2000 samples.
NOTE: The output of the pure octaved signal is a little quieter than the input. This has to be ammended by a compressor with a gain of up to 2.0. Sudden loud attacks will reach maximum output until the rolling average takes care of the DC part of the output again. So using only an amplifier would clip the output.

Install
===
Install the pre compiled artifacts from https://github.com/rominator1983/rectifyingOctave.lv2/releases
- Create a new folder in your lv2 directory (For example ~/.lv2/ or /usr/lib/lv2 or /usr/local/lib/lv2/ would all work in Ubuntu Studio)
- Copy rectifyingOctave.so, manifest.ttl and rectifyingOctave.ttl to this new folder.
- Restart/refresh your lv2 host

Build on your own
===
-  `./waf configure`
-  `./waf build`
-  `sudo ./waf install`
- Restart/refresh your lv2 host
