SET(KIT ofstd)
SET(UKIT OFSTD)

SET(Kit_SRCS
ofcmdln.cxx   
ofconapp.cxx  
ofcond.cxx    
ofconfig.cxx  
ofconsol.cxx  
ofcrc32.cxx   
ofdate.cxx    
ofdatime.cxx 
offname.cxx   
oflist.cxx    
ofstd.cxx     
ofstring.cxx
ofthread.cxx
oftime.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS ${THREAD_LIBS})
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
