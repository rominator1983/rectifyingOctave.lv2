Rectifying Octave
===

This [lv2 plugin](https://en.wikipedia.org/wiki/LV2) does a pure octave by inverting all negative values of the input. This is basically what an electronic rectifyer (not the famous rectifyer ampplifiers) does.

It is similiar to what fuzz octave pedals try to do but accomplishes this in an idealized manner without simulating electronic components and of course without the fuzz.

A potentially problematic DC offset is then removed by subtracting a rolling moving average of 2000 samples.
A gain of 1.5 partially restores the amplitude of the input after the rectification.
After a silence a suden loud attack can thus lead to some audible clipping which could only be avoided by sacrifying amplitude.

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
