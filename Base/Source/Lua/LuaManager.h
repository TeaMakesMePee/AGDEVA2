#pragma once

#include "SingletonTemplate.h"
#include "Vector3.h"
// Lua's headers
#include "../Lua/lua.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class CLuaManager : public Singleton<CLuaManager>
{
public:
	// Constructor
	CLuaManager(void);

	// Destructor
	virtual ~CLuaManager(void);

	// Initialise this class instance
	bool Init(void);
	// Initialise this class instance - overloaded
	bool Init(const string& filename, const std::string& Writefilename, const bool bDisplayFileContent = false);
	// Destroy this class instance
	void Destroy(void);
	// PrintSelf
	void PrintSelf(void);
	// Print error while using Lua functions
	void printError(const string& variableName, const string& reason);

	// Get an Vector of Integers
	vector<int> getIntVector(const string& name);
	// Get an Vector of String
	void getStringVector(const std::string& name, std::vector<string>& keys, std::vector<int>& values);
	// Get a table of keys
	vector<string> getTableKeys(const string& name);
	// Get distance square value through the Lua Interface Class
	float getDistanceSquareValue(const char* variableName, Vector3 source, Vector3 destination);
	// Get variable number of values through the Lua Interface Class
	bool getVariableValues(const char* variableName,
		int& minValue, int& maxValue, int& avgValue, int& numValues,
		const int varCount, ...);

	// Clean the Lua State
	inline void clean(void);

	// Generic get method
	template<typename T>
	T get(const std::string& variableName)
	{
		if (!pLuaState) {
			printError(variableName, "Script is not loaded");
			return lua_getdefault<T>();
		}

		T result;
		// Check if the variable exists in the Lua file
		if (lua_gettostack(variableName))
		{
			// variable succesfully on top of stack
			/* ADD CODES HERE */
			result = lua_get<T>(variableName);
		}
		else 
		{
			/* ADD CODES HERE */
			result = lua_getdefault<T>();
		}

		clean();
		return result;
	}

	// Get to Stack
	bool lua_gettostack(const std::string& variableName);

	// Generic get which return 0. This is a Template
	template<typename T>
	T lua_get(const std::string& variableName) {
		return 0;
	}

	// Generic default get which return 0. This is a Template
	template<typename T>
	T lua_getdefault() {
		return 0;
	}

	// Generic set method
	template<typename T>
	bool set(const std::string& variableName, const T value, const bool bOverwrite = true)
	{
		if (!pLuaState) {
			printError(variableName, "Script is not loaded");
			return false;
		}

		T result = false;
		// If overwriting existing variable, then don't check if it exists in the Lua file
		if (bOverwrite)
		{
			// variable succesfully on top of stack
			/* ADD CODES HERE */
			result = lua_set<T>(variableName, value, bOverwrite);
		}
		else
		{
			// Check if the variable exists in the Lua file
			if (lua_gettostack(variableName))
			{
				// variable succesfully on top of stack
				/* ADD CODES HERE */
				result = lua_set<T>(variableName, value, bOverwrite);
			}
		}

		clean();
		return result;
	}

	// Generic set. This is a Template
	template<typename T>
	bool lua_set(const std::string& variableName, const T value, const bool bOverwrite = true) {
		return false;
	}

	// Generic default set. This is a Template
	template<typename T>
	T lua_setdefault() {
		return false;
	}

protected:
	// Check if the Lua State is valid
	bool isLuaStateValid(void);
	// Stack dump
	void stackDump(void);

	// Lua State for Reading In
	lua_State* pLuaState;
	// Lua State for Writing Out
	lua_State* pWriteLuaState;
	std::string filename;
	int level;
};

/********************************************************************************/
// Helper template methods for GET
/********************************************************************************/
template <>
inline bool CLuaManager::lua_get<bool>(const std::string& variableName)
{
	return (bool)lua_toboolean(pLuaState, -1);
}

template <>
inline float CLuaManager::lua_get<float>(const std::string& variableName)
{
	if (!lua_isnumber(pLuaState, -1)) {
		printError(variableName, "Not a number");
	}
	return (float)lua_tonumber(pLuaState, -1);
}

template <>
inline int CLuaManager::lua_get<int>(const std::string& variableName)
{
	if (!lua_isnumber(pLuaState, -1)) {
		printError(variableName, "Not a number");
	}
	return (int)lua_tonumber(pLuaState, -1);
}

template <>
inline std::string CLuaManager::lua_get<std::string>(const std::string& variableName)
{
	std::string s = "null";
	if (lua_isstring(pLuaState, -1)) {
		s = std::string(lua_tostring(pLuaState, -1));
	}
	else {
		printError(variableName, "Not a string");
	}
	return s;
}

// Get Vector3 values through the Lua Manager Class
template <>
inline Vector3 CLuaManager::lua_get<Vector3>(const std::string& variableName)
{
	Vector3 aVector(0.0f, 0.0f, 0.0f);
	if (lua_istable(pLuaState, -1)) {
		lua_rawgeti(pLuaState, -1, 1);
		float x = lua_tonumber(pLuaState, -1);
		lua_pop(pLuaState, 1);
		lua_rawgeti(pLuaState, -1, 2);
		float y = lua_tonumber(pLuaState, -1);
		lua_pop(pLuaState, 1);
		lua_rawgeti(pLuaState, -1, 3);
		float z = lua_tonumber(pLuaState, -1);
		lua_pop(pLuaState, 1);

		aVector.Set(x, y, z);
	}
	else {
		printError(variableName, "Not a Vector3");
	}
	return aVector;
}

template<>
inline std::string CLuaManager::lua_getdefault<std::string>()
{
	return "null";
}

/********************************************************************************/
// Helper template methods for SET
/********************************************************************************/
template <>
inline bool CLuaManager::lua_set<bool>(const std::string& variableName, const bool bValue, const bool bOverwrite)
{
	lua_getglobal(pWriteLuaState, "SetToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d", variableName.c_str(), bValue);
	lua_pushstring(pWriteLuaState, outputString);
	lua_pushinteger(pWriteLuaState, bOverwrite);
	// Do a Lua call
	// lua_call(pWriteLuaState, 2, 0);
	// Do a Lua call with debugging information returned.
	if (lua_pcall(pWriteLuaState, 2, 0, 0) != 0)
		std::cout << "Unable to save to Lua file : " << lua_tostring(pWriteLuaState, -1) << std::endl;

	return true;
}

template <>
inline bool CLuaManager::lua_set<float>(const std::string& variableName, const float fValue, const bool bOverwrite)
{
	lua_getglobal(pWriteLuaState, "SetToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %f", variableName.c_str(), fValue);
	lua_pushstring(pWriteLuaState, outputString);
	lua_pushinteger(pWriteLuaState, bOverwrite);
	// Do a Lua call
	// lua_call(pWriteLuaState, 2, 0);
	// Do a Lua call with debugging information returned.
	if (lua_pcall(pWriteLuaState, 2, 0, 0) != 0)
		std::cout << "Unable to save to Lua file : " << lua_tostring(pWriteLuaState, -1) << std::endl;

	return true;
}

template <>
inline bool CLuaManager::lua_set<int>(const std::string& variableName, const int iValue, const bool bOverwrite)
{
	lua_getglobal(pWriteLuaState, "SetToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %d", variableName.c_str(), iValue);
	lua_pushstring(pWriteLuaState, outputString);
	lua_pushinteger(pWriteLuaState, bOverwrite);
	// Do a Lua call
	// lua_call(pWriteLuaState, 2, 0);
	// Do a Lua call with debugging information returned.
	if (lua_pcall(pWriteLuaState, 2, 0, 0) != 0)
		std::cout << "Unable to save to Lua file : " << lua_tostring(pWriteLuaState, -1) << std::endl;

	return true;
}

template <>
inline bool CLuaManager::lua_set<std::string>(const std::string& variableName, const std::string sValue, const bool bOverwrite)
{
	lua_getglobal(pWriteLuaState, "SetToLuaFile");
	char outputString[80];
	sprintf(outputString, "%s = %s", variableName.c_str(), sValue);
	lua_pushstring(pWriteLuaState, outputString);
	lua_pushinteger(pWriteLuaState, bOverwrite);
	// Do a Lua call
	// lua_call(pWriteLuaState, 2, 0);
	// Do a Lua call with debugging information returned.
	if (lua_pcall(pWriteLuaState, 2, 0, 0) != 0)
		std::cout << "Unable to save to Lua file : " << lua_tostring(pWriteLuaState, -1) << std::endl;

	return true;
}

template<>
inline std::string CLuaManager::lua_setdefault<std::string>() {
	return "null";
}
