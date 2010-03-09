SET(KIT dcmjpeg)
SET(UKIT DCMJPEG)

SET(Kit_SRCS
ddpiimpl.cxx
dipijpeg.cxx
djcodecd.cxx
djcodece.cxx
djcparam.cxx
djdecbas.cxx
djdecext.cxx
djdeclol.cxx
djdecode.cxx
djdecpro.cxx
djdecsps.cxx
djdecsv1.cxx
djdijg12.cxx
djdijg16.cxx
djdijg8.cxx
djeijg12.cxx
djeijg16.cxx
djeijg8.cxx
djencbas.cxx
djencext.cxx
djenclol.cxx
djencode.cxx
djencpro.cxx
djencsps.cxx
djencsv1.cxx
djrplol.cxx
djrploss.cxx
djutils.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmimgle ijg8 ijg12 ijg16)
SET(KIT_EXTRA_LIBS ${ZLIB_LIBS})

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
