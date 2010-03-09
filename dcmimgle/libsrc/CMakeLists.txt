SET(KIT dcmimgle)
SET(UKIT DCMIMGLE)

SET(Kit_SRCS
dcmimage.cxx
dibaslut.cxx
diciefn.cxx
dicielut.cxx
didislut.cxx
didispfn.cxx
didocu.cxx
digsdfn.cxx
digsdlut.cxx
diimage.cxx
diinpx.cxx
diluptab.cxx
dimo1img.cxx
dimo2img.cxx
dimoimg3.cxx
dimoimg4.cxx
dimoimg5.cxx
dimoimg.cxx
dimomod.cxx
dimoopx.cxx
dimopx.cxx
diovdat.cxx
diovlay.cxx
diovlimg.cxx
diovpln.cxx
diutils.cxx
)

SET(KIT_LIBS dcmdata)
SET(Kit_EXTRA_SRCS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
