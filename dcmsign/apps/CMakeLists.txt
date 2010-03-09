ADD_EXECUTABLE(dcmsign dcmsign)

# make sure executables are linked to the corresponding libraries
TARGET_LINK_LIBRARIES(dcmsign dcmdsig ${ZLIB_LIBS} ${OPENSSL_LIBS} ${DCMTK_LIBRARIES})