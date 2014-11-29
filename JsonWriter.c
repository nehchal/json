/*
 * systcs_JSON_Builder.c
 *
 *  Created on: Aug 9, 2013
 *      Author: Nehchal J. / Ram Das
 *      Email: nehchal@systemantics.com / ramdas@systemantics.com
 *  Edited on : Dec 5, 2013
 *  Revision Notes	  : Nov 20, 2013 | Changes made to the floatToStr()
 *  				  : Dec 3, 2013 | Optimized the code for computation
 *  				  : Dec 5, 2013 | Created an object JsonWriter separate
 *  				  	from json string - to align with general practices
 *  				  	for making a library.
 */

#include "stdio.h"
#include "string.h"
#include "JsonWriter.h"

//*****************************************************************************
// Converts an integer to a string. Max possible num of digits = 10
//*****************************************************************************
char* intToStr(int integer, char *str)
{
	char cTemp[11];
	int i = 0,j =0, temp;
	str[0] = '\0';

	if (integer == 0)
		strcpy(str,"0");
	else
	{
		if (integer < 0){
		str[j++] = '-';
		integer*= -1;		//make the integer positive
		}

		while(integer>0){
			temp = integer%10;
			cTemp[i++] = temp + 48;
			integer/=10;
		}

		while(i>0)			//reverse the string
			str[j++] = cTemp[--i];

		str[j] = '\0';
	}

	return str;
}

//*****************************************************************************
// Converts a the mantissa part of a float number to string. Precision value
// should be less than 4.
//*****************************************************************************
char* mantissaToStr(float floatNum, int precision, char* str)
{
	int i = 0, temp, j;
	int len;
	int intNum;
	char strTemp[6];

	str[0]='\0';
	if (!( precision > 0 && precision <=4))	//check the limits of precision
			return strcat(str, "Error");

	for (i=0; i<precision; i++)
		floatNum*=10.0;

	intNum = (int) floatNum;

	/* Conver integer into reversed string */
	for ( i=0, len=0; intNum>0; i++){
		temp = intNum%10;
		strTemp[i] = temp + 48;
		intNum/=10;
		len++;
	}

	/* Add zeroes if length is less than precision */
	for (i=0; i < precision - len; i++)
			str[i] = '0';
	/* Append strTemp to str after appending */
	for (j=len-1; j>=0; j--, i++)
			str[i] = strTemp[j];

	str[i]='\0';

	return str;
}

/* ======= init =======
 * Initializes the JsonWriter
 */
void JsonWriter_init(tJsonWriter *jsonWriter, char *buf){
	jsonWriter->len = 0;
	jsonWriter->outBuf = buf;

}

//*****************************************************************************
// Converts a float to a string. Supports max 6 digits after the decimal point
//*****************************************************************************
char* floatToStr(float floatNum, int precision, char *str)
{
	int i;
	int integral;
	float mantissa;
	char sIntegral[11];
	char mantissaStr[11];

	str[0]='\0';

	if(floatNum != 0){



		if (floatNum < 0){
			strcat(str,"-");
		floatNum*= -1;
		}

		integral = (int) floatNum;
		mantissa = (floatNum - integral);
		strcat(str, intToStr(integral,sIntegral));

		strcat(str,(const char*)".");
		strcat(str, mantissaToStr(mantissa, precision, mantissaStr));
		//else
			//strcat(str,".0");
	}
	else{
		str[0] = '0'; str[1] = '.';
		/* append trailing zeroes according to precision */
		for (i=2; i < precision + 2; i++)
			str[i]='0';
		str[i]='\0';
	}

	return str;
}

//Begins encoding a new array.
void JsonWriter_beginArray(tJsonWriter* obj)
{
	obj->outBuf[obj->len++] = '[';
	return;
}

//Begins encoding a new object.
void JsonWriter_beginObject(tJsonWriter* obj)
{
	//objectOpen = 1;
	obj->outBuf[obj->len++] = '{';
	return;
}

//Ends encoding the current array.
void JsonWriter_endArray(tJsonWriter* obj)
{
	obj->outBuf[obj->len++] = ']';
	obj->outBuf[obj->len] = '\0';
	return;
}
//Ends encoding the current object.
void JsonWriter_endObject(tJsonWriter* obj)
{
	obj->outBuf[obj->len++] = '}';
	obj->outBuf[obj->len] = '\0';
	return;
}

//Encodes the name.
void JsonWriter_name(tJsonWriter* obj, char* sName)
{
	int i;
	obj->outBuf[obj->len++] = '\"';
	for (i=0; sName[i]!='\0'; i++)
		obj->outBuf[obj->len++] = sName[i];
	obj->outBuf[obj->len++] = '\"';
	obj->outBuf[obj->len++] = ':';
	return;
}

//Encodes null.
void JsonWriter_nullValue(tJsonWriter* obj)
{
	obj->outBuf[obj->len++] = 'n';
	obj->outBuf[obj->len++] = 'u';
	obj->outBuf[obj->len++] = 'l';
	obj->outBuf[obj->len++] = 'l';
	return;
}

void JsonWriter_floatAsStringValue(tJsonWriter* obj, float fValue, int precision)
{
	char tempStr[21];
	int i;
	obj->outBuf[obj->len++] = '"';
	floatToStr(fValue, precision, tempStr);
	for (i=0; tempStr[i]!='\0'; i++)
			obj->outBuf[obj->len++] = tempStr[i];
	obj->outBuf[obj->len++] = '"';
	return;
}

//Encodes a float value
void JsonWriter_floatValue(tJsonWriter* obj, float fValue, int precision)
{
	char tempStr[21];
	int i;
	floatToStr(fValue, precision, tempStr);
	for (i=0; tempStr[i]!='\0'; i++)
			obj->outBuf[obj->len++] = tempStr[i];
	return;
}

//Encodes a string value
void JsonWriter_stringValue(tJsonWriter* obj, char* sValue)
{
	int i;
	obj->outBuf[obj->len++] = '\"';
	for (i=0; sValue[i]!='\0'; i++)
		obj->outBuf[obj->len++] = sValue[i];
	obj->outBuf[obj->len++] = '\"';
	return;
}

//Encodes a integer value
void JsonWriter_integerValue(tJsonWriter* obj, int iValue)
{
	char tempStr[11];
	int i;
	intToStr(iValue, tempStr);
	for (i=0; tempStr[i]!='\0'; i++)
			obj->outBuf[obj->len++] = tempStr[i];
	return;
}

//Encodes an object value
void JsonWriter_objectValue(tJsonWriter* obj, char* oValue)
{
	int i;
	for (i=0; oValue[i]!='\0'; i++)
		obj->outBuf[obj->len++] = oValue[i];
	return;
}

//Encodes an array value
void JsonWriter_arrayValue(tJsonWriter* obj, char* aValue)
{
	int i;
	for (i=0; aValue[i]!='\0'; i++)
		obj->outBuf[obj->len++] = aValue[i];
	return;
}


void JsonWriter_boolValue(tJsonWriter* obj, boolean bValue)
{
	if (bValue == TRUE){
		obj->outBuf[obj->len++] = 't';
		obj->outBuf[obj->len++] = 'r';
		obj->outBuf[obj->len++] = 'u';
		obj->outBuf[obj->len++] = 'e';

	}
	else{
		obj->outBuf[obj->len++] = 'f';
		obj->outBuf[obj->len++] = 'a';
		obj->outBuf[obj->len++] = 'l';
		obj->outBuf[obj->len++] = 's';
		obj->outBuf[obj->len++] = 'e';
	}
	return;
}

//to indicate next pair/value will be added
void JsonWriter_next(tJsonWriter* obj)
{
	obj->outBuf[obj->len++] = ',';
	return;
}
