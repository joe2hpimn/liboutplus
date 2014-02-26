liboutplus
==========

C library for structured output in many formats as text, csv, json, xml, html etc 

[![Build Status](https://travis-ci.org/jseidl/liboutplus.png)](https://travis-ci.org/jseidl/liboutplus)


Compinling
-------------

Building the lib

```
gcc -c outplus.c -o outplus.o
```

Compiling your code with outplus

```
 gcc -Wall -o your_program outplus.o your_program.c -I<path to lib outplus>
```


How to use
-------------

Simple example:

```c
#include <stdio.h>
#include "outplus.h"

int main(int argc, char *argv[])
{

    if (argc != 2) {
        printf("Usage %s <output type>", argv[0]);
        return 1;
    }//end :: if


    int rv = OUTPLUS_E_OK; // our return values
    OUTPLUS_SECTOR *output = NULL; // Declare your global output sector

    // Create a output sector and append to global output. Declare and initialize the sector
    OUTPLUS_SECTOR *output1 = NULL;
    rv = outplus_add_sector("Sector One", &output1, &output);
    if (rv != OUTPLUS_E_OK) return 1; // outplus functions must return OUTPLUS_E_OK or they failed

    // Add text to it!
    outplus_add_line("Key One Sector One", "Value One Sector One", output1);
    if (rv != OUTPLUS_E_OK) return 1;

    // Add a second sector
    OUTPLUS_SECTOR *output2 = NULL;
    rv = outplus_add_sector("Sector Two", &output2, &output);
    if (rv != OUTPLUS_E_OK) return 1;  

    // Add text to the second sector
    outplus_add_line("Key One Sector Two", "Value One Sector Two", output2);
    if (rv != OUTPLUS_E_OK) return 1;


    // You can also add child sector to sector two
    OUTPLUS_SECTOR *output2c = NULL;
    rv = outplus_add_child_sector("Sector Two One", &output2c, &output2);
    if (rv != OUTPLUS_E_OK) return 1;

    // Add lines to child sector
    rv = outplus_add_line("Key One Sector Two Sub-Sector One", "Value One Sector Two Sub-Sector One", output2c);
    if (rv != OUTPLUS_E_OK) return 1;

    // Finally use the appropriate functions to dump your output into the desired format

    /* Directly calling a format dump

        void outplus_dump_xml(output);
        void outplus_dump_text(output);
        void outplus_dump_csv(output);
        void outplus_dump_html(output);
        void outplus_dump_json(output);

    */

    // if using above, remember to call outplus_free(output);

    outplus_parse_format(argv[1]);
    outplus_dump(output); // this will call outplus_free(output) for you

    return 0;

}//end :: main
```

Output Examples
----------

**TEXT (default)**
```
Sector One
    Key One Sector One: Value One Sector One

Sector Two
    Key One Sector Two: Value One Sector Two

    Sector Two One
        Key One Sector Two Sub-Sector One: Value One Sector Two Sub-Sector One

```

**XML**
```xml
<?xml version="1.0" encoding="ISO-8859-1"?>
<output>
    <sector_one title="Sector One">
        <key_one_sector_one>Value One Sector One</key_one_sector_one>
    </sector_one>
    <sector_two title="Sector Two">
        <key_one_sector_two>Value One Sector Two</key_one_sector_two>
        <sector_two_one title="Sector Two One">
            <key_one_sector_two_sub_sector_one>Value One Sector Two Sub-Sector One</key_one_sector_two_sub_sector_one>
        </sector_two_one>
    </sector_two>
</output>
```

**JSON**
```json
{
    "sector_one":
    {
        "key_one_sector_one": "Value One Sector One"
    },
    "sector_two":
    {
        "key_one_sector_two": "Value One Sector Two"
        "sector_two_one":
        {
            "key_one_sector_two_sub_sector_one": "Value One Sector Two Sub-Sector One"
        }
    }
}
```

**CSV**
```csv
"Sector One","Key One Sector One","Value One Sector One"
"Sector Two","Key One Sector Two","Value One Sector Two"
"Sector Two One","Key One Sector Two Sub-Sector One","Value One Sector Two Sub-Sector One"
```

**HTML**
```html
<!DOCTYPE HTML>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
        <title>Outplus Output Output</title>
        <style type="text/css">
            body { font-family: Sans, Arial; }
            h1 { padding-top: 11px; padding-bottom: 11px; padding-left: 70px; }
            h2,h3,h4,h5 { clear: both; float: none; margin-bottom: 0px; }
            dl { margin-bottom: 20px; float: left; }
            .even { background-color: #EEE; }
            dt { padding: 2px 5px; float: left; margin-right: 0px; clear: left; width: 240px; font-weight: bold; margin-bottom: 5px; font-weight: bold; }
            dd { width: 360px; margin-left: 0px; padding: 2px 5px; float: left; }
        </style>
    </head>
    <body>
    <h1>Outplus Output</h1>
    <h2>Sector One</h2>
    <dl>
        <dt class="even">Key One Sector One</dt>
        <dd class="even">Value One Sector One</dd>
    </dl>
    <h2>Sector Two</h2>
    <dl>
        <dt class="even">Key One Sector Two</dt>
        <dd class="even">Value One Sector Two</dd>
    </dl>
    <h3>Sector Two One</h3>
    <dl>
        <dt class="even">Key One Sector Two Sub-Sector One</dt>
        <dd class="even">Value One Sector Two Sub-Sector One</dd>
    </dl>
    </body>
</html>
```

### TODO ###
* Add file output (printf->outplus_output)
* Add some more examples here
