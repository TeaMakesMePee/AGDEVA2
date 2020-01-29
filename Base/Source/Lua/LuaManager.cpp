#include "LuaManager.h"
#include <iostream>
#include <fstream>
#include <stdarg.h>

// Constructor
CLuaManager::CLuaManager(void)
	: pLuaState(NULL)
	, pWriteLuaState(NULL)
{
	Init();
}

// Destructor
CLuaManager::~CLuaManager(void)
{
	Destroy();
}

// Initialise this class instance
bool CLuaManager::Init(void)
{
	if (pLuaState == NULL)
		pLuaState = lua_open();

	if (pLuaState)
		return true;

	if (pWriteLuaState == NULL)
		pWriteLuaState = lua_open();

	if (pWriteLuaState)
		return true;

	return true;
}

// Initialise this class instance - overloaded
bool CLuaManager::Init(	const std::string& filename, 
						const std::string& Writefilename, 
						const bool bDisplayFileContent)
{
	// Check if the Lua State is valid.
	// Open the Lua State if not
	if (pLuaState == NULL)
	{
		//pLuaState = lua_open();
		pLuaState = luaL_newstate();
	}

	if (pLuaState)
		luaL_openlibs(pLuaState);

	// Open the Lua file and create the Lua State
	// Return false if unable to open the Lua file
	if (luaL_loadfile(pLuaState, filename.c_str()) || lua_pcall(pLuaState, 0, 0, 0)) {
		cout << "Error: script not loaded (" << filename << ")" << endl;
		pLuaState = NULL;
		return false;
	}

	// Display the file contents for debugging purposes
	if (bDisplayFileContent)
	{
		string STRING;
		ifstream infile;
		infile.open(filename.c_str());
		while (!infile.eof()) // To get you all the lines.
		{
			getline(infile, STRING); // Saves the line in STRING.
			cout << STRING << endl; // Prints our STRING.
		}
		infile.close();
	}

	// Check if the Lua State is valid.
	// Open the Lua State if not
	if (pWriteLuaState == NULL)
	{
		//pWriteLuaState = lua_open();
		pWriteLuaState = luaL_newstate();
	}

	if (pWriteLuaState)
		luaL_openlibs(pWriteLuaState);

	// Open the Lua file and create the Lua State
	// Return false if unable to open the Lua file
	if (luaL_loadfile(pWriteLuaState, Writefilename.c_str()) || lua_pcall(pWriteLuaState, 0, 0, 0)) {
		cout << "Error: script not loaded (" << Writefilename << ")" << endl;
		pWriteLuaState = NULL;
		return false;
	}

	// Display the file contents for debugging purposes
	if (bDisplayFileContent)
	{
		string STRING;
		ifstream infile;
		infile.open(Writefilename.c_str());
		while (!infile.eof()) // To get you all the lines.
		{
			getline(infile, STRING); // Saves the line in STRING.
			cout << STRING << endl; // Prints our STRING.
		}
		infile.close();
	}

	return true;
}

// Destroy this class instance
void CLuaManager::Destroy(void)
{
	if (pLuaState)
	{
		lua_close(pLuaState);
		pLuaState = NULL;
	}
}

// Stack Dump
void CLuaManager::stackDump(void)
{
	int i = lua_gettop(pLuaState);
	printf(" ----------------  Stack Dump ----------------\n");
	while (i) {
		int t = lua_type(pLuaState, i);
		switch (t) {
		case LUA_TSTRING:
			printf("%d:`%s'\n", i, lua_tostring(pLuaState, i));
			break;
		case LUA_TBOOLEAN:
			printf("%d: %s\n", i, lua_toboolean(pLuaState, i) ? "true" : "false");
			break;
		case LUA_TNUMBER:
			printf("%d: %g\n", i, lua_tonumber(pLuaState, i));
			break;
		default: 
			printf("%d: %s\n", i, lua_typename(pLuaState, t)); 
			break;
		}
		i--;
	}
	printf("--------------- Stack Dump Finished ---------------\n");
}

// PrintSelf
void CLuaManager::PrintSelf(void)
{
	cout << "********************************************************************************" << endl;
	cout << "CLuaManager::PrintSelf" << endl;
	if (isLuaStateValid())
		cout << "Lua State has been initialised" << endl;
	else
		cout << "Lua State has NOT been initialised" << endl;
	stackDump();
	cout << "********************************************************************************" << endl;
}

// Print error while using Lua functions
void CLuaManager::printError(const std::string& sVariableName, const std::string& sReason)
{
	cout << "Error: Unable to get [" << sVariableName << "] : " << sReason << endl;
}

// Get an Vector of Integers
std::vector<int> CLuaManager::getIntVector(const std::string& name)
{
	std::vector<int> v;
	lua_gettostack(name.c_str());
	if (lua_isnil(pLuaState, -1)) { // array is not found
		return std::vector<int>();
	}
	lua_pushnil(pLuaState);
	while (lua_next(pLuaState, -2)) {
		v.push_back((int)lua_tonumber(pLuaState, -1));
		lua_pop(pLuaState, 1);
	}
	clean();
	return v;
}

// Get an Vector of String
void CLuaManager::getStringVector(const std::string& name, std::vector<string>& keys, std::vector<int>& values)
{
	lua_gettostack(name.c_str());
	if (lua_isnil(pLuaState, -1)) { // array is not found
		return;
	}
	// stack now contains: -1 => nil; -2 => table
	lua_pushnil(pLuaState);
	while (lua_next(pLuaState, -2))
	{
		// stack now contains: -1 => value; -2 => key; -3 => table
		// copy the key so that lua_tostring does not modify the original
		lua_pushvalue(pLuaState, -2);
		// stack now contains: -1 => key; -2 => value; -3 => key; -4 => table

		// Push the key and value into the 2 vectors
		keys.push_back(lua_tostring(pLuaState, -1));
		values.push_back((int)lua_tonumber(pLuaState, -2));

		// pop value + copy of key, leaving original key
		lua_pop(pLuaState, 2);
		// stack now contains: -1 => key; -2 => table
	}

	// Clean the stack
	clean();
}

// Get a table of keys
std::vector<std::string> CLuaManager::getTableKeys(const std::string& name)
{
	// function for getting table keys
	std::string code = "function getKeys(name) "
		"s = \"\""
		"for k, v in ipairs(_G[name]) do "
		"    s = s..k..\",\" "
		"    end "
		"return s "
		"end";
	// Execute the code
	luaL_loadstring(pLuaState, code.c_str());
	lua_pcall(pLuaState, 0, 0, 0);
	// Get function; get ready to execute getKeys method
	lua_getglobal(pLuaState, "getKeys");
	lua_pushstring(pLuaState, name.c_str());
	// Execute getKeys method
	lua_pcall(pLuaState, 1, 1, 0);
	std::string test = lua_tostring(pLuaState, -1);
	std::vector<std::string> strings;
	std::string temp = "";
	std::cout << "TEMP:" << test << std::endl;
	// Loop through and get all the keys from the Lua State
	for (unsigned int i = 0; i < test.size(); i++) {
		if (test.at(i) != ',')
		{
			// Store the characters of a key into temp
			temp += test.at(i);
		}
		else
		{
			// Push the keys inside a temp into strings
			strings.push_back(temp);
			// Reset temp to empty string
			temp = "";
		}
	}
	// Clean the Lua State
	clean();
	// Return the string containing the keys
	return strings;
}

float CLuaManager::getDistanceSquareValue(const char * variableName, Vector3 source, Vector3 destination)
{
	if (!pWriteLuaState) {
		printError(variableName, "Script is not loaded");
		return -1.0f;
	}

	lua_getglobal(pWriteLuaState, variableName);
	lua_pushnumber(pWriteLuaState, source.x);
	lua_pushnumber(pWriteLuaState, source.y);
	lua_pushnumber(pWriteLuaState, source.z);
	lua_pushnumber(pWriteLuaState, destination.x);
	lua_pushnumber(pWriteLuaState, destination.y);
	lua_pushnumber(pWriteLuaState, destination.z);

	// Do a Lua call with debugging information returned.
	float distanceSquare = -1.0f;
	if (lua_pcall(pWriteLuaState, 6, 1, 0) != 0)
		std::cout << "Unable to call " << variableName << " : " << std::endl;
	else
		distanceSquare = (float)lua_tonumber(pWriteLuaState, -1);

	// Clean the stack
	clean();

	return distanceSquare;
}

bool CLuaManager::getVariableValues(const char * variableName, int & minValue, int & maxValue, int & avgValue, int & numValues, const int varCount, ...)
{
	lua_getglobal(pWriteLuaState, variableName);

	double fVariable;
	va_list paramList;
	va_start(paramList, varCount);
	for (int i = 0; i < varCount; i++)
	{
		fVariable = va_arg(paramList, double);
		lua_pushnumber(pWriteLuaState, fVariable);
	}
	va_end(paramList);

	lua_pcall(pWriteLuaState, varCount, 4, 0);

	numValues = lua_tonumber(pWriteLuaState, -1);
	lua_pop(pWriteLuaState, 1);
	avgValue = lua_tonumber(pWriteLuaState, -1);
	lua_pop(pWriteLuaState, 1);
	maxValue = lua_tonumber(pWriteLuaState, -1);
	lua_pop(pWriteLuaState, 1);
	minValue = lua_tonumber(pWriteLuaState, -1);
	lua_pop(pWriteLuaState, 1);

	// Clean the stack
	clean();

	return true;
}

// Clean the Lua State
inline void CLuaManager::clean(void)
{
	// Check if the Lua State is valid
	if (isLuaStateValid())
		return;

	// Get the number of entries in the Lua Stack
	int n = lua_gettop(pLuaState);
	// Pop the number of entries in the Lua Stack
	lua_pop(pLuaState, n);
}

// Get to Stack
bool CLuaManager::lua_gettostack(const string& variableName)
{
	level = 0;
	string var = "";

	// Loop through all the variables
	for (unsigned int i = 0; i < variableName.size(); i++)
	{
		if (variableName.at(i) == '.')
		{
			// If the variable is a Global variable...
			if (level == 0)
			{
				lua_getglobal(pLuaState, var.c_str());
			}
			else
			{
				lua_getfield(pLuaState, -1, var.c_str());
			}

			// If the variable is not found...
			if (lua_isnil(pLuaState, -1))
			{
				printError(variableName, var + " is not defined");
				return false;
			}
			else
			{
				var = "";
				level++;
			}
		}
		else
		{
			var += variableName.at(i);
		}
	}

	// If the variable is a Global variable...
	if (level == 0)
	{
		lua_getglobal(pLuaState, var.c_str());
	}
	else
	{
		lua_getfield(pLuaState, -1, var.c_str());
	}
	// If the variable is not found...
	if (lua_isnil(pLuaState, -1))
	{
		printError(variableName, var + " is not defined");
		return false;
	}

	return true;
}

// Check if the Lua State is valid
bool CLuaManager::isLuaStateValid(void)
{
	if (pLuaState)
		return true;

	cout << "Lua State has not been initialised" << endl;
	return false;
}