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
 *
 * extension for the assert function (with logger)
 *
 * @param logger a LOG4CXX logger
 * @param condition if true, nothing happens in particular. otherwise the error message will be printed AND the assert fails
 * @param message
 */
#define ASSERT_WITH_MESSAGE(logger, condition, message) do { \
if (!(condition)) { LOG4CXX_ERROR(logger,message) } \
assert ((condition)); } while(false)

//needs this fix because native cpp whould return floor(-1) == -2, but expected -1
#define floorFix(d) ((d >= 0)? floor(d) : -floor(-d))

#endif /* HELP_MACROS_H_ */
