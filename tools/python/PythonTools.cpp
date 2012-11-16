/*
 *  PythonTools.h
 *
 *  Created by David Cox on 10/20/10.
 *  Copyright 2010 Harvard University. All rights reserved.
 *
 */


#include "PythonSimpleConduit.h"
#include "PythonAccumulatingConduit.h"
#include "PythonDataBindingsHelpers.h"

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>


BEGIN_NAMESPACE_MW


BOOST_PYTHON_MODULE(_mworks)
{
    
    if (scarab_init(0) != 0) {
        PyErr_SetString(PyExc_RuntimeError, "Scarab initialization failed");
        throw_error_already_set();
    }
    
    class_<Event>("Event", no_init)
    .add_property("code", &Event::getEventCode)
    .add_property("time", &Event::getTime)
    .add_property("data", extractEventData)
    .add_property("value", extractEventData)  // For compatibility with EventWrapper
    ;
    
    register_ptr_to_python< shared_ptr<Event> >();
    
    class_<PythonIPCConduit, boost::noncopyable>("_IPCConduit", no_init)
    .def("initialize", &PythonIPCConduit::initialize)
    .def("finalize", &PythonIPCConduit::finalize)
    .def("send_float", &PythonIPCConduit::sendFloat)
    .def("send_integer", &PythonIPCConduit::sendInteger)
    .def("send_object", &PythonIPCConduit::sendPyObject)
    .def("register_callback_for_code", &PythonIPCConduit::registerCallbackForCode)
    .def("register_callback_for_name", &PythonIPCConduit::registerCallbackForName)
    .def("register_local_event_code", &PythonIPCConduit::registerLocalEventCode)
    .add_property("codec", &PythonIPCConduit::getCodec)
    .add_property("reverse_codec", &PythonIPCConduit::getReverseCodec)
    .add_property("initialized", &PythonIPCConduit::isInitialized)
    ;
    
    class_<PythonIPCServerConduit, boost::noncopyable, bases<PythonIPCConduit> >
    ("_IPCServerConduit", init<std::string, bool>())
    ;
    
    class_<PythonIPCClientConduit, boost::noncopyable, bases<PythonIPCConduit> >
    ("_IPCClientConduit", init<std::string, bool>())
    ;
    
    class_<PythonIPCAccumulatingConduit, boost::noncopyable, bases<PythonIPCConduit> >
    ("_IPCAccumulatingConduit", no_init)
    .def("initialize", &PythonIPCAccumulatingConduit::initialize)
    .def("register_bundle_callback", &PythonIPCAccumulatingConduit::registerBundleCallback)
    ;
    
    class_<PythonIPCAccumulatingServerConduit, boost::noncopyable, bases<PythonIPCAccumulatingConduit> >
    ("_IPCAccumulatingServerConduit", init< string,string,string,boost::python::list>())
    ;
    
    class_<PythonIPCAccumulatingClientConduit, boost::noncopyable, bases<PythonIPCAccumulatingConduit> >
    ("_IPCAccumulatingClientConduit", init< string,string,string,boost::python::list>())
    ;
    
    class_<EventWrapper>("EventWrapper", no_init)
    .add_property("code", &EventWrapper::getEventCode)
    .add_property("time", &EventWrapper::getTime)
    .add_property("value", extract_event_value)
    .add_property("data", extract_event_value)  // For compatibility with Event
    .add_property("empty", &EventWrapper::empty)
    ;
    
    class_<std::vector<EventWrapper> >("EventWrapperArray", no_init)
    .def(vector_indexing_suite< std::vector<EventWrapper> >())
    ;
    
    class_<PythonDataFile, boost::noncopyable>("_MWKFile", init<std::string>())
    .def("open", &PythonDataFile::open)
    .def("close", &PythonDataFile::close)
    .def("_select_events", &PythonDataFile::select_events)
    .def("_get_next_event", &PythonDataFile::get_next_event)
    .def("_get_events", &PythonDataFile::get_events)
    .add_property("exists", &PythonDataFile::exists)
    .add_property("loaded", &PythonDataFile::loaded)
    .add_property("valid", &PythonDataFile::valid)
    .add_property("minimum_time", &PythonDataFile::minimum_time)
    .add_property("maximum_time", &PythonDataFile::maximum_time)
    .add_property("file", &PythonDataFile::file)
    .add_property("true_mwk_file", &PythonDataFile::true_mwk_file)
    ;
    
    class_<PythonDataStream, boost::noncopyable>("_MWKStream", init<std::string>())
    .def("_create_file", &PythonDataStream::createFile)
    .staticmethod("_create_file")
    .def("open", &PythonDataStream::open)
    .def("close", &PythonDataStream::close)
    .def("_read", &PythonDataStream::read)
    .def("_write", &PythonDataStream::write)
    .def("_read_event", &PythonDataStream::read_event)
    .def("_write_event", &PythonDataStream::write_event)
    ;
    
}


END_NAMESPACE_MW


























