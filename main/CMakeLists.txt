# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.c ppvm.c printer.c test_device.c terminal.c")
set(COMPONENT_ADD_INCLUDEDIRS ".")

register_component()
