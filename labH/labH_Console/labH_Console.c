#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#else

#include <stdlib.h>

#endif // _DEBUG
#include "labH_Console.h"
#include <stdio.h>
#pragma warning(disable:4996)
#include <string.h>

static _dsGet* DsGet;

static _dsFree* DsFree;

static _dsFind* DsFind;

static _dsAdd* DsAdd;

static _dsRemove* DsRemove;

void SetDataStructure(_dsGet* dsGet, _dsFree* dsFree, _dsFind* dsFind, _dsAdd* dsAdd, _dsRemove* dsRemove)
{
  DsGet = dsGet;
  DsFree = dsFree;
  DsFind = dsFind;
  DsAdd = dsAdd;
  DsRemove = dsRemove;
}

static void* DataStructureGet(void)
{
  return (void*)DsGet();
}

static void DataStructureFree(void* dataStructure)
{
  DsFree(dataStructure);
}

typedef OUT_CODE CommandFunc_t(void** dataStructure_p, FILE* instream);

static OUT_CODE cmdAdd(void** dataStructure_p, FILE* instream)
{
  int key;
  int output;
  if (1 != fscanf(instream, "%i", &key))
  {
    return OC_ERROR;
  }
  output = DsAdd(dataStructure_p, key, key);
  switch (output)
  {
  case -1:
  case 0:
  case 1:
    return OC_OK;
    break;
  default:
    return OC_ERROR;
    break;
  }
}

static OUT_CODE cmdFind(void** dataStructure_p, FILE* instream)
{
  int key;
  int output;
  int tmp;
  if (1 != fscanf(instream, "%i", &key))
  {
    return OC_ERROR;
  }
  output = DsFind(dataStructure_p, key, &tmp);
  switch (output)
  {
  case -1:
    return OC_NO;
    break;
  case 1:
    return OC_YES;
    break;
  default:
    return OC_ERROR;
    break;
  }
}

static OUT_CODE cmdRemove(void** dataStructure_p, FILE* instream)
{
  int key;
  int output;
  int tmp;
  if (1 != fscanf(instream, "%i", &key))
  {
    return OC_ERROR;
  }
  output = DsRemove(dataStructure_p, key, &tmp);
  switch (output)
  {
  case -1:
  case 0:
  case 1:
    return OC_OK;
    break;
  default:
    return OC_ERROR;
    break;
  }
}

#define COMMAND_COUNT 3

static struct
{
  char str[2];
  CommandFunc_t* func;
}commands[] =
{
  {"a", cmdAdd},
  {"f", cmdFind},
  {"r", cmdRemove},
};

static int ScanCommand(FILE* instream)
{
  int i, commandID, len;
  char commandBuffer[3] = "";
  len = fscanf(instream, "%2s", commandBuffer);
  commandID = -1;
  if (len != 0 && strlen(commandBuffer) != 0)
  {
    for (i = 0; i < COMMAND_COUNT; i++)
    {
      if (strncmp(commandBuffer, commands[i].str, 2) == 0)
      {
        commandID = i;
        break;
      }
    }
  }
  return commandID;
}

static int IsCorrectCommandID(int commandID) { return (commandID < COMMAND_COUNT && commandID >= 0); }

static OUT_CODE ExecuteCommand(int commandID, void** dataStructure_p, FILE* instream)
{
  if (!IsCorrectCommandID(commandID))
  {
    return OC_ERROR;
  }
  return commands[commandID].func(dataStructure_p, instream);
}

int StartConsole(void)
{
  int commandID;
  OUT_CODE oCode;
  void* dataStructure;
  dataStructure = DataStructureGet();
  do
  {
    commandID = ScanCommand(stdin);
    if (IsCorrectCommandID(commandID))
    {
      oCode = ExecuteCommand(commandID, &dataStructure, stdin);
      switch (oCode)
      {
      case OC_OK:
        break;
      case OC_YES:
        printf("yes\n");
        break;
      case OC_NO:
        printf("no\n");
        break;
      default:
        DataStructureFree(dataStructure);
        return -1;
        break;
      }
    }
  } while (IsCorrectCommandID(commandID) && !feof(stdin));
  DataStructureFree(dataStructure);
  return 0;
}