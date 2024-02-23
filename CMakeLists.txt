cmake_minimum_required(VERSION 3.14)

project(PdfEnginePerformance LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
set(PDFium_DIR pdfium/)

#mupdf library
include_directories(mupdf/include)

find_package(PDFium)

add_executable(PdfEnginePerformance
  main.cpp
  MuPdfRenderer.cpp
  pdfiumrenderer.cpp
)

message("CURRENT DIR IS ${CMAKE_CURRENT_SOURCE_DIR}")

#target_link_libraries(PdfEnginePerformance Qt${QT_VERSION_MAJOR}::Core)

#mupdf library
target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/mupdf/libs/libmupdf.a)
target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/mupdf/libs/libmupdf-third.a)

target_link_libraries(PdfEnginePerformance pthread m)

target_link_libraries(PdfEnginePerformance pdfium)




install(TARGETS PdfEnginePerformance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
