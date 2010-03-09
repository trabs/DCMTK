SET(KIT dcmqrdb)
SET(UKIT DCMQRB)

SET(Kit_SRCS
dcmqrcbf.cxx 
dcmqrcbm.cxx 
dcmqrcnf.cxx 
dcmqrdbs.cxx 
dcmqrptb.cxx 
dcmqrtis.cxx
dcmqrcbg.cxx 
dcmqrcbs.cxx 
dcmqrdbi.cxx 
dcmqropt.cxx 
dcmqrsrv.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmnet)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
