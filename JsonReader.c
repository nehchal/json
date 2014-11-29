/*
 * JsonReader.c
 *
 * Created on: Dec 6, 2013
 * Last Edited: Dec 12, 2013
 * Author: Nehchal J.
 * Email: nehchal@systemantics.com
 * Organization: Systemantics India Pvt. Ltd.
 */

/* ======= Revision History ========
 * Dec 6, 2013	| New JsonReader library created.
 */

#include "JsonReader.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define isAlphabet(ch) ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
#define isDigit(ch)	(ch >= '0' && ch <= '9')

void JsonReader_init(tJsonReader *jsonReader, const char *jsonObj){
	jsonReader->ptr=0;			//point to the start of the string
	jsonReader->str = jsonObj;
}

void JsonReader_beginArray(tJsonReader *jsonReader){
	/* Array can be outermost container of Json string. It can be a value in
	 * key-value pair. It can be an element of array.
	 */
    while(jsonReader->str[jsonReader->ptr++] != '[');
}

void JsonReader_beginObject(tJsonReader* jsonReader){
	/* Object may be outermost container of Json string. It can be a value in
	 * key-value pair. It can be element of an array.
	 */
    while(jsonReader->str[jsonReader->ptr++] != '{');
}

void JsonReader_endArray(tJsonReader* jsonReader){
	/* The array should not be ended till all the elements have been read
	 * because ']' may be a part of name/string in subsequent elements. */
    while(jsonReader->str[jsonReader->ptr++] != ']');
}

void JsonReader_endObject(tJsonReader* jsonReader){
	/* An object should not be ended till all the pairs have been read
	 * because '}' may be a part of name/string in subsequent pairs. */
    while(jsonReader->str[jsonReader->ptr++]!='}');
}

boolean JsonReader_hasNext(tJsonReader* jsonReader){
	/* Return false if all characters before '}' or ']' are not alphabets,
	 * or are not digits or none of '[', '{', '"', ',' */
	int lookAheadPtr;
	char ch;
	lookAheadPtr = jsonReader->ptr;
	while ( (ch = jsonReader->str[lookAheadPtr]) != '\0' ){ //till end of str
		if ( isAlphabet(ch) || isDigit(ch) ||
				ch=='[' || ch=='{' || ch=='"' || ch==',' )
			return true;
		if (ch=='}' || ch==']')
			return false;
		lookAheadPtr++;
	}
	return false; //this line will not be reached
}

/*
 * Returns the boolean value of next token, consuming it
 */
boolean JsonReader_nextBoolean(tJsonReader* jsonReader){
	while(jsonReader->str[jsonReader->ptr]!='t' &&
			jsonReader->str[jsonReader->ptr]!='f'){
		jsonReader->ptr++;
	}

	if (!strncmp("true", jsonReader->str + jsonReader->ptr,	4)){
		jsonReader->ptr += 4;
		return true;
	}
	else if (!strncmp("false",jsonReader->str + jsonReader->ptr,5)){
		jsonReader->ptr += 5;
		return false;
	}

	return false; //this line will not be reached for valid Json string
}

int JsonReader_nextInt(tJsonReader* jsonReader){
	/* For 32-bit range, integer lies between -32768 and 32767 (2^15-1).
	 * So, max string length for double can be 5. */
	char ch;
	char sInt[6];
	int index = 0;

	/* move ahead ptr till +/- symbol or digit is encountered */
	ch = jsonReader->str[jsonReader->ptr];
	while( ch != '+' && ch != '-' && !isDigit(ch) ) ch = jsonReader->str[++jsonReader->ptr];

	ch = jsonReader->str[jsonReader->ptr];
	while ( ch == '+' || ch == '-' || isDigit(ch) ){	//till is +/- symbol or digit
		sInt[index++] = ch;
		jsonReader->ptr++;

		ch = jsonReader->str[jsonReader->ptr];
	}

	sInt[index]='\0';

	return atoi(sInt);
}

long JsonReader_nextLong(tJsonReader* jsonReader){
	/* For 32-bit range, double lies between -2147483647 and
	 * 2147483647 (2^31-1). So, maximum string length for double can be 11.
	 * Code will be same as nextInt() fxn with few minor changes. */
	char ch;
	char sLong[12];
	int index = 0;

	/* move ahead ptr till +/- symbol or digit is encountered */
	ch = jsonReader->str[jsonReader->ptr];
	while( ch != '+' && ch != '-' && !isDigit(ch) ) ch = jsonReader->str[++jsonReader->ptr];

	ch = jsonReader->str[jsonReader->ptr];
	while ( ch == '+' || ch == '-' || isDigit(ch) ){	//till is +/- symbol or digit
		sLong[index++] = ch;
		jsonReader->ptr++;

		ch = jsonReader->str[jsonReader->ptr];
	}

	sLong[index]='\0';

	return atol(sLong);
}

float JsonReader_nextFloat(tJsonReader* jsonReader){
	/* For 32-bit range, double lies between -2147483647 and
	 * 2147483647 (2^31-1). So, maximum string length for double can be 11.
	 * Code will be same as nextInt() fxn with few minor changes. */
	char ch;
	char sFloat[12];
	int index = 0;

	/* move ahead ptr till +/- symbol or digit or '.' is encountered */
	ch = jsonReader->str[jsonReader->ptr];
	while( ch != '+' && ch != '-' && !isDigit(ch) && ch != '.') ch = jsonReader->str[++jsonReader->ptr];

	ch = jsonReader->str[jsonReader->ptr];
	while ( ch == '+' || ch == '-' || isDigit(ch) || ch =='.' ){	//till is +/- symbol or digit
		sFloat[index++] = ch;
		jsonReader->ptr++;

		ch = jsonReader->str[jsonReader->ptr];
	}

	sFloat[index]='\0';

	return atof(sFloat);

}

char* JsonReader_nextName(tJsonReader* jsonReader, char *name){
	/* Read the string between next two double quotes. Double quote can be
	 * a part of name too, but then it would be preceded by backslash. This
	 * has been handled.
	 */
	int index=0;
	char ch;

	/* Move ahead till double quote is encountered */
	while (jsonReader->str[jsonReader->ptr++] != '"');

	while( (ch = jsonReader->str[jsonReader->ptr]) != '"' ||
			jsonReader->str[jsonReader->ptr - 1] == '\\' ){
		name[index++] = ch;
		jsonReader->ptr++;
	}

	jsonReader->ptr++;		//to move the ptr ahead of closing double quote

	name[index]='\0';
	return name;
}

void JsonReader_nextNull(tJsonReader* jsonReader){
	/* Move forward till character 'n' is encoutered */
	while(jsonReader->str[jsonReader->ptr++] != 'n');

	/* ptr is pointing at 'u' */
	if (!strncmp("null", jsonReader->str + jsonReader->ptr - 1,	4)){
		jsonReader->ptr += 3;
		return;
	}
}

/*
 * Returns the string value of next token, consuming it
 */
char* JsonReader_nextString(tJsonReader* jsonReader, char *str){
	/* It is same as getting the nextName() fxn */
	
	return JsonReader_nextName(jsonReader, str);
}

/*
 * skips a string and moves the ptr forward
 */
static void skipString(tJsonReader *jsonReader){
	/* Code is similar to nextString() fxn */
	
	/* Move ahead till double quote is encountered */
	while (jsonReader->str[jsonReader->ptr++] != '"');

	while( jsonReader->str[jsonReader->ptr] != '"' ||
			jsonReader->str[jsonReader->ptr - 1] == '\\' ){
		jsonReader->ptr++;
	}

	jsonReader->ptr++;		//to move the ptr ahead of closing double quote
}

/*
 * skips a object or array value and moves the ptr forward
 */
static void skipObjectOrArray(tJsonReader *jsonReader){

	int numCurlyOpBrckt=0, numCurlyClBrckt=0;
	int numSqOpBrckt=0, numSqClBrckt=0;
	char ch;

	/* find at the beginning of object/array */
	ch = jsonReader->str[jsonReader->ptr++];
	while(ch != '{' && ch != '[' && ch != '\0')	ch=jsonReader->str[jsonReader->ptr++];

	if (jsonReader->str[jsonReader->ptr - 1] == '{'){
		numCurlyOpBrckt = 1;
		numSqOpBrckt = 0;
	}
	else{
		numCurlyOpBrckt = 0;
		numSqOpBrckt = 1;
	}

	while(numCurlyOpBrckt != numCurlyClBrckt || numSqOpBrckt != numSqClBrckt ){

		switch ( (ch = jsonReader->str[jsonReader->ptr++]) ){
		case '{':
			numCurlyOpBrckt++;
			break;

		case '}':
			numCurlyClBrckt++;
			break;

		case '[':
			numSqOpBrckt++;
			break;

		case ']':
			numSqClBrckt++;
			break;

		default:
			break;
		}
	}
	return;
}

void JsonReader_skipValue(tJsonReader* jsonReader){
	int lookAhead;
	char ch;
	int isSkipped=0;
	lookAhead = jsonReader->ptr;

	while( (ch = jsonReader->str[lookAhead++]) != '\0'){

		switch(ch){

		case '"':			//value is a string
			skipString(jsonReader);
			isSkipped=1;
			break;

		case 'n':			//value is null
			JsonReader_nextNull(jsonReader);
			isSkipped=1;
			break;

		case 't': case 'f':		//value is Boolean
			JsonReader_nextBoolean(jsonReader);
			isSkipped=1;
			break;

		case '{': case '[':		//value is object or array
			skipObjectOrArray(jsonReader);
			isSkipped = 1;
			break;

		case '+': case '-':
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
		case '.':			//value is a integer or a float
			JsonReader_nextFloat(jsonReader);
			isSkipped = 1;
			break;

		default:
			break;
		}

		if (isSkipped){
			return;
		}

	}
	return;
}
