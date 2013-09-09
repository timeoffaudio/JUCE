/*
  ==============================================================================

   This file is part of the juce_core module of the JUCE library.
   Copyright (c) 2013 - Raw Material Software Ltd.

   Permission to use, copy, modify, and/or distribute this software for any purpose with
   or without fee is hereby granted, provided that the above copyright notice and this
   permission notice appear in all copies.

   THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD
   TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN
   NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL
   DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER
   IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
   CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ------------------------------------------------------------------------------

   NOTE! This permissive ISC license applies ONLY to files within the juce_core module!
   All other JUCE modules are covered by a dual GPL/commercial license, so if you are
   using any other modules, be sure to check that you also comply with their license.

   For more details, visit www.juce.com

  ==============================================================================
*/

#ifndef JUCE_STRINGREF_H_INCLUDED
#define JUCE_STRINGREF_H_INCLUDED


//==============================================================================
/**
    A simple class for holding temporary references to a string literal or String.

    Unlike a real String object, the StringRef does not allocate any memory or
    take ownership of the strings you give to it - it simply holds a reference to
    a string that has been allocated elsewhere.
    The main purpose of the class is to be used instead of a const String& as the type
    of function arguments where the caller may pass either a string literal or a String
    object. This means that when the called uses a string literal, there's no need
    for an temporary String object to be allocated, and this cuts down overheads
    substantially.

    Because the class is simply a wrapper around a pointer, you should always pass
    it by value, not by reference.

    @code
    void myStringFunction1 (const String&);
    void myStringFunction2 (StringRef);

    myStringFunction1 ("abc"); // Implicitly allocates a temporary String object.
    myStringFunction2 ("abc"); // Much faster, as no local allocations are needed.
    @endcode

    For examples of it in use, see the XmlElement or StringArray classes.

    Bear in mind that there are still many cases where it's better to use an argument
    which is a const String&. For example if the function stores the string or needs
    to internally create a String from the argument, then it's better for the original
    argument to already be a String.

    @see String
*/
class JUCE_API  StringRef
{
public:
    /** Creates a StringRef from a raw string literal.
        The StringRef object does NOT take ownership or copy this data, so you must
        ensure that the data does not change during the lifetime of the StringRef.
        Note that this pointer not be null!
    */
    StringRef (const String::CharPointerType::CharType* stringLiteral) noexcept;

    /** Creates a StringRef from a raw char pointer.
        The StringRef object does NOT take ownership or copy this data, so you must
        ensure that the data does not change during the lifetime of the StringRef.
    */
    StringRef (String::CharPointerType stringLiteral) noexcept;

    /** Creates a StringRef from a String.
        The StringRef object does NOT take ownership or copy the data from the String,
        so you must ensure that the String is not modified or deleted during the lifetime
        of the StringRef.
    */
    StringRef (const String& string) noexcept;

    //==============================================================================
    /** Returns a raw pointer to the underlying string data. */
    operator const String::CharPointerType::CharType*() const noexcept  { return text.getAddress(); }
    /** Returns a pointer to the underlying string data as a char pointer object. */
    operator String::CharPointerType() const noexcept                   { return text; }

    /** Returns true if the string is empty. */
    bool isEmpty() const noexcept                                       { return text.isEmpty(); }
    /** Returns true if the string is not empty. */
    bool isNotEmpty() const noexcept                                    { return ! text.isEmpty(); }
    /** Returns the number of characters in the string. */
    int length() const noexcept                                         { return (int) text.length(); }

    /** Compares this StringRef with a String. */
    bool operator== (const String& s) const noexcept                    { return text.compare (s.getCharPointer()) == 0; }
    /** Compares this StringRef with a String. */
    bool operator!= (const String& s) const noexcept                    { return text.compare (s.getCharPointer()) != 0; }

    /** Case-sensitive comparison of two StringRefs. */
    bool operator== (StringRef s) const noexcept                        { return text.compare (s.text) == 0; }
    /** Case-sensitive comparison of two StringRefs. */
    bool operator!= (StringRef s) const noexcept                        { return text.compare (s.text) != 0; }

    //==============================================================================
    /** The text that is referenced. */
    String::CharPointerType text;
};

//==============================================================================
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator== (const String& string1, StringRef string2) noexcept;
/** Case-sensitive comparison of two strings. */
JUCE_API bool JUCE_CALLTYPE operator!= (const String& string1, StringRef string2) noexcept;


#endif   // JUCE_STRINGREF_H_INCLUDED
