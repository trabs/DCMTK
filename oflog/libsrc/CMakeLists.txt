SET(KIT oflog)
SET(UKIT OFLOG)

SET(Kit_SRCS
apndimpl.cxx
appender.cxx
config.cxx
consap.cxx
factory.cxx
fileap.cxx
filter.cxx
globinit.cxx
hierarchy.cxx
hierlock.cxx
layout.cxx
lloguser.cxx
logevent.cxx
logger.cxx
logimpl.cxx
loglevel.cxx
loglog.cxx
ndc.cxx
ntelogap.cxx
nullap.cxx
objreg.cxx
oflog.cxx
patlay.cxx
pointer.cxx
property.cxx
rootlog.cxx
sleep.cxx
sockbuff.cxx
socket.cxx
socketap.cxx
strhelp.cxx
syncprims.cxx
syslogap.cxx
threads.cxx
timehelp.cxx
)

IF(WIN32)
  SET(Kit_SRCS ${Kit_SRCS} windebap.cxx winsock.cxx)
ELSE(WIN32)
  SET(Kit_SRCS ${Kit_SRCS} unixsock.cxx)
ENDIF(WIN32)


SET(KIT_LIBS oflog)
SET(Kit_EXTRA_SRCS)

# Include CMake code common to all dcmtk kits.
INCLUDE(${DCMTK_SOURCE_DIR}/CMake/KitCommonBlock.cmake)
