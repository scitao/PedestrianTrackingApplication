cmake_minimum_required (VERSION 3.0)
PROJECT(Pedestrian_Tracking_Application)

# Find the QtCore and QtWidgets libraries
find_package(Qt5Widgets REQUIRED)

# include the dlib library


# include the openCV library
find_package(OpenCV REQUIRED)

# Set the project include directories
include_directories(${PROJECT_SOURCE_DIR}/Include)
include_directories(${PROJECT_BINARY_DIR})

# Glob Project Source Files
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/Source/*.cpp )

# Glob Project Header Files
file(GLOB HEADERS ${PROJECT_SOURCE_DIR}/Include/*.h )


# Glob Project User Interface Files
file(GLOB Pedestrian_Tracking_Application_FORMS ${PROJECT_SOURCE_DIR}/Source/*.ui )


# MOC the headers and user interface
QT5_WRAP_CPP( HEADERS_MOC ${HEADERS} )
QT5_WRAP_UI( Pedestrian_Tracking_Application_FORMS_HEADERS ${Pedestrian_Tracking_Application_FORMS} )

# Add Qt Definitions
ADD_DEFINITIONS( ${QT_DEFINITIONS} )

# Static Flag Overrides
#set(CMAKE_C_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
#set(CMAKE_C_FLAGS_MINSIZEREL    "/MT /O1 /Ob1 /D NDEBUG")
#set(CMAKE_C_FLAGS_RELEASE        "/MT /O2 /Ob2 /D NDEBUG")
#set(CMAKE_C_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /D NDEBUG")

#set(CMAKE_CXX_FLAGS_DEBUG "/D_DEBUG /MTd /Zi /Ob0 /Od /RTC1")
#set(CMAKE_CXX_FLAGS_MINSIZEREL    "/MT /O1 /Ob1 /D NDEBUG")
#set(CMAKE_CXX_FLAGS_RELEASE       "/MT /O2 /Ob2 /D NDEBUG")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "/MT /Zi /O2 /Ob1 /D NDEBUG")

# Set MSVC Filters
source_group ("Headers" FILES ${HEADERS})
source_group ("Source" FILES ${SOURCES})
source_group ("MOC" FILES ${HEADERS_MOC})
source_group ("UI Form Headers" FILES ${Pedestrian_Tracking_Application_FORMS_HEADERS})

# Add Executables
ADD_EXECUTABLE(Pedestrian_Tracking_Application ${SOURCES} ${HEADERS_MOC} ${Pedestrian_Tracking_Application_FORMS_HEADERS} ${HEADERS})



# Target link libraries
#target_link_libraries (Pedestrian_Tracking_Application Qt5::Widgets dlib ${OpenCV_LIBS})
target_link_libraries (Pedestrian_Tracking_Application Qt5::Widgets ${OpenCV_LIBS})
