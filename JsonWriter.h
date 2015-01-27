/*
 * systcs_JSON_Builder.h
 *
 *  Created on: Dec 2, 2013
 *      Author: Nehchal J.
 *      Email: nehchalj@gmail.com
 *      Description: Build the JSON string.
 */

#ifndef SYSTCS_JSON_WRITER_H_
#define SYSTCS_JSON_WRITER_H_

#include <xdc/std.h>
#include <inc/FlashAPI/Types.h>

typedef struct{
	int len;
	char *outBuf;
} tJsonWriter;

/*
 * Initializes the JsonWriter
 * JsonWriter   : [IN]  pointer to tJsonWriter object
 * buf          : [OUT] JSON-string is written to it
 */
void JsonWriter_init(tJsonWriter *jsonWriter, char* buf);

//*****************************************************************************
// Begins encoding a new array.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_beginArray(tJsonWriter* obj);
//*****************************************************************************
// Begins encoding a new object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_beginObject(tJsonWriter* obj);
//*****************************************************************************
// Ends encoding the current array.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_endArray(tJsonWriter* obj);
//*****************************************************************************
// Ends encoding the current object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_endObject(tJsonWriter* obj);

//*****************************************************************************
// Encodes a name to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_name(tJsonWriter* obj, char* sName);

//*****************************************************************************
// Encodes a null value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// sName   - points to the name to be encoded
//*****************************************************************************
void JsonWriter_nullValue(tJsonWriter* obj);

//*****************************************************************************
// Encodes a integer value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// iValue  - the integer value to be encoded
//*****************************************************************************
void JsonWriter_integerValue(tJsonWriter* obj, int iValue);

/*
 * Endoes a float value to the given object in quotes.
 * str - points to the string variable to which the JSON string is encoded
 * fValue  - the float value to be encoded
 * precision - the  required number of digits in the mantissa part
 */
void JsonWriter_floatAsStringValue(tJsonWriter* obj, float fValue, int precision);

//*****************************************************************************
// Encodes a float value to the given object without quotes
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// fValue  - the float value to be encoded
// precision - the  required number of digits in the mantissa part
//*****************************************************************************
void JsonWriter_floatValue(tJsonWriter* obj, float fValue, int precision);

//*****************************************************************************
// Encodes a string value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// sValue  - the string to be encoded (Assumed to be ending at null character)
//*****************************************************************************
void JsonWriter_stringValue(tJsonWriter* obj, char* sValue);

//*****************************************************************************
// Encodes a boolean value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// bValue  - points to the boolean value to be encoded
//*****************************************************************************
void JsonWriter_boolValue(tJsonWriter* obj, boolean bValue);

//*****************************************************************************
// Encodes a pre-built object value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// oValue  - points to the pre-built object (effectively a string)
//*****************************************************************************
void JsonWriter_objectValue(tJsonWriter* obj, char* oValue);

//*****************************************************************************
// Encodes a pre-built array value to the given object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
// aValue  - points to the pre-built array (effectively a string)
//*****************************************************************************
void JsonWriter_arrayValue(tJsonWriter* obj, char* aValue);

//*****************************************************************************
// Use this to specify if there is a next element or pair.
// in the current array or object.
// Parameters:
// str - points to the string variable to which the JSON string is encoded
//*****************************************************************************
void JsonWriter_next(tJsonWriter* obj);

#endif /* SYSTCS_JSON_WRITER_H_ */
