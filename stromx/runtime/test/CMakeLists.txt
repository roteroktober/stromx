add_test(NAME stromx_runtime_test COMMAND stromx_runtime_test)
set_tests_properties(stromx_runtime_test PROPERTIES ENVIRONMENT "${TEST_ENVIRONMENT}")
    
if(MSVC)
    add_definitions(/DSTROMX_RUNTIME_STATIC)
endif(MSVC)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${Boost_INCLUDE_DIRS}
    ${CPPUNIT_INCLUDE_DIR}
)

if(BUILD_FILE_PERSISTENCE)
    include_directories(${XERCES_INCLUDE_DIR})
    include_directories(${LIBZIP_INCLUDE_DIR})
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/archive.zip ${CMAKE_CURRENT_BINARY_DIR}/archive.zip COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data.txt ${CMAKE_CURRENT_BINARY_DIR}/data.txt COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/dtd.xml ${CMAKE_CURRENT_BINARY_DIR}/dtd.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/invalid.xml ${CMAKE_CURRENT_BINARY_DIR}/invalid.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/invalid.zip ${CMAKE_CURRENT_BINARY_DIR}/invalid.zip COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/nonsense.stromx ${CMAKE_CURRENT_BINARY_DIR}/nonsense.stromx COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parameters.xml ${CMAKE_CURRENT_BINARY_DIR}/parameters.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parameters.zip ${CMAKE_CURRENT_BINARY_DIR}/parameters.zip COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/parameters.stromx ${CMAKE_CURRENT_BINARY_DIR}/parameters.stromx COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/stream.xml ${CMAKE_CURRENT_BINARY_DIR}/stream.xml COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/stream.zip ${CMAKE_CURRENT_BINARY_DIR}/stream.zip COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/stream.stromx ${CMAKE_CURRENT_BINARY_DIR}/stream.stromx COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/double_matrix.npy ${CMAKE_CURRENT_BINARY_DIR}/double_matrix.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/empty_float_matrix.npy ${CMAKE_CURRENT_BINARY_DIR}/empty_float_matrix.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fortran_order.npy ${CMAKE_CURRENT_BINARY_DIR}/fortran_order.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/uint16_matrix.npy ${CMAKE_CURRENT_BINARY_DIR}/uint16_matrix.npy COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data.txt ${CMAKE_CURRENT_BINARY_DIR}/directory/data.txt COPYONLY)

set(SOURCES
    ../AssignThreadsAlgorithm.cpp
    ../Block.cpp
    ../Color.cpp
    ../Compare.cpp
    ../Connector.cpp
    ../ConstDataRef.cpp
    ../Runtime.cpp
    ../ConstData.cpp
    ../Counter.cpp
    ../Data.cpp
    ../DataRef.cpp
    ../DataContainer.cpp
    ../DescriptionBase.cpp
    ../Dump.cpp
    ../Enum.cpp
    ../EnumParameter.cpp
    ../Exception.cpp
    ../Factory.cpp
    ../File.cpp
    ../Filter.cpp
    ../Fork.cpp
    ../Join.cpp
    ../Id2DataComposite.cpp
    ../Id2DataPair.cpp
    ../Image.cpp
    ../ImageWrapper.cpp
    ../List.cpp
    ../Locale.cpp
    ../Matrix.cpp
    ../MatrixDescription.cpp
    ../MatrixParameter.cpp
    ../MatrixWrapper.cpp
    ../Merge.cpp
    ../None.cpp
    ../Operator.cpp
    ../OperatorKernel.cpp
    ../Parameter.cpp
    ../ParameterGroup.cpp
    ../PeriodicDelay.cpp
    ../Primitive.cpp
    ../Push.cpp
    ../Queue.cpp
    ../ReadAccess.cpp
    ../Receive.cpp
    ../RecycleAccess.cpp
    ../Repeat.cpp
    ../Thread.cpp
    ../Send.cpp
    ../SortInputsAlgorithm.cpp
    ../Split.cpp
    ../Stream.cpp
    ../String.cpp
    ../Tribool.cpp
    ../TriggerData.cpp
    ../Try.cpp
    ../Variant.cpp
    ../VariantComposite.cpp
    ../VariantInterface.cpp
    ../VariantHandle.cpp
    ../Version.cpp
    ../Visualization.cpp
    ../WriteAccess.cpp
    ../impl/Client.cpp
    ../impl/DataContainerImpl.cpp
    ../impl/DataOperatorBase.cpp
    ../impl/Id2DataMap.cpp
    ../impl/InputNode.cpp
    ../impl/Network.cpp
    ../impl/OutputNode.cpp
    ../impl/ReadAccessImpl.cpp
    ../impl/RecycleAccessImpl.cpp
    ../impl/Server.cpp
    ../impl/SerializationHeader.cpp
    ../impl/SynchronizedOperatorKernel.cpp
    ../impl/ThreadImpl.cpp
    ../impl/WriteAccessImpl.cpp
    AssignThreadsAlgorithmTest.cpp
    BlockTest.cpp
    BoolTest.cpp
#     ClientTest.cpp
    CompareTest.cpp
    ConstDataTest.cpp
    CounterTest.cpp
    DataContainerTest.cpp
    DataRefTest.cpp
    DataTest.cpp
    DumpTest.cpp
    EnumTest.cpp
    ExceptionOperator.cpp
    ExceptionTest.cpp
    FileTest.cpp
    FilterTest.cpp
    Float64Test.cpp
    ForkTest.cpp
    Id2DataCompositeTest.cpp
    Id2DataMapTest.cpp
    Id2DataPairTest.cpp
    ImageWrapperTest.cpp
    InputNodeTest.cpp
    Int32Test.cpp
    JoinTest.cpp
    ListTest.cpp
    MatrixWrapperTest.cpp
    MergeTest.cpp
    OperatorKernelTest.cpp
    OperatorTest.cpp
    OutputNodeTest.cpp
    ParameterTest.cpp
    PeriodicDelayTest.cpp
    PushTest.cpp
    QueueTest.cpp
    ReadAccessTest.cpp
    RecycleAccessTest.cpp
    RepeatTest.cpp
    TestOperator.cpp
    ThreadImplTest.cpp
    ThreadTest.cpp
    TriboolTest.cpp
    NetworkTest.cpp
    FactoryTest.cpp
    RuntimeTest.cpp
#     SendReceiveTest.cpp
    StringTest.cpp
    TestData.cpp
    TryTest.cpp
#     ServerTest.cpp
    SplitTest.cpp
    SortInputsAlgorithmTest.cpp
    StreamTest.cpp
    TestUtilities.cpp
    UInt8Test.cpp
    VariantTest.cpp
    VersionTest.cpp
    VisualizationTest.cpp
    WriteAccessTest.cpp
    main.cpp
)

if(BUILD_FILE_PERSISTENCE)
    set(SOURCES
        ${SOURCES}
        ../DirectoryFileInput.cpp
        ../DirectoryFileOutput.cpp
        ../XmlReader.cpp
        ../XmlWriter.cpp
        ../ZipFileInput.cpp
        ../ZipFileOutput.cpp
        ../impl/XmlReaderImpl.cpp
        ../impl/XmlUtilities.cpp
        ../impl/XmlWriterImpl.cpp
        DirectoryFileInputTest.cpp
        DirectoryFileOutputTest.cpp
        XmlReaderTest.cpp
        XmlUtilitiesTest.cpp
        XmlWriterTest.cpp
        ZipFileInputTest.cpp
        ZipFileOutputTest.cpp
    )
endif(BUILD_FILE_PERSISTENCE)

add_executable(stromx_runtime_test ${SOURCES})

set_target_properties(stromx_runtime_test PROPERTIES
    FOLDER "test"
)

target_link_libraries(stromx_runtime_test
    ${Boost_LIBRARIES}
    ${CPPUNIT_LIBRARY}
    ${CMAKE_DL_LIBS}
    ${CMAKE_THREAD_LIBS_INIT}
)

if(BUILD_FILE_PERSISTENCE)
    target_link_libraries(stromx_runtime_test ${XERCES_LIBRARIES})
    target_link_libraries(stromx_runtime_test ${LIBZIP_LIBRARY})
endif()


