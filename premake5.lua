
solution "pmap"
  configurations "lib"
  objdir         "build/obj"
  
project "pmap"
  location       "build"
  targetdir      "lib"
  targetname     "pmap"
  kind           "StaticLib"
  language       "C"
  files        { "src/**.c" }
  includedirs  { "include" }
  --links        { "GL" }
  --linkoptions  { "`sdl2-config --static-libs`" }
  buildoptions { "-Wall", "`sdl2-config --cflags`" }
