# -----------------------------------------------------------------
# Start of common section
ADD_LIBRARY(${KIT} STATIC ${Kit_SRCS} ${Kit_EXTRA_SRCS})
TARGET_LINK_LIBRARIES(${KIT} ${KIT_LIBS} ${KIT_EXTRA_LIBS})

# End of common section
# -----------------------------------------------------------------
