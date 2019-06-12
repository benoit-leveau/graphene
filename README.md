graphene
========

[WIP] Dataflow Programming Framework with interesting features not found usually in node editors like loops or streamable data.

Features
========

Plugin system: Node types are loaded and registered at run-time. The implementation is loosely based on the 3dsMax plugin mechanism.

Advanced features for nodes:
* <b>Dynamic Typing</b>: a node can define an input or output plug as dynamic, meaning it will accept different types of data.
* <b>Multiple Inputs</b>: a node can define an input as multiple, it is then possible to plug any number of connections to this input (typical for an 'addition' node)
* <b>Streamable Output</b>: nodes can declare their output as streamable. If it is supported along the DAG, then  the value will be queried in a buffered way instead of querying the entire value (useful to process files).
* <b>Conditional Nodes</b>: "if" nodes querying only the necessary branches (lazy evaluation).
* <b>Loops</b>: "for" and "while" nodes. These nodes contain a subgraph which is executed several times depending on the stop conditions. This subgraph is accumulating a value (which is feed back into the subgraph at each cycle) which is then outputted by the loop node.

Graph evaluation:
* <b>Caching</b>: the engine caches as much as possible the values in the graph, with a clean/dirty propagation mechanism, allowing effective lazy evaluation
* <b>Multi-threading</b>: the graph evaluation is executed on a pool of threads to maximize efficiency. One of the test scenes contain over 1,000,000 nodes.

List of Nodes
=============

* Basics: BooleanNode, IntegerNode, FloatNode, StringNode, Point3Node, Matrix3Node
* Conditionals: IfNode
* Converters: ItoA
* File: FileNode, StreamFileNode
* Loops: ForNode, WhileNode
* Operations: ConcatNode, AddMultIntNode, GenericNode
* Utilities: ConsoleOutput

Example Graphs
==============

This example shows how to connect an *IfNode* in a graph.

![If Node](/doc/test_if_node.png)

This example shows how to use a *ForNode*. This is slightly more complex, as you need to connect the subgraph's output to the ForNode but also you need to connect the ForNode's current iteration to the subgraph.

![For Node](/doc/test_for_node.png)

This example shows how a *FileNode* can be used to read data from a file and pass it on to another node.

![File Node](/doc/test_file_node.png)

This example shows the same graph but this time with a *StreamFileNode* which will stream its data to the Console node.

![StreamFile Node](/doc/test_stream_file_node.png)


Dependencies
=============

graphene depends on the following:
* boost: http://www.boost.org/
* cptl: https://github.com/vit-vit/ctpl
