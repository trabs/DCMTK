SET(KIT dcmwlm)
SET(UKIT DCMWLM)

SET(Kit_SRCS
wlfsim.cxx 
wlds.cxx 
wldsfs.cxx 
wlmactmg.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmnet)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
