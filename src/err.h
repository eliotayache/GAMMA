#ifndef ERR_H_
#define ERR_H_ 

#include <iostream>
#include <exception>
#include "environment.h"

using namespace std;

struct inconsistentEnvironmentException : public exception
{
  const char * what () const throw ()
  {
    return "Forbidden combination of environment options (check documentation)!";
  }
};

struct notImplementedException : public exception
{
  const char * what () const throw ()
  {
    return "This is not implemented yet!";
  }
};

struct MPITooManyTasksException : public exception
{
  const char * what () const throw ()
  {
    return "Too many MPI tasks, Number of tasks must be equal to number of nodes.";
  }
};

struct NegativePressureException : public exception
{
  const char * what () const throw ()
  {
    return "Negative Pressure Exception!";
  }
};

struct PrimitiveReconstructionDomainException : public exception
{
  const char * what () const throw ()
  {
    return "Pressure ran out of definition domain in primitive reconstruction!";
  }
};

struct PrimitiveReconstructionFailedException : public exception
{
  const char * what () const throw ()
  {
    return "Timeout on primitive reconstruction!";
  }
};

struct StartupFileManagementException : public exception
{
  const char * what () const throw ()
  {
    return "Error when handling files on startup";
  }
};

struct OverwriteOutputException : public exception
{
  const char * what () const throw ()
  {
    return "You are about to overwrite ouput files. Use '-w' flag if it's intentional.";
  }
};

struct WrongCombinatinoOfFlagsException : public exception
{
  const char * what () const throw ()
  {
    return "Wrong combination of flags! Check that they can be used together.";
  }
};

#endif