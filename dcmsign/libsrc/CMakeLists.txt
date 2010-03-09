SET(KIT dcmdsig)
SET(UKIT DCMDSIG)

SET(Kit_SRCS
dcsignat.cxx 
sicert.cxx   
sidsa.cxx    
sinullpr.cxx 
sirsa.cxx    
sitypes.cxx
siautopr.cxx 
sicertvf.cxx 
simaccon.cxx 
siprivat.cxx 
sisha1.cxx
sibrsapr.cxx 
sicreapr.cxx 
simd5.cxx    
siripemd.cxx 
sisprof.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmdata)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
