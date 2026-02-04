# kotel
A Minimal Extendable Package Manager


Features:
-Extendability

-Customization

-easy scripting using lua

-easy to use,no complicated 
flags or long/confusing arguments

## How To Build
#### Requirements:
-nodejs(if also hosting a server)

-libcurl

tar(for the installing step)

-gcc
________________
1)clone the repository:
` git clone https://github.com/tohar777/kotel.git`

2)build using the make(G++)
`make build` or `make build-debug`

it will generate a release or debug binaries




## How to Use

install:

`kotel get org.example.package`

install packages locally:

`kotel localget org.example.package`

load Lua scripts:

`kotel load ./test.lua`
