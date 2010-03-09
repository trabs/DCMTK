SET(KIT dcmdata)
SET(UKIT DCMDATA)

SET(Kit_SRCS
dcbytstr.cxx
dcchrstr.cxx
dccodec.cxx
dcdatset.cxx
dcddirif.cxx
dcdicdir.cxx
dcdicent.cxx
dcdict.cxx
dcdictzz.cxx # the builtin dictionary
dcdirrec.cxx
dcelem.cxx
dcerror.cxx
dcfilefo.cxx
dchashdi.cxx
dcistrma.cxx
dcistrmb.cxx
dcistrmf.cxx
dcistrmz.cxx
dcitem.cxx
dclist.cxx
dcmetinf.cxx
dcobject.cxx
dcostrma.cxx
dcostrmb.cxx
dcostrmf.cxx
dcostrmz.cxx
dcpcache.cxx
dcpixel.cxx
dcpixseq.cxx
dcpxitem.cxx
dcrleccd.cxx
dcrlecce.cxx
dcrlecp.cxx
dcrledrg.cxx
dcrleerg.cxx
dcrlerp.cxx
dcsequen.cxx
dcstack.cxx
dcswap.cxx
dctag.cxx
dctagkey.cxx
dctypes.cxx
dcuid.cxx
dcvm.cxx
dcvrae.cxx
dcvras.cxx
dcvrat.cxx
dcvrcs.cxx
dcvr.cxx
dcvrda.cxx
dcvrds.cxx
dcvrdt.cxx
dcvrfd.cxx
dcvrfl.cxx
dcvris.cxx
dcvrlo.cxx
dcvrlt.cxx
dcvrobow.cxx
dcvrof.cxx
dcvrpn.cxx
dcvrpobw.cxx
dcvrsh.cxx
dcvrsl.cxx
dcvrss.cxx
dcvrst.cxx
dcvrtm.cxx
dcvrui.cxx
dcvrul.cxx
dcvrulup.cxx
dcvrus.cxx
dcvrut.cxx
dcxfer.cxx
vrscan.cxx
dcwcache.cxx
cmdlnarg.cxx
dcpath.cxx
)

SET(KIT_LIBS ofstd oflog)
SET(Kit_EXTRA_SRCS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)


