/*
 * help_macros.h
 *
 *  Created on: Dec 5, 2013
 *      Author: paul
 */

#ifndef HELP_MACROS_H_
#define HELP_MACROS_H_

/**
 * CAUTION! to refresh this file, make sure to clean the project.
 */

#include <cassert>

/**
 * extension for the assert function (with logger)
 */
#define ASSERT_WITH_MESSAGE(logger, condition, message) do { \
if (!(condition)) { LOG4CXX_ERROR(logger,message) } \
assert ((condition)); } while(false)

#endif /* HELP_MACROS_H_ */
