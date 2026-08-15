#CMakeLists.txt for JAM
#======================

set(JAM_SOURCES
        About.cpp
        base64.cpp
        COMAKInverseKinematicsTool.cpp
        COMAKTarget.cpp
        COMAKTool.cpp
        COMAKSettings.cpp
        COMAKSettingsSet.cpp
        ForsimTool.cpp
        JointMechanicsTool.cpp
        JointMechanicsSettings.cpp
        JointMechanicsSettingsSet.cpp
        JAMUtilities.cpp
        RegisterTypes_osimJAM.cpp
        VTPFileAdapter.cpp
        )
        
set(JAM_INCLUDES
        About.h
        base64.h
        COMAKInverseKinematicsTool.h
        COMAKTarget.h
        COMAKTool.h
        COMAKSettings.h
        COMAKSettingsSet.h
        ForsimTool.h
        JointMechanicsTool.h
        JointMechanicsSettings.h
        JointMechanicsSettingsSet.h
        JAMUtilities.h
        osimJAM.h
        osimJAMDLL.h
        RegisterTypes_osimJAM.h
        VTPFileAdapter.h
        )

OpenSimAddLibrary(
    KIT JAM
    AUTHORS "Colin_Smith"    
    LINKLIBS PUBLIC ${Simbody_LIBRARIES} spdlog::spdlog osimTools osimCommon
    INCLUDES ${JAM_INCLUDES} 
    SOURCES ${JAM_SOURCES}
    TESTDIRS Test
    )

# if(WIN32)
#     # On Windows only, debug libraries cannot be mixed with release
#     # libraries, and we must copy the DLLs from the dependencies
#     # into OpenSim's build directory (so that the DLLs are found
#     # when running the tests).
#     add_dependencies(osimJAM
#         Simbody_CONFIG_check Copy_Simbody_DLLs)

# endif()

#if(BUILD_TESTING)
#    add_subdirectory(Test)
#endif()