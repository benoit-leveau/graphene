
#include "common.h"
#include "application.h"
#include "graph.h"
#include "list_classIds.h"
#include <stdio.h>
#include <thread>

void test_for_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_if_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_multithread_lots_of_nodes(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_cache(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_chained_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);
void test_multi_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph);

int main(int argc, char **argv)
{
	Application app;

	// create graph
	boost::shared_ptr<ClientGraph> graph = app.createGraph();

size_t nb_thread = 1; //std::thread::hardware_concurrency();

    std::cout << "Enter test number:" << std::endl;
    std::cout << "Test 0: test_for_node" << std::endl;
    std::cout << "Test 1: test_if_node" << std::endl;
    std::cout << "Test 2: test_multithread_lots_of_nodes" << std::endl;
    std::cout << "Test 3: test_file_node" << std::endl;
    std::cout << "Test 4: test_cache" << std::endl;
    std::cout << "Test 5: test_chained_stream_file_node" << std::endl;
    std::cout << "Test 6: test_stream_file_node" << std::endl;
    std::cout << "Test 7: test_multi_stream_file_node" << std::endl;
    std::cout << std::endl;
    std::cout << "Enter test number:" << std::endl;
    int test_number;
    std::cin >> test_number;

    std::cout << test_number << std::endl;

    switch(test_number)
    {
    case 0: 
        {
            test_for_node(nb_thread, graph);
            break;
        }
    case 1: 
        {
            test_if_node(nb_thread, graph);
            break;
        }
    case 2: 
        {
            test_multithread_lots_of_nodes(nb_thread, graph);
            break;
        }
    case 3: 
        {
            test_file_node(nb_thread, graph);
            break;
        }
    case 4: 
        {
            test_cache(nb_thread, graph);
            break;
        }
    case 5: 
        {
            test_chained_stream_file_node(nb_thread, graph);
            break;
        }
    case 6: 
        {
            test_stream_file_node(nb_thread, graph);
            break;
        }
    case 7: 
        {
            test_multi_stream_file_node(nb_thread, graph);
            break;
        }
    default:
        exit(0);
    }
}

void test_multi_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	//     Console
	//        |
	//  --- GenAdd --------------------------
	//  |			|			|			|
	//  File		File		File		File
	//  |			|			|			|
	//  Filename	Filename	Filename	Filename

	int n_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int n_genadd = graph->addNode(CID_GENERICADD_NODE);
	int n_string = graph->addNode(CID_STRING_NODE);
	
	graph->connect(n_console, 0, ROOT_NODE, 0);
	graph->connect(n_genadd, 0, n_console, 0);
	graph->connect(n_string, 0, n_genadd, 0);

	graph->editNodeParameters(n_console, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(n_string, Value(std::string("Read from file = ")));
	
	for (int i=1; i<=4; ++i)
	{
		int n_filename = graph->addNode(CID_STRING_NODE);
		int n_file = graph->addNode(CID_STREAM_FILE_NODE);	
		int n_string_sep = graph->addNode(CID_STRING_NODE);

		std::string filename = (boost::format("D:/Prog/test%d.txt") % i).str();
		graph->editNodeParameters(n_filename, Value(filename));
		graph->editNodeParameters(n_string_sep, Value(std::string(" | ")));
		graph->connect(n_file, 0, n_genadd, 0);
		graph->connect(n_filename, 0, n_file, 0);
		graph->connect(n_string_sep, 0, n_genadd, 0);
	}

	graph->execute(nb_threads);

	getchar();
}

void test_chained_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	//     Console
	//        |
	//  --- GenAdd ---
	//  |            |
	//  String     File
	//               |
	//             Filename

	int n_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int n_filename = graph->addNode(CID_STRING_NODE);
	int n_file = graph->addNode(CID_STREAM_FILE_NODE);
	int n_string = graph->addNode(CID_STRING_NODE);
	int n_genadd = graph->addNode(CID_GENERICADD_NODE);

    std::string path;
    std::cout << "Enter path of file:" << std::endl;
    std::cin >> path;

	// create connections
	graph->connect(n_console, 0, ROOT_NODE, 0);
	graph->connect(n_genadd, 0, n_console, 0);
	graph->connect(n_string, 0, n_genadd, 0);
	graph->connect(n_file, 0, n_genadd, 0);
	graph->connect(n_filename, 0, n_file, 0);

	graph->editNodeParameters(n_console, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(n_string, Value(std::string("Read from file = ")));

	for (int i=0; i<256; ++i)
	{
		// execute graph with no file
		graph->editNodeParameters(n_filename, Value(std::string("")));
		graph->execute(nb_threads);

		// execute graph with an input file
		graph->editNodeParameters(n_filename, Value(path));
		graph->execute(nb_threads);
	}
	getchar();
}

void test_stream_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	int n_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int n_filename = graph->addNode(CID_STRING_NODE);
	int n_file = graph->addNode(CID_STREAM_FILE_NODE);

    std::string path;
    std::cout << "Enter path of file:" << std::endl;
    std::cin >> path;

	graph->editNodeParameters(n_console, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(n_filename, Value(path));


	// create connections
	graph->connect(n_filename, 0, n_file, 0);
	graph->connect(n_file, 0, n_console, 0);
	graph->connect(n_console, 0, ROOT_NODE, 0);

	// execute graph
	for (int i=0; i<512; ++i)
	{
		graph->execute(nb_threads);
	}

	std::cout << "Done!" << std::endl;

	getchar();
}

void test_file_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	int n_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int n_filename = graph->addNode(CID_STRING_NODE);
	int n_file = graph->addNode(CID_FILE_NODE);

    std::string path;
    std::cout << "Enter path of file:" << std::endl;
    std::cin >> path;

	graph->editNodeParameters(n_console, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(n_filename, Value(path));

	// create connections
	graph->connect(n_filename, 0, n_file, 0);
	graph->connect(n_file, 0, n_console, 0); // if
	graph->connect(n_console, 0, ROOT_NODE, 0);

	// execute graph
	graph->execute(nb_threads);
	getchar();
}

void test_multithread_lots_of_nodes(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	int node_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int node_itoa = graph->addNode(CID_ITOA_NODE);
	int node_genadd = graph->addNode(CID_GENERICADD_NODE);

	std::vector<int> nodes;
	nodes.push_back(node_genadd);
	while(nodes.size()<32768)
	{
		std::vector<int>::iterator it = nodes.begin();
		int linked_node = *it;
		nodes.erase(it);
		for (int i=0; i<32; ++i)
		{
			int tmp = graph->addNode(CID_GENERICADD_NODE);
			graph->connect(tmp, 0, linked_node, 0);
			nodes.push_back(tmp);
		}
	}

	for (std::vector<int>::iterator it = nodes.begin(); it != nodes.end(); ++it)
	{
		for (int i=0; i<32; ++i)
		{
			int node_int = graph->addNode(CID_INTEGER_NODE);
			graph->connect(node_int, 0, *it, 0);
			graph->editNodeParameters(node_int, Value(1));
		}
	}

	// create connections
	graph->connect(node_genadd, 0, node_itoa, 0);
	graph->connect(node_itoa, 0, node_console, 0);
	graph->connect(node_console, 0, ROOT_NODE, 0);

	graph->editNodeParameters(node_console, Value(std::string("ConsoleOutput")));

	// execute graph
	graph->execute(nb_threads);
	getchar();
}

void test_cache(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	//     Console
	//        |
	//  --- GenAdd ---
	//  |            |
	//  String     ItoA
	//               |
	//             GenAdd
	//            |       |
	//           Point3  Point3

	int node_console = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int node_genadd1 = graph->addNode(CID_GENERICADD_NODE);
	int node_string = graph->addNode(CID_STRING_NODE);
	int node_itoa = graph->addNode(CID_ITOA_NODE);
	int node_genadd2 = graph->addNode(CID_GENERICADD_NODE);
	int node_point31 = graph->addNode(CID_POINT3_NODE);
	int node_point32 = graph->addNode(CID_POINT3_NODE);
		
	// create connections
	graph->connect(node_console, 0, ROOT_NODE, 0);
	graph->connect(node_genadd1, 0, node_console, 0);
	graph->connect(node_string, 0, node_genadd1, 0);
	graph->connect(node_itoa, 0, node_genadd1, 0);
	graph->connect(node_genadd2, 0, node_itoa, 0);
	graph->connect(node_point31, 0, node_genadd2, 0);
	graph->connect(node_point32, 0, node_genadd2, 0);
	
	graph->editNodeParameters(node_console, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(node_string, Value(std::string("Computed value = ")));
	graph->editNodeParameters(node_point31, Point3(1, 1, 1));
	graph->editNodeParameters(node_point32, Point3(2, 2, 2));
	
	// execute graph
	graph->execute(nb_threads);
	getchar();

	// execute graph
	graph->editNodeParameters(node_point32, Point3(4, 4, 4));
	graph->execute(nb_threads);
	getchar();
}

void test_if_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	int node_console_id = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int node_string_id = graph->addNode(CID_STRING_NODE);
	int node_if_id = graph->addNode(CID_IF_NODE);
	int node_bool_id = graph->addNode(CID_BOOLEAN_NODE);
	int node_point3_id = graph->addNode(CID_POINT3_NODE);
	int node_matrix3_id = graph->addNode(CID_MATRIX3_NODE);
	int node_genadd_id = graph->addNode(CID_GENERICADD_NODE);
	int node_itoa_id = graph->addNode(CID_ITOA_NODE);

	// create connections
	graph->connect(node_string_id, 0, node_genadd_id, 0);
	graph->connect(node_bool_id, 0, node_if_id, 0); // if
	graph->connect(node_point3_id, 0, node_if_id, 1); // then
	graph->connect(node_matrix3_id, 0, node_if_id, 2); // else
	graph->connect(node_if_id, 0, node_itoa_id, 0); // output of the if node
	graph->connect(node_itoa_id, 0, node_genadd_id, 0);
	graph->connect(node_genadd_id, 0, node_console_id, 0);
	//graph->connect(node_console_id, 0, ROOT_NODE, 0);

	graph->editNodeParameters(node_console_id, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(node_string_id, Value(std::string("Computed value = ")));
	graph->editNodeParameters(node_point3_id, Point3(3, 7, 9));
	graph->editNodeParameters(node_matrix3_id, Matrix3(4,5,6,1,2,3,4,2,5));
	graph->editNodeParameters(node_bool_id, Value(true));

	// execute graph
	graph->execute(nb_threads);
	getchar();

	// execute graph
	graph->editNodeParameters(node_bool_id, Value(false));
	graph->execute(nb_threads);
	getchar();
}

void test_for_node(size_t nb_threads, boost::shared_ptr<ClientGraph> graph)
{
	int node_integer_id = graph->addNode(CID_INTEGER_NODE);
	int node_for_id = graph->addNode(CID_FOR_NODE);
	int node_itoa_id = graph->addNode(CID_ITOA_NODE);
	int node_string_id = graph->addNode(CID_STRING_NODE);
	int node_console_id = graph->addNode(CID_CONSOLE_OUTPUT_NODE);
	int node_genadd_id = graph->addNode(CID_GENERICADD_NODE);

	// create global connections
	graph->connect(node_integer_id, 0, node_for_id, 0); // nb iterations
	graph->connect(node_for_id, 0, ROOT_NODE, 0); // 

	// create loop connections
	graph->connect(node_for_id, 1, node_itoa_id, 0); // convert iteration into string
	graph->connect(node_string_id, 0, node_genadd_id, 0); // 
	graph->connect(node_itoa_id, 0, node_genadd_id, 0); // 
	graph->connect(node_genadd_id, 0, node_console_id, 0); // 
	graph->connect(node_console_id, 0, node_for_id, 1); // 

	graph->editNodeParameters(node_console_id, Value(std::string("ConsoleOutput")));
	graph->editNodeParameters(node_string_id, Value(std::string("Current iteration = ")));
	graph->editNodeParameters(node_integer_id, Value(5));

	// execute graph
	graph->execute(nb_threads);
	getchar();
}
