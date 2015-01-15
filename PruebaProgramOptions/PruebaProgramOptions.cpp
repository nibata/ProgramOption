// PruebaProgramOptions.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

namespace
{
	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t SUCCESS = 0;
	const size_t ERROR_UNHABLED_EXCEPTION=2;

}

int _tmain(int argc, _TCHAR* argv[])
{
	
	try
	{
		po::options_description desc("Options");
		
		desc.add_options()
			("help,h", "mensaje de ayuda")
			("constructor,c", "Muestra constructor")
			("valor,v", po::value<int>(),"asigna el valor del divisor de 1/x");
		
		po::variables_map vm;
		try
		{
			auto parsed = po::parse_command_line(argc, argv, desc);
			po::store(parsed, vm);

			if(vm.count("help"))
			{
				cout<< "Linea de comandos (breve descripcion)" << endl
					<< desc << endl;
				
				return SUCCESS;
	
			}

			if(vm.count("constructor"))
			{
				ClaseSimple cp;
				return SUCCESS;
			}

			if(vm.count("valor"))
			{
				try
				{
					if(vm["valor"].as<int>())throw vm["valor"].as<int>();
					else throw 'e';
				}
				catch(int i)
				{
					cout << "Valor = " << 1/i;
					return SUCCESS;
				}
				catch(...)
				{
					cerr << "ERROR: " << endl;
					return ERROR_UNHABLED_EXCEPTION;
				}
				
			}

			po::notify(vm);
		
		}
		catch(po::error& e)
		{
			cerr << "ERROR: " << e.what() << endl << endl;
			cerr << desc << endl;

			return ERROR_IN_COMMAND_LINE;
		}

	
	}
	catch(exception& e)
	{
		cerr << "Exepcion: " << e.what() << ", la aplicacion existira ahora" << endl;
		return ERROR_UNHABLED_EXCEPTION;
	}
	
	return SUCCESS;
}

