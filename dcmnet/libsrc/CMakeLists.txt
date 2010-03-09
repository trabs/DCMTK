SET(KIT dcmnet)
SET(UKIT DCMNET)

SET(Kit_SRCS
assoc.cxx
cond.cxx
dcasccff.cxx
dcasccfg.cxx
dccfenmp.cxx
dccfpcmp.cxx
dccfprmp.cxx
dccfrsmp.cxx
dccftsmp.cxx
dccfuidh.cxx
dcmlayer.cxx
dcmtrans.cxx
dcompat.cxx
dcuserid.cxx
dimcancl.cxx
dimcmd.cxx
dimdump.cxx
dimecho.cxx
dimfind.cxx
dimget.cxx
dimmove.cxx
dimse.cxx
dimstore.cxx
diutil.cxx
dul.cxx
dulconst.cxx
dulextra.cxx
dulfsm.cxx
dulparse.cxx
dulpres.cxx
extneg.cxx
lst.cxx
scp.cxx
scu.cxx
dfindscu.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmdata)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
