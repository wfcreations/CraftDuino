/*
 *	Copyright (c) 2013 by Welsiton Ferreira, WFCreations (wfcreations@gmail.com)
 *	All rights reserved.
 *
 *	Redistribution and use in source and binary forms, with or without modification,
 *	are permitted provided that the following conditions are met:
 *
 *      Redistributions of source code must retain the above copyright notice, this
 * 	list of conditions and the following disclaimer.
 *
 * 	Redistributions in binary form must reproduce the above copyright notice, this
 *	list of conditions and the following disclaimer in the documentation and/or
 * 	other materials provided with the distribution.
 *
 * 	Neither the name of the {organization} nor the names of its
 *	contributors may be used to endorse or promote products derived from
 * 	this software without specific prior written permission.
 *
 * 	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * 	ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * 	WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * 	DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * 	ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * 	(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * 	LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * 	ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * 	(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * 	SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SFA_SFACALLBACK_H
#define SFA_SFACALLBACK_H

#include <stddef.h>

namespace SFACall {

    struct Void {
    };
    
    static Void VoidP;
}

template <class ReturnT = void, class ParamT = SFACall::Void>
class SFACallback {
private:
    typedef ReturnT(*Functor)(const SFACallback*, ParamT);
    typedef ReturnT(*Function)(ParamT);
    typedef ReturnT(SFACallback::*Member)(ParamT);

    Functor const functor;

public:
    Function const function;
    void* const object;
    Member const method;

    SFACallback(Functor const functor, Function const function) : functor(functor), function(function), object(NULL), method(NULL) {
    };

    SFACallback(Functor const functor, void* const object, const void* method) : functor(functor), function(NULL), object(object), method(*static_cast<const Member*> (method)) {
    };

    Function const getFunction() const {
        return function;
    };

    template <class Class>
    Class * const getObject() const {
        return (Class *) object;
    };

    template <class Class>
    ReturnT(Class::* const getMethod())(const ParamT) {
        typedef ReturnT (Class::* MethodPointer)(const ParamT);
        return * reinterpret_cast<MethodPointer const*> (&this->method);
    };

    ReturnT operator()(const ParamT param = SFACall::VoidP) const {
        return functor(this, param);
    };
};

#endif