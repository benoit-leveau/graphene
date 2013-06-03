graphene
========

[WIP] Dataflow Programming Framework with interesting features

Overview
========


Features
========

* Generic Nodes
* Caching: nodes try as much as possible to cache the values of their inputs, with a clean/dirty mechanism (lazy evaluation)
* Stream Output: nodes can declare their output as streamable. If it is supported by the nodes along the DAG, then  the value will be queried in a stream
* Conditional Nodes: IF nodes
* Loops: for and while nodes
