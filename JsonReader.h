/*
 * JsonReader.h
 *
 * Created on: Dec 6, 2013
 * Last Edited: Dec 12, 2013
 * Author: Nehchal J.
 * Email: nehchalj@gmail.com
 * Description: Used to read the JSON string if syntactic structure is
 *       		already known. The design is on the lines of Android
 *      		JsonReader.
 *      		(http://developer.android.com/reference/android/util/JsonReader.html)
 *      		Code is not resilient to invalid function calls (eg. calling
 *      		beginObject() fxn even if there is no object in json string).
 */

/* ======= Revision History ========
 * Dec 6, 2013	| New JsonReader library created.
 */

#ifndef _SYSTCS_JSONREADER_H_
#define _SYSTCS_JSONREADER_H_

#include <inc/FlashAPI/Types.h>

typedef struct{
	int ptr;	//current index in string while reading the string
	const char *str;	//pointer to string holding json string
} tJsonReader;

/*
 * Initializes the JsonReader
 */
void JsonReader_init(tJsonReader *jsonReader, const char *jsonObject);

/*
 * Consumes opening bracket of an array
 */
void JsonReader_beginArray(tJsonReader* jsonReader);

/*
 * Consumes opening bracket of an object
 */
void JsonReader_beginObject(tJsonReader* jsonReader);

/*
 * Consumes closing bracket of an array
 */
void JsonReader_endArray(tJsonReader* jsonReader);

/*
 * Consumes closing bracket of an object
 */
void JsonReader_endObject(tJsonReader* jsonReader);

/*
 * Returns true if current array or object has next element.
 */
boolean JsonReader_hasNext(tJsonReader* jsonReader);

/*
 * Returns the boolean value of next token, consuming it
 */
boolean JsonReader_nextBoolean(tJsonReader* jsonReader);

/*
 * Returns the integer value of next token, consuming it
 */
int JsonReader_nextInt(tJsonReader* jsonReader);

/*
 * Returns the long value of next token, consuming it
 */
long JsonReader_nextLong(tJsonReader* jsonReader);

/*
 * Returns the float value of next token, consuming it
 */
float JsonReader_nextFloat(tJsonReader* jsonReader);

/*
 * Returns the next toke, a property name, consuming it
 */
char* JsonReader_nextName(tJsonReader* jsonReader, char *name);

/*
 * Returns the null value of next token, consuming it
 */
void JsonReader_nextNull(tJsonReader* jsonReader);

/*
 * Returns the string value of next token, consuming it
 */
char* JsonReader_nextString(tJsonReader* jsonReader, char *str);

/*
 * Skips the next value recursively
 */
void JsonReader_skipValue(tJsonReader* jsonReader);

#endif /* _SYSTCS_JSONREADER_H_ */
