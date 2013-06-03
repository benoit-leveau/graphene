
#ifndef LINKTYPE_H
#define LINKTYPE_H

#ifdef WIN32
	#ifdef IMPORT_GRAPH
		#define LINKTYPE __declspec( dllimport )
	#else
		#define LINKTYPE __declspec( dllexport )
	#endif
#else
	#define LINKTYPE
#endif

#endif //!LINKTYPE_H
