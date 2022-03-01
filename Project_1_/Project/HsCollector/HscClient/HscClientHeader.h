#ifndef HSCMESSAGEHEADER_H
#define HSCMESSAGEHEADER_H

#ifdef WIN32
#if defined(HSCCLIENT_LIBRARY)
#  define HSCCLIENTSHARED_EXPORT __declspec(dllexport)
#else
#  define HSCCLIENTSHARED_EXPORT __declspec(dllimport)
#endif
#else
#  define HSCCLIENTSHARED_EXPORT
#endif
#endif // HSCMESSAGEHEADER_H
