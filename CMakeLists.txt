cmake_minimum_required (VERSION 3.0)
PROJECT(HOG_Trainer)

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
file(GLOB HOG_Trainer_FORMS ${PROJECT_SOURCE_DIR}/Source/*.ui )


# MOC the headers and user interface
QT5_WRAP_CPP( HEADERS_MOC ${HEADERS} )
QT5_WRAP_UI( HOG_Trainer_FORMS_HEADERS ${HOG_Trainer_FORMS} )

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
source_group ("UI Form Headers" FILES ${HOG_Trainer_FORMS_HEADERS})

# Add Executables
ADD_EXECUTABLE(HOG_Trainer ${SOURCES} ${HEADERS_MOC} ${HOG_Trainer_FORMS_HEADERS} ${HEADERS})



# Target link libraries
#target_link_libraries (Pedestrian_Tracking_Application Qt5::Widgets dlib ${OpenCV_LIBS})
target_link_libraries (HOG_Trainer Qt5::Widgets ${OpenCV_LIBS})
