/*
 *  Exceptions.h
 *  MWorksCore
 *
 *  Created by David Cox on 1/27/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef M_EXCEPTIONS_H_
#define M_EXCEPTIONS_H_

#include <boost/format.hpp>
#include <string>
#include <exception>
#include "EventConstants.h"
#include <map>
#include <sstream>
#include <boost/shared_ptr.hpp>
#include <boost/exception/all.hpp>


namespace mw {
using namespace std;
using namespace boost;

// fwd dec
class Component;

class SimpleException : public std::exception, public boost::exception {

	protected:
	
		string message;
		//string subject;
		MessageDomain domain;
		
	public:

		SimpleException(string _message) : message(_message){ 
			domain = M_GENERIC_MESSAGE_DOMAIN;
		};
		
		SimpleException(string _message, string _subject) : message(_message + ": " + _subject){ 
			domain = M_GENERIC_MESSAGE_DOMAIN;
		};

        SimpleException(MessageDomain _domain, string _message):
                                                            message(_message){
            domain = _domain;
        }
		
		SimpleException(MessageDomain _domain, string _message, string _subject):
															message(_message + ": " + _subject){
			domain = _domain;
		}
		
		SimpleException(const SimpleException& e){
			domain = e.domain;
			message = e.message;
			//subject = e.subject;
		}
		
		virtual ~SimpleException() throw() {}
		
		virtual string getMessage(){ return message; }
		//string getSubject(){ return subject; }
		MessageDomain getDomain(){ return domain; }
		
		virtual const char* what() const throw(){
            return message.c_str();
		}

};

class NonFatalSimpleException : public SimpleException{ };


class MalformedXMLException : public SimpleException{ 

	public:
	
	MalformedXMLException(string _message) 
							: SimpleException(M_PARSER_MESSAGE_DOMAIN, _message){ 
	};
};

class InvalidXMLException : public SimpleException{

	protected:
	
	string reference_id;

	
	public:
	
	InvalidXMLException(string _refid, string _message, string _subject = "") :
				SimpleException(M_PARSER_MESSAGE_DOMAIN, _message, _subject){
					
		reference_id = _refid;
	}
	
	InvalidXMLException(string _refid, const SimpleException& e) :
				SimpleException(e){
		reference_id = _refid;
	}
	
	virtual ~InvalidXMLException() throw() {}
	
	string getReferenceID(){  return reference_id;  }
};
    

class AmbiguousComponentReferenceException : public SimpleException {

public:
    AmbiguousComponentReferenceException(string _subject) :
        SimpleException(M_PARSER_MESSAGE_DOMAIN, "An attempt was made to access an ambiguously referenced component.  "
                                                 "Please ensure that all object tag names are unique", _subject){ }
    
    virtual ~AmbiguousComponentReferenceException() throw() {}

};


class FatalParserException : public SimpleException {

public:
    FatalParserException(string _subject) : SimpleException(M_PARSER_MESSAGE_DOMAIN, _subject){ }
    
    FatalParserException() : SimpleException(M_PARSER_MESSAGE_DOMAIN, "A fatal error occurred"){ }
    
    virtual ~FatalParserException() throw(){ }
    
    
};

class ComponentFactoryConflictException : public SimpleException{
  
    
public:
    
    ComponentFactoryConflictException(string _subject) : 
        SimpleException(M_PLUGIN_MESSAGE_DOMAIN, "A plugin has attempted to redefine the behavior of an existing XML signature.", _subject){
        }
    
    virtual ~ComponentFactoryConflictException() throw() {}
};
    
}

#endif

