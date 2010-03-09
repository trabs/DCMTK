SET(KIT dcmimage)
SET(UKIT DCMIMAGE)

SET(Kit_SRCS
diargimg.cxx
dicmyimg.cxx
dicoimg.cxx
dicoopx.cxx
dicopx.cxx
dihsvimg.cxx
dipalimg.cxx
dipipng.cxx
dipitiff.cxx
diqtctab.cxx
diqtfs.cxx
diqthash.cxx
diqthitl.cxx
diqtpbox.cxx
diquant.cxx
diregist.cxx
dirgbimg.cxx
diybrimg.cxx
diyf2img.cxx
diyp2img.cxx
dilogger.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS ofstd dcmimgle)
SET(KIT_EXTRA_LIBS)

# PNG
IF(DCMTK_WITH_PNG)
  SET(KIT_EXTRA_LIBS ${KIT_EXTRA_LIBS} ${PNG_LIBRARIES})
ENDIF(DCMTK_WITH_PNG)

# TIFF
IF(DCMTK_WITH_TIFF)
  SET(KIT_EXTRA_LIBS ${KIT_EXTRA_LIBS} ${TIFF_LIBRARIES})
ENDIF(DCMTK_WITH_TIFF)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
