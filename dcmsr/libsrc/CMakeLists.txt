SET(KIT dcmsr)
SET(UKIT DCMSR)

SET(Kit_SRCS
dsrbascc.cxx
dsrchecc.cxx
dsrcitem.cxx
dsrcodtn.cxx
dsrcodvl.cxx
dsrcomcc.cxx
dsrcomtn.cxx
dsrcomvl.cxx
dsrcontn.cxx
dsrcsidl.cxx
dsrdattn.cxx
dsrdoc.cxx
dsrdoctn.cxx
dsrdoctr.cxx
dsrdtitn.cxx
dsrenhcc.cxx
dsrimgfr.cxx
dsrimgtn.cxx
dsrimgvl.cxx
dsriodcc.cxx
dsrkeycc.cxx
dsrmamcc.cxx
dsrnumtn.cxx
dsrnumvl.cxx
dsrpnmtn.cxx
dsrprocc.cxx
dsrreftn.cxx
dsrscogr.cxx
dsrscotn.cxx
dsrscovl.cxx
dsrsoprf.cxx
dsrstrvl.cxx
dsrtcodt.cxx
dsrtcosp.cxx
dsrtcotn.cxx
dsrtcoto.cxx
dsrtcovl.cxx
dsrtextn.cxx
dsrtimtn.cxx
dsrtncsr.cxx
dsrtree.cxx
dsrtypes.cxx
dsruidtn.cxx
dsrwavch.cxx
dsrwavtn.cxx
dsrwavvl.cxx
dsrxmlc.cxx
dsrxmld.cxx
dsrxrdcc.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmdata oflog)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
