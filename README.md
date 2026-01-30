# kotel
A Minimal Extendable Package Manager


Features:
-Extendability

-Customization

-easy scripting using lua

-easy to use,no complicated 
flags or long/confusing arguments

## How To Build

1)clone the repository:
` git clone https://github.com/tohar777/kotel.git`

2)build using the compile.sh(G++)
`./compile.sh`

it will generate a release and debug binaries

2.1) in case of premission denied:
`sudo(or doas) bash ./compile.sh`


## How to Use

install:

`kotel get org.example.package`

load Lua scripts:

`kotel load ./test.lua`