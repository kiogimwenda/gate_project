# Find Tesseract library
find_path(Tesseract_INCLUDE_DIRS
  NAMES tesseract/baseapi.h
  PATHS /usr/include /usr/local/include
)

find_library(Tesseract_LIBRARIES
  NAMES tesseract
  PATHS /usr/lib /usr/local/lib
)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Tesseract DEFAULT_MSG
  Tesseract_INCLUDE_DIRS Tesseract_LIBRARIES
)

mark_as_advanced(Tesseract_INCLUDE_DIRS Tesseract_LIBRARIES)
