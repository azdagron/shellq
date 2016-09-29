
# TODO: run midl from here, in the meantime:
# midl shellq.idl

add_definitions(-DENTRY_PREFIX=Proxy)
add_definitions(-DPROXY_CLSID=CLSID_OurProxyFactory)

add_library(shellq SHARED
    dllmain.cpp
    exports.def
    shellq.rc
    shellq_i.c
    shellq_p.c
    dlldata.c
    ContextMenu.cpp
    OperationQueue.cpp
    Queue.cpp
    TrayIcon.cpp
    )
target_link_libraries(shellq
    ole32
    rpcrt4
    shlwapi
    comctl32
    )
set_source_files_properties(shellq_i.c PROPERTIES COMPILE_FLAGS -DINITGUID)
