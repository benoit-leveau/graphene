
#ifndef LIST_CLASSIDS_H
#define LIST_CLASSIDS_H

// basic nodes
#define CID_BOOLEAN_NODE		ClassID(1,0)
#define CID_INTEGER_NODE		ClassID(1,1)
#define CID_FLOAT_NODE			ClassID(1,2)
#define CID_STRING_NODE			ClassID(1,3)
#define CID_POINT3_NODE			ClassID(1,4)
#define CID_MATRIX3_NODE		ClassID(1,5)

// conditionals
#define CID_IF_NODE			ClassID(2,0)

// loops
#define CID_FOR_NODE			ClassID(2,1)
#define CID_WHILE_NODE			ClassID(2,2)

// converters
#define CID_ITOA_NODE			ClassID(3,0)

// operations
#define CID_GENERICADD_NODE		ClassID(4,0)
#define CID_CONCAT_NODE			ClassID(4,1)
#define CID_MULTADD_NODE		ClassID(4,2)

// utilities
#define CID_CONSOLE_OUTPUT_NODE ClassID(5,0)

// file
#define CID_FILE_NODE			ClassID(6,0)
#define CID_STREAM_FILE_NODE	ClassID(6,1)

#endif //!LIST_CLASSIDS_H
