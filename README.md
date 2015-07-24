# kati

kati is an experimental GNU make clone.
The main goal of this tool is to speed-up incremental build of Android.

## Installing kati

### Build kati

    % cd ~/src
    % git clone https://github.com/google/kati
    % cd kati
    % make

All you need is `m2n`, `ckati`, `ninja` binaries on your PATH.

### Using Homebrew

kati for [Homebrew](http://brew.sh/) is available:

    % brew install --HEAD homebrew/head-only/kati

## How to use for Android

Currently, kati does not offer a faster build by itself. It instead converts
your Makefile to a ninja file.

### Build Android

    % cd <android-directory>
    % source build/envsetup.sh
    % lunch <your-choice>
    % m2n --kati_stats  # Use --goma if you are a Googler.
    % ./ninja.sh

## More usage examples

### "make clean"

    % ./ninja.sh -t clean

Note ./ninja.sh passes all parameters to ninja.

### Build a specific target

For example, the following is equivalent to "make cts":

    % ./ninja.sh cts

Or, if you know the path you want, you can do:

    % ./ninja.sh out/host/linux-x86/bin/adb

### Specify the number of default jobs used by ninja

    % ~/src/kati/m2n -j10
    % ./ninja.sh

Or

    % ./ninja.sh -j10

Note the latter kills the parallelism of goma.
