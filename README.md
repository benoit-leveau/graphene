graphene
========

[WIP] Dataflow Programming Framework with interesting features

Features
========

Plugin system: Node types are loaded and registered at run-time. The implementation is based on 3dsMax plugin mechanism.

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
