/*
 * JsonReader_test.c
 *
 *  Created on: 25-Apr-2014
 *      Author: Nehchal J. (nehchalj@gmail.com)
 */


#include "JsonReader_test.h"

#include <string.h>

#include "ArTalker_test.h"

#include <string.h>

#include <inc/FlashAPI/Types.h>

void JsonReader_initSuite(){


    return;
}

void JsonReader_testRunner(){

    char str[500];

    tJsonReader jsonReader;
    char temp[20];

    /* Reading of following string (ignore spaces, tab and new lines)
        {
        "company"   : "Systemantics",
        "employees" : [
                        { "firstName":"John" , "lastName":"Doe" },
                        { "firstName":"Anna" , "lastName":"Smith" }
                    ]
        }
    */
    strcpy(str, "{\"company\"   : \"Systemantics\",\"employees\": [{ \"firstName\":\"John\" , \"lastName\":\"Doe\" },{ \"firstName\":\"Anna\" , \"lastName\":\"Smith\" }]}");

    JsonReader_init(&jsonReader, str);
    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("company", temp));

    JsonReader_skipValue(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("employees", temp));

    JsonReader_beginArray(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("firstName", temp));

    JsonReader_skipValue(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("lastName", temp));

    JsonReader_nextString(&jsonReader, temp);
    UT_ASSERT0(!strcmp("Doe", temp));

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);

    JsonReader_endObject(&jsonReader);

    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("firstName", temp));

    JsonReader_nextString(&jsonReader, temp);
    UT_ASSERT0(!strcmp("Anna", temp));

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("lastName", temp));

    JsonReader_nextString(&jsonReader, temp);
    UT_ASSERT0(!strcmp("Smith", temp));

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);

    JsonReader_endObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);

    JsonReader_endArray(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);

    JsonReader_endObject(&jsonReader);

    /* Reading of folowing string (ignore spaces, tab and new lines)
        {
        "TPL"   : FALSE,
        "CNT"   : null    ,
        "AM"    : TRUE
        }
    */

    strcpy(str, "{\"TPL\":false ,\"CNT\":null,\"AM\":true}");


    JsonReader_init(&jsonReader, str);
    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("TPL", temp));

    UT_ASSERT0( JsonReader_nextBoolean(&jsonReader) == FALSE);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("CNT", temp));

    JsonReader_nextNull(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("AM", temp));

    UT_ASSERT0( JsonReader_nextBoolean(&jsonReader) == TRUE);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);

    JsonReader_endObject(&jsonReader);

    /* Reading of folowing string (ignore spaces, tab and new lines)
        { "{\"IntArray\":[11,22,33] ,
         \"LongArray\":[1111,2222,3333]}"
        }
    */
    strcpy(str, "{\"IntArray\":[11,22,33] ,\"LongArray\":[1111,2222,3333]}");

    JsonReader_init(&jsonReader, str);
    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("IntArray", temp));

    JsonReader_beginArray(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_skipValue(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    UT_ASSERT0( JsonReader_nextInt(&jsonReader) == 22);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    UT_ASSERT0( JsonReader_nextInt(&jsonReader) == 33);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);
    JsonReader_endArray(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("LongArray", temp));

    JsonReader_beginArray(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    UT_ASSERT0( JsonReader_nextLong(&jsonReader) == 1111);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_skipValue(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    UT_ASSERT0( JsonReader_nextLong(&jsonReader) == 3333);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);
    JsonReader_endArray(&jsonReader);

    JsonReader_endObject(&jsonReader);

    /* Reading of folowing string (ignore spaces, tab and new lines)
        { "{\"AM\":{\"ab\":\"cd\"} ,
            \"FloatArray\":[11.11,22.22,33.33}"
        }
    */
    strcpy(str, "{\"AM\":{\"ab\":\"cd\"} ,\"FloatArray\":[11.11,22.22,33.33]}");

    JsonReader_init(&jsonReader, str);
    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("AM", temp));

    JsonReader_beginObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("ab", temp));
    JsonReader_nextString(&jsonReader, temp);
    UT_ASSERT0(!strcmp("cd", temp));

    JsonReader_endObject(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("FloatArray", temp));

    JsonReader_beginArray(&jsonReader);

    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);

    UT_ASSERT0( (JsonReader_nextFloat(&jsonReader) - 11.11) <= 0.1 || (JsonReader_nextFloat(&jsonReader) - 11.11) >= 0.1);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    UT_ASSERT0( (JsonReader_nextFloat(&jsonReader) - 22.22) <= 0.1 || (JsonReader_nextFloat(&jsonReader) - 22.22) >= 0.1);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_skipValue(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == FALSE);
    JsonReader_endArray(&jsonReader);
    JsonReader_endObject(&jsonReader);

    strcpy(str, "{\"AM\":{\"ab\":\"cd\"},\"ram\":\"das\"}");

    JsonReader_init(&jsonReader, str);
    JsonReader_beginObject(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("AM", temp));
    JsonReader_skipValue(&jsonReader);
    UT_ASSERT0( JsonReader_hasNext(&jsonReader) == TRUE);
    JsonReader_nextName(&jsonReader, temp);
    UT_ASSERT0(!strcmp("ram", temp));
    JsonReader_nextString(&jsonReader, temp);
    UT_ASSERT0(!strcmp("das", temp));

    JsonReader_endObject(&jsonReader);

    return;
}

void JsonReader_cleanUp(){
    return;
}




