cmake_minimum_required(VERSION 3.29)
project(PathPlanning3D)

# C++ Standard
set(CMAKE_CXX_STANDARD 20)

find_package(Eigen3 REQUIRED)
find_package(jsoncpp REQUIRED)

# Include the path to RAPID headers
include_directories(${CMAKE_SOURCE_DIR}/../libraries/rapid)

# Include the path to MPNN headers
include_directories(${CMAKE_SOURCE_DIR}/../libraries/mpnn)

# Set the path to RAPID build directory (containing the .a file)
set(RAPID_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/rapid/build)

# Set the path to MPNN build directory (containing the .a file)
set(MPNN_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/mpnn/build)

# Set RAPID static library file
set(RAPID_STATIC_LIB ${RAPID_LIB_DIR}/libRAPID.a)

# Set MPNN static library file
set(MPNN_STATIC_LIB ${MPNN_LIB_DIR}/libDNN.a)

# Set FBX include and library directories
set(FBX_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/include)
set(FBX_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/fbx_sdk/lib/release)

include_directories(${FBX_INCLUDE_DIR})


set(SPDLOG_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../libraries/spdlog/include)
set(SPDLOG_STATIC_LIB_DIR ${CMAKE_SOURCE_DIR}/../libraries/spdlog/build)
set(SPDLOG_STATIC_LIB ${SPDLOG_STATIC_LIB_DIR}/libspdlog.a)

include_directories(${SPDLOG_INCLUDE_DIR})

add_definitions(-DSPDLOG_COMPILED_LIB)

# Add your source files (adjusted to use the src/ directory)
add_executable(project
    src/main.cpp
        src/components/solvers/solvers/static/RRT*/RrtStarSolver.cpp
        src/components/solvers/solvers/static/RRT/RRTsolver.cpp
    src/poses/static/PoseMath.cpp
    src/poses/static/Pose.cpp
    src/fileParsers/meshParsers/RapidObjMeshParser.cpp
        src/dto/ConfigurationSpaceBoundaries.cpp
        src/components/exporters/defaultExporter/DefaultExporter.cpp
        src/input/InputParser.cpp
        src/components/nearestNeighbour/bruteForce/BruteForceNNsearch.cpp
        src/components/distanceMeasurement/euclidian/EuclidianDistanceMetric.cpp
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.cpp
        src/components/sampling/pose/defaultRandom/DefaultRandomSampler.cpp
        src/components/sampling/pose/biasedRandom/BiasedRandomSampler.cpp
        src/components/collisionHandlers/static/rapid/RapidCollisionHandler.cpp
        src/components/nearestNeighbour/mpnn/MPNNsearch.cpp
        src/components/pathGenerator/tree/uniform/UniformPathGenerator.cpp
    src/poses/dynamic/Keyframe.cpp
    src/poses/dynamic/Animation.cpp
    src/poses/dynamic/DynamicObject.cpp
        src/components/solvers/solverConfigs/ASolverConfig.h
        src/components/IComponent.h
        src/components/capabilities/Capability.h
        src/components/registration/ComponentRegistry.h
        src/components/IComponentFactory.h
        src/components/IComponentFactory.h
        src/components/collisionHandlers/static/rapid/RapidCollisionHandlerFactory.cpp
        src/components/collisionHandlers/static/rapid/RapidCollisionHandlerFactory.h
        src/components/registration/ComponentRegistration.cpp
        src/input/ComponentsParser.cpp
        src/input/ComponentsParser.h
        src/core/Program.cpp
        src/core/Program.h
        src/core/reader/IReader.h
        src/core/creator/IComponentManager.h
        src/core/executor/IExecutor.h
        src/core/validator/IValidator.h
        src/core/exporter/IExporter.h
        src/core/creator/ComponentManager.cpp
        src/core/creator/ComponentManager.h
        src/core/executor/Executor.cpp
        src/core/executor/Executor.h
        src/core/exporter/Exporter.cpp
        src/core/exporter/Exporter.h
        src/core/reader/Reader.cpp
        src/core/reader/Reader.h
        src/core/validator/Validator.cpp
        src/core/validator/Validator.h
        src/core/reader/IReaderFactory.h
        src/core/reader/DefaultReaderFactory.cpp
        src/core/reader/DefaultReaderFactory.h
        src/components/solvers/solvers/static/RRT/RRTsolverFactory.cpp
        src/components/solvers/solvers/static/RRT/RRTsolverFactory.h
        src/components/nearestNeighbour/mpnn/MPNNsearchFactory.cpp
        src/components/nearestNeighbour/mpnn/MPNNsearchFactory.h
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetricFactory.cpp
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetricFactory.h
        src/components/pathGenerator/tree/uniform/UniformPathGeneratorFactory.cpp
        src/components/pathGenerator/tree/uniform/UniformPathGeneratorFactory.h
        src/components/sampling/pose/defaultRandom/DefaultRandomSamplerFactory.cpp
        src/components/sampling/pose/defaultRandom/DefaultRandomSamplerFactory.h
        src/components/sampling/pose/biasedRandom/BiasedRandomSamplerFactory.cpp
        src/components/sampling/pose/biasedRandom/BiasedRandomSamplerFactory.h
        src/components/exporters/defaultExporter/DefaultExporterFactory.cpp
        src/components/exporters/defaultExporter/DefaultExporterFactory.h
        src/components/solvers/solvers/static/RRT*/RrtStarSolverFactory.cpp
        src/components/solvers/solvers/static/RRT*/RrtStarSolverFactory.h
        src/components/solvers/solvers/static/IStaticSolver.h
        src/components/solvers/ASolver.h
        src/components/solvers/solvers/dynamic/IDynamicSolver.h
        src/components/solvers/solvers/dynamic/TARRT/TARRTsolver.cpp
        src/components/solvers/solvers/dynamic/TARRT/TARRTsolver.h
        src/components/solvers/solverConfigs/dynamic/TARRT/TARRTsolverConfig.h
        src/components/collisionHandlers/dynamic/IDynamicCollisionHandler.h
        src/components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandler.cpp
        src/components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandler.h
        src/poses/dynamic/KeyframeMath.cpp
        src/poses/dynamic/KeyframeMath.h
        src/components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandlerFactory.cpp
        src/components/collisionHandlers/dynamic/rapid/RapidDynamicCollisionHandlerFactory.h
        src/components/sampling/ISampler.h
        src/components/sampling/pose/IPoseSampler.h
        src/components/sampling/keyframe/IKeyframeSampler.h
        src/components/solvers/solvers/dynamic/TARRT/TARRTsolverFactory.cpp
        src/components/solvers/solvers/dynamic/TARRT/TARRTsolverFactory.h
        src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.cpp
        src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGenerator.h
        src/components/pathGenerator/tree/dynamic/DefaultDynamicPathGeneratorFactory.h
        src/components/exporters/dynamicExporter/DefaultDynamicExporter.cpp
        src/components/exporters/dynamicExporter/DefaultDynamicExporter.h
        src/components/exporters/dynamicExporter/DefaultDynamicExporterFactory.cpp
        src/components/exporters/dynamicExporter/DefaultDynamicExporterFactory.h
        src/components/solvers/solverConfigs/static/RRT*/RrtStarSolverConfig.h
        src/components/solvers/solverConfigs/ASolverConfig.h
        src/components/solvers/solverConfigs/ARRTsolverConfig.h
        src/components/solvers/solverConfigs/static/RRT/RRTsolverConfig.h
        src/components/solvers/treeUtils/ATreeSolver.h
        src/components/solvers/solvers/dynamic/movingTarget/IMovingTargetSolver.h
        src/components/capabilities/manager/CapabilityManager.h
        src/components/capabilities/manager/CapabilityManager.cpp
        src/dto/EnvSettingsRaw.h
        src/components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolver.cpp
        src/components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolver.h
        src/components/terminationConditions/ITerminationCondition.h
        src/components/terminationConditions/default/DefaultTerminationCondition.cpp
        src/components/terminationConditions/default/DefaultTerminationCondition.h
        src/components/terminationConditions/default/DefaultTerminationConditionFactory.cpp
        src/components/terminationConditions/default/DefaultTerminationConditionFactory.h
        src/components/terminationConditions/movingTarget/MovingTargetTerminationCondition.cpp
        src/components/terminationConditions/movingTarget/MovingTargetTerminationCondition.h
        src/components/terminationConditions/movingTarget/MovingTargetTerminationConditionFactory.cpp
        src/components/terminationConditions/movingTarget/MovingTargetTerminationConditionFactory.h
        src/components/solvers/solverConfigs/movingTarget/MT_TARRTsolverConfig.h
        src/components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSampler.cpp
        src/components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSampler.h
        src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.cpp
        src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearch.h
        src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearchFactory.cpp
        src/components/nearestNeighbour/temporalMPNN/TemporalMPNNsearchFactory.h
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.cpp
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetric.h
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetricFactory.cpp
        src/components/distanceMeasurement/temporalTotal/TemporalTransRotMetricFactory.h
        src/components/distanceMeasurement/temporalTotal/ITotalDistanceMetric.h
        src/components/distanceMeasurement/defaultSpatial/DefaultSpatialDistanceMetric.h
        src/components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSamplerFactory.cpp
        src/components/sampling/keyframe/biasedRandomMovingTarget/BiasedRandomMovingTargetSamplerFactory.h
        src/components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolverFactory.cpp
        src/components/solvers/solvers/dynamic/movingTarget/MT_TARRTsolverFactory.h
        src/components/ComponentType.h
        src/components/pathGenerator/tree/ITreePathGenerator.h
        src/components/sampling/pose/defaultRandom/DefaultRandomSampler.h
)

# Include headers from src/ directory
target_include_directories(project PRIVATE src/)

# Link RAPID static library
target_link_libraries(project ${RAPID_STATIC_LIB})

# Link MPNN static library
target_link_libraries(project ${MPNN_STATIC_LIB})

# Link jsoncpp library
target_link_libraries(project jsoncpp)

# Link FBX library
target_link_directories(project PRIVATE ${FBX_LIB_DIR})
target_link_libraries(project fbxsdk)


target_link_libraries(project ${SPDLOG_STATIC_LIB})
