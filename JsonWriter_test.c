/*
 * JsonWriter_test.c
 *
 *  Created on: 25-Apr-2014
 *      Author: Nehchal J. (nehchalj@gmail.com)
 */


#include "JsonWriter_test.h"

#include <string.h>

#include "ArTalker_test.h"

#include <string.h>

#include <inc/FlashAPI/Types.h>

#include <xdc/runtime/System.h>

void JsonWriter_initSuite(){
    return;
}

void JsonWriter_testRunner(){
    char str[500];
    tJsonWriter jsonWriter;

    System_printf("Note: No assert statments used for this test. Verify the output manually.\n");
    System_flush();

    /*
     *  ======== test1 ========
     *  Building of the string
     *  {"sushma":"pawar","age":23}
     */
      JsonWriter_init(&jsonWriter, str);

      JsonWriter_beginObject(&jsonWriter);
      JsonWriter_name(&jsonWriter, "sushma");
      JsonWriter_stringValue(&jsonWriter, "pawar");
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "age");
      JsonWriter_integerValue(&jsonWriter, 23);
      JsonWriter_endObject(&jsonWriter);

      System_printf("JSON string-1: %s\n", str);
      System_flush();
     /*
   *  ======== test2 ========
   *  Building of the string
   * {"SM":"DB","ROLL":45,"YAW":45.12,"PITCH":null,"ST":false,
   * "PNTS":{"TAG":"AT","FR":"TL"},"CRDS":[101,201,301,401]}
   */
      JsonWriter_init(&jsonWriter, str);

      JsonWriter_beginObject(&jsonWriter);
      JsonWriter_name(&jsonWriter, "SM");
      JsonWriter_stringValue(&jsonWriter, "DB");
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "ROLL");
      JsonWriter_integerValue(&jsonWriter, 45);
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "YAW");
      JsonWriter_floatValue(&jsonWriter, 45.1234,2);
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "PITCH");
      JsonWriter_nullValue(&jsonWriter);
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "ST");
      JsonWriter_boolValue(&jsonWriter, FALSE);
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "PNTS");
      JsonWriter_beginObject(&jsonWriter);
      JsonWriter_name(&jsonWriter, "TAG");
      JsonWriter_stringValue(&jsonWriter, "AT");
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "FR");
      JsonWriter_stringValue(&jsonWriter, "TL");
      JsonWriter_endObject(&jsonWriter);
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "CRDS");
      JsonWriter_beginArray(&jsonWriter);
      JsonWriter_integerValue(&jsonWriter, 101);
      JsonWriter_next(&jsonWriter);
      JsonWriter_integerValue(&jsonWriter, 201);
      JsonWriter_next(&jsonWriter);
      JsonWriter_integerValue(&jsonWriter, 301);
      JsonWriter_next(&jsonWriter);
      JsonWriter_integerValue(&jsonWriter, 401);
      JsonWriter_endArray(&jsonWriter);
      JsonWriter_endObject(&jsonWriter);

      System_printf("JSON string-2: %s\n", str);
      System_flush();
    /*
   *  ======== test3========
   *  Building of the string
   * {"TAG":"AB@_$","TEMP":"def!*^#"}
   */
      JsonWriter_init(&jsonWriter, str);

      JsonWriter_beginObject(&jsonWriter);
      JsonWriter_name(&jsonWriter, "TAG");
      JsonWriter_stringValue(&jsonWriter, "AB@_$");
      JsonWriter_next(&jsonWriter);
      JsonWriter_name(&jsonWriter, "TEMP");
      JsonWriter_stringValue(&jsonWriter, "def!*^#");
      JsonWriter_endObject(&jsonWriter);

      System_printf("JSON string-3: %s\n", str);
      System_flush();

   /*
   *  ======== test4========
   *  Building of the string
   * {"CRDS":0.950,"TMP":8.007,"INT":45.00}
   */
    JsonWriter_init(&jsonWriter, str);

    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "CRDS");
    JsonWriter_floatValue(&jsonWriter,0.95,3);
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "TMP");
    JsonWriter_floatValue(&jsonWriter,8.007007,3);
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "INT");
    JsonWriter_floatValue(&jsonWriter,45.00,2);
    JsonWriter_endObject(&jsonWriter);

    System_printf("JSON string-4: %s\n", str);
    System_flush();

     /*
   *  ======== test5========
   *  Building of the string
   * {"CNT":10,"CYC":{"TAG":"Cycle_Tag",
         "LPNT":"Last_Point_Tag","OPTH":"On_Path_Tag","CNT":"10"}}
   */
    JsonWriter_init(&jsonWriter, str);

    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "CNT");
    JsonWriter_integerValue(&jsonWriter, 10);
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "CYC");
    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "TAG");
    JsonWriter_stringValue(&jsonWriter, "Cycle_Tag");
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "LPNT");
    JsonWriter_stringValue(&jsonWriter, "Last_Point_Tag");
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "OPTH");
    JsonWriter_stringValue(&jsonWriter, "On_Path_Tag");
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "CNT");
    JsonWriter_stringValue(&jsonWriter, "10");
    JsonWriter_endObject(&jsonWriter);
    JsonWriter_endObject(&jsonWriter);

    System_printf("JSON string-5: %s\n", str);
    System_flush();

  /*
   *  ======== test6========
   *  Building of the string
   *  [{"Ramesh":[1,2]},{"Suresh":{"Ganesh":"Ram","AB":"Sham"}}]
   */

    JsonWriter_init(&jsonWriter, str);

    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "Ramesh");
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter, 1);
    JsonWriter_next(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter, 2);
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_endObject(&jsonWriter);
    JsonWriter_next(&jsonWriter);
    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "Suresh");
    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "Ganesh");
    JsonWriter_stringValue(&jsonWriter, "Ram");
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "AB");
    JsonWriter_stringValue(&jsonWriter, "Sham");
    JsonWriter_endObject(&jsonWriter);
    JsonWriter_endObject(&jsonWriter);
    JsonWriter_endArray(&jsonWriter);

    System_printf("JSON string-6: %s\n", str);
    System_flush();

    /*
   *  ======== test7========
   *  Building of the string
   *{"CRDS":[100.22,"267.83",30.4],
   *        "STR":["TAG:Cycle_Tag","LPNT:Last_Point_Tag","OPTH:On_Path_Tag"]}
   */
    JsonWriter_init(&jsonWriter, str);

    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "CRDS");
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_floatValue(&jsonWriter, 100.22,2);
    JsonWriter_next(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "267.83");
    JsonWriter_next(&jsonWriter);
    JsonWriter_floatValue(&jsonWriter, 30.48,1);
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_next(&jsonWriter);
    JsonWriter_name(&jsonWriter, "STR");
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "TAG:Cycle_Tag");
    JsonWriter_next(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "LPNT:Last_Point_Tag");
    JsonWriter_next(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "OPTH:On_Path_Tag");
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_endObject(&jsonWriter);

    System_printf("JSON string-7: %s\n", str);
    System_flush();


      /*
   *  ======== test8========
   *  Building of the string
   *  {"ARRAY":[[1,2,3,5],[11.0,12.11],["AB","CD"]]}
   */
    JsonWriter_init(&jsonWriter, str);

    JsonWriter_beginObject(&jsonWriter);
    JsonWriter_name(&jsonWriter, "ARRAY");
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter,1);
    JsonWriter_next(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter,2);
    JsonWriter_next(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter,3);
    JsonWriter_next(&jsonWriter);
    JsonWriter_integerValue(&jsonWriter,5);
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_next(&jsonWriter);
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_floatValue(&jsonWriter, 11.0,1);
    JsonWriter_next(&jsonWriter);
    JsonWriter_floatValue(&jsonWriter, 12.12,2);
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_next(&jsonWriter);
    JsonWriter_beginArray(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "AB");
    JsonWriter_next(&jsonWriter);
    JsonWriter_stringValue(&jsonWriter, "CD");
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_endArray(&jsonWriter);
    JsonWriter_endObject(&jsonWriter);

    System_printf("JSON string-8: %s\n", str);
    System_flush();

    return;
}

void JsonWriter_cleanUp(){
    return;
}




