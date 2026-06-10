# hyprmag

A wlroots-compatible Wayland screen magnifier with basic customization options.

![hyprmag screencast](https://user-images.githubusercontent.com/63104422/280996521-71936981-d8b4-45cf-9ad7-07dc16f9b24a.gif)

# Usage

Launch it. Move the mouse. That's it.

## Options

`-h | --help` prints a help message

`-r | --radius` sets the radius of the magnifying lens

`-s | --scale` sets the zoom factor

`-g | --draw-grid` draws a pixel grid

`--grid-colour "<r> <g> <b> <a>"` sets the colour of the pixel grid

# Building

## Arch
`yay -S hyprmag-git`

## Manual

Building is done via CMake:

```sh
cmake --no-warn-unused-cli -DCMAKE_BUILD_TYPE:STRING=Release -DCMAKE_INSTALL_PREFIX:PATH=/usr -S . -B ./build
cmake --build ./build --config Release --target hyprmag -j`nproc 2>/dev/null || getconf _NPROCESSORS_CONF`
```

Install with:

```sh
cmake --install ./build
```

# Caveats

"Freezes" your displays while magnifying.
