SET(KIT dcmtls)
SET(UKIT DCMTLS)

SET(Kit_SRCS
tlslayer.cxx
tlstrans.cxx
tlsscu.cxx
)

SET(KIT_LIBS)
SET(Kit_EXTRA_SRCS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
