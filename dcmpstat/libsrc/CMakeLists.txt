SET(KIT dcmpstat)
SET(UKIT DCMPSTAT)

SET(Kit_SRCS
dcmpstat.cxx
dviface.cxx
dvpsab.cxx
dvpsabl.cxx
dvpsal.cxx
dvpsall.cxx
dvpscf.cxx
dvpscu.cxx
dvpscul.cxx
dvpsda.cxx
dvpsdal.cxx
dvpsfs.cxx
dvpsga.cxx
dvpsgal.cxx
dvpsgl.cxx
dvpsgll.cxx
dvpsgr.cxx
dvpsgrl.cxx
dvpshlp.cxx
dvpsib.cxx
dvpsibl.cxx
dvpsmsg.cxx
dvpsov.cxx
dvpsovl.cxx
dvpspl2.cxx
dvpspl.cxx
dvpspll.cxx
dvpspr.cxx
dvpsprt.cxx
dvpsri.cxx
dvpsril.cxx
dvpsrs.cxx
dvpsrsl.cxx
dvpssp.cxx
dvpsspl.cxx
dvpssv.cxx
dvpssvl.cxx
dvpstat.cxx
dvpstx.cxx
dvpstxl.cxx
dvpsvl.cxx
dvpsvll.cxx
dvpsvw.cxx
dvpsvwl.cxx
dvsighdl.cxx
)

SET(Kit_EXTRA_SRCS)
SET(KIT_LIBS dcmdata dcmqrdb dcmimage dcmsr)
SET(KIT_EXTRA_LIBS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
