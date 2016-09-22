

add_library(thinger SHARED
  dllmain.cpp
  thinger.def
  thinger.rc
  ContextMenu.cpp
  )
target_link_libraries(thinger shlwapi)
