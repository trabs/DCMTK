# declare executables
FOREACH(PROGRAM echoscu findscu movescu storescp storescu termscu)
  ADD_EXECUTABLE(${PROGRAM} ${PROGRAM})
ENDFOREACH(PROGRAM)

# make sure executables are linked to the corresponding libraries
FOREACH(PROGRAM echoscu findscu movescu storescp storescu termscu)
  TARGET_LINK_LIBRARIES(${PROGRAM} dcmnet ${ZLIB_LIBS})
  IF(WIN32)
    TARGET_LINK_LIBRARIES(${PROGRAM}  ws2_32 netapi32 wsock32)
  ENDIF(WIN32)
ENDFOREACH(PROGRAM)

FOREACH(PROGRAM echoscu findscu storescp storescu)
  TARGET_LINK_LIBRARIES(${PROGRAM} dcmtls ${OPENSSL_LIBS})
ENDFOREACH(PROGRAM)
