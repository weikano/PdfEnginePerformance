cmake_minimum_required(VERSION 3.14)

project(PdfEnginePerformance LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

#mupdf library
include_directories(mupdf/include)



add_executable(PdfEnginePerformance
  main.cpp
  MuPdfRenderer.cpp
  pdfiumrenderer.cpp
)

set(PdfiumUseSkia true)
message(${CMAKE_CURRENT_SOURCE_DIR}/testpdf)
add_definitions(-DRESOURCE_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}/testpdf\")
if(PdfiumUseSkia)
    message("SKIA ENABLED")
    add_definitions(-DUSE_SKIA)
    include_directories(pdfium/skia/include)
else()
    include_directories(pdfium/skia_disabled/include)
    message("SKIA DISABLED")
endif()

#target_link_libraries(PdfEnginePerformance Qt${QT_VERSION_MAJOR}::Core)

#mupdf library
target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/mupdf/libs/libmupdf.a)
target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/mupdf/libs/libmupdf-third.a)

target_link_libraries(PdfEnginePerformance pthread m)

#target_link_libraries(PdfEnginePerformance pdfium)

if(PdfiumUseSkia)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libbase_allocator_partition_allocator_src_partition_alloc_allocator_base.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libbase_allocator_partition_allocator_src_partition_alloc_allocator_core.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libbase_allocator_partition_allocator_src_partition_alloc_allocator_shim.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libbase_allocator_partition_allocator_src_partition_alloc_raw_ptr.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libc++.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libchrome_zlib.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libicuuc.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libpdfium.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libskia.so)
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia/lib/libthird_party_abseil-cpp_absl.so)
else()
    target_link_libraries(PdfEnginePerformance ${CMAKE_CURRENT_SOURCE_DIR}/pdfium/skia_disabled/lib/libpdfium.so)
endif()



install(TARGETS PdfEnginePerformance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
